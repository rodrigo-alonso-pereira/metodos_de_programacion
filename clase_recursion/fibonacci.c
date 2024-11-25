#include <stdio.h>
#include <time.h>

// 0 1 1 2 3 5 8 13 21 
// 0 1 2 3 4 5 6  7  8

int fibonacciStack(int n) {
	
	if (n == 0) //Caso base 1
		return 0;
	else if (n == 1)  //Caso base 2
		return 1;
	else 
		return fibonacciStack(n - 1) + fibonacciStack(n - 2);
}

// 0 1 1 2 3 5 8 13 21 
// 0 1 2 3 4 5 6  7  8
int fibonacciIterativo(int n) {
	int anterior, anterior_anterior, resultado;

	if (n == 0 || n == 1)
		return n;

	anterior = 1;
	anterior_anterior = 0;
	resultado = 1;

	/*for (int i = 2; i < n; i++) {
		anterior_anterior = anterior;
		anterior = resultado;
		resultado = anterior + anterior_anterior;
	}*/

	int i = 2;
	while (i < n) {
		anterior_anterior = anterior;
		anterior = resultado;
		resultado = anterior + anterior_anterior;
		i++;
	}

	return resultado;
}

// 0 1 1 2 3 5 8 13 21 
// 0 1 2 3 4 5 6  7  8
int fibonacciCola(int n, int anterior, int anterior_anterior) {
	int actual;
	if (n == 0) 
		return anterior_anterior;
	else if (n == 1)
		return anterior;
	else
		actual = anterior + anterior_anterior;
		anterior_anterior = anterior;
		anterior = actual;
		return fibonacciCola(n - 1, anterior, anterior_anterior);
		
}

int main() {
	printf("\n****************** INICIO DEL PROGRAMA ******************\n");

	int i = 50, r1, r2, r3;
	time_t comienzo, final, comienzo_2, final_2, comienzo_3, final_3;

	comienzo = time(NULL);
	r1 = fibonacciStack(i);
	final = time(NULL);

	comienzo_2 = time(NULL);
	r2 = fibonacciIterativo(i);
	final_2 = time(NULL);

	comienzo_3 = time(NULL);
	r3 = fibonacciCola(i, 1, 0);
	final_3 = time(NULL);

	printf("\nResultado Fibonacci Recursivo_Stack: %d", r1);
	printf("\nTiempo algoritmo Recursivo_Stack: %f\n", difftime(final, comienzo));
	printf("\nResultado Fibonacci Iterativo: %d", r2);
	printf("\nTiempo algoritmo Iterativo: %f\n", difftime(final_2, comienzo_2));
	printf("\nResultado Fibonacci Recursivo_Cola: %d", r3);
	printf("\nTiempo algoritmo Recursivo_Cola: %f\n", difftime(final_3, comienzo_3));

	printf("\n****************** FIN DEL PROGRAMA ******************\n");
	return 0;
}