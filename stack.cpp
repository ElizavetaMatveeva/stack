#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define L 10

// Написать программу, которая определяет, в правильном ли порядке располагаются скобки, находящиеся в стеке. В случае, если порядок неправильный, вывести номер позиции с ошибкой
struct stack;
void push(stack* stk, char ch); // Функция, помещающая значение на вершину стека
char pop(stack* stk); // функция, снимающая значение с вершины стека; возвращает значение с вершины стека 
char top(stack* stk); // функция, копирующая значение с вершины стека; возвращает значение с вершины стека
int full(stack* stk); // функция, проверяющая, заполнен ли стек; возвращает 1 или 0 (правда или ложь)
int empty(stack* stk); // функция, проверяющая, пуст ли стек; возвращает 1 или 0 (правда или ложь)
void reset(stack* stk); // функция, сбрасывающая индекс стека на начальное значение
int check(stack* stk, char* str, int* i); // Функция, проверяющая, есть ли ошибки в стеке, возвращает номер ошибки
char openBracket(char c); // Функция, возвращающая по закрывающей скобке парную ей открывающую
int isOpeningBracket(char c); // Функция, провряющая, является ли символ открывающей скобкой, возвращает 1 или 0 (правда или ложь)
int isClosingBracket(char c); // Функция, провряющая, является ли символ закрывающей скобкой, возвращает 1 или 0 (правда или ложь)
void printStk(stack* stk); // Функция печати остатка из стека
void printError(int er, int i); // Функция, выводящая ошибки

struct stack{ // Структура стек, состоящая из массива символов (скобок) и переменной, отвечающей за номер позиции элемента в стеке
	char s[L];
	int up;
};

void push(stack* stk, char ch){ // Функция, помещающая значение на вершину стека
	stk->s[++stk->up]=ch;
}

char pop(stack* stk){ // функция, снимающая значение с вершины стека
	return stk->s[stk->up--];
}

char top(stack* stk){ // функция, копирующая значение с вершины стека
	return stk->s[stk->up];
}

int full(stack* stk){ // функция, проверяющая, заполнен ли стек
	return stk->up==L-1;
}

int empty(stack* stk){ // функция, проверяющая, пуст ли стек
	return stk->up==-1;
}

void reset(stack* stk){ // функция, сбрасывающая индекс стека на начальное значение
	stk->up=-1;
}

void printError(int er, int i){ // Функция, выводящая ошибки
	switch(er){
		case 0: 
			printf("Everything is OK!"); // Нет ошибок
			break;
		case 1: 
			printf("Error! Brackets are of different types (position N %i) ", i); // Скобки непарные
			break;
		case 2: 
			printf("Error! Extra bracket (position N %i) ", i); // Лишняя скобка
			break;
		case 3: 
			printf("Error! There is no pair bracket (position N %i) ", i-1); // Не хватает парной скобки
			break;
		case 4: 
			printf("Error! Stack is full"); // Стек заполнен
	}
}

char openBracket(char c){ // Функция, возвращающая по закрывающей скобке парную ей открывающую
	switch (c){
		case ')': 
			return '('; 
		case ']': 
			return '[';
		case '}': 
			return '{';
	}	
}

int isOpeningBracket(char c){ // Функция, проверяющая, является ли символ открывающей скобкой
	return (c=='(' || c=='[' || c=='{');
}

int isClosingBracket(char c){ // Функция, провряющая, является ли символ закрывающей скобкой 
	return (c==')' || c==']' || c=='}');
}

void printStk(stack* stk){ // Функция печати остатка из стека
	printf("\nRest: ");
	while(!empty(stk)) 
		printf("%c", pop(stk));
}

int check(stack* stk, char* str, int* i){ // Проверка на наличие ошибок в расстановке скобок
	for(*i; str[*i]!='\0'; (*i)++){ // Цикл продолжается до тех пор, пока не закончится массив со скобками
		if (isOpeningBracket(str[*i])){
			if (full(stk))
				return 4; // Если стек полон, возвращается номер ошибки "полный стек"
			else	
				push(stk, str[*i]); // Если в стеке есть место, то на вершину кладётся открывающая скобка 
		}
		else {
			if(isClosingBracket(str[*i])){ // Если символ, взятый из массива, является закрывающей скобкой, то проводится сравнение
				if (!empty(stk)){ // Если стек не пустой, проводится сравнение вершины со скобкой, соответствующей закрывающей скобке из массива
					if (openBracket(str[*i])==top(stk)) // Если скобки парные, то с вершины снимается открывающая скобка
						pop(stk);
					else 
						return 1; // Если скобки непарные, то возвращается ошибка "непарная скобка"
				}
				else 
					return 2; // Возвращается номер ошибки "лишняя скобка"
			}
		}	
	}
	if (!empty(stk))
		return 3; // Если после всех проверок стек не пуст, возвращается код ошибки "не хватает парной скобки"
	else 
		return 0; // В случае, если стек пуст после проверки, возвращается 0, обозначающий отсутствие ошибок
}

int main(){
	stack my_stk;
	reset(&my_stk); // Переход на начало стека
	char str[]="({[]]))";
	int i=0;
	int error=check(&my_stk, str, &i); // Проверяется стек на наличие ошибок
	printError(error, i); // Выводится соответствующее сообщение
	if (!empty(&my_stk))
		printStk(&my_stk); // Выводятся символы, оставшиеся в стеке (для проверки)
	return 0;
}
