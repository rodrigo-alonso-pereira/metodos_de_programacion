#include <stdio.h>
#include <stdlib.h>

typedef struct bidones bidones;

struct bidones{
	int AguaBidon5L;
	int AguaBidon3L;
	int idEstado;
	int estadoAnterior;
	char * transicion;
};

int correlativo;

bidones crearEstado(int ab3, int ab5, int anterior, char * t);
bidones * agregarEstado(bidones * lista, int * elementos, bidones estado);
int verificarLL5(bidones estado);
int verificarLL3(bidones estado);
int verificarV5(bidones estado);
int verificarV3(bidones estado);
int verificarT5(bidones estado);
int verificarT3(bidones estado);
bidones llenar5(bidones estado);
bidones llenar3(bidones estado);
bidones vaciar5(bidones estado);
bidones vaciar3(bidones estado);
bidones tras5(bidones estado);
bidones tras3(bidones estado);
bidones * sacarElemento(bidones * lista, int * elementos);
int esFinal(bidones b);
void imprimirEstado(bidones b);
int estaEstado(bidones * lista, int elementos, bidones b);


bidones crearEstado(int ab3, int ab5, int anterior, char * t){
	bidones nuevoEstado;
	nuevoEstado.AguaBidon3L = ab3;
	nuevoEstado.AguaBidon5L = ab5;
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}

bidones * agregarEstado(bidones * lista, int * elementos, bidones estado){
	bidones * nuevaLista = (bidones *)malloc(sizeof(bidones)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

int verificarLL5(bidones estado){
	if(estado.AguaBidon5L < 5){
		return 1;
	}return 0;
}

bidones llenar5(bidones estado){
	return crearEstado(estado.AguaBidon3L, 5, estado.idEstado, "LL5");
}

int verificarLL3(bidones estado){	
	if(estado.AguaBidon3L < 3){
		return 1;
	}return 0;
}

bidones llenar3(bidones estado){
	return crearEstado(3, estado.AguaBidon5L, estado.idEstado, "LL3");
}

int verificarV5(bidones estado){
	if(estado.AguaBidon5L > 0){
		return 1;
	}return 0;
}

bidones vaciar5(bidones estado){
	return crearEstado(estado.AguaBidon3L, 0, estado.idEstado, "V5");
}

int verificarV3(bidones estado){
	if(estado.AguaBidon3L > 0){
		return 1;
	}return 0;
}

bidones vaciar3(bidones estado){
	return crearEstado(0, estado.AguaBidon5L, estado.idEstado, "V3");
}

int verificarT5(bidones estado){
	if(estado.AguaBidon3L < 3 && estado.AguaBidon5L > 0 && (estado.AguaBidon5L + estado.AguaBidon3L)<=8){
		return 1;
	}return 0;
}

bidones tras5(bidones estado){
	if((estado.AguaBidon3L + estado.AguaBidon5L) <= 3){
		return crearEstado((estado.AguaBidon3L + estado.AguaBidon5L), 0, estado.idEstado, "T5");
	}else{
		return crearEstado(3, (estado.AguaBidon3L + estado.AguaBidon5L) - 3, estado.idEstado, "T5");
	}
}

int verificarT3(bidones estado){
	if(estado.AguaBidon5L < 5 && estado.AguaBidon3L > 0  && (estado.AguaBidon5L + estado.AguaBidon3L)<=8){
		return 1;
	}return 0;
}

bidones tras3(bidones estado){
	if((estado.AguaBidon3L + estado.AguaBidon5L) <= 3){
		return crearEstado(0, (estado.AguaBidon3L + estado.AguaBidon5L), estado.idEstado, "T3");
	}else{
		return crearEstado((estado.AguaBidon3L + estado.AguaBidon5L) - 5, 5, estado.idEstado, "T5");
	}
}

bidones * sacarElemento(bidones * lista, int * elementos){
	bidones * nuevaLista = (bidones *)malloc(sizeof(bidones)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}

int esFinal(bidones b){
	if(b.AguaBidon5L == 4)
		return 1;
	return 0;
}

void imprimirEstado(bidones b){
	printf("Id:%d; A5:%d, A3:%d; T:%s, IdAnt:%d\n", b.idEstado, b.AguaBidon5L, b.AguaBidon3L, b.transicion, b.estadoAnterior);
}

int estaEstado(bidones * lista, int elementos, bidones b){
	for (int i = 0; i < elementos; ++i){
		if((lista[i].AguaBidon3L == b.AguaBidon3L) && (lista[i].AguaBidon5L == b.AguaBidon5L))
			return 1;
	}return 0;
}

void mostrarSolucion(bidones * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].transicion);
		ultimo = lista[ultimo].estadoAnterior;
	}
}


int main(){
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	bidones bActual, bSiguiente;
	bidones * abiertos = (bidones *)malloc(sizeof(bidones)*canAbiertos);
	bidones * cerrados = (bidones *)malloc(sizeof(bidones)*canCerrados);
	bidones inicial = crearEstado(0, 0, correlativo, "");
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	while(canAbiertos > 0){
		bActual = abiertos[0];
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados, bActual);
		if(esFinal(bActual) == 1){
			printf("Llegue\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{
			//LL5
			if(verificarLL5(bActual) == 1){
				bSiguiente = llenar5(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//LL3
			if(verificarLL3(bActual) == 1){
				bSiguiente = llenar3(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//V5
			if(verificarV5(bActual) == 1){
				bSiguiente = vaciar5(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//V3
			if(verificarV3(bActual) == 1){
				bSiguiente = vaciar3(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//T5
			if(verificarT5(bActual) == 1){
				bSiguiente = tras5(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//T3
			if(verificarT3(bActual) == 1){
				bSiguiente = tras3(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
		}

		printf("ABIERTOS:");
		for (int i = 0; i < canAbiertos; ++i)
		{
			imprimirEstado(abiertos[i]);
		}


		printf("\nCERRADOS:");
		for (int i = 0; i < canCerrados; ++i)
		{
			imprimirEstado(cerrados[i]);
		}
		printf("\n\n");
	}
	return 0;
}