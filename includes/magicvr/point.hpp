#ifndef BOOST_GEOMETRY_TRAITS_POINT_HPP
#define BOOST_GEOMETRY_TRAITS_POINT_HPP

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/cs.hpp>
#include <OSGVector.h>

namespace boost { namespace geometry {

// Adapt the point to the concept
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
    namespace traits {

        template<class ValueTypeT, OSG::UInt32 SizeI>
        struct tag<OSG::Vector<ValueTypeT, SizeI>> {
            typedef point_tag type;
        };

        template<class ValueTypeT, OSG::UInt32 SizeI>
        struct coordinate_type<OSG::Vector<ValueTypeT, SizeI>> {
            typedef ValueTypeT type;
        };

        template<class ValueTypeT, OSG::UInt32 SizeI>
        struct coordinate_system<OSG::Vector<ValueTypeT, SizeI>> {
            typedef boost::geometry::cs::cartesian type;
        };

        template<class ValueTypeT, OSG::UInt32 SizeI>
        struct dimension<OSG::Vector<ValueTypeT, SizeI>>
                : boost::mpl::int_<3> {
        };

        template<class ValueTypeT, OSG::UInt32 SizeI, std::size_t Dimension>
        struct access<OSG::Vector<ValueTypeT, SizeI>, Dimension> {
            static inline ValueTypeT
            get(const OSG::Vector<ValueTypeT, SizeI> &v) {
                return v[Dimension];
            }

            static inline void
            set(OSG::Vector<ValueTypeT, SizeI> &v, const ValueTypeT &value) {
                v[Dimension] = value;
            }
        };

    } // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // boost::geometry

#endif //BOOST_GEOMETRY_TRAITS_POINT_HPP
