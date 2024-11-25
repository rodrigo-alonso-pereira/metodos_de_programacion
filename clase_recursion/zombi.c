#include <stdio.h>

int cantidadRecursionColas(int zombie, int dias) {
	//printf("n_zombies: %d, dias: %d\n", zombie, dias);
	if (dias == 0)
		return zombie;
	else {

		zombie = (int) zombie * 0.98;
		zombie = zombie * 6; //zombie -> 5 + 1 (original)
		dias--;
		return cantidadRecursionColas(zombie, dias);
	}
}

int main() {

	int n_zombies = 20, dias = 10, n_zombie_final;
	
	n_zombie_final = cantidadRecursionColas(n_zombies, dias);
	printf("La cantidad de zombies es %d, al cabo de %d dias\n", n_zombie_final, dias);

	return 0;
}