struct CPU : Z80, Z80::Bus, Thread {
  Node::Object node;
  Memory::Writable<u8> ram;

  struct Debugger {
    //debugger.cpp
    auto load(Node::Object) -> void;
    auto instruction() -> void;
    auto interrupt(string_view) -> void;

    struct Memory {
      Node::Debugger::Memory ram;
    } memory;

    struct Tracer {
      Node::Debugger::Tracer::Instruction instruction;
      Node::Debugger::Tracer::Notification interrupt;
    } tracer;
  } debugger;

  auto synchronizing() const -> bool override { return scheduler.synchronizing(); }

  //cpu.cpp
  auto load(Node::Object) -> void;
  auto unload() -> void;

  auto main() -> void;
  auto step(uint clocks) -> void override;

  auto power() -> void;
  auto setIrq(bool line) -> void;

  //memory.cpp
  auto read(n16 address) -> n8 override;
  auto write(n16 address, n8 data) -> void override;
  auto readBanked(n3 bank, n16 address) -> n8;
  auto writeBanked(n3 bank, n16 address, n8 data) -> void;

  auto in(n16 address) -> n8 override;
  auto out(n16 address, n8 data) -> void override;

  //serialization.cpp
  auto serialize(serializer&) -> void;

private:
  n1 irqLine;
};

extern CPU cpu;
