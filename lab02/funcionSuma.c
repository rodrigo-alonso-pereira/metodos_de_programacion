#include<stdio.h>

int suma(int a, int b) {
  int resultado = a + b;
  return resultado;
}

int main() {
  int valor1, valor2;
  int resultadoSuma;
  printf("Ingrese el primer numero: ");
  scanf("%d", &valor1);
  
  printf("Ingrese el segundo numero: ");
  scanf("%d", &valor2);
  
  resultadoSuma = suma(valor1, valor2);
  
  printf("El valor de la suma de %d + %d es %d\n", valor1, valor2, resultadoSuma);
  
  return 0;
}
