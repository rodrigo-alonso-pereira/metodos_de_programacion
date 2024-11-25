#include <stdio.h>
#include <stdlib.h>
//linda.munoz@usach.cl

void imprimir_arreglo () {

}

int busqueda_binaria_indice(int* arreglo, int inicio, int fin, int numero_buscado) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		if (arreglo[0] == numero_buscado) {
			return 1;
		}
		return 0;
	} else if (arreglo[inicio] == numero_buscado) {
		return 1;
	} else if (arreglo[inicio] > numero_buscado) {
		if (inicio < (fin-inicio)/2) {
			inicio++;
		}
		return busqueda_binaria_indice(arreglo, inicio, fin, numero_buscado);
	} else if (arreglo[fin] < numero_buscado) {
		if (fin > (fin-inicio)/2) {
			fin--;
		}
		return busqueda_binaria_indice(arreglo, inicio, fin, numero_buscado)
	}
}

int busqueda_binaria(int* arreglo, int numero_buscado, int n) {
	printf("mitad: %d\n", n/2);
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		if (arreglo[0] == numero_buscado) {
			return 1;
		}
		return 0;
	} else if (arreglo[n/2] == numero_buscado) {
		return 1;
	} else if (arreglo[n/2] < numero_buscado) {
		int* arreglo_der = (int*)malloc(sizeof(int) * n/2 - 1);
		int i;
		int j;
		for (i = n/2 + 1; i < n; ++i) {
			arreglo_der[j] = arreglo[i];
			j++;
		}
		return busqueda_binaria(arreglo_der, numero_buscado, n/2);
	} else if (arreglo[n/2] > numero_buscado) {
		int* arreglo_izq = (int*)malloc(sizeof(int) * (n/2 + 1));
		int i;
		for (i = 0; i < n/2; ++i) {
			arreglo_izq[i] = arreglo[i];
		}
		return busqueda_binaria(arreglo_izq, numero_buscado, n/2);
	}

}

int main() {
	
int * arreglo = (int*)malloc(sizeof(int) * 10);
int i;
for (i = 0; i < 10; ++i) { //L = [1,2,3,4,5,6,7,8,9,10]
	arreglo[i] = i + 1;
}

int numero_buscado;
printf("Que numero desea buscar\n");
scanf("%d", &numero_buscado);

int resultado = busqueda_binaria_indice(arreglo, 0, 9);
if (resultado == 0) {
	printf("El numero buscado %d, no se encuentra en el arreglo\n", numero_buscado);
} else {
	printf("El numero buscado %d, se encuentra en el arreglo\n", numero_buscado);
}

/*int resultado = busqueda_binaria(arreglo, numero_buscado, 10);
if (resultado == 0) {
	printf("El numero buscado %d, no se encuentra en el arreglo\n", numero_buscado);
} else {
	printf("El numero buscado %d, se encuentra en el arreglo\n", numero_buscado);
}*/

return 0;
}