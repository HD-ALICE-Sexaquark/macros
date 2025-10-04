#ifndef SM_DF_PACKED_EVENTS_HXX
#define SM_DF_PACKED_EVENTS_HXX

#include <cstddef>
#include <format>
#include <string_view>

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

// Most of this file has been generated with:
// `PackedEvents->MakeSelector()`
namespace SexaquarkMacros::Packed {

struct Event {
    Event() = delete;
    explicit Event(TTreeReader& reader)
        : RunNumber{reader, "RunNumber"},
          DirNumber{reader, "DirNumber"},
          EventNumber{reader, "EventNumber"},
          Centrality{reader, "Centrality"},
          MagneticField{reader, "MagneticField"},
          PV_Xv{reader, "PV_Xv"},
          PV_Yv{reader, "PV_Yv"},
          PV_Zv{reader, "PV_Zv"} {};

    TTreeReaderValue<unsigned int> RunNumber;
    TTreeReaderValue<unsigned int> DirNumber;
    TTreeReaderValue<unsigned int> EventNumber;
    TTreeReaderValue<float> Centrality;
    TTreeReaderValue<float> MagneticField;
    TTreeReaderValue<float> PV_Xv;
    TTreeReaderValue<float> PV_Yv;
    TTreeReaderValue<float> PV_Zv;
};

struct MC_Event {
    MC_Event() = delete;
    explicit MC_Event(TTreeReader& reader)
        : MC_PV_Xv{reader, "MC_PV_Xv"},  //
          MC_PV_Yv{reader, "MC_PV_Yv"},
          MC_PV_Zv{reader, "MC_PV_Zv"} {};

    TTreeReaderValue<float> MC_PV_Xv;
    TTreeReaderValue<float> MC_PV_Yv;
    TTreeReaderValue<float> MC_PV_Zv;
};

struct Track {
    Track() = delete;
    Track(TTreeReader& reader, std::string_view part_name)
        : Entry{reader, std::format("{}_Entry", part_name).c_str()},
          X{reader, std::format("{}_X", part_name).c_str()},
          Y{reader, std::format("{}_Y", part_name).c_str()},
          Z{reader, std::format("{}_Z", part_name).c_str()},
          Px{reader, std::format("{}_Px", part_name).c_str()},
          Py{reader, std::format("{}_Py", part_name).c_str()},
          Pz{reader, std::format("{}_Pz", part_name).c_str()},
          E{reader, std::format("{}_E", part_name).c_str()},
          SigmaX2{reader, std::format("{}_SigmaX2", part_name).c_str()},
          SigmaXY{reader, std::format("{}_SigmaXY", part_name).c_str()},
          SigmaY2{reader, std::format("{}_SigmaY2", part_name).c_str()},
          SigmaXZ{reader, std::format("{}_SigmaXZ", part_name).c_str()},
          SigmaYZ{reader, std::format("{}_SigmaYZ", part_name).c_str()},
          SigmaZ2{reader, std::format("{}_SigmaZ2", part_name).c_str()},
          SigmaXPx{reader, std::format("{}_SigmaXPx", part_name).c_str()},
          SigmaYPx{reader, std::format("{}_SigmaYPx", part_name).c_str()},
          SigmaZPx{reader, std::format("{}_SigmaZPx", part_name).c_str()},
          SigmaPx2{reader, std::format("{}_SigmaPx2", part_name).c_str()},
          SigmaXPy{reader, std::format("{}_SigmaXPy", part_name).c_str()},
          SigmaYPy{reader, std::format("{}_SigmaYPy", part_name).c_str()},
          SigmaZPy{reader, std::format("{}_SigmaZPy", part_name).c_str()},
          SigmaPxPy{reader, std::format("{}_SigmaPxPy", part_name).c_str()},
          SigmaPy2{reader, std::format("{}_SigmaPy2", part_name).c_str()},
          SigmaXPz{reader, std::format("{}_SigmaXPz", part_name).c_str()},
          SigmaYPz{reader, std::format("{}_SigmaYPz", part_name).c_str()},
          SigmaZPz{reader, std::format("{}_SigmaZPz", part_name).c_str()},
          SigmaPxPz{reader, std::format("{}_SigmaPxPz", part_name).c_str()},
          SigmaPyPz{reader, std::format("{}_SigmaPyPz", part_name).c_str()},
          SigmaPz2{reader, std::format("{}_SigmaPz2", part_name).c_str()},
          SigmaXE{reader, std::format("{}_SigmaXE", part_name).c_str()},
          SigmaYE{reader, std::format("{}_SigmaYE", part_name).c_str()},
          SigmaZE{reader, std::format("{}_SigmaZE", part_name).c_str()},
          SigmaPxE{reader, std::format("{}_SigmaPxE", part_name).c_str()},
          SigmaPyE{reader, std::format("{}_SigmaPyE", part_name).c_str()},
          SigmaPzE{reader, std::format("{}_SigmaPzE", part_name).c_str()},
          SigmaE2{reader, std::format("{}_SigmaE2", part_name).c_str()} {}
    [[nodiscard]] size_t GetSize() const { return X.GetSize(); }

