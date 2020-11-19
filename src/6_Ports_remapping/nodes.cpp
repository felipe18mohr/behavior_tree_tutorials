#include "behaviortree_cpp_v3/bt_factory.h"

struct Pose2D {
  double x, y, theta;
};

namespace BT {
  template <> inline Pose2D convertFromString (StringView str) {
    auto parts = splitString(str, ';');
    if (parts.size() != 3)
      throw RuntimeError("Invalid Input");
    else {
      Pose2D output;
      output.x = convertFromString<double>(parts[0]);
      output.y = convertFromString<double>(parts[1]);
      output.theta = convertFromString<double>(parts[2]);
      return output;
    }    
  }
}


class SaySomething : public BT::SyncActionNode {
  public:
    SaySomething(const std::string &name, const BT::NodeConfiguration &config) 
      : BT::SyncActionNode(name, config){
    }

    static BT::PortsList providedPorts() {
      return { BT::InputPort<std::string>("message") };
    }

    BT::NodeStatus tick() override {
      BT::Optional<std::string> msg = getInput<std::string>("message");
      if(!msg)
        throw BT::RuntimeError("missing required input [message]: ", msg.error());
      std::cout << "Robot says: " << msg.value() << std::endl;
      return BT::NodeStatus::SUCCESS;
    }
};


class MoveBaseAction : public BT::AsyncActionNode {
  public:
    MoveBaseAction(const std::string &name, const BT::NodeConfiguration &config) 
      : BT::AsyncActionNode(name, config) {
    }

    static BT::PortsList providedPorts() {
      return {BT::InputPort<Pose2D>("goal")};
    }

    BT::NodeStatus tick() override;

    void halt() override {
      _halt_requested.store(true);
    }

  private:
    std::atomic_bool _halt_requested;

};

BT::NodeStatus MoveBaseAction::tick() {
  Pose2D goal;
  if(!getInput<Pose2D>("goal", goal)) 
    throw BT::RuntimeError("missing requiered input [goal]");

  printf("[ MoveBase: STARTED ]. goal: x=%.1f y=%.1f theta=%.2f\n", goal.x, goal.y, goal.theta);

  _halt_requested.store(false);
  int cont = 0;

  while (!_halt_requested && cont++ < 25) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  std::cout << "[ MoveBase: FINISHED ]" << std::endl;
  return _halt_requested ? BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;

}
