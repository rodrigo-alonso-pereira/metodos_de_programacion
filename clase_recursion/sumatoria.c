#include <stdio.h>

/*
 * Caracteristicas:
 * 	Simple
 * 	Directa
 * 	No anidada
 * 	Cola
*/
int sumatoria_cola(int n, int resultado) {
	if (n == 0)
		return resultado;
	else 
		return sumatoria_cola(n - 1, resultado + n);
}

//Funcion auxiliar que conecta con sumatoria de cola
int sumatoria_real(int n) {
	return sumatoria_cola(n, 0);
}

/*
 * Caracteristicas:
 * 	Simple
 * 	Directa
 * 	No anidada
 * 	Stack
*/
int sumatoria_stack(int n) {
	if (n == 0) //Caso base
		return 0;
	else  //Caso recursivo
		return n + sumatoria_stack(n - 1);
}

int main() {

	printf("\n****************** INICIO DEL PROGRAMA ******************\n");

	int res = sumatoria_stack(5);
	printf("\nResultado Recursion Stack: %d\n", res);

	res = sumatoria_cola(5, 0);
	printf("\nResultado Recursion Cola: %d\n", res);

	res = sumatoria_real(5);
	printf("\nResultado Recursion Cola c/Sumatoria Real: %d\n", res);		

	printf("\n****************** FIN DEL PROGRAMA ******************\n");
	return 0;
} 