#include "mylegacy.cpp"

static const char* xml_text = R"(
  <root>
    <BehaviorTree>
      <MoveTo goal="-1;3;0.5" />
    </BehaviorTree>
  </root>
)";

// Para envolver o método MyLegacyMoveTo::go, precisamos usar uma lambda 
// ou std::brind para criar um ponteiro de função e SimpleActionNode
int main(){
  MyLegacyMoveTo move_to;

  // Aqui, usamos a função lambda que captura a referência de move_to
  auto MoveToWrapperWithLambda = [&move_to](BT::TreeNode &parent_node) -> BT::NodeStatus {
    Point3D goal;
    // Graças ao parent_node, podemos facilmente acessar as portas de input e output
    parent_node.getInput("goal", goal);

    bool res = move_to.go(goal);
    // Convertendo o resultado bool para um NodeStatus
    return res ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  };

  BT::BehaviorTreeFactory factory;

  // Registramos a função lambda com o BehaviorTreeFactory::registerSimpleAction
  BT::PortsList ports = { BT::InputPort<Point3D>("goal") };
  factory.registerSimpleAction("MoveTo", MoveToWrapperWithLambda, ports);

  auto tree = factory.createTreeFromText(xml_text);

  tree.tickRoot();

  return 0;
}
