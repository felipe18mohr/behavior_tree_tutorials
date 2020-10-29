#include "action_nodes.cpp"

int main(){

  // Precisaremos primeiro registrar os nossos TreeNodes
  BT::BehaviorTreeFactory factory;

  // Se o Node foi criado utilizando Herança, ele será registrado desta forma:
  factory.registerNodeType<ApproachObject>("ApproachObject");
  // Registrando um SimpleActionNode usando um ponteiro de função
  factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));
  // Também pode ser feito utilizando metodos da classe
  GripperInterface gripper;
  factory.registerSimpleAction("OpenGripper", std::bind(&GripperInterface::open, &gripper));
  factory.registerSimpleAction("CloseGripper", std::bind(&GripperInterface::close, &gripper));

  // Após os TreeNodes terem sido registrados, carregaremos o arquivo XML 
  auto tree = factory.createTreeFromFile("../src/my_tree.xml");

  // Para "executar" a árvore, precisamos fazer um "tick" nela
  tree.tickRoot();
  
  return 0;
}
