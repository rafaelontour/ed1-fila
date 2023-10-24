#include "tad_pilha_estatica.hpp"
#include <cstring>
#include <iostream>

enum Operacoes { 
    MULT='*', 
    SOMA='+', 
    SUB='-', 
    DIV='/' 
};
    
void posfixa_simples(T_Pilha *plOutput, char exp[]) {
    T_Pilha plOperadores;
    iniciarPilha(&plOperadores);
    T_Item item;
    
    for (int i = 0;i < strlen(exp);i++) {
        item.campo = exp[i];
        switch (exp[i]) {
            case '0'...'9': 
                inserir(plOutput, item);
                break; 
            case MULT...DIV:
                inserir(&plOperadores, item);
                break;
            case ')': {
                inserir(plOutput, plOperadores.dados[plOperadores.topo-1]);
                remover(&plOperadores);
                break; 
            } 
        } 
    }  
}

void calcular(T_Pilha *plOutput, T_PilhaInt *plResult) {
    for (int c = 0;c < plOutput->qtdeAtual;c++) {
        T_ItemInt itemInt, res;
        
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
                inserirInt(plResult, itemInt);
                break;
            case MULT:
                res.campo = plResult -> dados[plResult -> topo - 1].campo;
                res.campo *= (int)plResult -> dados[plResult->topo - 2].campo;
                removerInt(plResult);
                removerInt(plResult);
                inserirInt(plResult, res);
                break;
            case SOMA:
                res.campo = plResult -> dados[plResult -> topo - 1].campo;
                res.campo += (int)plResult -> dados[plResult -> topo - 2].campo;
                removerInt(plResult);
                removerInt(plResult);
                inserirInt(plResult, res);
                break; 
            case SUB:
                res.campo = plResult -> dados[plResult->topo - 1].campo;
                res.campo -= (int)plResult -> dados[plResult->topo - 2].campo;
                removerInt(plResult);
                removerInt(plResult);
                inserirInt(plResult, res);
                break; 
            case DIV:
                res.campo = plResult -> dados[plResult->topo - 1].campo;
                res.campo /= (int)plResult -> dados[plResult->topo - 2].campo;
                removerInt(plResult);
                removerInt(plResult);
                inserirInt(plResult, res);
                break;     

        }
    }
}

int main() {
    T_Pilha pilha;
    char exp[5];

    iniciarPilha(&pilha);

    exp[0] = '(';
    exp[1] = '3';
    exp[2] = '+';
    exp[3] = '(';
    exp[4] = '7';
    exp[5] = '*';
    exp[6] = '4';
    exp[7] = ')';
    exp[8] = ')';

    posfixa_simples(&pilha, exp);

    for (int i = 0;i < strlen(exp);i++) {
        std::cout << pilha.dados[i].campo << " ";
    }

    printf("Resultado da soma: \n\n");
    T_PilhaInt plResult;
    iniciarPilhaInt(&plResult);

    calcular(&pilha, &plResult);

    for (int i = 0;i < plResult.qtdeAtual;i++) {
        std::cout << plResult.dados[i].campo << " ";
    }

    return 0;
}