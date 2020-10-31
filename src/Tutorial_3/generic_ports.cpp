#include "nodes.cpp"

int main(){
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<CalculateGoal>("CalculateGoal");
  factory.registerNodeType<PrintTarget>("PrintTarget");

  auto tree = factory.createTreeFromFile("../src/Tutorial_3/my_tree.xml");
  tree.tickRoot();

  return 0;

}
