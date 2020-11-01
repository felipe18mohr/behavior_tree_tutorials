#include "behaviortree_cpp_v3/bt_factory.h"
#include "async_node.cpp"
#include "dummy.cpp"

int main(){
  BT::BehaviorTreeFactory factory;
  factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));
  factory.registerNodeType<MoveBaseAction>("MoveBase");
  factory.registerNodeType<SaySomething>("SaySomething");

  auto tree = factory.createTreeFromFile("../src/Tutorial_4/reactive_sequence.xml");

  BT::NodeStatus status;

  std::cout << "\n--- 1st executeTick() ---" << std::endl;
  status = tree.tickRoot();

  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  std::cout << "\n--- 2nd executeTick() ---" << std::endl;
  status = tree.tickRoot();

  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  std::cout << "\n--- 3rd executeTick() ---" << std::endl;
  status = tree.tickRoot();

  std::cout << std::endl;

  return 0;
}
