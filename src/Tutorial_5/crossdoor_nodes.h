#pragma once
#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_minitrace_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_file_logger.h"

#ifdef ZMQ_FOUND
#include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"
#endif

namespace CrossDoor {
  inline void SleepMS(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  }

  BT::NodeStatus IsDoorOpen();
  BT::NodeStatus IsDoorLocked();
  BT::NodeStatus UnlockDoor();
  BT::NodeStatus PassThroughDoor();
  BT::NodeStatus PassThroughWindow();
  BT::NodeStatus OpenDoor();
  BT::NodeStatus CloseDoor();
  void RegisterNodes(BT::BehaviorTreeFactory &factory);

}
