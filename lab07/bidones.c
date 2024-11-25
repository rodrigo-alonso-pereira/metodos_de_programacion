#include <stdio.h>
#include <stdlib.h>

/*
 * Definir la estructura del estado
 * Estado Inicial: agua_bidon_5L = 0, agua_bidon_3L = 0
 * Estado Final: agua_bidon_5L = 4;
 * Transiciones: llenar5, llenar3, vaciar5, vaciar3, trasvasijar3_5, trasvacijar5_3
 * //LL5, LL3, V5, V3, T3_5, T5_3
 * Verificaciones:
 */

// bideones corresponde a la estructura del estado
typedef struct bidones {
    int agua_bidon_5L;
    int agua_bidon_3L;
    int id_estado;
    int estado_anterior;
    char* transicion;
} bidones;

int correlativo;

bidones  crear_estado(int ab3, int ab5, int anterior, char* transicion) {
    bidones nuevo_estado;
    nuevo_estado.agua_bidon_3L = ab3;
    nuevo_estado.agua_bidon_5L = ab5;
    nuevo_estado.estado_anterior = anterior;
    nuevo_estado.id_estado = correlativo++;
    nuevo_estado.transicion = transicion;

    return bidones;
}

bidones* agregar_estado(bidones* lista_estados, int* n, bidones nuevo_estado) {
    bidones* nuevo_lista_estados = (bidones*) malloc(sizeof(bidones) * (*n + 1));
    int i;

    for (i=0, i < *n, i++) {
        nuevo_lista_estados[i] = lista_estados[i];
    }

    nuevo_lista_estados[*n] = nuevo_estado;
    //*n++;
    *n = *n +1;
    free(lista_estados);

    return nuevo_lista_estados;
}

bidones* sacar_estado(bidones* lista_estados, int* elementos) {
    bidones* nuevo_lista_estados = (bidones*) malloc(sizeof(bidones) * (*n - 1));
    int i;

    for (i = 1, i < * elementos, i++) {
        nuevo_lista_estados[i-1] = lista_estados[i];
    }

    *elementos = *elementos - 1;
    free(lista_estados);

    return nuevo_lista_estados;
}

int verificar_llenar_5(bidones estado) {
    if (estado.agua_bidon_5L < 5) {
        return 1
    } else {
        return 0;
    }
}

int  verificar_llenar_3(bidones estado) {
    if (estado.agua_bidon_3L < 3) {
        return 1;
    } else {
        return 0;
    }
}

int verificar_vaciar_5(bidones estado) {
    // metodo para verificar si podemos vaciar un bidon de 5 litros
    if (estado.agua_bidon_5L > 0) {
        return 1;
    } else {
        return 0;
    }
}

int verificar_vaciar_3(bidones estado) {
    // metodo para verificar si podemos vaciar un bidon 3 litros
    if (estado.agua_bidon_3L > 0) {
        return 1;
    } else {
        return 0;
    }
}

