// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_MATERIALPROFILE_H
#define DAREFL_QUICKSIMEDITOR_MATERIALPROFILE_H

#include <darefl/quicksimeditor/slice.h>

//! Collection of methods borrowed from BornAgain for material profile calculations.

namespace MaterialProfile
{

//! Calculate average material profile for given multilayer
std::vector<complex_t> CalculateProfile(const multislice_t& multilayer, int n_points, double z_min,
                                        double z_max);

//! Get default z limits for generating a material profile
std::pair<double, double> DefaultMaterialProfileLimits(const multislice_t& multilayer);

//! Generate z values (equidistant) for use in MaterialProfile
std::vector<double> GenerateZValues(int n_points, double z_min, double z_max);

} // namespace MaterialProfile

#endif // DAREFL_QUICKSIMEDITOR_MATERIALPROFILE_H
