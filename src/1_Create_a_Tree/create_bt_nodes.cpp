#include "behaviortree_cpp_v3/bt_factory.h"

// Synchronous action
// A maneira mais comum de criar um TreeNode é utilizando Herança
class ApproachObject : public BT::SyncActionNode {
  public:
    ApproachObject(const std::string &name) : BT::SyncActionNode(name, {}) {
    } // Todo TreeNode deve ter o seu nome, que não precisa ser único

    // O método tick() deve ser sobrescrito
    BT::NodeStatus tick() override {
      std::cout << "ApproachObject: " << this->name() << std::endl;
      return BT::NodeStatus::SUCCESS; // Deve SEMPRE retornar um NodeStatus
    }
};

// Outra maneira de se criar um TreeNode é utilizando dependency injection
BT::NodeStatus CheckBattery() {
  std::cout << "[ Battery: OK ]" << std::endl;
  return BT::NodeStatus::SUCCESS;
}

class GripperInterface {
  public:
    GripperInterface() : _open(true) {
    }

    BT::NodeStatus open() {
      _open = true;
      std::cout << "GripperInterface::open" << std::endl;
      return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus close() {
      std::cout << "GripperInterface::close" << std::endl;
      return BT::NodeStatus::SUCCESS;
    }

  private:
    bool _open;
};
