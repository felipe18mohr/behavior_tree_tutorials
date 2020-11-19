#include "behaviortree_cpp_v3/bt_factory.h"
#include "pose_2d.cpp"

// Uma Action Assincrona poderá retornar RUNNING, e será executada em outra thread
class MoveBaseAction : public BT::AsyncActionNode {
  public:
    MoveBaseAction(const std::string &name, const BT::NodeConfiguration &config) 
      : BT::AsyncActionNode(name, config) {
    }

    static BT::PortsList providedPorts() {
      return {BT::InputPort<Pose2D>("goal")};
    }

    BT::NodeStatus tick() override;

    // Esse método overloaded é usado para parar a execução deste Node
    // Devemos implementar uma funcionalidade válida para o método halt() 
    void halt() override {
      // Se, por exemplo, utilizando o ReactiveSequence, em algum ponto BatteryOK
      // retornar FAILURE, o MoveBase action vai ser interrompido (halted)
      _halt_requested.store(true);
      //std::cout << "MoveBase halted" << std::endl;
    }

  private:
    // O atomic_bool permite que essa variavel booleana seja utilizada em outras threads
    std::atomic_bool _halt_requested;

};

// Este método MoveBaseAction::tick() é executado em uma outra thread, diferente 
// da thread principal que chamou MoveBaseAction::executeTick()
BT::NodeStatus MoveBaseAction::tick() {
  Pose2D goal;
  if(!getInput<Pose2D>("goal", goal)) {
    throw BT::RuntimeError("missing requiered input [goal]");
  }

  printf("[ MoveBase: STARTED ]. goal: x=%.1f y=%.1f theta=%.2f\n", goal.x, goal.y, goal.theta);
  
  _halt_requested.store(false);
  int cont = 0;

  // Imagine que a computação leva 250 milisegundos. 
  // Devemos verificar periodicamente _halt_requested e 
  // interromper esse tick() se ele for true
  while (!_halt_requested && cont++ < 25) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  } 

  std::cout << "[ MoveBase: FINISHED ]" << std::endl;
  return _halt_requested ? BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;

}
