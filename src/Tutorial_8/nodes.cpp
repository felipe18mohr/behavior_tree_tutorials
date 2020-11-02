#include "behaviortree_cpp_v3/bt_factory.h"

// Se quisermos passar mais argumentos para o construtor
// Não é recomendável passar esses argumentos usando Blackboards

// ---------- Metodo 1: registrando um construtor customizado ----------

// Action_A tem um construtor diferente do default
class Action_A : public BT::SyncActionNode {
  public:
    // Argumentos adicionais passados ao construtor
    Action_A(const std::string &name, const BT::NodeConfiguration &config,
             int arg1, double arg2, std::string arg3) : 
             BT::SyncActionNode(name, config), 
             _arg1(arg1), _arg2(arg2), _arg3(arg3) {
    }

    // Este exemplo não requer nenhuma porta
    static BT::PortsList providedPorts() { return {}; }

    // tick() pode acessar os membros privados
    BT::NodeStatus tick() override {
      std::cout << "Action_B: " << _arg1 << " / " << _arg2 << " / " << _arg3 << std::endl;
      return BT::NodeStatus::SUCCESS;
    }

  private:
    int _arg1;
    double _arg2;
    std::string _arg3; 
};

// ------------------ Metodo 2: usando um método init ------------------
class Action_B : public BT::SyncActionNode {
  public:
    // Construtor da mesma maneira
    Action_B(const std::string &name, const BT::NodeConfiguration &config) 
      : BT::SyncActionNode(name, config) {
    }

    // Queremos que esse método seja chamado uma vez, antes do primeiro tick()
    void init(int arg1, double arg2, std::string arg3) {
      _arg1 = arg1;
      _arg2 = arg2;
      _arg3 = arg3;
    }

    // Este exemplo não requer nenhuma porta
    static BT::PortsList providedPorts() { return {}; }
    
    // tick() pode acessar os membros privados
    BT::NodeStatus tick() override {
      std::cout << "Action_B: " << _arg1 << " / " << _arg2 << " / " << _arg3 << std::endl;
      return BT::NodeStatus::SUCCESS;
    }

  private:
    int _arg1;
    double _arg2;
    std::string _arg3;
    
};
