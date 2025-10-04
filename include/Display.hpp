#ifndef SM_DISPLAY_HXX
#define SM_DISPLAY_HXX

#include <array>
#include <cmath>

#include <TEveLine.h>

#include "Math.hpp"

namespace SexaquarkMacros::Display {

static constexpr double absmax_z{300.};
static constexpr double max_radius{300.};
static constexpr double max_s{750.};
static constexpr double delta_s{1.};

static std::array<double, 3> EvaluateHelix(double ds, float x0, float y0, float z0, float px0, float py0, float pz0, float charge, float bz) {

    double bq{bz * charge * Const::Kappa};

    double theta{bq * ds};
    auto [sin, cos] = Math::sincos(theta);
    double sB{sin / bq};
    double cB{(1. - cos) / bq};

    return {x0 + sB * px0 + cB * py0, y0 - cB * px0 + sB * py0, z0 + ds * pz0};
}

static void SetPointsAsHelix(TEveLine* el, float x0, float y0, float z0, float px0, float py0, float pz0, float charge, float bz) {
    double s{0.};
    std::array<double, 3> xyz{};
    while (s < max_s && std::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]) < max_radius && std::abs(xyz[2]) < absmax_z) {
        xyz = EvaluateHelix(s, x0, y0, z0, px0, py0, pz0, charge, bz);
        el->SetNextPoint(xyz[0], xyz[1], xyz[2]);
        s += delta_s;
    }
}

}  // namespace SexaquarkMacros::Display

#endif  // SM_DISPLAY_HXX