    TTreeReaderArray<int> Entry;
    TTreeReaderArray<float> X;
    TTreeReaderArray<float> Y;
    TTreeReaderArray<float> Z;
    TTreeReaderArray<float> Px;
    TTreeReaderArray<float> Py;
    TTreeReaderArray<float> Pz;
    TTreeReaderArray<float> E;
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
    TTreeReaderArray<float> SigmaXE;
    TTreeReaderArray<float> SigmaYE;
    TTreeReaderArray<float> SigmaZE;
    TTreeReaderArray<float> SigmaPxE;
    TTreeReaderArray<float> SigmaPyE;
    TTreeReaderArray<float> SigmaPzE;
    TTreeReaderArray<float> SigmaE2;
};

struct MC_Track {
    MC_Track() = delete;
    MC_Track(TTreeReader& reader, std::string_view part_name)
        : Entry{reader, std::format("{}_MC_Entry", part_name).c_str()},
          X{reader, std::format("{}_MC_X", part_name).c_str()},
          Y{reader, std::format("{}_MC_Y", part_name).c_str()},
          Z{reader, std::format("{}_MC_Z", part_name).c_str()},
          Px{reader, std::format("{}_MC_Px", part_name).c_str()},
          Py{reader, std::format("{}_MC_Py", part_name).c_str()},
          Pz{reader, std::format("{}_MC_Pz", part_name).c_str()},
          E{reader, std::format("{}_MC_E", part_name).c_str()},
          PdgCode{reader, std::format("{}_MC_PdgCode", part_name).c_str()},
          Mother_Entry{reader, std::format("{}_MC_Mother_Entry", part_name).c_str()},
          Mother_PdgCode{reader, std::format("{}_MC_Mother_PdgCode", part_name).c_str()},
          GrandMother_Entry{reader, std::format("{}_MC_GrandMother_Entry", part_name).c_str()},
          GrandMother_PdgCode{reader, std::format("{}_MC_GrandMother_PdgCode", part_name).c_str()},
          IsTrue{reader, std::format("{}_MC_IsTrue", part_name).c_str()},
          IsSignal{reader, std::format("{}_MC_IsSignal", part_name).c_str()},
          IsSecondary{reader, std::format("{}_MC_IsSecondary", part_name).c_str()},
          ReactionID{reader, std::format("{}_MC_ReactionID", part_name).c_str()} {};
    [[nodiscard]] size_t GetSize() const { return X.GetSize(); }

