#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"


int lectura(char *** programa, int * push);
char ** crearStackInstrucciones(char ** programa,int instrucciones);
void escritura(int n);
void mostrarStack(char ** stack,int instrucciones,char *  mensaje);
void ejecutar(char ** programa, char ** stack, int instrucciones,  int push);


int lectura(char *** programa, int* push){
	printf("\n******** LECTURA ********\n");
	
	int instrucciones;
	FILE *archivoEntrada;
	
	archivoEntrada = fopen("stack.in","r");
	fscanf(archivoEntrada,"%d",&instrucciones);
	int i;
	char variable1[20];
	for (i=0;i<instrucciones;i++){
		fscanf(archivoEntrada,"%s",variable1);
		if (strcmp(variable1,"PUSH") == 0){
			instrucciones=instrucciones+1;	
			*push = *push + 1;
		}
	}
	fclose(archivoEntrada);

	
	archivoEntrada = fopen("stack.in","r");
	int variable2;
	fscanf(archivoEntrada,"%d",&variable2);
	
	*programa = (char **) malloc(sizeof(char *)*instrucciones);

	for (i=0;i<instrucciones;i++){

		(*programa)[i] = (char *) malloc(sizeof(char )*10);
		fscanf(archivoEntrada,"%s",(*programa)[i]);

	}	
	fclose(archivoEntrada);
	
	return instrucciones;
}

char ** crearStackInstrucciones(char ** programa,int instrucciones){
	
	char ** programaOrdenado;
	
	programaOrdenado = (char **) malloc(sizeof(char *)*instrucciones);
	
	int i;
	for (i=0;i<instrucciones;i++){
		if (strcmp(programa[i],"PUSH") == 0){
			programaOrdenado[instrucciones-(i+2)] = programa[i];	
			programaOrdenado[instrucciones-(i+1)] = programa[i+1];
			i++;
		}	
		else{
			programaOrdenado[instrucciones-(i+1)] = programa[i];
		}
	}

	
	return programaOrdenado;

}
	
void escritura(int n){
	
	FILE *archivoSalida;
	archivoSalida = fopen("Salida.out","w");
	fprintf(archivoSalida,"%d",n);
	fclose(archivoSalida);
	
}

void mostrarStack(char ** stack,int instrucciones,char *  mensaje){
	
	printf("\n******** %s ********\n",mensaje);
	
	int i;
	for (i=instrucciones-1;i >= 0;i--){
		if(i<9)
			printf("Registro 0%d: %s\n",i+1,stack[i]);
		else		
			printf("Registro %d: %s\n",i+1,stack[i]);

	}	
}

void ejecutar(char ** programa, char ** stack, int instrucciones,int push){
	int i;
	printf("\n************************************\n");
	printf("******** EJECUCION PROGRAMA ********\n");
	printf("************************************\n\n");
	
	int primero = 0;
	
	for(i = 0; i<instrucciones;i++){
		
		printf("\n_______________________________________________________________\n");
		
		if (strcmp(programa[i],"PUSH") == 0){
			printf("\nInstruccion: %s %s\n",programa[i],programa[i+1]);
		
			i++;
			PUSH(&primero,&stack, programa[i]);			
		}
		else if(strcmp(programa[i],"POP") == 0){
			printf("\nInstruccion: %s \n",programa[i]);
		
			POP(&primero, &stack);
		}
		else if(strcmp(programa[i],"SUM") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			SUM(&primero, &stack);
		}
		else if(strcmp(programa[i],"RES") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			RES(&primero, &stack);
		}
		else if(strcmp(programa[i],"MUL") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			MUL(&primero, &stack);
		}
		else if(strcmp(programa[i],"DIV") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			DIV(&primero, &stack);
		}
		else if(strcmp(programa[i],"MOD") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			MOD(&primero, &stack);
		}
		else if(strcmp(programa[i],"POT") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			POT(&primero, &stack);
		}
		else if(strcmp(programa[i],"EXP") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			EXP(&primero, &stack);
		}
		else if(strcmp(programa[i],"RAI") == 0){
			printf("\nInstruccion: %s \n",programa[i]);	
			RAI(&primero, &stack);
		}
		else{
			printf("\nInstruccion: %s (No se reconoce)\n",programa[i]);
		}	
		mostrarStack(stack,push,"STACK RESULTANTE");
	}
}

int main (){
	system("cls");
	printf("\n\n********************** INICIO DEL PROGRAMA **********************\n");

	
	int instrucciones;
	char ** programa; 
	int push =0;
	
	instrucciones = lectura(&programa,&push);
	


	printf("\n******** CREACION DEL STACK ********\n");
	
	char ** stack = (char **) malloc(sizeof(char *)*push);
	int i;
	for (i=0;i<push;i++){
		stack[i] = (char *) malloc(sizeof(char )*10);
		stack[i] = "";
	}	
	
	printf("\nExisten %d instrucciones PUSH en el programa...\n",push);
	printf("por lo que se creo un stack de %d espacios...\n",push);

	printf("\n******** PROGRAMA LEIDO ********\n");
	int j;
	for (i=0,j=1;i<instrucciones;i++,j++){
		if (strcmp(programa[i],"push") == 0){
			
		printf("instruccion %d: %s %s\n",j,programa[i],programa[i+1]);
		i++;
		}
		else 
			printf("instruccion %d: %s\n",j,programa[i]);

	}

	mostrarStack(stack,push,"STACK INICIAL");
	
	//Se ordenan las instrucciones del modo que seran ejecutadas
	programa = crearStackInstrucciones(programa,instrucciones);

	ejecutar(programa, stack, instrucciones,push);
		

	for(i=0;i<instrucciones;i++){
		free(programa[i]);
	
	}

	
	free(programa);
	free(stack);
	
	printf("\n\n********************** FIN DEL PROGRAMA **********************\n");
	
	return 0;

}
