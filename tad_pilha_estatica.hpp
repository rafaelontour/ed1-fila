#include <stdio.h>
#include <iostream>

int const max = 10;

struct T_Item { // campo como char
	char campo;

	T_Item& operator =(char c) {
		char character;
		character = c;
		return *this;
	}

};

struct T_ItemInt { // campo como int
	int campo;

	T_ItemInt& operator =(int valor) {
		campo = valor;
		return *this;
	}

};


struct T_Pilha { // Usando T_Item com campo do tipo char
	int base;
	int topo;
	int qtdeAtual;
	T_Item dados[max];
};

struct T_PilhaInt { // Usando T_Item com campo do tipo int
	int base;
	int topo;
	int qtdeAtual;
	T_ItemInt dados[max];


};

void iniciarPilha(T_Pilha *pilha) { // item.campo sendo char
	(*pilha).base = 0;
	(*pilha).topo = 0;
	(*pilha).qtdeAtual = 0;
}

void iniciarPilhaInt(T_PilhaInt *pilha) { // item.campo sendo int
	(*pilha).base = 0;
	(*pilha).topo = 0;
	(*pilha).qtdeAtual = 0;
}

int chkPilhaVazia(T_Pilha *pilha) {
	return (*pilha).topo == 0;
}

int chkPilhaVazia(T_PilhaInt *pilha) {
	return (*pilha).topo == 0;
}


int inserir(T_Pilha *pilha, T_Item item) { // Usando item.campo como char
	int flag = 0;
	
	if ((*pilha).qtdeAtual < max) {
		(*pilha).dados[(*pilha).topo] = item;
		(*pilha).topo++;
		(*pilha).qtdeAtual++;
		flag = 1;
	}
		
	return flag;	
}

int inserirInt(T_PilhaInt *pilha, T_ItemInt item) { // Usando item.campo como int
	int flag = 0;
	
	if ((*pilha).qtdeAtual < max) {
		(*pilha).dados[(*pilha).topo] = (int)item.campo;
		(*pilha).topo++;
		(*pilha).qtdeAtual++;
		flag = 1;
	}
		
	return flag;	
}

int remover(T_Pilha *pilha) {
	int flag;
	
	if (chkPilhaVazia(pilha) )
		flag = 0;
	else
	{
		(*pilha).topo--;
		(*pilha).qtdeAtual--;
		
		flag = 1;
	}
	
	return flag;
}

int removerInt(T_PilhaInt *pilha) {
	int flag;
	
	if (chkPilhaVazia(pilha) )
		flag = 0;
	else
	{
		(*pilha).topo--;
		(*pilha).qtdeAtual--;
		
		flag = 1;
	}
	
	return flag;
}