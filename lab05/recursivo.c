#include <stdio.h>

int contar_recursivo(int n){
	if(n == 0) {
		return 0;
	}
	return contar_recursivo(n-1) + 1;
}

// 1 1 1 2 3 5 8 13 21
// 0 1 2 3 4 5 6  7  8
int fib_pila(int n){
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return fib_pila(n-1) + fib_pila(n-2);
}

int fib_iterativo(int n) {
	int actual;
	int ant = 1;
	int ant_ant = 0;
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}

	int i;
	for (i = 2; i <= n; n++) {
		actual = ant + ant_ant;
		ant_ant = ant;
		ant = actual;
	}
	return actual;
}

int fib_cola(int n, int ant, int ant_ant) {
	int actual; 
	if (n == 0) {
		return ant_ant;
	} else if (n == 1) {
		return ant;
	} else
		actual = ant + ant_ant;
		ant_ant = ant;
		ant = actual;

		return fib_cola(n - 1, ant, ant_ant);

}

void main() {

	int i = 0;
	int n;
	int fib;

	while (i < 10) {
		scanf("%d", &n);
		fib = fib_pila(n);
		printf("Fibonacci recursivo de pila: %d \n", fib);
		fib = fib_iterativo(n);
		printf("Fibonacci iterativo: %d \n", fib);
		fib = fib_cola(n, 1, 0);
		printf("Fibonacci de cola: %d\n", fib);
	}

}