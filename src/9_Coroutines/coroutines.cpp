#include "async_node.cpp"

// A sequência inteira será parada (halted) pelo Timeout após 150 ms
static const char* xml_text = R"(
 <root >
     <BehaviorTree>
        <Timeout msec="150">
            <SequenceStar name="sequence">
                <MyAsyncAction name="action_A"/>
                <MyAsyncAction name="action_B"/>
            </SequenceStar>
        </Timeout>
     </BehaviorTree>
 </root>
 )";

int main(){
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<MyAsyncAction>("MyAsyncAction");

  auto tree = factory.createTreeFromText(xml_text);

  // Continua o tick até que retorne SUCCESS ou FAILURE
  while( tree.tickRoot() == BT::NodeStatus::RUNNING ) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
