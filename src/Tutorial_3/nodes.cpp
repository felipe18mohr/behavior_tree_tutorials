#include "behaviortree_cpp_v3/bt_factory.h"

struct Position2D{
  double x;
  double y;
};

namespace BT{
  // Precisamos implementar um template specialiaztion do 
  // convertFromString para o tipo que desejamos
  template <> inline Position2D convertFromString(StringView str) {
    printf("Converting string: \"%s\"\n", str.data());
    
    // Separando os números usando ";", mas ainda é string 
    auto parts = splitString(str, ';');
    if (parts.size() != 2)
      throw RuntimeError("Invalid Input");
    else{
      Position2D output;  // Aqui convertemos cada parte da struct para double
      output.x = convertFromString<double>(parts[0]);
      output.y = convertFromString<double>(parts[1]);
      return output;
    }
  }
}


// Esta Action vai escrever na porta "goal"
class CalculateGoal : public BT::SyncActionNode {
  public:
    CalculateGoal(const std::string &name, const BT::NodeConfiguration config) 
      : BT::SyncActionNode(name, config) {
    }

    static BT::PortsList providedPorts() {
      return {BT::OutputPort<Position2D>("goal")};
    }

    BT::NodeStatus tick() override {
      Position2D my_goal = {1.1, 2.3};
      setOutput<Position2D>("goal", my_goal);
      return BT::NodeStatus::SUCCESS;
    }
};


// Esta Action vai ler a porta "target"
class PrintTarget : public BT::SyncActionNode {
  public:
    PrintTarget(const std::string &name, const BT::NodeConfiguration &config) 
      : BT::SyncActionNode(name, config) {
    }
    
    static BT::PortsList providedPorts() {
      const char* description = "Simply print the goal on console...";
      return { BT::InputPort<Position2D>("target", description)};
    }

    BT::NodeStatus tick() override {
      auto res = getInput<Position2D>("target");
      if (!res)
        throw BT::RuntimeError("error reading port [target]: ", res.error());
      Position2D target = res.value();
      printf("Target positions: [%.1f, %.1f]\n", target.x, target.y);
      return BT::NodeStatus::SUCCESS;
    }
};