    TTreeReaderArray<int> Entry;
    TTreeReaderArray<float> X;
    TTreeReaderArray<float> Y;
    TTreeReaderArray<float> Z;
    TTreeReaderArray<float> Px;
    TTreeReaderArray<float> Py;
    TTreeReaderArray<float> Pz;
    TTreeReaderArray<float> E;
    TTreeReaderArray<int> PdgCode;
    TTreeReaderArray<int> Mother_Entry;
    TTreeReaderArray<int> Mother_PdgCode;
    TTreeReaderArray<int> GrandMother_Entry;
    TTreeReaderArray<int> GrandMother_PdgCode;
    TTreeReaderArray<char> IsTrue;
    TTreeReaderArray<char> IsSignal;
    TTreeReaderArray<char> IsSecondary;
    TTreeReaderArray<int> ReactionID;
};

struct V0 {
    V0() = delete;
    V0(TTreeReader& reader, std::string_view v0_name)
        : Entry{reader, std::format("{}_Entry", v0_name).c_str()},
          X{reader, std::format("{}_X", v0_name).c_str()},
          Y{reader, std::format("{}_Y", v0_name).c_str()},
          Z{reader, std::format("{}_Z", v0_name).c_str()},
          Px{reader, std::format("{}_Px", v0_name).c_str()},
          Py{reader, std::format("{}_Py", v0_name).c_str()},
          Pz{reader, std::format("{}_Pz", v0_name).c_str()},
          E{reader, std::format("{}_E", v0_name).c_str()},
          SigmaX2{reader, std::format("{}_SigmaX2", v0_name).c_str()},
          SigmaXY{reader, std::format("{}_SigmaXY", v0_name).c_str()},
          SigmaY2{reader, std::format("{}_SigmaY2", v0_name).c_str()},
          SigmaXZ{reader, std::format("{}_SigmaXZ", v0_name).c_str()},
          SigmaYZ{reader, std::format("{}_SigmaYZ", v0_name).c_str()},
          SigmaZ2{reader, std::format("{}_SigmaZ2", v0_name).c_str()},
          SigmaXPx{reader, std::format("{}_SigmaXPx", v0_name).c_str()},
          SigmaYPx{reader, std::format("{}_SigmaYPx", v0_name).c_str()},
          SigmaZPx{reader, std::format("{}_SigmaZPx", v0_name).c_str()},
          SigmaPx2{reader, std::format("{}_SigmaPx2", v0_name).c_str()},
          SigmaXPy{reader, std::format("{}_SigmaXPy", v0_name).c_str()},
          SigmaYPy{reader, std::format("{}_SigmaYPy", v0_name).c_str()},
          SigmaZPy{reader, std::format("{}_SigmaZPy", v0_name).c_str()},
          SigmaPxPy{reader, std::format("{}_SigmaPxPy", v0_name).c_str()},
          SigmaPy2{reader, std::format("{}_SigmaPy2", v0_name).c_str()},
          SigmaXPz{reader, std::format("{}_SigmaXPz", v0_name).c_str()},
          SigmaYPz{reader, std::format("{}_SigmaYPz", v0_name).c_str()},
          SigmaZPz{reader, std::format("{}_SigmaZPz", v0_name).c_str()},
          SigmaPxPz{reader, std::format("{}_SigmaPxPz", v0_name).c_str()},
          SigmaPyPz{reader, std::format("{}_SigmaPyPz", v0_name).c_str()},
          SigmaPz2{reader, std::format("{}_SigmaPz2", v0_name).c_str()},
          SigmaXE{reader, std::format("{}_SigmaXE", v0_name).c_str()},
          SigmaYE{reader, std::format("{}_SigmaYE", v0_name).c_str()},
          SigmaZE{reader, std::format("{}_SigmaZE", v0_name).c_str()},
          SigmaPxE{reader, std::format("{}_SigmaPxE", v0_name).c_str()},
          SigmaPyE{reader, std::format("{}_SigmaPyE", v0_name).c_str()},
          SigmaPzE{reader, std::format("{}_SigmaPzE", v0_name).c_str()},
          SigmaE2{reader, std::format("{}_SigmaE2", v0_name).c_str()},
          Neg_Entry{reader, std::format("{}_Neg_Entry", v0_name).c_str()},
          Neg_X{reader, std::format("{}_Neg_X", v0_name).c_str()},
          Neg_Y{reader, std::format("{}_Neg_Y", v0_name).c_str()},
          Neg_Z{reader, std::format("{}_Neg_Z", v0_name).c_str()},
          Neg_Px{reader, std::format("{}_Neg_Px", v0_name).c_str()},
          Neg_Py{reader, std::format("{}_Neg_Py", v0_name).c_str()},
          Neg_Pz{reader, std::format("{}_Neg_Pz", v0_name).c_str()},
          Neg_E{reader, std::format("{}_Neg_E", v0_name).c_str()},
          Neg_X_AtPCA{reader, std::format("{}_Neg_X_AtPCA", v0_name).c_str()},
          Neg_Y_AtPCA{reader, std::format("{}_Neg_Y_AtPCA", v0_name).c_str()},
          Neg_Z_AtPCA{reader, std::format("{}_Neg_Z_AtPCA", v0_name).c_str()},
          Neg_Px_AtPCA{reader, std::format("{}_Neg_Px_AtPCA", v0_name).c_str()},
          Neg_Py_AtPCA{reader, std::format("{}_Neg_Py_AtPCA", v0_name).c_str()},
          Neg_Pz_AtPCA{reader, std::format("{}_Neg_Pz_AtPCA", v0_name).c_str()},
          Pos_Entry{reader, std::format("{}_Pos_Entry", v0_name).c_str()},
          Pos_X{reader, std::format("{}_Pos_X", v0_name).c_str()},
          Pos_Y{reader, std::format("{}_Pos_Y", v0_name).c_str()},
          Pos_Z{reader, std::format("{}_Pos_Z", v0_name).c_str()},
          Pos_Px{reader, std::format("{}_Pos_Px", v0_name).c_str()},
          Pos_Py{reader, std::format("{}_Pos_Py", v0_name).c_str()},
          Pos_Pz{reader, std::format("{}_Pos_Pz", v0_name).c_str()},
          Pos_E{reader, std::format("{}_Pos_E", v0_name).c_str()},
          Pos_X_AtPCA{reader, std::format("{}_Pos_X_AtPCA", v0_name).c_str()},
          Pos_Y_AtPCA{reader, std::format("{}_Pos_Y_AtPCA", v0_name).c_str()},
          Pos_Z_AtPCA{reader, std::format("{}_Pos_Z_AtPCA", v0_name).c_str()},
          Pos_Px_AtPCA{reader, std::format("{}_Pos_Px_AtPCA", v0_name).c_str()},
          Pos_Py_AtPCA{reader, std::format("{}_Pos_Py_AtPCA", v0_name).c_str()},
          Pos_Pz_AtPCA{reader, std::format("{}_Pos_Pz_AtPCA", v0_name).c_str()} {};
    [[nodiscard]] size_t GetSize() const { return X.GetSize(); }

