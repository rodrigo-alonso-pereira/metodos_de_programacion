#include <stdio.h>

int funcion(int n) {
  n = n + 1;
  return n;
}

int main() {
  printf("\n\n******* Inicio del Programa *******\n\n");
  
  int valor1 = 0;
  
  printf("< int valor1 = 0 >\n");
  printf("valor1: %d \n\n", valor1);
  
  printf("< funcion(valor1) >\n");
  funcion(valor1);
  printf("valor1: %d \n\n", valor1);
  
  printf("< valor1 = funcion(valor1) >\n");
  valor1 = funcion(valor1);
  printf("valor1: %d", valor1);

  printf("\n\n******* Fin del Programa *******\n\n");
}
