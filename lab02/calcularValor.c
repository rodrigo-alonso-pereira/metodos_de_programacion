#include <stdio.h>

int main() {
  int numero;
  int opcion;
  
  do {
    printf("Ingrese un numero: ");
    scanf("%d", &numero);
    
    printf("Seleccione una operacion: \n");
    printf("1. Valor Absoluto: \n");
    printf("2. Valor al cuadrado: \n");
    printf("3. Valor al cubo: \n");
    printf("4. Salir del programa \n");
    scanf("%d", &opcion);
    
    switch(opcion) {
      case 1:
        numero >= 0 ? printf("El valor absoluto es: %d \n", numero) : printf("El valor absoluto es: %d \n", numero*-1);
        break;
      case 2:
        printf("El valor al cuadrado es: %d\n", numero*numero);
        break;
      case 3:
        printf("El valor al cubo es: %d \n", numero*numero*numero);
        break;
    }
    printf("\n");
    
  } while(opcion != 4);
  
  printf("\n");
  printf("Hasta luego... \n");
  
  return 0;
}
