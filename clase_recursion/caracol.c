#include <stdio.h>

int tiempoSubidaRecursivoCola(int h, int subido, int tiempo) {
	if (h <= subido) { //caso base
		return tiempo; 
	}
	else {
		tiempo++; //sube
		subido = subido + 2;
		if (subido >= h) { //Evalua si salio
			return tiempo;
		} else {
			subido--; //retrocede
			tiempo++;
			return tiempoSubidaRecursivoCola(h, subido, tiempo);
		}
	}
}

int tiempoSubidaIterativo(int h) {
	int tiempo = 0, subido = 0, i = 0;
	if (h <= subido) {
		return tiempo;
	} 

	while(i < h) {
		subido = subido + 2;
		tiempo++;
		if (subido >= h)
			return tiempo;
		subido--;
		tiempo++;
		i++;
	}
}

int tiempoSubidaRecursivoStack(int h) {
	int tiempo = 0, subido;
	if (h < 2) {
		return tiempo;
	} else {
		h = h - 2;
		tiempo++;
		if (h < 1)
			return tiempo;
		else {
			h++;
			tiempo++;
			return tiempo + tiempoSubidaRecursivoStack(h);
		}
	}
}

int main() {
	printf("\n****************** INICIO DEL PROGRAMA ******************\n");
	int h = 1, tiempo;

	tiempo = tiempoSubidaRecursivoCola(h, 0, 0);
	printf("\nCaracol sube la altura de '%d'[mt], en un tiempo de '%d'[min].\n", h, tiempo);

	tiempo = tiempoSubidaIterativo(h);
	printf("\nCaracol sube la altura de '%d'[mt], en un tiempo de '%d'[min].\n", h, tiempo);

	tiempo = tiempoSubidaRecursivoStack(h);
	printf("\nCaracol sube la altura de '%d'[mt], en un tiempo de '%d'[min].\n", h, tiempo);

	printf("\n****************** FIN DEL PROGRAMA ******************\n");
	return 0;
}