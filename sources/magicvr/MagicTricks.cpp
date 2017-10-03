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
        auto pattern_L_trajectory_stream =
                rxcpp::observable<>::just(
                        Trajectory{
                                {0, 2, 0},
                                {0, 0, 0},
                                {1, 0, 0},
                        }
                );
        auto pattern_M_trajectory_stream =
                rxcpp::observable<>::just(
                        Trajectory{
                                {0, 0, 0},
                                {1, 4, 0},
                                {2, 0, 0},
                                {3, 4, 0},
                                {4, 0, 0},
                        }
                );

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
        auto preprocessed_pattern_L_trajectory_stream =
                preprocess(pattern_L_trajectory_stream);
        auto preprocessed_pattern_M_trajectory_stream =
                preprocess(pattern_M_trajectory_stream);
        const trajecmp::distance::neighbours_percentage_range neighbours(0.1);
        const auto modified_hausdorff =
                trajecmp::distance::modified_hausdorff(neighbours);
        const auto compare = match_by(modified_hausdorff,
                                      less_than(normalized_size * 0.3));
        input_matches_pattern_L_stream =
                compare(preprocessed_input_trajectory_stream,
                        preprocessed_pattern_L_trajectory_stream);
        input_matches_pattern_M_stream =
                compare(preprocessed_input_trajectory_stream,
                        preprocessed_pattern_M_trajectory_stream);

        input_matches_pattern_L_stream | subscribe_with_latest_from(
                [&](auto distance, auto &&input_trajcetory,
                    auto &&pattern_trajcetory) {
                    std::cout << "L: " << distance << '\n';
                },
                preprocessed_input_trajectory_stream,
                preprocessed_pattern_L_trajectory_stream
        );
        input_matches_pattern_M_stream | subscribe_with_latest_from(
                [&](auto distance, auto &&input_trajcetory,
                    auto &&pattern_trajcetory) {
                    std::cout << "M: " << distance << '\n';
                },
                preprocessed_input_trajectory_stream,
                preprocessed_pattern_M_trajectory_stream
        );
    }

    void MagicTricks::emit(MagicTricks::Trajectory &&trajectory) const {
        input_trajectory_subject.get_subscriber().on_next(trajectory);
    }
}