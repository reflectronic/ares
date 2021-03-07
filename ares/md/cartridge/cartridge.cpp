#include <md/md.hpp>

namespace ares::MegaDrive {

Cartridge& cartridge = cartridgeSlot.cartridge;
Cartridge& expansion = expansionSlot.cartridge;
#include "board/board.cpp"
#include "slot.cpp"
#include "serialization.cpp"

auto Cartridge::allocate(Node::Port parent) -> Node::Peripheral {
  return node = parent->append<Node::Peripheral>(string{"Mega Drive ", parent->type()});
}

auto Cartridge::connect() -> void {
  if(!node->setPak(pak = platform->pak(node))) return;

  information = {};
  information.title    = pak->attribute("title");
  information.regions  = pak->attribute("region").split(",").strip();
  information.bootable = pak->attribute("bootable").boolean();

  if(pak->read("patch.rom")) {
    board = new Board::LockOn(*this);
  } else if(pak->attribute("label") == "Game Genie") {
    board = new Board::GameGenie(*this);
  } else if(pak->read("program.rom") && pak->read("program.rom")->size() > 0x200000) {
    board = new Board::Banked(*this);
  } else {
    board = new Board::Linear(*this);
  }
  board->pak = pak;
  board->load();

  if(auto fp = pak->read("backup.ram")) {
    mcd.bram.load(fp);
  }

  power();
}

auto Cartridge::disconnect() -> void {
  if(!node) return;
  board->pak.reset();
  board.reset();
  pak.reset();
  node.reset();
  information = {};
}

auto Cartridge::save() -> void {
  if(!node) return;
  board->save();

  if(auto fp = pak->write("backup.ram")) {
    mcd.bram.save(fp);
  }
}

auto Cartridge::power() -> void {
  board->power();
}

auto Cartridge::read(n1 upper, n1 lower, n22 address, n16 data) -> n16 {
  return board->read(upper, lower, address, data);
}

auto Cartridge::write(n1 upper, n1 lower, n22 address, n16 data) -> void {
  return board->write(upper, lower, address, data);
}

auto Cartridge::readIO(n1 upper, n1 lower, n24 address, n16 data) -> n16 {
  return board->readIO(upper, lower, address, data);
}

auto Cartridge::writeIO(n1 upper, n1 lower, n24 address, n16 data) -> void {
  return board->writeIO(upper, lower, address, data);
}

}
