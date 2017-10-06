#ifndef MAGICVR_MAGICTRICKS_HPP
#define MAGICVR_MAGICTRICKS_HPP

#include <vector>
#include <iostream>

#include <OpenSG/OSGVector.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <rxcpp/rx.hpp>

#include <boost/geometry/geometries/register/linestring.hpp>
BOOST_GEOMETRY_REGISTER_LINESTRING(std::vector<OSG::Vec3f>);

#include "boost/geometry/traits/point.hpp"


namespace magicvr {
    class MagicTricks {
    public:
        using Trajectory = std::vector<OSG::Vec3f>;
        rxcpp::observable<double> input_matches_pattern_water_stream;
        rxcpp::observable<double> input_matches_pattern_wind_stream;
        rxcpp::observable<double> input_matches_pattern_lightning_stream;
        rxcpp::observable<double> input_matches_pattern_fire_stream;
        rxcpp::observable<double> input_matches_pattern_quaterCircleFromAbove_stream;
        rxcpp::observable<double> input_matches_pattern_circle_stream;

        rxcpp::observable<Trajectory> preprocessed_pattern_circle_trajectory_stream;
        rxcpp::observable<Trajectory> preprocessed_pattern_lightning_trajectory_stream;
        rxcpp::observable<Trajectory> preprocessedWithoutRotation_input_trajectory_stream;
        rxcpp::observable<Trajectory> left_preprocessed_input_trajectory_stream;
        rxcpp::observable<Trajectory> right_preprocessed_input_trajectory_stream;

        MagicTricks();

        void emit(Trajectory &&trajectory) const;

    private:
        rxcpp::rxsub::subject<Trajectory> input_trajectory_subject;
    };
}

#endif //MAGICVR_MAGICTRICKS_HPP
