#ifndef SM_HP_PACKED_V0S_HXX
#define SM_HP_PACKED_V0S_HXX

#include <string>
#include <vector>

#include <TColor.h>

#include "Style.hpp"

namespace SexaquarkMacros::PackedV0s {

// Settings //

enum EProperties : size_t {
    Mass,
    Pt,
    Eta,
    Radius2D,
    CPAwrtPV,
    DCAwrtPV,
    ArmQtOverAlpha,
    DCAnegV0,
    DCAposV0,
    DCAbtwDau,
    DecayX,
    DecayY,
    DecayZ,
    Px,
    Py,
    Pz,
    P,
    NProperties
};
const std::vector<std::string_view> Properties_names{"Mass",      "Pt",       "Eta",
                                                     "Radius2D",  //
                                                     "CPAwrtPV",  "DCAwrtPV", "ArmQtOverAlpha",
                                                     "DCAnegV0",  "DCAposV0",
                                                     "DCAbtwDau",  //
                                                     "DecayX",    "DecayY",   "DecayZ",
                                                     "Px",        "Py",       "Pz",
                                                     "P"};
std::vector<std::string_view> Properties_latex{"",
                                               "p_{T} [GeV/c]",
                                               "#eta",
                                               "Radius2D [cm]",
                                               "CPAwrtPV",
                                               "DCAwrtPV [cm]",
                                               "ArmQtOverAlpha",
                                               "DCAnegV0 [cm]",
                                               "DCAposV0 [cm]",
                                               "DCAbtwDau [cm]",
                                               "v_{x} [cm]",
                                               "v_{y} [cm]",
                                               "v_{z} [cm]",
                                               "p_{x} [GeV/c]",
                                               "p_{y} [GeV/c]",
                                               "p_{z} [GeV/c]",
                                               "P [GeV/c]"};
std::vector<float> Properties_min{-1.,   0.,    -2.,  0.,          //
                                  -1.,   -50.,  -1.,  0., 0., 0.,  //
                                  -200., -200., -60., 0., 0., 0., 0.};
std::vector<float> Properties_max{+1.,  5.,   2.,  200.,            //
                                  1.,   50.,  1.,  50.,  50., 50.,  //
                                  200., 200., 60., 5.,   5.,  5.,  25.};

enum ESubsets : size_t { All, True, Secondary, Signal, Hybrid, RealBkg, NSubsets };
const std::vector<std::string_view> Subsets_names{"", "_True", "_Secondary", "_Signal", "_Hybrid", "_RealBkg"};
const std::vector<Color_t> Subsets_colors{static_cast<Color_t>(SexaquarkMacros::Style::Gray.GetNumber()),    //
                                          static_cast<Color_t>(SexaquarkMacros::Style::Orange.GetNumber()),  //
                                          static_cast<Color_t>(SexaquarkMacros::Style::Brown.GetNumber()),   //
                                          static_cast<Color_t>(SexaquarkMacros::Style::Red.GetNumber()),     //
                                          static_cast<Color_t>(SexaquarkMacros::Style::Green.GetNumber()),   //
                                          static_cast<Color_t>(SexaquarkMacros::Style::Purple.GetNumber())};

}  // namespace SexaquarkMacros::PackedV0s

#endif  //  SM_HP_PACKED_V0S_HXX
