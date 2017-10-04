#include <magicvr/animation/BezierCurve.hpp>
#include <magicvr/Spiral.hpp>
#include "magicvr/MagicTricks.hpp"

#include "trajecmp/functional/functional.hpp"
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

        static const auto normalized_size = 100;
        const auto transform = [=](Trajectory &trajectory) {
            const auto mbs =
                    trajecmp::geometry::min_bounding_sphere(trajectory);
            return trajecmp::transform::scale_to_const<normalized_size>(
                    mbs.radius * 2)(
                    trajecmp::transform::translate_by(
                            trajecmp::geometry::negative_vector_of(mbs.center))(
                            trajectory)
            );
        };

        const auto preprocess = [&transform](auto &&trajectory_stream) {
            return trajectory_stream
                    .filter(has_min_num_points(2))
                    .map(transform);
        };
        auto preprocessed_input_trajectory_stream =
                preprocess(input_trajectory_stream);

        const trajecmp::distance::neighbours_percentage_range neighbours(0.1);
        const auto modified_hausdorff =
                trajecmp::distance::modified_hausdorff(neighbours);
        const auto compare = match_by(modified_hausdorff,
                                      less_than(normalized_size * 0.3));

        input_matches_pattern_water_stream =
                compare(preprocessed_input_trajectory_stream,
                        preprocess(pattern_water_trajectory_stream));
        input_matches_pattern_wind_stream =
                compare(preprocessed_input_trajectory_stream,
                        preprocess(pattern_wind_trajectory_stream));
        input_matches_pattern_lightning_stream =
                compare(preprocessed_input_trajectory_stream,
                        preprocess(pattern_lightning_trajectory_stream));
        input_matches_pattern_fire_stream =
                compare(preprocessed_input_trajectory_stream,
                        preprocess(pattern_fire_trajectory_stream));
        input_matches_pattern_quaterCircleFromAbove_stream =
                compare(preprocessed_input_trajectory_stream,
                        preprocess(pattern_quaterCircleFromAbove_trajectory_stream));
    }

    void MagicTricks::emit(MagicTricks::Trajectory &&trajectory) const {
        input_trajectory_subject.get_subscriber().on_next(trajectory);
    }
}