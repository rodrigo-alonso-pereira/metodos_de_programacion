//Escriba un programa en C que realice las siguientes acciones:
// Utilizando division y conquista, indique cual es el elemento
// mayor dentro de un arreglo desordenado (sin ordenar el arreglo).

#include <stdio.h>
#include <stdlib.h>

int mayor(int* arreglo, int inicial, int final){
	if(inicial == final){
		return arreglo[inicial];
	}
	int mitad;
	mitad = (inicial+final)/2;
	int mayor_izquierda, mayor_derecha;
	mayor_izquierda = mayor(arreglo, inicial, mitad);
	mayor_derecha = mayor(arreglo, mitad + 1, final);
	if (mayor_izquierda > mayor_derecha){
		return mayor_izquierda;
	}
	return mayor_derecha;
}

int main(){
	int n;
	printf("indique cuantos elementos va a ingresar: ");
	scanf("%d", &n);
	int* arreglo = (int*)malloc(sizeof(int)*n);
	int i;
	for (i = 0; i < n; i++){
		printf("Ingrese el %d numero:", i+1);
		scanf("%d",&arreglo[i]);
	}
	
	int max;
	max = mayor(arreglo,0,n-1);
	
	printf("el numero mayor es: %d", max);
	
	free(arreglo);
	
	return 0;
}