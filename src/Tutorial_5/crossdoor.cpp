#include "crossdoor_nodes.cpp"

int main(){
  BT::BehaviorTreeFactory factory;
  CrossDoor::RegisterNodes(factory);

  auto tree = factory.createTreeFromFile("../src/Tutorial_5/tree.xml");

  // Este logger print as mudanças de estado no console
  BT::StdCoutLogger logger_cout(tree);
  // Este logger salva as mudanças no arquivo
  BT::FileLogger logger_file(tree, "../src/Tutorial_5/loggers/bt_trace.fbl");
  // Este logger armazena o tempo de execução de cada Node
  BT::MinitraceLogger logger_minitrace(tree, "../src/Tutorial_5/loggers/bt_trace.json");
  
  #ifdef ZMQ_FOUND
    // Este logger publica as mudanças de estado usando XeroMQ. Usado pelo Groot
    BT::PublisherZMQ publisher_zmq(tree);
  #endif

  // Printa na tela a hierarquia da árvore
  BT::printTreeRecursively(tree.rootNode());

  // while (1)
  {
    BT::NodeStatus status = BT::NodeStatus::RUNNING;
    // Continua fazendo o tick até obter SUCCESS ou FAILURE
    while (status == BT::NodeStatus::RUNNING) {
      status = tree.tickRoot();
      CrossDoor::SleepMS(1); // Apenas para evitar "busy loops"
    }
    CrossDoor::SleepMS(2000);
  }

  return 0;
}
