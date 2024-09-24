#include <iostream>
#include <cstring>
#include "Pilha.h"

using namespace std;

// Função que valida uma expressão matemática
bool validarExpressao(char* expressao) {
    // Inicializa uma pilha vazia
    Pilha_Construtor();

    for (int i = 0; i < strlen(expressao); i++) {
        char simbolo = expressao[i];

        // Adiciona símbolo de abertura à pilha
        if (simbolo == '(' || simbolo == '[') {
            Pilha_Empilhar(simbolo);
        }
        // Para símbolo de fechamento, verifica a pilha
        else if (simbolo == ')' || simbolo == ']') {
            if (Pilha_Vazia()) {
                Pilha_Destrutor(); // Libera memória
                return false; // Expressão inválida
            }

            TipoDado topoElemento;
            if (!Pilha_Topo(topoElemento)) {
                Pilha_Destrutor(); // Libera memória
                return false; // Expressão inválida
            }

            // Confere se o fechamento combina com o que está no topo da pilha
            if ((simbolo == ')' && topoElemento != '(') || (simbolo == ']' && topoElemento != '[')) {
                Pilha_Destrutor(); // Libera memória
                return false; // Expressão inválida
            }

            // Remove o símbolo de abertura da pilha
            Pilha_Desempilhar(topoElemento);
        }
    }

    // Retorna verdadeiro se a pilha estiver vazia no final
    bool resultado = Pilha_Vazia();
    Pilha_Destrutor(); // Libera memória
    return resultado;
}

int main() {
    char expressao[100];
    cout << "Digite uma expressao matematica: ";
    cin.getline(expressao, 100);

    if (validarExpressao(expressao)) {
        cout << "A expressao e valida." << endl;
    } else {
        cout << "A expressao nao e valida." << endl;
    }

    return 0;
}

#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef char TipoDado;

// Estrutura de uma célula da pilha
struct TipoCelula {
    TipoDado Item;
    TipoCelula* Prox;
};

// Prototipos das funções da pilha
bool Pilha_Vazia();
int Pilha_Tamanho();
bool Pilha_Empilhar(TipoDado Elemento);
bool Pilha_Desempilhar(TipoDado& Elemento);
bool Pilha_Topo(TipoDado& Elemento);
void Pilha_Construtor();
void Pilha_Destrutor();

#endif // PILHA_H_INCLUDED

// Pilha.cpp
#include "Pilha.h"

// Ponteiro para o topo da pilha
TipoCelula* TopoPilha = nullptr;
int ContadorElementos = 0;

// Inicializa a pilha
void Pilha_Construtor() {
    TopoPilha = nullptr;
    ContadorElementos = 0;
}

// Libera a pilha da memória
void Pilha_Destrutor() {
    while (TopoPilha != nullptr) {
        TipoCelula* CelulaTemp = TopoPilha;
        TopoPilha = TopoPilha->Prox;
        free(CelulaTemp); // Libera a célula
    }
    ContadorElementos = 0;
}

// Checa se a pilha está vazia
bool Pilha_Vazia() {
    return TopoPilha == nullptr;
}

// Retorna a quantidade de itens na pilha
int Pilha_Tamanho() {
    return ContadorElementos;
}

// Adiciona um elemento na pilha
bool Pilha_Empilhar(TipoDado Elemento) {
    TipoCelula* NovaCelula = (TipoCelula*) malloc(sizeof(TipoCelula));
    if (NovaCelula == nullptr) {
        return false; // Falha na alocação
    }
    NovaCelula->Item = Elemento;
    NovaCelula->Prox = TopoPilha;
    TopoPilha = NovaCelula;
    ContadorElementos++;
    return true;
}

// Remove um elemento da pilha
bool Pilha_Desempilhar(TipoDado& Elemento) {
    if (Pilha_Vazia()) {
        return false; // Pilha vazia
    }
    TipoCelula* CelulaTemp = TopoPilha;
    TopoPilha = TopoPilha->Prox;
    Elemento = CelulaTemp->Item;
    free(CelulaTemp); // Libera a célula
    ContadorElementos--;
    return true;
}

// Retorna o elemento do topo da pilha
bool Pilha_Topo(TipoDado& Elemento) {
    if (Pilha_Vazia()) {
        return false; // Pilha vazia
    }
    Elemento = TopoPilha->Item;
    return true;
}
