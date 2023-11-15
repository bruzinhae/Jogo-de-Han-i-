#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

#define TAM 6

typedef int stack_element;

#include "stack.h"

typedef struct {
    int numero_elementos;
    Stack pilha;
} Tubo;

struct stack {
    int top;
    stack_element local[TAM];
};

void inicia_vazias(Tubo T[]) {
    for (int i = 0; i < TAM; ++i) {
        T[i].numero_elementos = 0;
        initStack(T[i].pilha);
    }
}

void distribuir_tubo(Tubo T[]) {
    srand(time(0));

    // Distribuir os 30 "O"s pelos 6 tubos de forma aleatória
    for (int i = 0; i < 30; ++i) {
        int tubo = rand() % TAM;
        int valor = i % 5 + 1;   // Alternar entre as 5 cores

        push(T[tubo].pilha, valor);
        T[tubo].numero_elementos++;
    }
}

void mudacor(int cor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void printa_cor(int cor, char c) {
    mudacor(cor);
    cout << c;
    mudacor(15); // Restaurar a cor padrão
}

void mostrar(Tubo T[]) {
    // Imprimir o número do tubo referente e espaço entre eles
    for (int i = 1; i <= TAM; ++i) {
        cout << "  " << i << "   ";
    }
    cout << endl;

    for (int i = TAM - 1; i >= 0; --i) {
        for (int j = 0; j < TAM; ++j) {
            cout << "| ";

            if (i < T[j].pilha.top + 1) {
                int valor = T[j].pilha.local[i];
                int cor = 10 + valor;
                printa_cor(cor, 'O');
            } else {
                cout << " ";
            }

            cout << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

int validar(Tubo T[], int o, int d) {
    if (isEmpty(T[o - 1].pilha)) {
        cout << "Origem vazia! Escolha outra." << endl;
        return 0;
    }

    if (T[d - 1].numero_elementos < TAM) {
        return 1;
    } else {
        cout << "Destino cheio! Escolha outro tubo." << endl;
        return 0;
    }
}

int validar_fim(Tubo T[]) {
    int cor_topo = -1;

    for (int i = 0; i < TAM; ++i) {
        if (!isEmpty(T[i].pilha)) {
            int cor = T[i].pilha.local[T[i].pilha.top];
            if (cor_topo == -1) {
                cor_topo = cor;
            } else if (cor_topo != cor) {
                return 0;
            }
        } else {
            return 0;
        }
    }

    return 1;
}

int jogada(Tubo T[]) {
    int origem, destino;

    do {
        cout << "Escolha um tubo de origem (1-" << TAM << ") ou digite -1 para sair: ";
        cin >> origem;

        // Verifica se o usuário quer sair
        if (origem == -1) {
            return 0; // Sair do jogo
        }

        cout << "Escolha um tubo de destino (1-" << TAM << ") ou digite -1 para sair: ";
        cin >> destino;

        // Verifica se o usuário quer sair
        if (destino == -1) {
            return 0; // Sair do jogo
        }

        // Verifica se a origem e o destino estão dentro do intervalo válido
        if (origem < 1 || origem > TAM || destino < 1 || destino > TAM) {
            cout << "Tubo de origem ou destino inválido! Escolha outra." << endl;
        }
    } while (origem < 1 || origem > TAM || destino < 1 || destino > TAM);

    // Verifica se a origem não está vazia e se a jogada é válida
    if (!isEmpty(T[origem - 1].pilha) && validar(T, origem, destino)) {
        // Armazena temporariamente o primeiro elemento que será movido
        stack_element elementoTemporario = peek(T[origem - 1].pilha);

        // Mover o elemento temporário para a nova pilha do destino
        push(T[destino - 1].pilha, elementoTemporario);
        T[destino - 1].numero_elementos++;

        // Remove o primeiro elemento da pilha de origem
        pop(T[origem - 1].pilha);
        T[origem - 1].numero_elementos--;

        if (validar_fim(T)) {
            return 0; // Fim do jogo
        }
        return 1; // Continua o jogo
    } else {
        return 1; // Continua o jogo
    }
}

int main() {
    Tubo T[TAM];
    int repetir = 1, retorno;

    inicia_vazias(T);
    distribuir_tubo(T);
    mostrar(T);

    do {
        do {
            retorno = jogada(T);

            // Verifica se o usuário escolheu sair (-1)
            if (retorno == 0) {
                break; // Sair do loop interno
            }

            mostrar(T);
        } while (retorno);

        // Verifica se o usuário escolheu sair (-1)
        if (retorno == 0) {
            break; // Sair do loop externo
        }

        cout << "Parabéns! Você venceu!" << endl;
        cout << "Deseja jogar novamente? 1 SIM ou 0 NÃO: ";
        cin >> repetir;

        // Verifica se o usuário escolheu sair (-1)
        if (repetir == 0) {
            break; // Sair do loop externo
        }

        inicia_vazias(T);
        distribuir_tubo(T);
        mostrar(T);

    } while (repetir);

    cout << "Fim de jogo! Obrigado por jogar!" << endl;

    return 0;
}
