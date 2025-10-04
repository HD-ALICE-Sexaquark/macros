#ifndef SM_CONSTANTS_HXX
#define SM_CONSTANTS_HXX

#include <numbers>
#include <string>
#include <string_view>
#include <vector>

namespace SexaquarkMacros::Const {
static constexpr double Kappa{0.000299792458};  // (GeV/c) / (kG/cm)
static constexpr double AbsAlmostZero{1.E-8};
static constexpr double BigNumber{1.E8};
static constexpr int DummyInt{-1};
static constexpr float DummyFloat{-999.};
static constexpr double DummyDouble{-999.};
static constexpr double Pi{std::numbers::pi};
static constexpr int NReactionsPerEvent{20};
static constexpr std::string OutputDir{"output"};
static constexpr std::string PlotsDir{"gfx"};

enum EStages { kDeepESD, kConverted, kPackedEvents, kFound, kPackedV0s };
const std::vector<std::string_view> StagesNames{"DeepESD", "Converted", "PackedEvents", "Found", "PackedV0s"};
const std::vector<std::string_view> StagesDirNames{"deep_esd", "esd2vector", "t2s_packed", "t2s_found"};

static constexpr float MinMass_Lambda{1.08};
static constexpr float MaxMass_Lambda{1.14};
static constexpr float MinMass_K0S{0.49};
static constexpr float MaxMass_K0S{0.51};
const std::string Latex_AntiLambda{"m(#bar{p} #pi^{+}) [GeV/c^{2}]"};
const std::string Latex_Lambda{"m(p #pi^{-}) [GeV/c^{2}]"};
const std::string Latex_K0S{"m(#pi^{+} #pi^{-}) [GeV/c^{2}]"};

}  // namespace SexaquarkMacros::Const

#endif  // SM_CONSTANTS_HXX
