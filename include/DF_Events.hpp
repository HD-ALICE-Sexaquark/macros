#ifndef SM_DF_EVENTS_HXX
#define SM_DF_EVENTS_HXX

#include <cstddef>

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

// Most of this file has been generated with:
// `Events->MakeSelector()`
namespace SexaquarkMacros::Events {

struct Event {
    Event() = delete;
    explicit Event(TTreeReader& reader)
        : RunNumber{reader, "RunNumber"},
          DirNumber{reader, "DirNumber"},
          EventNumber{reader, "EventNumber"},
          Centrality{reader, "Centrality"},
          MagneticField{reader, "MagneticField"},
          PV_NContributors{reader, "PV_NContributors"},
          PV_Dispersion{reader, "PV_Dispersion"},
          PV_Xv{reader, "PV_Xv"},
          PV_Yv{reader, "PV_Yv"},
          PV_Zv{reader, "PV_Zv"},
          PV_CovMatrix{reader, "PV_CovMatrix"},
          SPD_PV_Zv{reader, "SPD_PV_Zv"},
          SPD_PV_ZvErr{reader, "SPD_PV_ZvErr"},
          NTracks{reader, "NTracks"},
          NTPCClusters{reader, "NTPCClusters"},
          IsMB{reader, "IsMB"},
          IsHighMultV0{reader, "IsHighMultV0"},
          IsHighMultSPD{reader, "IsHighMultSPD"},
          IsCentral{reader, "IsCentral"},
          IsSemiCentral{reader, "IsSemiCentral"} {};

    TTreeReaderValue<unsigned int> RunNumber;
    TTreeReaderValue<unsigned int> DirNumber;
    TTreeReaderValue<unsigned int> EventNumber;
    TTreeReaderValue<float> Centrality;
    TTreeReaderValue<float> MagneticField;
    TTreeReaderValue<int> PV_NContributors;
    TTreeReaderValue<float> PV_Dispersion;
    TTreeReaderValue<float> PV_Xv;
    TTreeReaderValue<float> PV_Yv;
    TTreeReaderValue<float> PV_Zv;
    TTreeReaderArray<float> PV_CovMatrix;
    TTreeReaderValue<float> SPD_PV_Zv;
    TTreeReaderValue<float> SPD_PV_ZvErr;
    TTreeReaderValue<int> NTracks;
    TTreeReaderValue<int> NTPCClusters;
    TTreeReaderValue<bool> IsMB;
    TTreeReaderValue<bool> IsHighMultV0;
    TTreeReaderValue<bool> IsHighMultSPD;
    TTreeReaderValue<bool> IsCentral;
    TTreeReaderValue<bool> IsSemiCentral;
};

struct MCEvent {
    MCEvent() = delete;
    explicit MCEvent(TTreeReader& reader)
        : PV_Xv{reader, "MC_PV_Xv"},
          PV_Yv{reader, "MC_PV_Yv"},
          PV_Zv{reader, "MC_PV_Zv"},
          IsGenPileup{reader, "MC_IsGenPileup"},
          IsSBCPileup{reader, "MC_IsSBCPileup"} {};

    TTreeReaderValue<float> PV_Xv;
    TTreeReaderValue<float> PV_Yv;
    TTreeReaderValue<float> PV_Zv;
    TTreeReaderValue<bool> IsGenPileup;
    TTreeReaderValue<bool> IsSBCPileup;
};

struct MCParticle {
    MCParticle() = delete;
    explicit MCParticle(TTreeReader& reader)
        : PdgCode{reader, "MC_PdgCode"},
          Mother_McEntry{reader, "MC_Mother_McEntry"},
          X{reader, "MC_X"},
          Y{reader, "MC_Y"},
          Z{reader, "MC_Z"},
          Px{reader, "MC_Px"},
          Py{reader, "MC_Py"},
          Pz{reader, "MC_Pz"},
          E{reader, "MC_E"},
          Status{reader, "MC_Status"},
          Generator{reader, "MC_Generator"},
          IsPrimary{reader, "MC_IsPrimary"},
          IsSecFromMat{reader, "MC_IsSecFromMat"},
          IsSecFromWeak{reader, "MC_IsSecFromWeak"},
          MC_IsOOBPileup{reader, "MC_IsOOBPileup"} {};
    [[nodiscard]] size_t GetSize() const { return X.GetSize(); };

    TTreeReaderArray<int> PdgCode;
    TTreeReaderArray<int> Mother_McEntry;
    TTreeReaderArray<float> X;
    TTreeReaderArray<float> Y;
    TTreeReaderArray<float> Z;
    TTreeReaderArray<float> Px;
    TTreeReaderArray<float> Py;
    TTreeReaderArray<float> Pz;
    TTreeReaderArray<float> E;
    TTreeReaderArray<int> Status;
    TTreeReaderArray<char> Generator;
    TTreeReaderArray<char> IsPrimary;
    TTreeReaderArray<char> IsSecFromMat;
    TTreeReaderArray<char> IsSecFromWeak;
    TTreeReaderArray<char> MC_IsOOBPileup;
};

struct Injected {
    Injected() = delete;
    explicit Injected(TTreeReader& reader)
        : ReactionID{reader, "ReactionID"},
          Sexaquark_Px{reader, "Sexaquark_Px"},
          Sexaquark_Py{reader, "Sexaquark_Py"},
          Sexaquark_Pz{reader, "Sexaquark_Pz"},
          Nucleon_Px{reader, "Nucleon_Px"},
          Nucleon_Py{reader, "Nucleon_Py"},
          Nucleon_Pz{reader, "Nucleon_Pz"} {};
    [[nodiscard]] size_t GetSize() const { return ReactionID.GetSize(); };

