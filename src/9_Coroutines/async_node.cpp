#include "behaviortree_cpp_v3/bt_factory.h"

typedef std::chrono::milliseconds Milliseconds;

// CoroActionNode tem a mesma função do AsyncActionNode, mas utiliza corrotinas 
// ao invés de criar uma nova thread, sendo mais eficiente
class MyAsyncAction : public BT::CoroActionNode {
  public:
    MyAsyncAction (const std::string &name) : CoroActionNode(name, {}) {
    }

  private:
    /* Esqueleto ideal para uma Action assíncrona:
       - Request para um remote service provider
       - Um loop para verificar se a resposta foi recebida
       - Podemos chamar setStatusRunningAndYield() para "pausar"
       - Código a ser executado após a resposta
       - Uma maneira simples de lidar com o halt()*/
    BT::NodeStatus tick() override {
      std::cout << name() << ": Started. Send Request to server." << std::endl;

      auto Now = [](){ return std::chrono::high_resolution_clock::now(); };

      BT::TimePoint initial_time = Now();
      BT::TimePoint time_before_reply = initial_time + Milliseconds(100);

      int count = 0;
      bool reply_received = false;

      while (!reply_received) {
        if(count++ == 0) {
          // Apenas uma vez
          std::cout << name() << ": Waiting Reply..." << std::endl;
        }
        if (Now() >= time_before_reply) {
          reply_received = true;
        }
        if (!reply_received) {
          // Seta o status como RUNNING e "pause/sleep"
          // Se halt() for chamado, não continuará a execução
          setStatusRunningAndYield();
        }
      }

      std::cout << name() <<": Done. 'Waiting Reply' loop repeated " << count << " times" << std::endl;
      cleanup(false);
      return BT::NodeStatus::SUCCESS;
   }

    void cleanup(bool halted) {
      if (halted) {
        std::cout << name() <<": cleaning up after an halt()\n" << std::endl;
      }
      else {
        std::cout << name() <<": cleaning up after SUCCESS\n" << std::endl;
      }
    }

    void halt() override {
      std::cout << name() <<": Halted." << std::endl;
      cleanup(true);
      // Precisamos chamar isso ao final
      BT::CoroActionNode::halt();
    }

};
