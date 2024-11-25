#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int* arreglo, int inicio, int fin) {
	//printf("Inicio: %d, fin: %d\n", inicio, fin);
	if (inicio >= fin) { //lista con un elemento o vacia
		return;
	} else {
		//Podria omitirse variable pivote y trabajar con arreglo[inicio]
        /*
        if (arreglo[inicio] < arreglo[fin] && arreglo[inicio] > arreglo[inicio + 1]) { //Busca elemento de valor central entre arreglo[inicio], arreglo[fin] y arreglo[inicio+1];
            int pivote = arreglo[inicio];
        } else if (arreglo[fin] > arreglo[inicio] && arreglo[fin] < arreglo[inicio + 1]){
            int pivote = arreglo[fin];
        } else {
            int pivote = arreglo[inicio + 1];
        }
        */
        int pivote = arreglo[inicio]; //Version sin optimizar
        int i, bandera = inicio;
		
		for (i = inicio + 1; i <= fin; i++){
			if (arreglo[i] < pivote) {
				int aux;
				aux = arreglo[bandera + 1]; //intercambiar valores
				arreglo[bandera + 1] = arreglo[i];
				arreglo[i] = aux;
				bandera++;
                //Visualizar avance lista
                printf("\n");
                for (int j = 0; j < fin; j++)
                    printf("%d ", arreglo[j]);
			}
            //printf("\nPivote: %d", pivote);
            //printf("\nbandera: [%d] = %d", bandera, arreglo[bandera]);
		}

		int aux2 = arreglo[inicio];
		arreglo[inicio] = arreglo[bandera];
		arreglo[bandera] = aux2;

		quickSort(arreglo, inicio, bandera - 1); //Ordena los que estan a la izquierda de bandera
		quickSort(arreglo, bandera + 1, fin); //Ordena los que estan a la derecha de bandera

		return;
	}
}

int main() {

	srand(time(NULL)); //Semilla segun hora
	int i, num = 10;
	int* arreglo = (int*)malloc(sizeof(int) * num);
	
	for (i = 0; i < num; i++) {
		arreglo[i] = rand() % 100; //Numeros aleatorios sin orden
	}

	//*********************************************************//
	
	printf("\n****** Numeros DESORDENADOS\n");

	for (i = 0; i < num; i++)
		printf("%d ", arreglo[i]);
    printf("\n\n");

    printf("\n****** PROCESO\n");
	quickSort(arreglo, 0, num - 1);

	printf("\n\n****** Numeros ORDENADOS\n");

	for (i = 0; i < num; i++)
		printf("%d ", arreglo[i]);
    printf("\n\n");
	free(arreglo);

	printf("\n\n ************* FIN DEL PROGRAMA ************* \n");

}