    TTreeReaderArray<int> Entry;
    TTreeReaderArray<float> X;
    TTreeReaderArray<float> Y;
    TTreeReaderArray<float> Z;
    TTreeReaderArray<float> Px;
    TTreeReaderArray<float> Py;
    TTreeReaderArray<float> Pz;
    TTreeReaderArray<float> E;
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
    TTreeReaderArray<float> SigmaXE;
    TTreeReaderArray<float> SigmaYE;
    TTreeReaderArray<float> SigmaZE;
    TTreeReaderArray<float> SigmaPxE;
    TTreeReaderArray<float> SigmaPyE;
    TTreeReaderArray<float> SigmaPzE;
    TTreeReaderArray<float> SigmaE2;
    TTreeReaderArray<int> Neg_Entry;
    TTreeReaderArray<float> Neg_X;
    TTreeReaderArray<float> Neg_Y;
    TTreeReaderArray<float> Neg_Z;
    TTreeReaderArray<float> Neg_Px;
    TTreeReaderArray<float> Neg_Py;
    TTreeReaderArray<float> Neg_Pz;
    TTreeReaderArray<float> Neg_E;
    TTreeReaderArray<float> Neg_X_AtPCA;
    TTreeReaderArray<float> Neg_Y_AtPCA;
    TTreeReaderArray<float> Neg_Z_AtPCA;
    TTreeReaderArray<float> Neg_Px_AtPCA;
    TTreeReaderArray<float> Neg_Py_AtPCA;
    TTreeReaderArray<float> Neg_Pz_AtPCA;
    TTreeReaderArray<int> Pos_Entry;
    TTreeReaderArray<float> Pos_X;
    TTreeReaderArray<float> Pos_Y;
    TTreeReaderArray<float> Pos_Z;
    TTreeReaderArray<float> Pos_Px;
    TTreeReaderArray<float> Pos_Py;
    TTreeReaderArray<float> Pos_Pz;
    TTreeReaderArray<float> Pos_E;
    TTreeReaderArray<float> Pos_X_AtPCA;
    TTreeReaderArray<float> Pos_Y_AtPCA;
    TTreeReaderArray<float> Pos_Z_AtPCA;
    TTreeReaderArray<float> Pos_Px_AtPCA;
    TTreeReaderArray<float> Pos_Py_AtPCA;
    TTreeReaderArray<float> Pos_Pz_AtPCA;
};

struct MC_V0 {
    MC_V0() = delete;
    MC_V0(TTreeReader& reader, std::string_view v0_name)
        : Entry{reader, std::format("{}_MC_Entry", v0_name).c_str()},
          X{reader, std::format("{}_MC_X", v0_name).c_str()},
          Y{reader, std::format("{}_MC_Y", v0_name).c_str()},
          Z{reader, std::format("{}_MC_Z", v0_name).c_str()},
          Px{reader, std::format("{}_MC_Px", v0_name).c_str()},
          Py{reader, std::format("{}_MC_Py", v0_name).c_str()},
          Pz{reader, std::format("{}_MC_Pz", v0_name).c_str()},
          E{reader, std::format("{}_MC_E", v0_name).c_str()},
          DecayX{reader, std::format("{}_MC_DecayX", v0_name).c_str()},
          DecayY{reader, std::format("{}_MC_DecayY", v0_name).c_str()},
          DecayZ{reader, std::format("{}_MC_DecayZ", v0_name).c_str()},
          PdgCode{reader, std::format("{}_MC_PdgCode", v0_name).c_str()},
          Mother_Entry{reader, std::format("{}_MC_Mother_Entry", v0_name).c_str()},
          Mother_PdgCode{reader, std::format("{}_MC_Mother_PdgCode", v0_name).c_str()},
          IsTrue{reader, std::format("{}_MC_IsTrue", v0_name).c_str()},
          IsSignal{reader, std::format("{}_MC_IsSignal", v0_name).c_str()},
          IsSecondary{reader, std::format("{}_MC_IsSecondary", v0_name).c_str()},
          ReactionID{reader, std::format("{}_MC_ReactionID", v0_name).c_str()},
          IsHybrid{reader, std::format("{}_MC_IsHybrid", v0_name).c_str()},
          Neg_Entry{reader, std::format("{}_MC_Neg_Entry", v0_name).c_str()},
          Neg_Px{reader, std::format("{}_MC_Neg_Px", v0_name).c_str()},
          Neg_Py{reader, std::format("{}_MC_Neg_Py", v0_name).c_str()},
          Neg_Pz{reader, std::format("{}_MC_Neg_Pz", v0_name).c_str()},
          Neg_PdgCode{reader, std::format("{}_MC_Neg_PdgCode", v0_name).c_str()},
          Neg_IsTrue{reader, std::format("{}_MC_Neg_IsTrue", v0_name).c_str()},
          Neg_IsSignal{reader, std::format("{}_MC_Neg_IsSignal", v0_name).c_str()},
          Neg_IsSecondary{reader, std::format("{}_MC_Neg_IsSecondary", v0_name).c_str()},
          Neg_ReactionID{reader, std::format("{}_MC_Neg_ReactionID", v0_name).c_str()},
          Pos_Entry{reader, std::format("{}_MC_Pos_Entry", v0_name).c_str()},
          Pos_Px{reader, std::format("{}_MC_Pos_Px", v0_name).c_str()},
          Pos_Py{reader, std::format("{}_MC_Pos_Py", v0_name).c_str()},
          Pos_Pz{reader, std::format("{}_MC_Pos_Pz", v0_name).c_str()},
          Pos_PdgCode{reader, std::format("{}_MC_Pos_PdgCode", v0_name).c_str()},
          Pos_IsTrue{reader, std::format("{}_MC_Pos_IsTrue", v0_name).c_str()},
          Pos_IsSignal{reader, std::format("{}_MC_Pos_IsSignal", v0_name).c_str()},
          Pos_IsSecondary{reader, std::format("{}_MC_Pos_IsSecondary", v0_name).c_str()},
          Pos_ReactionID{reader, std::format("{}_MC_Pos_ReactionID", v0_name).c_str()} {}

