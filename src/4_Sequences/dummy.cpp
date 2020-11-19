#include "behaviortree_cpp_v3/bt_factory.h"

BT::NodeStatus CheckBattery() {
  std::cout << "[ Battery: OK ]" << std::endl;
  return BT::NodeStatus::SUCCESS;
}

class SaySomething : public BT::SyncActionNode {
  public:
    SaySomething(const std::string &name, const BT::NodeConfiguration &config) 
      : BT::SyncActionNode(name, config) {
    }

    static BT::PortsList providedPorts() {
      return { BT::InputPort<std::string>("message") };
    }

    BT::NodeStatus tick() override {
      BT::Optional<std::string> msg = getInput<std::string>("message");

      if(!msg)
        throw BT::RuntimeError("missing required input [message]: ", msg.error());
      
      std::cout << "Robot Says: " << msg.value() << std::endl;
      return BT::NodeStatus::SUCCESS;
    }
};
