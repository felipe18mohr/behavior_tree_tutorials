# behavior_tree_tutorials
A Behavior Tree (ou Árvore de Comportamento) é um modelo para estruturar tomadas de decisão (Task Switching Structure), criado inicialmente para a área de robótica, mas também amplamente utilizado na indústria de jogos, para desenvolvimento da Inteligência Artificial das entidades dos games. 

## Vantagens da Behavior Tree

Dentre as vantagens de se utilizar uma árvore de comportamento em comparação a outros métodos de Task Switching Structure (como a Máquina de Estados, por exemplo), estão:  

- **Hierarquia:** Podemos criar quantas subárvores quisermos, detalhando o sistema; 
- **Modularidade:** Há pouca ou nenhuma dependência entre os componentes (subárvores, e folhas), de forma que eles podem ser utilizados e reaproveitados para diferentes aplicações; 
- **Flexibilidade:** Com a Árvore de Comportamentos, pode-se facilmente adicionar, retirar ou modificar Nós e Subárvores, tornando o sistema bastante flexível e maleável; 
- **Representação gráfica:** Todo o comportamento pode ser facilmente representado de forma gráfica, em uma estrutura de árvore, em que cada subárvore representa um “galho” da árvore principal, e cada Ação a ser tomada representa uma “folha” dessa árvore. Isso torna a Behavior Tree um método de simples compreensão e fácil desenvolvimento. 

Posteriormente será realizada uma comparação entre a Behavior Tree (BT) e a Finite State Machine (FSM), tornando essas vantagens mais evidentes.



