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

struct T_ItemFloat { // campo como int
	float campo;

	T_ItemFloat& operator =(float valor) {
		campo = valor;
		return *this;
	}

	// std::ostream& operator <<(std::ostream& os, T_PilhaFloat& index) {
	// 	os << "Valor: " << index.base;
	// 	return os;
	// }
};


struct T_Pilha { // Usando T_Item com campo do tipo char
	int base;
	int topo;
	int qtdeAtual;
	T_Item dados[max];

	T_Pilha& operator ==(char c) {
		char character = c;
		return *this;
	}
};

struct T_PilhaFloat { // Usando T_Item com campo do tipo int
	int base;
	int topo;
	int qtdeAtual;
	T_ItemFloat dados[max];

};

void iniciarPilha(T_Pilha *pilha) { // item.campo sendo char
	(*pilha).base = 0;
	(*pilha).topo = 0;
	(*pilha).qtdeAtual = 0;
}

void iniciarPilhaInt(T_PilhaFloat *pilha) { // item.campo sendo int
	(*pilha).base = 0;
	(*pilha).topo = 0;
	(*pilha).qtdeAtual = 0;
}

int chkPilhaVazia(T_Pilha *pilha) {
	return (*pilha).topo == 0;
}

int chkPilhaVazia(T_PilhaFloat *pilha) {
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

int inserirFloat(T_PilhaFloat *pilha, T_ItemFloat item) { // Usando item.campo como int
	int flag = 0;
	
	if ((*pilha).qtdeAtual < max) {
		(*pilha).dados[(*pilha).topo] = (float)item.campo;
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

float removerFloat(T_PilhaFloat *pilha) {
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