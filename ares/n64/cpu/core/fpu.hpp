//{
  //fpu-registers.cpp
  template<typename T> auto fgr(uint) -> T&;
  auto getControlRegisterFPU(uint5) -> u32;
  auto setControlRegisterFPU(uint5, uint32) -> void;

  struct FPU {
    //fpu-registers.cpp
    auto setFloatingPointMode(bool) -> void;

    r64 r[32];

    struct Coprocessor {
      static constexpr u8 revision = 0x00;
      static constexpr u8 implementation = 0x0b;
    } coprocessor;

    struct ControlStatus {
      uint2 roundMode = 0;
      struct Flag {
        uint1 inexact = 0;
        uint1 underflow = 0;
        uint1 overflow = 0;
        uint1 divisionByZero = 0;
        uint1 invalidOperation = 0;
      } flag;
      struct Enable {
        uint1 inexact = 0;
        uint1 underflow = 0;
        uint1 overflow = 0;
        uint1 divisionByZero = 0;
        uint1 invalidOperation = 0;
      } enable;
      struct Cause {
        uint1 inexact = 0;
        uint1 underflow = 0;
        uint1 overflow = 0;
        uint1 divisionByZero = 0;
        uint1 invalidOperation = 0;
        uint1 unimplementedOperation = 0;
      } cause;
      uint1 compare = 0;
      uint1 flushed = 0;
    } csr;
  } fpu;

  //fpu-instructions.cpp
  auto instructionBC1(bool value, bool likely, i16 imm) -> void;
  auto instructionCFC1(r64& rt, u8 rd) -> void;
  auto instructionCTC1(cr64& rt, u8 rd) -> void;
  auto instructionDMFC1(r64& rt, u8 fs) -> void;
  auto instructionDMTC1(cr64& rt, u8 fs) -> void;
  auto instructionFABS_S(u8 fd, u8 fs) -> void;
  auto instructionFABS_D(u8 fd, u8 fs) -> void;
  auto instructionFADD_S(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFADD_D(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFCEIL_L_S(u8 fd, u8 fs) -> void;
  auto instructionFCEIL_L_D(u8 fd, u8 fs) -> void;
  auto instructionFCEIL_W_S(u8 fd, u8 fs) -> void;
  auto instructionFCEIL_W_D(u8 fd, u8 fs) -> void;
  auto instructionFCEQ_S(u8 fs, u8 ft) -> void;
  auto instructionFCEQ_D(u8 fs, u8 ft) -> void;
  auto instructionFCF() -> void;
  auto instructionFCOLE_S(u8 fs, u8 ft) -> void;
  auto instructionFCOLE_D(u8 fs, u8 ft) -> void;
  auto instructionFCOLT_S(u8 fs, u8 ft) -> void;
  auto instructionFCOLT_D(u8 fs, u8 ft) -> void;
  auto instructionFCUEQ_S(u8 fs, u8 ft) -> void;
  auto instructionFCUEQ_D(u8 fs, u8 ft) -> void;
  auto instructionFCULE_S(u8 fs, u8 ft) -> void;
  auto instructionFCULE_D(u8 fs, u8 ft) -> void;
  auto instructionFCULT_S(u8 fs, u8 ft) -> void;
  auto instructionFCULT_D(u8 fs, u8 ft) -> void;
  auto instructionFCUN() -> void;
  auto instructionFCVT_S_D(u8 fd, u8 fs) -> void;
  auto instructionFCVT_S_W(u8 fd, u8 fs) -> void;
  auto instructionFCVT_S_L(u8 fd, u8 fs) -> void;
  auto instructionFCVT_D_S(u8 fd, u8 fs) -> void;
  auto instructionFCVT_D_W(u8 fd, u8 fs) -> void;
  auto instructionFCVT_D_L(u8 fd, u8 fs) -> void;
  auto instructionFCVT_L_S(u8 fd, u8 fs) -> void;
  auto instructionFCVT_L_D(u8 fd, u8 fs) -> void;
  auto instructionFCVT_W_S(u8 fd, u8 fs) -> void;
  auto instructionFCVT_W_D(u8 fd, u8 fs) -> void;
  auto instructionFDIV_S(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFDIV_D(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFFLOOR_L_S(u8 fd, u8 fs) -> void;
  auto instructionFFLOOR_L_D(u8 fd, u8 fs) -> void;
  auto instructionFFLOOR_W_S(u8 fd, u8 fs) -> void;
  auto instructionFFLOOR_W_D(u8 fd, u8 fs) -> void;
  auto instructionFMOV_S(u8 fd, u8 fs) -> void;
  auto instructionFMOV_D(u8 fd, u8 fs) -> void;
  auto instructionFMUL_S(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFMUL_D(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFNEG_S(u8 fd, u8 fs) -> void;
  auto instructionFNEG_D(u8 fd, u8 fs) -> void;
  auto instructionFROUND_L_S(u8 fd, u8 fs) -> void;
  auto instructionFROUND_L_D(u8 fd, u8 fs) -> void;
  auto instructionFROUND_W_S(u8 fd, u8 fs) -> void;
  auto instructionFROUND_W_D(u8 fd, u8 fs) -> void;
  auto instructionFSQRT_S(u8 fd, u8 fs) -> void;
  auto instructionFSQRT_D(u8 fd, u8 fs) -> void;
  auto instructionFSUB_S(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFSUB_D(u8 fd, u8 fs, u8 ft) -> void;
  auto instructionFTRUNC_L_S(u8 fd, u8 fs) -> void;
  auto instructionFTRUNC_L_D(u8 fd, u8 fs) -> void;
  auto instructionFTRUNC_W_S(u8 fd, u8 fs) -> void;
  auto instructionFTRUNC_W_D(u8 fd, u8 fs) -> void;
  auto instructionLDC1(u8 ft, cr64& rs, i16 imm) -> void;
  auto instructionLWC1(u8 ft, cr64& rs, i16 imm) -> void;
  auto instructionMFC1(r64& rt, u8 fs) -> void;
  auto instructionMTC1(cr64& rt, u8 fs) -> void;
  auto instructionSDC1(u8 ft, cr64& rs, i16 imm) -> void;
  auto instructionSWC1(u8 ft, cr64& rs, i16 imm) -> void;
//};
