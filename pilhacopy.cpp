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
    
void posfixa_simples(T_Pilha *plOutput, std::string expressao, bool temParentese) {
    T_Pilha plOperadores;
    iniciarPilha(&plOperadores);
    T_Item item;


    if (temParentese) {
        for (int i = 0;i < expressao.length();i++) {
            item.campo = expressao[i];
        
            switch (expressao[i]) {
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

void calcular(T_Pilha *plOutput, T_PilhaFloat *plResult, bool temParentese,  std::string expressao, char exp[]) {

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
        bool chave = false;
        int k = 0;

        std::string digito = "";

        iniciarPilha(&plOperadores);
        int l = strlen(exp);

        // for (int a = 0, b = 0;a < expressao.length();a++) {
        //     if (isdigit(expressao[a])) {
        //         digito += expressao[a];
        //     } else {
        //         T_ItemFloat item;
        //         item.campo = stof(digito);
        //         inserirFloat(&plResult, item);

        //         digito = "";

        //         op[b] = expressao[a];
        //         b++;
        //     }
        // }


        for (int i = 0;i < expressao.length() - 1;i++) {
            crt.campo = expressao[i];

            // if (isdigit(crt.campo)) { // Se é dígito
            //     std::cout << crt.campo;
            //     ; // Concatena na string
                
            // } else {
            //     item.campo = stof(digito);
            //     inserirFloat(plResult, item);
            //     digito = "";
            // }

            //  34 * 26453

            switch (expressao[i]) {
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

                        std::cout << crt.campo;
                        digito += crt.campo;
                        if (i == expressao.length() - 1) {
                            item.campo = stof(digito);
                            inserirFloat(plResult, item);
                        }
                        
                    
                    break; 
                case MULT:

                    item.campo = stof(digito);
                    inserirFloat(plResult, item);

                    crt.campo = '*';
                    inserir(&plOperadores, crt);                    
                    digito = "";

                    break;
                case DIV:
                    item.campo = stof(digito);
                    inserirFloat(plResult, item);

                    crt.campo = '/';
                    inserir(&plOperadores, crt);
                    digito = "";

                    break;
                case SOMA:
                    
                    item.campo = stof(digito);
                    inserirFloat(plResult, item);

                    crt.campo = '+';
                    inserir(&plOperadores, crt);
                    
                    opAtual = 'M';
                    inserir(&plOperadores, crt);

                    digito = "";

                    break;
                case SUB:
                    item.campo = stof(digito);
                    inserirFloat(plResult, item);

                    crt.campo = '-';
                    inserir(&plOperadores, crt);
                    digito = "";
                    break;

            } 
            
            printf("\n");

            // if (i == l - 1) {
            //     T_ItemFloat res;
            //     int len = plResult -> qtdeAtual;
                
            //     for (int c = 1;c < len;c++) {
            //         if (plOperadores.dados[c - 1].campo == '+') {
            //             plResult -> dados[plResult -> base].campo += plResult -> dados[plResult -> base + c].campo;
            //         }
            //         if (plOperadores.dados[c - 1].campo == '-') {
            //             plResult -> dados[plResult -> base].campo -= plResult -> dados[c].campo;
            //         }
            //     }

            //     for (int o = 0;o < plResult -> qtdeAtual;o++) {
            //         removerFloat(plResult);
            //     }
                
            // } 
        } 
        for (int p = 0;p <= plResult->topo;p++) {
            std::cout << plResult->dados[p].campo << " - ";
        }
        printf("\n");
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

    exp[0] = '3';
    exp[1] = '-';
    exp[2] = '4';
    exp[3] = '/';
    exp[4] = '2';
    exp[5] = '*';
    exp[6] = '5';
    exp[7] = '-';
    exp[8] = '9';
    exp[9] = '/';
    exp[10] = '6';
    exp[11] = '-';
    exp[12] = '7';
    
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

    calcular(&pilha, &plResult, temParentese, expressao, exp);

    // std::cout << plResult.dados[0].campo << " ";

    printf("\n\n");

    return 0;
}