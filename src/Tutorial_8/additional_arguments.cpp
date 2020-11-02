#include "nodes.cpp"

static const char* xml_text = R"(
 <root >
    <BehaviorTree>
      <Sequence>
        <Action_A/>
        <Action_B/>
      </Sequence>
  </BehaviorTree>
 </root>
 )";

int main() {
  BT::BehaviorTreeFactory factory;

  // ---------- Metodo 1: registrando um construtor customizado ----------
  // NodeBuilder é um functor que cria um std::unique_ptr<TreeNode>
  // Usando lambdas ou std::bind, podemos "injetar" argumentos adicionais
  BT::NodeBuilder builder_A = [](const std::string &name, const BT::NodeConfiguration &config) {
    return std::make_unique<Action_A>(name, config, 42, 3.14, "hello world");
  };

  // BehaviorTreeFactory::registerBuilder é uma forma mais generalizada de 
  // registrar um Node customizado
  factory.registerBuilder<Action_A>("Action_A", builder_A);

  // ------------------ Metodo 2: usando um método init ------------------
  // Registramos da mesma maneira, mas precisaremos chamar Action_B::init() depois
  factory.registerNodeType<Action_B>("Action_B");

  auto tree = factory.createTreeFromText(xml_text); 

  // Itera através de todos os nós, e chama init() se for o Action_B
  for (auto &node : tree.nodes){
    if (auto action_B = dynamic_cast<Action_B*>(node.get())) {
      action_B->init(24, 41.3, "world hello");
    }
  }

  tree.tickRoot();

  return 0;
}
