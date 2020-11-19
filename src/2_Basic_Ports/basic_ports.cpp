#include "input_port_node.cpp"
#include "output_port_node.cpp"

int main(){

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

  // Registrando o SaySomethingSimple, que foi criado como uma função simples
  /* SimpleActionNodes não conseguem definir seu próprio método providedPorts(),
     precisamos passar um PortsList explicitamente se quisermos que o Action
     seja capaz de usat getInput() ou setOutput()
  */
  BT::PortsList say_something_ports = { BT::InputPort<std::string>("message")};
  factory.registerSimpleAction("SaySomething2", SaySomethingSimple, say_something_ports);

  auto tree = factory.createTreeFromFile("../src/Tutorial_2/my_tree.xml");

  tree.tickRoot();

  return 0;
}
