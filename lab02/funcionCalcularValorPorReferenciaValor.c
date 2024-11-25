#include <stdio.h>

// Paso por referencia
int cuadrado (int * a) {
  * a = *a * *a;
}

//Paso por valor
int cubo (int b) {
  b = b * b * b;
  return b;
}

//Paso por referencia
int absoluto (int * c) {
  if (*c <= 0) {
    * c = *c * -1;
  }
}

int main() {
  int numero;
  int opcion;
  
  do {
    
    printf("Seleccione una operacion: \n");
    printf("1. Valor Absoluto: \n");
    printf("2. Valor al cuadrado: \n");
    printf("3. Valor al cubo: \n");
    printf("4. Salir del programa. \n");
    printf("\nOpcion: ");
    scanf("%d", &opcion);
    
    if (opcion != 4) {
      printf("\nIngrese un numero: ");
      scanf("%d", &numero);
    }
    
    switch(opcion) {
      case 1:
      absoluto(&numero);
        printf("\nEl valor absoluto es: %d \n", numero);
        break;
      case 2:
        cuadrado(&numero);
        printf("El valor al cuadrado es: %d \n", numero);
        break;
      case 3:
        printf("El valor al cubo es: %d \n", cubo(numero));
        break;
    }
    printf("\n");
    
  } while(opcion != 4);
  
  printf("Hasta luego... \n");
  
  return 0;
}
