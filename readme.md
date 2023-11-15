Descrição do Jogo
O programa implementa uma versão simplificada do famoso quebra-cabeça Torre de Hanói em C++. O objetivo do jogo é mover uma série de discos coloridos entre três tubos, de modo a organizar os discos em um dos tubos de destino. Os discos podem ser movidos de um tubo para outro, seguindo duas regras básicas:

Apenas um disco pode ser movido por vez.
Um disco só pode ser colocado sobre outro se for menor em diâmetro.
Os tubos são representados por barras verticais, e os discos são representados por letras 'O' coloridas. O jogador escolhe o tubo de origem e destino para cada movimento. O jogo termina quando todos os discos estão empilhados no tubo de destino na ordem correta.

Compilação e Execução
Certifique-se de ter um compilador C++ instalado em seu sistema. Você pode compilar e executar o programa usando os seguintes comandos:

bash
Copy code
g++ nome_do_programa.cpp -o nome_do_programa
./nome_do_programa
Substitua nome_do_programa pelo nome que você deseja dar ao executável.

Controles do Jogo
O jogo solicitará que você escolha um tubo de origem e um tubo de destino para cada movimento. Digite o número correspondente ao tubo desejado quando solicitado. Se desejar sair do jogo a qualquer momento, insira -1 como escolha de tubo, e o jogo será encerrado.

Observações
O programa usa cores no console para diferenciar os discos.
O jogo exibe uma mensagem de vitória quando todos os discos estão empilhados corretamente.
O jogador pode optar por jogar novamente após a conclusão do jogo.