    TTreeReaderArray<int> Entry;
    TTreeReaderArray<float> X;
    TTreeReaderArray<float> Y;
    TTreeReaderArray<float> Z;
    TTreeReaderArray<float> Px;
    TTreeReaderArray<float> Py;
    TTreeReaderArray<float> Pz;
    TTreeReaderArray<float> E;
    TTreeReaderArray<float> DecayX;
    TTreeReaderArray<float> DecayY;
    TTreeReaderArray<float> DecayZ;
    TTreeReaderArray<int> PdgCode;
    TTreeReaderArray<int> Mother_Entry;
    TTreeReaderArray<int> Mother_PdgCode;
    TTreeReaderArray<char> IsTrue;
    TTreeReaderArray<char> IsSignal;
    TTreeReaderArray<char> IsSecondary;
    TTreeReaderArray<int> ReactionID;
    TTreeReaderArray<char> IsHybrid;
    TTreeReaderArray<int> Neg_Entry;
    TTreeReaderArray<float> Neg_Px;
    TTreeReaderArray<float> Neg_Py;
    TTreeReaderArray<float> Neg_Pz;
    TTreeReaderArray<int> Neg_PdgCode;
    TTreeReaderArray<char> Neg_IsTrue;
    TTreeReaderArray<char> Neg_IsSignal;
    TTreeReaderArray<char> Neg_IsSecondary;
    TTreeReaderArray<int> Neg_ReactionID;
    TTreeReaderArray<int> Pos_Entry;
    TTreeReaderArray<float> Pos_Px;
    TTreeReaderArray<float> Pos_Py;
    TTreeReaderArray<float> Pos_Pz;
    TTreeReaderArray<int> Pos_PdgCode;
    TTreeReaderArray<char> Pos_IsTrue;
    TTreeReaderArray<char> Pos_IsSignal;
    TTreeReaderArray<char> Pos_IsSecondary;
    TTreeReaderArray<int> Pos_ReactionID;
};

}  // namespace SexaquarkMacros::Packed

#endif  // SM_DF_PACKED_EVENTS_HXX