    TTreeReaderArray<int> ReactionID;
    TTreeReaderArray<float> Sexaquark_Px;
    TTreeReaderArray<float> Sexaquark_Py;
    TTreeReaderArray<float> Sexaquark_Pz;
    TTreeReaderArray<float> Nucleon_Px;
    TTreeReaderArray<float> Nucleon_Py;
    TTreeReaderArray<float> Nucleon_Pz;
};

struct Track {
    Track() = delete;
    explicit Track(TTreeReader& reader)
        : X{reader, "Track_X"},
          Y{reader, "Track_Y"},
          Z{reader, "Track_Z"},
          Px{reader, "Track_Px"},
          Py{reader, "Track_Py"},
          Pz{reader, "Track_Pz"},
          Charge{reader, "Track_Charge"},
          NSigmaPion{reader, "Track_NSigmaPion"},
          NSigmaKaon{reader, "Track_NSigmaKaon"},
          NSigmaProton{reader, "Track_NSigmaProton"},
          DCAxy{reader, "Track_DCAxy"},
          DCAz{reader, "Track_DCAz"},
          TPC_Signal{reader, "Track_TPC_Signal"},
          SigmaX2{reader, "Track_SigmaX2"},
          SigmaXY{reader, "Track_SigmaXY"},
          SigmaY2{reader, "Track_SigmaY2"},
          SigmaXZ{reader, "Track_SigmaXZ"},
          SigmaYZ{reader, "Track_SigmaYZ"},
          SigmaZ2{reader, "Track_SigmaZ2"},
          SigmaXPx{reader, "Track_SigmaXPx"},
          SigmaYPx{reader, "Track_SigmaYPx"},
          SigmaZPx{reader, "Track_SigmaZPx"},
          SigmaPx2{reader, "Track_SigmaPx2"},
          SigmaXPy{reader, "Track_SigmaXPy"},
          SigmaYPy{reader, "Track_SigmaYPy"},
          SigmaZPy{reader, "Track_SigmaZPy"},
          SigmaPxPy{reader, "Track_SigmaPxPy"},
          SigmaPy2{reader, "Track_SigmaPy2"},
          SigmaXPz{reader, "Track_SigmaXPz"},
          SigmaYPz{reader, "Track_SigmaYPz"},
          SigmaZPz{reader, "Track_SigmaZPz"},
          SigmaPxPz{reader, "Track_SigmaPxPz"},
          SigmaPyPz{reader, "Track_SigmaPyPz"},
          SigmaPz2{reader, "Track_SigmaPz2"},
          McEntry{reader, "Track_McEntry"} {};
    [[nodiscard]] size_t GetSize() const { return X.GetSize(); };

    TTreeReaderArray<float> X;
    TTreeReaderArray<float> Y;
    TTreeReaderArray<float> Z;
    TTreeReaderArray<float> Px;
    TTreeReaderArray<float> Py;
    TTreeReaderArray<float> Pz;
    TTreeReaderArray<int> Charge;
    TTreeReaderArray<float> NSigmaPion;
    TTreeReaderArray<float> NSigmaKaon;
    TTreeReaderArray<float> NSigmaProton;
    TTreeReaderArray<float> DCAxy;
    TTreeReaderArray<float> DCAz;
    TTreeReaderArray<float> TPC_Signal;
    TTreeReaderArray<float> SigmaX2;
    TTreeReaderArray<float> SigmaXY;
    TTreeReaderArray<float> SigmaY2;
    TTreeReaderArray<float> SigmaXZ;
    TTreeReaderArray<float> SigmaYZ;
    TTreeReaderArray<float> SigmaZ2;
    TTreeReaderArray<float> SigmaXPx;
    TTreeReaderArray<float> SigmaYPx;
    TTreeReaderArray<float> SigmaZPx;
    TTreeReaderArray<float> SigmaPx2;
    TTreeReaderArray<float> SigmaXPy;
    TTreeReaderArray<float> SigmaYPy;
    TTreeReaderArray<float> SigmaZPy;
    TTreeReaderArray<float> SigmaPxPy;
    TTreeReaderArray<float> SigmaPy2;
    TTreeReaderArray<float> SigmaXPz;
    TTreeReaderArray<float> SigmaYPz;
    TTreeReaderArray<float> SigmaZPz;
    TTreeReaderArray<float> SigmaPxPz;
    TTreeReaderArray<float> SigmaPyPz;
    TTreeReaderArray<float> SigmaPz2;
    TTreeReaderArray<int> McEntry;
};

}  // namespace SexaquarkMacros::Events

#endif  // SM_DF_EVENTS_HXX
