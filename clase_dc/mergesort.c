#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergesort(int* arreglo, int inicio, int fin) {

    if (inicio >= fin) {
        return;
    }

    //Division de listas
    int pivote = (inicio + fin) / 2;

    mergesort(arreglo, inicio, pivote);
    mergesort(arreglo, pivote + 1, fin);

    //Composicion de la lista.
    int i, j, k, a;
    int* aux = (int*)malloc(sizeof(int) * ((fin + 1)  - inicio)); //arreglo para guardar valores ordenados

    //i     j
    //2 3 4 6 3 1
    //Etapa de comparar elementos
    for (i = inicio, j = pivote + 1, k = 0; i <= pivote && j <= fin; k++) {
        if (arreglo[i] <= arreglo[j]) { //Compara elementos buscando menor
            aux[k] = arreglo[i]; //Se guarda en arreglo auxiliar arreglo[i]
            i++;
        } else {
            aux[k] = arreglo[j]; //Se guarda en arreglo auxiliar arreglo[j]
            j++;
        }

    }

    //Etapa de copiar toda la lista restante cuando la otra termino
    if (i > pivote) { //For paro pq se acabo la primera lista
        for (; j<= fin; j++, k++)
            aux[k] = arreglo[j];
    } else { //For paro que se acabo la segunda lista
        for (; i<= fin; i++, k++)
            aux[k] = arreglo[i];
    }

    //Etapa de copiar todos los elementos ordenados a lista original
    for (i = inicio, k = 0; i <= fin; i++, k++) { //Agregar lista ordenada a lista original, pero desde la posicion de inicio.
        arreglo[i] = aux[k];
    }

    //Visualizar avance lista
    printf("\n");
    for (a = 0; a <= fin; a++) {
        printf("%d ", arreglo[a]);
        if (a == 4) {
            printf("_|_ ");
        }
    }

    free(aux);
    return;
}

int main() {
    /*srand(time(NULL)); //Semilla segun hora
    int i, num = 10; //num es cantidad de elementos dentro del array
    int* arreglo = (int*)malloc(sizeof(int) * num);

    for (i = 0; i < num; i++) {
        arreglo[i] = rand() % 100; //Numeros aleatorios sin orden de 0 al 100
    }
    */
    int i, num = 10;
    int arreglo[10];
    arreglo[0] = 4;
    arreglo[1] = 5;
    arreglo[2] = 1;
    arreglo[3] = 2;
    arreglo[4] = 8;
    arreglo[5] = 6;
    arreglo[6] = 7;
    arreglo[7] = 4;
    arreglo[8] = 7;
    arreglo[9] = 9;
    //*********************************************************//

    printf("\n****** Numeros DESORDENADOS\n");

    for (i = 0; i < num; i++) {
        printf("%d ", arreglo[i]);
        if (i == 4) {
            printf("_|_ ");
        }
    }
    printf("\n\n");

    printf("\n****** PROCESO\n");
    mergesort(arreglo, 0, num - 1);

    printf("\n\n****** Numeros ORDENADOS\n");

    for (i = 0; i < num; i++)
        printf("%d ", arreglo[i]);
    printf("\n\n");

    //free(arreglo);

    printf("\n\n ************* FIN DEL PROGRAMA ************* \n");

    return 0;
}