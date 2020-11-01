#include "nodes.cpp"

int main() {
  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<MoveBaseAction>("MoveBase");

  auto tree = factory.createTreeFromFile("../src/Tutorial_6/tree.xml");

  BT::NodeStatus status = BT::NodeStatus::RUNNING;

  // Continua o tick até retornar SUCCESS ou FAILURE
  while(status == BT::NodeStatus::RUNNING) {
    status = tree.tickRoot();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  // Visualizando algumas informações sobre o estado atual dos Blackboards
  std::cout << "----------" << std::endl;
  tree.blackboard_stack[0]->debugMessage();
  std::cout << "----------" << std::endl;
  tree.blackboard_stack[1]->debugMessage();
  std::cout << "----------" << std::endl;  

  return 0;
}
