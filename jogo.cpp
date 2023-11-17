//Bruna Barbour Fernandes 23007950
//João Victor Francetto Xavier 23003634

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

#define TAM 6
#define cores 5
#define elemento_cor 5

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
    int cores_disponiveis[cores];
    for (int i = 0; i < cores; ++i) {
        cores_disponiveis[i] = elemento_cor;
    }

    for (int i = 0; i < TAM - 1; ++i) {
        for (int j = 0; j < elemento_cor; ++j) {
            int cor = rand() % cores;
            while (cores_disponiveis[cor] == 0) {
                cor = rand() % cores;
            }
            push(T[i].pilha, cor + 1);
            T[i].numero_elementos++;
            cores_disponiveis[cor]--;
        }
    }
}

void mudacor(int cor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void printa_cor(int cor, char c) {
    mudacor(cor);
    cout << c;
    mudacor(15);
}

void mostrar(Tubo T[]) {
    system("cls");
    cout << "BEM VINDO!" << endl;
    cout << "______________________________________" << endl;
    cout << endl;

    for (int i = elemento_cor - 1; i >= 0; --i) {
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

    for (int i = 1; i <= TAM; ++i) {
        cout << "  " << i << "   ";
    }
    cout << endl << endl;
}

int validar(Tubo T[], int o, int d) {
    if (isEmpty(T[o - 1].pilha)) {
        cout << "Origem vazia! Escolha outra." << endl;
        return 0;
    }

    if (T[d - 1].numero_elementos < elemento_cor) {
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
            return 1;
        }
    }

    return 1;
}

int jogada(Tubo T[]) {
    int o, d;

    do {
        cout << "Escolha um tubo de origem (1-" << TAM << ") ou digite -1 para sair: ";
        cin >> o;
        if (o == -1) {
            return 0;
        }

        cout << "Escolha um tubo de destino (1-" << TAM << ") ou digite -1 para sair: ";
        cin >> d;

        if (d == -1) {
            return 0;
        }
        if (o < 1 || o > TAM || d < 1 || d > TAM) {
            cout << "Tubo de origem ou destino inválido! Escolha outra." << endl;
        }
    } while (o < 1 || o > TAM || d < 1 || d > TAM);

    if (!isEmpty(T[o - 1].pilha) && validar(T, o, d)) {
        stack_element elementoT = peek(T[o - 1].pilha);
        push(T[d - 1].pilha, elementoT);
        T[d - 1].numero_elementos++;
        pop(T[o - 1].pilha);
        T[o - 1].numero_elementos--;
        return 1;
    } else {
        return 1;
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

            if (retorno == 0) {
                break;
            }

            mostrar(T);
        } while (retorno);

        if (retorno == 0) {
            break;
        }

        if (validar_fim(T)) {
            cout << "Parabéns! Você venceu!" << endl;
            break;
        }

        cout << "Deseja jogar novamente? 1 SIM ou 0 NÃO: ";
        cin >> repetir;

        if (repetir == 0) {
            break;
        }

        inicia_vazias(T);
        distribuir_tubo(T);
        mostrar(T);

    } while (repetir);

    cout << "Fim de jogo! Obrigado por jogar!" << endl;

    return 0;
}
