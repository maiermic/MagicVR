#include "magicvr/MagicTricks.hpp"

#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>

#include <range/v3/utility/functional.hpp>

#include <magicvr/animation/BezierCurve.hpp>
#include <magicvr/Spiral.hpp>
#include <magicvr/ranges/view/rotate.hpp>
#include <magicvr/DrawingDirection.hpp>
#include <magicvr/ranges/view/Circle.hpp>

//#include "trajecmp/functional/functional.hpp"
#include "trajecmp/distance/modified_hausdorff.hpp"
#include "trajecmp/geometry/min_bounding_sphere.hpp"
#include "trajecmp/geometry/vector.hpp"
#include "trajecmp/transform/translate.hpp"
#include "trajecmp/transform/scale.hpp"
#include "trajecmp/predicate/has_min_num_points.hpp"
#include "trajecmp/compare/less_than.hpp"
#include "trajecmp/compare/match_by.hpp"
#include "trajecmp/util/subscribe_with_latest_from.hpp"
#include "trajecmp/util/boost_geometry_to_string.hpp"

namespace magicvr {

    MagicTricks::MagicTricks() {
        using trajecmp::predicate::has_min_num_points;
        using trajecmp::compare::less_than;
        using trajecmp::compare::match_by;
        using trajecmp::util::subscribe_with_latest_from;
        using trajecmp::geometry::min_bounding_sphere;

        const auto input_trajectory_stream =
                input_trajectory_subject.get_observable();
        const BezierCurve<> waterBezier{
                {0,    0,  0},
                {1.5f, 3,  0},
                {1.5f, -2, 0},
                {3,    1,  0},
        };
        auto pattern_water_trajectory_stream =
                rxcpp::observable<>::just(waterBezier.sample(10));
        auto pattern_wind_trajectory_stream =
                rxcpp::observable<>::just(Spiral().sample());
        auto pattern_lightning_trajectory_stream =
                rxcpp::observable<>::just(
                        Trajectory{
                                {1, 2, 0},
                                {0, 1, 0},
                                {1, 1, 0},
                                {0, 0, 0},
                        }
                );
        auto pattern_fire_trajectory_stream =
                rxcpp::observable<>::just(
                        Trajectory{
                                {0,  0, 0},
                                {-1, 3, 0},
                                {1,  2, 0},
                                {2,  5, 0},
                                {2,  5, 0},
                                {3,  2, 0},
                                {5,  3, 0},
                                {4,  0, 0},
                        }
                );

        const BezierCurve<> quaterCircleFromAbove{
                {0, 1, 0},
                {1, 1, 0},
                {1, 0, 0},
                {1, 0, 0},
        };
        auto pattern_quaterCircleFromAbove_trajectory_stream =
                rxcpp::observable<>::just(quaterCircleFromAbove.sample(10));

        auto pattern_circle_trajectory_stream =
                rxcpp::observable<>::just(
                        magicvr::ranges::view::Circle(1).sample(0, 360, 10) |
                                ::ranges::view::transform([](OSG::Vec2f v) {
                                    return OSG::Vec3f(v.x(), v.y(), 0);
                                }) |
                                ::ranges::to_vector
                );
        static const auto normalized_size = 100;
        const auto scale_mbs = [=](auto &mbs) {
            return trajecmp::transform::scale_to_const<normalized_size>(
                    mbs.radius * 2
            );
        };
        const auto translate_mbs = [=](auto &mbs) {
            return trajecmp::transform::translate_by(
                    trajecmp::geometry::negative_vector_of(mbs.center));
        };
        const auto rotate_y_with_direction =
                [=](DrawingDirection drawingDirection) {
                    return [=](Trajectory &&trajectory) {
                        const auto first = trajectory.front();
                        const OSG::Vec3f xzVec(first.x(), 0, first.z());
                        if (drawingDirection != LEFT && drawingDirection != RIGHT) {
                                std::cout << "WARNING: invalid drawing direction: "
                                          << drawingDirection << '\n';
                        }
                        return trajectory |
                               magicvr::ranges::view::rotate(
                                       OSG::Quaternion(
                                               xzVec,
                                               OSG::Vec3f(drawingDirection, 0, 0)
                                       )
                               ) |
                               ::ranges::to_vector;
                    };
                };
        const auto transform_with_direction = [&](DrawingDirection drawingDirection) {
                return [=](Trajectory &trajectory) {
                    const auto mbs = min_bounding_sphere(trajectory);
                    return trajectory |
                           ::ranges::make_pipeable(translate_mbs(mbs)) |
                           ::ranges::make_pipeable(scale_mbs(mbs)) |
                           ::ranges::make_pipeable(rotate_y_with_direction(drawingDirection));
                };
        };
        const auto transformWithoutRotation = [&](Trajectory &trajectory) {
            const auto mbs = min_bounding_sphere(trajectory);
            return trajectory |
                   ::ranges::make_pipeable(translate_mbs(mbs)) |
                   ::ranges::make_pipeable(scale_mbs(mbs));
        };

        const auto make_preprocess = [](auto transform) {
                return [=](auto &&trajectory_stream) {
                    return trajectory_stream
                            .filter(has_min_num_points(2))
                            .map(transform);
                };
        };
        const auto preprocess_left =
                make_preprocess(transform_with_direction(LEFT));
        const auto preprocess_right =
                make_preprocess(transform_with_direction(RIGHT));
        const auto preprocessWithoutRotation = [&transformWithoutRotation](auto &&trajectory_stream) {
            return trajectory_stream
                    .filter(has_min_num_points(2))
                    .map(transformWithoutRotation);
        };
        left_preprocessed_input_trajectory_stream =
                preprocess_left(input_trajectory_stream);
        right_preprocessed_input_trajectory_stream =
                preprocess_right(input_trajectory_stream);

        const trajecmp::distance::neighbours_percentage_range neighbours(0.1);
        const auto modified_hausdorff =
                trajecmp::distance::modified_hausdorff(neighbours);
        const auto compare = match_by(modified_hausdorff,
                                      less_than(normalized_size * 0.3));

        input_matches_pattern_water_stream =
                compare(right_preprocessed_input_trajectory_stream,
                        preprocess_right(pattern_water_trajectory_stream));
        input_matches_pattern_wind_stream =
                compare(left_preprocessed_input_trajectory_stream,
                        preprocess_left(pattern_wind_trajectory_stream));
        input_matches_pattern_lightning_stream =
                compare(left_preprocessed_input_trajectory_stream,
                        preprocess_left(pattern_lightning_trajectory_stream));
        input_matches_pattern_fire_stream =
                compare(right_preprocessed_input_trajectory_stream,
                        preprocess_right(pattern_fire_trajectory_stream));
        input_matches_pattern_quaterCircleFromAbove_stream =
                compare(right_preprocessed_input_trajectory_stream,
                        preprocess_right(
                                pattern_quaterCircleFromAbove_trajectory_stream));
        preprocessed_pattern_circle_trajectory_stream =
                preprocess_right(pattern_circle_trajectory_stream);
        input_matches_pattern_circle_stream =
                compare(right_preprocessed_input_trajectory_stream,
                        preprocessed_pattern_circle_trajectory_stream);
        preprocessed_pattern_lightning_trajectory_stream =
                preprocess_left(pattern_lightning_trajectory_stream);
        preprocessedWithoutRotation_input_trajectory_stream =
                preprocessWithoutRotation(input_trajectory_stream);
    }

    void MagicTricks::emit(MagicTricks::Trajectory &&trajectory) const {
        input_trajectory_subject.get_subscriber().on_next(trajectory);
    }
}