#ifndef SM_DF_DEEP_ESD_HXX
#define SM_DF_DEEP_ESD_HXX

#include <string_view>
#include <vector>

namespace SexaquarkMacros::DeepESD {

enum EProp1D {
    Charge,  // charge
    //
    Inner_X,  // track parameters estimated at the inner wall of TPC at PropagateBack stage
    Inner_Y,
    Inner_Z,
    Inner_Radius,
    Inner_Px,
    Inner_Py,
    Inner_Pz,
    Inner_Eta,
    Inner_Pt,
    Inner_P,
    Inner_Snp,
    Inner_Tgl,
    Inner_Signed1Pt,
    Inner_Alpha,
    //
    DCAxy,
    DCAz,
    DCA_Chi2,  // [0.,0.,8] chi2 at the primary vertex
    NCrossedRows,
    Chi2TPCConstrainedVsGlobal,
    PID_NSigma_Muon,
    PID_NSigma_Electron,
    PID_NSigma_Pion,
    PID_NSigma_Kaon,
    PID_NSigma_Proton,
    //
    TPC_DCAxy,
    TPC_DCAz,
    TPC_DCA_Chi2,
    TPC_Chi2,
    TPC_NCls,
    TPC_Chi2OverNCls,
    TPC_NClsF,
    TPC_Signal,
    TPC_SignalTuned,
    TPC_SignalS,
    TPC_SignalN,
    TPC_PointsFirst,
    TPC_PointsIndexMax,
    TPC_PointsLast,
    TPC_PointsMaxDens,
    //
    ITS_Chi2_In,
    ITS_Chi2_Out,
    ITS_Chi2_Refit,
    ITS_Chi2,
    ITS_Signal,
    ITS_SignalTuned,
    ITS_NCls,
    //
    NProps1D
};

const std::vector<std::string_view> Prop1D_Name{
    "Charge",
    //
    "Inner_X", "Inner_Y", "Inner_Z", "Inner_Radius", "Inner_Px", "Inner_Py", "Inner_Pz", "Inner_Eta", "Inner_Pt", "Inner_P", "Inner_Snp", "Inner_Tgl",
    "Inner_Signed1Pt", "Inner_Alpha",
    //
    "DCAxy", "DCAz", "DCA_Chi2", "NCrossedRows", "Chi2TPCConstrainedVsGlobal", "PID_NSigma_Muon", "PID_NSigma_Electron", "PID_NSigma_Pion",
    "PID_NSigma_Kaon", "PID_NSigma_Proton",
    //
    "TPC_DCAxy", "TPC_DCAz", "TPC_DCA_Chi2", "TPC_Chi2", "TPC_NCls", "TPC_Chi2OverNCls", "TPC_NClsF", "TPC_Signal", "TPC_SignalTuned", "TPC_SignalS",
    "TPC_SignalN", "TPC_PointsFirst", "TPC_PointsIndexMax", "TPC_PointsLast", "TPC_PointsMaxDens",
    //
    "ITS_Chi2_In", "ITS_Chi2_Out", "ITS_Chi2_Refit", "ITS_Chi2", "ITS_Signal", "ITS_SignalTuned", "ITS_NCls"};

enum EProp2D {
    DCAz_vs_DCAxy,
    TPC_DCAz_vs_TPC_DCAxy,
    //
    TPC_Signal_vs_Inner_P,
    TPC_Signal_vs_Inner_Eta,
    //
    TPC_SignalTuned_vs_Inner_P,
    TPC_SignalTuned_vs_Inner_Eta,
    //
    PID_NSigma_Muon_vs_Inner_P,
    PID_NSigma_Muon_vs_Inner_Eta,
    //
    PID_NSigma_Electron_vs_Inner_P,
    PID_NSigma_Electron_vs_Inner_Eta,
    //
    PID_NSigma_Pion_vs_Inner_P,
    PID_NSigma_Pion_vs_Inner_Eta,
    //
    PID_NSigma_Kaon_vs_Inner_P,
    PID_NSigma_Kaon_vs_Inner_Eta,
    //
    PID_NSigma_Proton_vs_Inner_P,
    PID_NSigma_Proton_vs_Inner_Eta,
    //
    NProps2D
};

std::vector<int> Prop2D_XProp{
    EProp1D::DCAxy,
    EProp1D::TPC_DCAxy,  //
    EProp1D::Inner_P,
    EProp1D::Inner_Eta,  //
    EProp1D::Inner_P,
    EProp1D::Inner_Eta,  //
    EProp1D::Inner_P,
    EProp1D::Inner_Eta,  //
    EProp1D::Inner_P,
    EProp1D::Inner_Eta,  //
    EProp1D::Inner_P,
    EProp1D::Inner_Eta,  //
    EProp1D::Inner_P,
    EProp1D::Inner_Eta,  //
    EProp1D::Inner_P,   EProp1D::Inner_Eta,
};

std::vector<int> Prop2D_YProp{
    EProp1D::DCAz,
    EProp1D::TPC_DCAz,  //
    EProp1D::TPC_Signal,
    EProp1D::TPC_Signal,  //
    EProp1D::TPC_SignalTuned,
    EProp1D::TPC_SignalTuned,  //
    EProp1D::PID_NSigma_Muon,
    EProp1D::PID_NSigma_Muon,  //
    EProp1D::PID_NSigma_Electron,
    EProp1D::PID_NSigma_Electron,  //
    EProp1D::PID_NSigma_Pion,
    EProp1D::PID_NSigma_Pion,  //
    EProp1D::PID_NSigma_Kaon,
    EProp1D::PID_NSigma_Kaon,  //
    EProp1D::PID_NSigma_Proton,
    EProp1D::PID_NSigma_Proton,
};

enum ESet {
    All,
    True_Electron,
    True_Muon,
    True_Pion,
    True_Kaon,
    True_Proton,
    Bkg,
    Signal,
    Signal_PiMinus_FromSV,
    Signal_PiMinus_FromK0S,
    Signal_PiPlus_FromSV,
    Signal_PiPlus_FromK0S,
    Signal_PiPlus_FromAL,
    Signal_PosKaon_FromSV,
    Signal_AntiProton_FromAL,
    NSets
};

const std::vector<std::string_view> Set_Suffix{"",
                                               "_True_Electron",
                                               "_True_Muon",
                                               "_True_Pion",
                                               "_True_Kaon",
                                               "_True_Proton",
                                               "_Bkg",
                                               "_Signal",
                                               "_Signal_PiMinus_FromSV",
                                               "_Signal_PiMinus_FromK0S",
                                               "_Signal_PiPlus_FromSV",
                                               "_Signal_PiPlus_FromK0S",
                                               "_Signal_PiPlus_FromAL",
                                               "_Signal_PosKaon_FromSV",
                                               "_Signal_AntiProton_FromAL"};
}  // namespace SexaquarkMacros::DeepESD

#endif  //  SM_DF_DEEP_ESD_HXX
