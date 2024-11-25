#include <stdio.h>



int heladosRecursivoStack(int cant) {
	int helados = 0;
	if (cant <= 2)
		return 0;
	else if (cant == 3)
		return 1;
	else {
		cant = cant - 3;
		cant++;
		helados++;
		return helados + heladosRecursivoStack(cant);
	}
}


int heladosRecursivoCola(int cant, int helados) {
	//printf("cant: %d, helados: %d\n", cant, helados);
	if (cant == 3){
		helados++;
		return helados;
	} else {
		cant = cant - 3;
		cant++;
		helados++;
		if (cant < 3) 
			return helados;
		else 
			return heladosRecursivoCola(cant, helados);
	}
}

int heladosIterativo(int cant) {
	int helados = 0;

	if (cant == 3)
		return 1;
	else if (cant <= 2)
		return 0;

	while(cant > 0) {
		cant = cant - 3;
		cant++;
		helados++;

		if (cant < 3)
			return helados;
	}
}

int main() {
	printf("\n****************** INICIO DEL PROGRAMA ******************\n");
	int palitos = 14, consumidos;

	consumidos = heladosIterativo(palitos);
	printf("\nSe comen %d helados\n", consumidos);

	consumidos = heladosRecursivoCola(palitos, 0);
	printf("Se comen %d helados\n", consumidos);

	consumidos = heladosRecursivoStack(palitos);
	printf("Se comen %d helados\n", consumidos);

	printf("\n****************** FIN DEL PROGRAMA ******************\n");	
	return 0;
}