int verificar_trasvasijar_3_5(bidones estado) {
    if ((estado.agua_bidon_3L > 0 && estado.agua_bidon_5L < 5) {
        return 1;
    } else {
        return 0;
    }
}

int verificar_trasvasijar_3_5(bidones estado) {
    if ((estado.agua_bidon_3L < 3 && estado.agua_bidon_5L > 0) {
        return 1;
    } else {
        return 0;
    }
}

bidones llenar_5(bidones estado) {
    return crear_estado(estado.agua_bidon_3L, 5, estado.id_estado, "LL5");
}

bidones llenar_3(bidones estado) {
    return crear_estado(3, estado.agua_bidon_5L, estado.id_estado, "LL3");
}

bidones vaciar_5(bidones estado) {
    return crear_estado(estado.agua_bidon_3L, 0, estado.id_estado, "V5")
}

bidones vaciar_3(bidones estado) {
    return crear_estado(0, estado.agua_bidon_5L, estado.id_estado, "V3")
}

bidones trasvacijar3_5(bidones estado) {
    int suma = estado.agua_bidon_3L + estado.agua_bidon_5L;
    int agua_bidon_3L, agua_bidon_5L;

    if (suma > 5) {
        agua_bidon_5L = 5;
        agua_bidon_3L = suma - 5;
    } else {
        agua_bidon_5L = suma;
        agua_bidon_3L = 0;
    }

    return crear_estado(agua_bidon_3L, agua_bidon_5L, estado.id_estado, "T3_5");
}

bidones trasvacijar5_3(bidones estado) {
    int suma = estado.agua_bidon_3L + estado.agua_bidon_5L;
    int agua_bidon_5L, agua_bidon_3L;

    if (suma > 3) {
        agua_bidon_3L = 3;
        agua_bidon_5L = suma - 3;
    } else {
        agua_bidon_3L = suma;
        agua_bidon_5L = suma 
    }
    return crear_estado(agua_bidon_3L, agua_bidon_5L, estado.id_estado, "T5_3");
}

int es_final(bidones estado) {
    if (estado.agua_bidon_5L == 4) {
        return 1;
    } else {
        return 0;
    }
}

void mostrar_solucion(bidones* lista, int ultimo) {
    printf("Los pasos son, del ultimo al primero: \n");
    while (lista[ultimo].id_estado != 0) {
        printf("%s\n", lista[ultimo].transicion);
        ultimo = lista[ultimo].estado_anterior;
    }
    return;
}

int estado_existe(bidones* lista, int* n, bidones estado) {
    for (int i = 0; i < n; ++i) {
        if ((lista[i].agua_bidon_3L == estado.agua_bidon_3L) && (lista[i].agua_bidon_5L == estado.agua_bidon_5L)) {
            return 1;
        } else {
            return 0;
        }
    }
}

//Lab 03, recorrer laberintos con algoritmos.

int main() {

    correlativo = 0;
    int n_estados_abiertos = 0;
    bidones* estados_abiertos = (bidones*)malloc(sizeof(bidones) * n_estados_abiertos);
    int n_estados_cerrados = 0;
    bidones* estados_cerrados = (bidones*)malloc(sizeof(bidones) * n_estados_cerrados);

    bidones estado_inicial = crear_estado(0, 0, correlativo, "");
    estados_abiertos = agregar_estado(estados_abiertos, &n_estados_abiertos, estado_inicial);
    while (n_estados_abiertos > 0) {
        bidones estado_actual = estados_abiertos[0];
        estados_cerrados = agregar_estado(estados_cerrados, &n_estados_cerrados, estado_actual);
        estados_abiertos = sacar_estado(estados_abiertos, n_estados_abiertos);
        if (es_final(estado_actual  == 1)) {
            printf("Llegamos\n");
            mostrar_solucion(estados_cerrados, n_estados_cerrados - 1); //Revisar.
            return 0;
        } else {
            //LL3
            if (verificar_llenar_3(estado_actual) ==  1) {
                bidones estado_siguiente = llenar_3(estado_actual);
                if ((estado_existe(estados_abiertos, n_estados_abiertos, estado_siguiente) == 0) && (estado_existe(estados_cerrados, n_estados_cerrados, estado_siguiente) == 0)) {
                    estados_abiertos = agregar_estado(estados_abiertos, &n_estados_abiertos, estado_siguiente);
                } else {
                    correlativo = correlativo - 1;
                }
            }
            //LL5
            if (verificar_llenar_5(estado_actual) ==  1) {
                bidones estado_siguiente = llenar_5(estado_actual);
                if ((estado_existe(estados_abiertos, n_estados_abiertos, estado_siguiente) == 0) && (estado_existe(estados_cerrados, n_estados_cerrados, estado_siguiente) == 0)) {
                    estados_abiertos = agregar_estado(estados_abiertos, &n_estados_abiertos, estado_siguiente);
                } else {
                    correlativo = correlativo - 1;
                }
            }
            //V3
            if (verificar_vaciar_3(estado_actual) ==  1) {
                bidones estado_siguiente = vaciar3(estado_actual);
                if ((estado_existe(estados_abiertos, n_estados_abiertos, estado_siguiente) == 0) && (estado_existe(estados_cerrados, n_estados_cerrados, estado_siguiente) == 0)) {
                    estados_abiertos = agregar_estado(estados_abiertos, &n_estados_abiertos, estado_siguiente);
                } else {
                    correlativo = correlativo - 1;
                }
            }
            //V5
            //T3_5
            //T5_4
        }
    }

    return 0;
}