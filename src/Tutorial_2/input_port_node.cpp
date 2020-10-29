#include "behaviortree_cpp_v3/bt_factory.h"

// Synchronoys action node com porta de entrada
class SaySomething : public BT::SyncActionNode {
  public:
    // Se o Node tem portas, precisamos utilizar o construtor dessa forma
    SaySomething(const std::string &name, const BT::NodeConfiguration &config) 
      : BT::SyncActionNode(name, config) {
    }

    // Precisamos definir esse método static
    static BT::PortsList providedPorts() {
      // Tem apenas uma porta de entrada, chamada "message"
      return { BT::InputPort<std::string>("message") };
    }

    // Utilizamos Herança para criar o TreeNode, precisamos sobrescrever
    BT::NodeStatus tick() override {
      // O método getInput() deve estar dentro do tick(), não do construtor
      BT::Optional<std::string> msg = getInput<std::string>("message");
      // Checa se é válido. Se não for, lança o erro
      if(!msg)
        throw BT::RuntimeError("missing required input [message]: ", msg.error());
      
      // Usa o método value() para extrair a mensagem válida
      std::cout << "Robot Says: " << msg.value() << std::endl;
      return BT::NodeStatus::SUCCESS;
    }
};

// A mesma funcionalidade pode ser implementada com uma função simples
BT::NodeStatus SaySomethingSimple(BT::TreeNode &self) {
  BT::Optional<std::string> msg = self.getInput<std::string>("message");
  if(!msg)
    throw BT::RuntimeError("missing required input [message]: ", msg.error());
  
  std::cout << "Robot says: " <<msg.value() << std::endl;
  return BT::NodeStatus::SUCCESS;
}
