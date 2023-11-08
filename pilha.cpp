#include "tad_pilha_estatica.hpp"
#include <cstring>
#include <iostream>
#include <stdbool.h>
#include <vector>

enum Operacoes { 
    MULT='*', 
    SOMA='+', 
    SUB='-', 
    DIV='/' 
};
    
void posfixa_simples(T_Pilha *plOutput, char exp[], bool temParentese) {
    T_Pilha plOperadores;
    iniciarPilha(&plOperadores);
    T_Item item;


    if (temParentese) {
        for (int i = 0;i < strlen(exp);i++) {
            item.campo = exp[i];
        
            switch (exp[i]) {
                case '0'...'9': 
                    inserir(plOutput, item); // Vetor de números
                    break; 
                case MULT...DIV:
                    inserir(&plOperadores, item); // Vetor de operadores
                    break;
                case ')': 
                    inserir(plOutput, plOperadores.dados[plOperadores.topo-1]);
                    remover(&plOperadores);
                    break; 
                 
            } 
        }  
    } else {
        
    }
}

void calcular(T_Pilha *plOutput, T_PilhaFloat *plResult, bool temParentese, std::string exp) {

    if (temParentese) {
        for (int c = 0;c < plOutput->qtdeAtual;c++) {
            T_ItemFloat itemInt, res;
            
            T_Item item;

            item.campo = plOutput -> dados[c].campo;

            if (isdigit(item.campo)) {
                itemInt.campo = (int)item.campo - 48;
            }
        
            switch (item.campo) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':  
                    inserirFloat(plResult, itemInt);
                    break;
                case MULT:
                    res.campo = plResult -> dados[plResult -> topo - 1].campo;
                    removerFloat(plResult);
                    res.campo *= plResult -> dados[plResult->topo - 1].campo;
                    removerFloat(plResult);

                    inserirFloat(plResult, res);
                    break;
                case SOMA:
                    res.campo = plResult -> dados[plResult -> topo - 1].campo;
                    removerFloat(plResult);

                    res.campo += plResult -> dados[plResult -> topo - 1].campo;
                    removerFloat(plResult);

                    inserirFloat(plResult, res);
                    break; 
                case SUB:
                    res.campo = plResult -> dados[plResult->topo - 1].campo;
                    removerFloat(plResult);

                    res.campo -= plResult -> dados[plResult->topo - 1].campo;
                    removerFloat(plResult);

                    inserirFloat(plResult, res);
                    break; 
                case DIV:
                    res.campo = plResult -> dados[plResult->topo - 1].campo;
                    removerFloat(plResult);

                    res.campo /= plResult -> dados[plResult->topo - 1].campo;
                    removerFloat(plResult);

                    inserirFloat(plResult, res);
                    break;     

            }
        }
    } else { 
        
        char opAtual = 'p';
        T_Pilha plOperadores;
        T_ItemFloat item;
        T_Item crt;

        iniciarPilha(&plOperadores);

        for (int i = 0;i < exp.length();i++) {
            crt.campo = exp[i];

            if (isdigit(crt.campo)) {
                item.campo = (float)crt.campo - 48;
            }

            switch (crt.campo) {
                case '0':
                case '1': 
                case '2':
                case '3': 
                case '4':
                case '5': 
                case '6':
                case '7':
                case '8':
                case '9':  

                    inserirFloat(plResult, item); // Vetor de números

                    if (opAtual == '*') {
                        item.campo = plResult -> dados[plResult -> topo - 2].campo;
                        item.campo *= plResult -> dados[plResult->topo - 1].campo;

                        removerFloat(plResult);
                        removerFloat(plResult);

                        inserirFloat(plResult, item);
                    }
                    if (opAtual == '/') {
                        item.campo = plResult -> dados[plResult -> topo - 2].campo;
                        item.campo /= plResult -> dados[plResult -> topo - 1].campo;

                        removerFloat(plResult);
                        removerFloat(plResult);
                        
                        inserirFloat(plResult, item);
                    }
                    break; 
                case MULT:
                    opAtual = '*';
                    break;
                case DIV:
                    opAtual = '/';
                    break;
                case SOMA:
                    opAtual = 'p';
                    inserir(&plOperadores, crt);
                    break;
                case SUB:
                    opAtual = 'p';
                    inserir(&plOperadores, crt);
                    break;

            } 

            if (i == exp.length() - 1) {
                T_ItemFloat res;
                int len = plResult -> qtdeAtual;
                
                for (int c = 1;c < len;c++) {
                    if (plOperadores.dados[c - 1].campo == '+') {
                        plResult -> dados[plResult -> base].campo += plResult -> dados[plResult -> base + c].campo;
                    }
                    if (plOperadores.dados[c - 1].campo == '-') {
                        plResult -> dados[plResult -> base].campo -= plResult -> dados[c].campo;
                    }
                }

                for (int o = 0;o < plResult -> qtdeAtual;o++) {
                    removerFloat(plResult);
                }
                
            } 
        }  
    }
} 

int main() { 
    T_Pilha pilha;
    char exp[15];
    bool temParentese = false;

    iniciarPilha(&pilha);

    std::string expressao; // A expressão a ser lida
    std::string vetor[10]; // Vetor para os números
    std::string digito = "";
    char op[10]; // Vetor para operadores
    
    std::cout << "Digite a expressão: ";

    getline(std::cin, expressao);
    
    for (int c = 0;c < strlen(exp);c++) {
        if (exp[c] == '(') {
            temParentese = true;
            break;
        }

    }

    posfixa_simples(&pilha, exp, temParentese);

    for (int i = 0;i < pilha.topo;i++) {
        std::cout << pilha.dados[i].campo << " ";
    }

    printf("\nResultado: ");
    T_PilhaFloat plResult;
    iniciarPilhaInt(&plResult);

    calcular(&pilha, &plResult, temParentese, expressao);

    std::cout << plResult.dados[0].campo << " ";

    printf("\n\n");

    return 0;
}