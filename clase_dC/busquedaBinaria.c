#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int busquedaBinariaRecursivo(int* arreglo, int inicio, int fin, int buscar) {
	printf("Inicio: %d, Fin: %d, buscar: %d\n", inicio, fin, buscar);
	if (inicio > fin) //Condicion cuando inicio supera en tamaño a fin -> arreglo vacio.
		return 0;

	if (inicio == fin) { //Hay solo un dato
		if (arreglo[inicio] == buscar)
			return 1;
		else
			return 0;
	} else {
		int mitad = (inicio + fin) / 2;
		printf("**** Flag: %d, evaluado en mitad: %d ****\n", mitad, arreglo[mitad]);
		if (arreglo[mitad] == buscar)
			return 1;
		else if (arreglo[mitad] < buscar) { //Esta en arreglo a la derecha
			inicio = mitad + 1; //Posicion inicio es mitad + 1
			return busquedaBinariaRecursivo(arreglo, inicio, fin, buscar);
		} else { //Esta en arreglo a la izquierda de mitad
			fin = mitad - 1; //Posicion fin es mitad - 1
			return busquedaBinariaRecursivo(arreglo, inicio, fin, buscar);
		}
	}

}

int main() {

    //Arreglo con elementos aleatorios
	srand(time(NULL)); //Semilla segun hora del PC
	int arreglo[100];

	int i, dato = rand() % 3; //datos: random modulo de 3 = 0
    printf("dato: %d\n", dato);
	for (i = 0; i < 100; i++) {
		dato = dato + rand() % 3; //Numeros aleatorios ordenados, empieza con 0, 1 o 2 y aumenta en esa proporcion
		arreglo[i] = dato;
	}

	//*********************************************************//
	int buscar = rand() % 100; //Valores entre 0 y 99
	printf("\n****** Numeros\n");

	for (i = 0; i < 100; i++) 
		printf("%d ", arreglo[i]);
	
	printf("\n\nNumero a buscar: %d\n", buscar);

	int encontrado = busquedaBinariaRecursivo(arreglo, 0, 99, buscar);
	encontrado == 1 ? printf("\nSI se ha encontrado el numero < %d >\n", buscar): printf("\nNO se ha encontrado el numero < %d >\n", buscar);

	printf("\n ************* FIN DEL PROGRAMA ************* \n");

}