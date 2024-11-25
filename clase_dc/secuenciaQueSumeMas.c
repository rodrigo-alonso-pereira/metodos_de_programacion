#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sumaMas(int* arreglo, int inicio, int fin) {
   if (inicio >= fin) {
       return arreglo[inicio];
   } else {
       int mitad = (inicio + fin) / 2;
       int r_i = sumaMas(arreglo, inicio, mitad);
       int r_d = sumaMas(arreglo, mitad + 1, fin);
       int suma = arreglo[mitad];
       int m_i = arreglo[mitad];
       int x = mitad - 1;

       while (x >= inicio) {
           suma = suma + arreglo[x];
           if (m_i < suma) {
               m_i = suma;
           }
           x--;
       }
       int c = m_i +
   }
}

int main() {

    srand(time(NULL)); //Semilla segun hora
    int i, num = 10;
    int* arreglo = (int*)malloc(sizeof(int) * num);

    for (i = 0; i < num; i++) {
        arreglo[i] = rand() % 100 - 50; //Numeros aleatorios sin orden
    }

    //*********************************************************//

    printf("\n****** Numeros DESORDENADOS\n");

    for (i = 0; i < num; i++)
        printf("%d ", arreglo[i]);
    printf("\n\n");

    printf("\n****** PROCESO\n");

    printf("\n\n****** Secuencia que suma mas\n");

    for (i = 0; i < num; i++)
        printf("%d ", arreglo[i]);
    printf("\n\n");
    free(arreglo);

    printf("\n\n ************* FIN DEL PROGRAMA ************* \n");

}