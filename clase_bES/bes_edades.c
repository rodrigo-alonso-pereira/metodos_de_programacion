

#include <stdio.h>

#include <stdlib.h>

struct edades{
	
	int x;
	int y;
	int z;
	
}; 

typedef struct edades edades;


void mostrar(edades * arreglo,int largo);

edades * append(edades * arreglo, int largo, edades nueva_edad){
	
	

	
	edades * nuevo_arreglo = (edades * )malloc(sizeof(edades)*(largo+1));
	
	int i;
	for(i = 0 ; i < largo; i++){
		nuevo_arreglo[i] = arreglo[i];	
	}
	
	nuevo_arreglo[i] = nueva_edad;
																				//free(arreglo);  Esto ES!
	

	return nuevo_arreglo;
	
}



edades * pop(edades * arreglo, int largo){
	
	
	
	edades * nuevo_arreglo = (edades * )malloc(sizeof(edades)*(largo-1));
	
	int i;
	for(i = 0 ; i < largo-1; i++){
		nuevo_arreglo[i] = arreglo[i];	
	}
	free(&(arreglo[i]));
	free(arreglo);
	return nuevo_arreglo;
	
}




edades crear_solucion(int e1,int e2, int e3){
	
	
	 edades * nueva_edad =  (edades *)malloc(sizeof(edades));
	 
	 
	 nueva_edad->x = e1;
	 nueva_edad->y = e2;
	 nueva_edad->z = e3;
	 
	 return *nueva_edad;
	 
}



void mostrar(edades * arreglo,int largo){
	
	printf("\n\n************   Mostrar  **********************\n\n");
	
	int i;
	
	for (i = 0; i < largo; i++)
		printf("%d %d %d\n",arreglo[i].x,arreglo[i].y,arreglo[i].z);
	
	return;
	
}


//la edades multiplicadas dan 36
edades * restriccion1(edades * arreglo,int * largo){
	

	
	edades * nuevo_arreglo;
	int largo_nuevo = 0;
	
	int i;
	for (i = 0 ; i < (*largo); i++){
		
			if (arreglo[i].x * arreglo[i].y * arreglo[i].z  == 36)
				nuevo_arreglo = append(nuevo_arreglo, largo_nuevo++, arreglo[i]);

		
	}
	
	
	
	
	*largo = largo_nuevo;
	
	
	return nuevo_arreglo;
	
	
	
}


edades * restriccion2 (edades * arreglo,int * largo){
	
	
	

	edades * nuevo_arreglo;
	int largo_nuevo = 0;
	
	int i,j;
	for (i = 0 ; i < (*largo); i++){
		
		int contar = 0;
		int suma = arreglo[i].x + arreglo[i].y + arreglo[i].z;
		

		for (j = 0 ; j < (*largo); j++){
			
		
			int otra_suma = arreglo[j].x + arreglo[j].y + arreglo[j].z;
			
			if (otra_suma == suma)
				contar++;

		}
		

		if (contar > 1){
			nuevo_arreglo = append(nuevo_arreglo, largo_nuevo++, arreglo[i]);
		}

		
	}
	

	
	
	*largo = largo_nuevo;
	
	
	return nuevo_arreglo;
	
	
	
}


edades * restriccion3 (edades * arreglo,int * largo){
	
	
	
	edades * nuevo_arreglo;
	int largo_nuevo = 0;
	
	int i;
	for (i = 0 ; i < (*largo); i++){
		
			if (arreglo[i].y < arreglo[i].z  )
				nuevo_arreglo = append(nuevo_arreglo, largo_nuevo++, arreglo[i]);

	}
	
	
	
	
	*largo = largo_nuevo;
	
	
	return nuevo_arreglo;
	
	
	
	
}


int main(){

	printf("\n\n************   Inicio del programa **********************\n\n");
	
	edades * arreglo;
	int largo = 0;
	

//conjunto inicial de soluciones
	int i,j,k;
	
	for (i = 0; i <= 40 ; i++)
		for (j = i; j <= 40 ; j++)
				for (k = j; k <= 40 ; k++)
					arreglo = append(arreglo, largo++, crear_solucion(i,j,k));
					

		
	
//restriccion 1
	arreglo = restriccion1(arreglo,&largo);


	mostrar(arreglo,largo);
	
	
	
	arreglo = restriccion2 (arreglo,&largo);
	
	
	mostrar(arreglo,largo);
	
	arreglo = restriccion3 (arreglo,&largo);
	
	
	mostrar(arreglo,largo);
	
	printf("\n\n************   fin del programa  **********************\n\n");
	

	return 0;
}