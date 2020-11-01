#include "crossdoor_nodes.h"

// Esta função precisa ser implementada no arquivo .cpp, não no header
BT_REGISTER_NODES(factory) {
  CrossDoor::RegisterNodes(factory);
}

// Neste exemplo, para simplificar, não compartilhamos o status da door usando ports e blackboards
static bool _door_open = false;
static bool _door_locked = true;

BT::NodeStatus CrossDoor::IsDoorOpen() {
  SleepMS(500);
  return _door_open ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus CrossDoor::IsDoorLocked() {
  SleepMS(500);
  return _door_locked ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus CrossDoor::UnlockDoor() {
  if(_door_locked) {
    SleepMS(2000);
    _door_locked = false;
  }
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CrossDoor::PassThroughDoor() {
  SleepMS(1000);
  return _door_open ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus CrossDoor::PassThroughWindow() {
  SleepMS(1000);
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CrossDoor::OpenDoor() {
  if (_door_locked) {
    return BT::NodeStatus::FAILURE;
  }
  SleepMS(2000);
  _door_open = true;
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CrossDoor::CloseDoor() {
  if (_door_open) {
    SleepMS(1500);
    _door_open = false;
  }
  return BT::NodeStatus::SUCCESS;
}

void CrossDoor::RegisterNodes(BT::BehaviorTreeFactory &factory) {
  factory.registerSimpleCondition("IsDoorOpen", std::bind(IsDoorOpen));
  factory.registerSimpleAction("PassThroughDoor", std::bind(PassThroughDoor));
  factory.registerSimpleAction("PassThroughWindow", std::bind(PassThroughWindow));
  factory.registerSimpleAction("OpenDoor", std::bind(OpenDoor));
  factory.registerSimpleAction("CloseDoor", std::bind(CloseDoor));
  factory.registerSimpleCondition("IsDoorLocked", std::bind(IsDoorLocked));
  factory.registerSimpleAction("UnlockDoor", std::bind(UnlockDoor));
}
