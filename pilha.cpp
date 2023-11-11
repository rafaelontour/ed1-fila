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

    
void posfixa_simples(T_Pilha *plOutput, std::string exp, bool temParentese) {
    T_Pilha plOperadores;
    std::string pos_fixa = "";
    iniciarPilha(&plOperadores);
    T_Item item;
    char opAtual = 'p';

    printf("Notação posfixa: ");

    for (int i = 0;i < exp.length();i++) {
        item.campo = exp[i];

        switch (exp[i]) {
            case '0'...'9': 
                inserir(plOutput, item);
                if (i == (exp.length() - 1)) {
                    item.campo = plOperadores.dados[plOperadores.topo - 1].campo;
                    inserir(plOutput, item);
                    remover(&plOperadores);
                } 
                break;
            case MULT...DIV:    
                inserir(&plOperadores, item);
                break;
            case ')': 
                item.campo = plOperadores.dados[plOperadores.topo - 1].campo;
                inserir(plOutput, item);
                remover(&plOperadores);
                break;         
        } 
    } 
    item.campo = plOperadores.dados[plOperadores.topo - 1].campo;
    inserir(plOutput, item);
    remover(&plOperadores);
}

void calcular(T_PilhaFloat *plResult, bool temParentese, std::string exp) {

    if (temParentese) {
        T_Pilha plOperadores;
        iniciarPilha(&plOperadores);

        T_ItemFloat item;
        T_Item crt;
        std::string digito;
        char opAtual = ' ';

        for (int i = 0;i < exp.length();i++) {
            crt.campo = exp[i];
            switch (exp[i]) {
                case '0'...'9':
                    item.campo = float(crt.campo) - 48;
                
                    inserirFloat(plResult, item); // Vetor de números
                    
                    if (i == exp.length() - 1) {
                        if (opAtual == '+') {
                            item.campo = plResult -> dados[plResult -> topo - 1].campo;
                            item.campo += plResult -> dados[plResult -> topo - 2].campo;
                        }

                        if (opAtual == '-') {
                            item.campo = plResult -> dados[plResult -> topo - 2].campo;
                            item.campo -= plResult -> dados[plResult -> topo - 1].campo;
                        }

                        if (opAtual == '*') {
                            item.campo = plResult -> dados[plResult -> topo - 1].campo;
                            item.campo *= plResult -> dados[plResult -> topo - 2].campo;
                        }
                        if (opAtual == '/') {
                            item.campo = plResult -> dados[plResult -> topo - 2].campo;
                            item.campo /= plResult -> dados[plResult -> topo - 1].campo;
                        }

                        crt.campo = plOperadores.dados[plOperadores.topo - 1].campo;
                        
                        removerFloat(plResult);
                        removerFloat(plResult);

                        inserirFloat(plResult, item);
                    }
                    
                    break; 
               
                case MULT:
                    opAtual = '*';
                    crt.campo = opAtual;
                    inserir(&plOperadores, crt);
                    
                    break;
                case SOMA:
                    opAtual = '+';
                    crt.campo = opAtual;
                    inserir(&plOperadores, crt);
                    
                    break;
                case SUB:
                    opAtual = '-';
                    crt.campo = opAtual;
                    inserir(&plOperadores, crt);
                    
                    break;
                case DIV:
                    opAtual = '/';
                    crt.campo = opAtual;
                    inserir(&plOperadores, crt);
                    
                    break;
                case ')':
                    if (opAtual == '+') {
                        item.campo = plResult -> dados[plResult -> topo - 1].campo;
                        item.campo += plResult -> dados[plResult -> topo - 2].campo;
                    }
                    if (opAtual == '-') {
                        item.campo = plResult -> dados[plResult -> topo - 2].campo;
                        item.campo -= plResult -> dados[plResult -> topo - 1].campo;
                    }

                    if (opAtual == '*') {
                        item.campo = plResult -> dados[plResult -> topo - 1].campo;
                        item.campo *= plResult -> dados[plResult -> topo - 2].campo;
                    }
                    if (opAtual == '/') {
                        item.campo = plResult -> dados[plResult -> topo - 2].campo;
                        item.campo /= plResult -> dados[plResult -> topo - 1].campo;
                    }

                    removerFloat(plResult);
                    removerFloat(plResult);

                    inserirFloat(plResult, item); 
                    remover(&plOperadores);

                    opAtual = plOperadores.dados[plOperadores.topo - 1].campo;
                    break;
            } 
            
        } 

        for (int c = plResult->qtdeAtual - 1;c != 0;c--) {
            if (plResult -> qtdeAtual == 1) {
                break;
            }

            opAtual = plOperadores.dados[plOperadores.topo - 1].campo;
            if (opAtual == '+') {
                item.campo = plResult -> dados[plResult -> topo - 1].campo;
                item.campo += plResult -> dados[plResult -> topo - 2].campo;
            }
            if (opAtual == '-') {
                item.campo = plResult -> dados[plResult -> topo - 2].campo;
                item.campo -= plResult -> dados[plResult -> topo - 1].campo;
            }

            if (opAtual == '*') {
                item.campo = plResult -> dados[plResult -> topo - 1].campo;
                item.campo *= plResult -> dados[plResult -> topo - 2].campo;
            }
            if (opAtual == '/') {
                item.campo = plResult -> dados[plResult -> topo - 2].campo;
                item.campo /= plResult -> dados[plResult -> topo - 1].campo;
            }
            
            removerFloat(plResult);
            removerFloat(plResult);
            remover(&plOperadores);

            inserirFloat(plResult, item);
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
    bool temParentese = false;

    iniciarPilha(&pilha);

    std::string expressao; // A expressão a ser lida
    std::string digito = "";
    
    std::cout << "Digite a expressão: ";

    getline(std::cin, expressao);
    
    for (int c = 0;c < expressao.length();c++) {
        if (expressao[c] == '(') {
            temParentese = true;
            break;
        }

    }

    posfixa_simples(&pilha, expressao, temParentese);

    for (int c = 0;c < pilha.topo;c++) { // Imprimindo posfixa
        std::cout << pilha.dados[c].campo << ' ';
    }  

    printf("\n");

    T_PilhaFloat plResult;
    iniciarPilhaInt(&plResult);

    calcular(&plResult, temParentese, expressao);
    printf("\nResultado: ");
    std::cout << plResult.dados[plResult.base].campo << " ";

    printf("\n\n");

    return 0;
}