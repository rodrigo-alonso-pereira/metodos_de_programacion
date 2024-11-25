#include <stdio.h>

int funcRecursivoCola(int num, int resultado) {
	if (num <= 0) {
		return resultado;
	} else {
		int res = num % 10;
		num = num / 10;
		resultado = (resultado * 10) + res;

		return funcRecursivoCola(num, resultado);
	}
}

int funcIterativo(int num) {
	int res, numero_vuelta = 0;

	while (num > 0) {
		res = num % 10; //% entrega el resto
		num = num / 10;
		numero_vuelta = (numero_vuelta * 10) + res;
	}

	return numero_vuelta;
}

int main() {
	int num = 987654321, resultado;

	resultado = funcIterativo(num);
	printf("El numero original es: '%d' y queda: '%d'\n", num, resultado);

	resultado = funcRecursivoCola(num, 0);
	printf("El numero original es: '%d' y queda: '%d'\n", num, resultado);

	return 0;
}