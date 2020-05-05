#include "registers.hpp"
#include "memory.cpp"
#include "instruction.cpp"
#include "instructions-core.cpp"
#include "instructions-cop0.cpp"
#include "instructions-cop1.cpp"
#include "disassembler.cpp"
#include "serialization.cpp"

auto CPU::powerR4300() -> void {
  //ROUND.W/L conform to IEEE 754, which uses round-to-nearest mode.
  //ensure that we are in this mode to prevent off-by-one errors.
  //note: this is an expensive operation, so we assume this won't be changed.
  //if other code elsewhere changes this, it will harm emulation accuracy.
  fesetround(FE_TONEAREST);

  for(uint n : range(32)) GPR[n].u64 = 0;
  for(uint n : range(32)) SPR[n].u64 = 0;
  SPR[COP0::Register::Status].u64 = 0xf400'0000;
  LO.u64 = 0;
  HI.u64 = 0;
  PC = 0xbfc00000;
  IP = nothing;
  LLBIT = 0;
}