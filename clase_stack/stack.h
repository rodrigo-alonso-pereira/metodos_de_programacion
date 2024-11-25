#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void PUSH(int * primero, char *** stack, char * dato);
char * POP(int *primero, char *** stack);
void SUM (int *primero, char *** stack);
void RES (int *primero, char *** stack);
void MUL (int *primero, char *** stack);
void DIV (int *primero, char *** stack);
void MOD (int *primero, char *** stack);
void RAI (int *primero, char *** stack);
void EXP (int *primero, char *** stack);
void POT (int *primero, char *** stack);

void PUSH(int * primero, char *** stack, char * dato){	

	(*stack)[(*primero)] = dato; 
	*primero = * primero + 1;
}

char * POP(int *primero, char *** stack){
	int n = *primero;
	*primero = *primero - 1;
	char * dato = (*stack)[n-1];
	(*stack)[n-1] = "";
	return dato;
}

void SUM (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	char * n2 = POP(primero, stack);
	
	int num1 = atoi(n1);
	int num2 = atoi(n2);
	

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( num1 +  num2 , suma , 10 ) ;

        sprintf(suma,"%d",num1+num2);
	PUSH(primero,stack,suma);
	
}

void RES (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	char * n2 = POP(primero, stack);
	
	int num1 = atoi(n1);
	int num2 = atoi(n2);
	

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( num1 -  num2 , suma , 10 ) ;

        sprintf(suma,"%d",num1-num2);
	PUSH(primero,stack,suma);
	
}

void MUL (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	char * n2 = POP(primero, stack);
	
	int num1 = atoi(n1);
	int num2 = atoi(n2);
	

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( num1 *  num2 , suma , 10 ) ;

        sprintf(suma,"%d",num1*num2);
	PUSH(primero,stack,suma);
	
}

void DIV (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	char * n2 = POP(primero, stack);
	
	int num1 = atoi(n1);
	int num2 = atoi(n2);
	

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( num1 /  num2 , suma , 10 ) ;

        sprintf(suma,"%d",num1/num2);
	PUSH(primero,stack,suma);
	
}

void MOD (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	char * n2 = POP(primero, stack);
	
	int num1 = atoi(n1);
	int num2 = atoi(n2);
	

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( num1 %  num2 , suma , 10 ) ;

        sprintf(suma,"%d",num1%num2);
	PUSH(primero,stack,suma);
}

void RAI (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	
	int num1 = atoi(n1);

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( sqrt(num1) , suma , 10 ) ;

        sprintf(suma,"%f",sqrt(num1));
	PUSH(primero,stack,suma);
}

void EXP (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	
	int num1 = atoi(n1);

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( exp(num1) , suma , 10 ) ;
        sprintf(suma,"%f",exp(num1));

	PUSH(primero,stack,suma);
}

void POT (int *primero, char *** stack){
	
	char * n1 = POP(primero, stack);
	char * n2 = POP(primero, stack);
	
	int num1 = atoi(n1);
	int num2 = atoi(n2);
	

	char * suma = (char *) malloc(sizeof(char)*20); 
	//itoa ( pow(num1,  num2) , suma , 10 ) ;
        sprintf(suma,"%f",pow(num1,num2));

	PUSH(primero,stack,suma);
}
