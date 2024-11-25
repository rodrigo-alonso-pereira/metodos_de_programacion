/*
 *  Universidad de Santiago de Chile _ Ing. Ejecucion en Computacion e Informatica
 *  Laboratorio 03: Laberinto Subterraneo
 *  Lenguaje aplicado: C.
 *  Alumno: Rodrigo Pereira Yañez
 *  Rut: 16.610.470-k
 *  Fecha: 19/12/2023
 */

//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

//Macro que contiene el nombre archivo .txt
#define nombre_archivo_laberinto "Mapa-1.txt"

//Struct de un estado
typedef struct posicion {
    int id_estado;
    int posicion[2];
    char* transicion;
    int estado_anterior;
} estado_posicion;

//Variables globales
int posicion_inicial[2];
int posicion_final[2];
int posicion_llave[2];
int row, col, correlativo_id_estado_abiertos_1, correlativo_id_estado_abiertos_2;

estado_posicion* agregarEstado(estado_posicion* old_arreglo_estado_posicion, int* n, estado_posicion nuevo_estado_posicion) {
    /*
     * Input:   -old_arreglo_estado_posicion: Arreglo original que contiene Struct de estado_posicion.
                -n: Entero puntero que representa el tamaño del "old_arreglo_estado_posicion"
                -nuevo_estado_posicion: Nuevo estado_posicion que se debe agregar al arreglo "old_arreglo_estado_posicion"
     * Output:  -Nuevo arreglo de Struct estado_posicion
     * Remarks: Esta funcion permite agregar un estado_posicion a un arreglo de estado_posicion.
     *
    */
    int i;
    estado_posicion* nuevo_arreglo_estado_posicion = (estado_posicion*) malloc(sizeof(estado_posicion) * (*n + 1));

    for (i = 0; i < *n; i++) {
        nuevo_arreglo_estado_posicion[i] = old_arreglo_estado_posicion[i];
    }
    nuevo_arreglo_estado_posicion[*n] = nuevo_estado_posicion;
    *n += 1;
    free(old_arreglo_estado_posicion);

    return nuevo_arreglo_estado_posicion;
}

estado_posicion* quitarEstado(estado_posicion* old_arreglo_estado_posicion, int* n, int indice_estado_eliminar) {
    /*
     * Input:   -old_arreglo_estado_posicion: Arreglo original que contiene Struct de estado_posicion.
                -n: Entero puntero que representa el tamaño del "old_arreglo_estado_posicion"
                -indice_estado_eliminar: Entero que contiene el indice del estado_posicion que se debe eliminar
     * Output:  -Nuevo arreglo de Struct estado_posicion
     * Remarks: Esta funcion permite eliminar un estado_posicion a un arreglo de estado_posicion.
     *
    */
    int i, cont = 0;
    estado_posicion* nuevo_arreglo_estado_posicion = (estado_posicion*) malloc(sizeof(estado_posicion) * (*n - 1));

    for (i = 0; i < *n; i++) {
        if(indice_estado_eliminar != i) {
            nuevo_arreglo_estado_posicion[cont] = old_arreglo_estado_posicion[i];
            cont++;
        }
    }
    *n -= 1;
    free(old_arreglo_estado_posicion);

    return nuevo_arreglo_estado_posicion;
}

void buscarElemento(char** laberinto, char elemento, int* arr) {
    /*
     * Input:   -laberinto: Arreglo de dos dimensiones o Matriz de char que representa un mapa de un laberinto
                -elemento: char que contiene el elemento a buscar dentro de la matriz
                -arr: Arreglo de enteros que contiene la posicion del elemento a buscar
     * Output:  - Sin retorno
     * Remarks: Funcion que busca en un arreglo de char de dos dimensiones un elemento de interes y luego lo guarda en el
     *          arreglo de enteros 'arr', que hace referencia a una variable global.
    */
    int i,j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (laberinto[i][j] == elemento) {
                arr[0] = i;
                arr[1] = j;
            };
        }
    }
}

estado_posicion crearEstado(int* posicion, char* transicion, int estado_anterior, int opcion) {
    /*
     * Input:   -posicion: Arreglo de enteros que contiene la posicion del estado a crear.
                -transicion: Arreglo de char (String) que contiene la transicion del estado a crear.
                -estado_anterior: Entero que contiene el id_estado del estado anterior que crea este nuevo estado.
                -opcion: Entero que permite indiar si es el primer recorrido o es el 2do recorrido (1 = busqueda llave, 0 = busqueda salida)
     * Output:  -Nuevo Struct de estado_posicion.
     * Remarks: Funcion que permite crear un nuevo estado.
     *
    */
    estado_posicion nuevo_estado_posicion;

    if (opcion == 1) {
        nuevo_estado_posicion.id_estado = correlativo_id_estado_abiertos_1;
        for (int i = 0; i < 2; ++i)
            nuevo_estado_posicion.posicion[i] = posicion[i];
        nuevo_estado_posicion.transicion = (char*) malloc(sizeof(char) * 10);
        strcpy(nuevo_estado_posicion.transicion, transicion);
        nuevo_estado_posicion.estado_anterior = estado_anterior;
        correlativo_id_estado_abiertos_1 += 1;
    } else {
        nuevo_estado_posicion.id_estado = correlativo_id_estado_abiertos_2;
        for (int i = 0; i < 2; ++i)
            nuevo_estado_posicion.posicion[i] = posicion[i];
        nuevo_estado_posicion.transicion = (char*) malloc(sizeof(char) * 10);
        strcpy(nuevo_estado_posicion.transicion, transicion);
        nuevo_estado_posicion.estado_anterior = estado_anterior;
        correlativo_id_estado_abiertos_2 += 1;
    }

    return nuevo_estado_posicion;
}

void imprimirEstados(estado_posicion* arreglo_estados, int n) {
    /*
     * Input:   -arreglo_estados: Arreglo de estado_posicion
                -n: Entero que contiene el tamaño del arreglo "arreglo_estados"
     * Output:  - Sin Retorno
     * Remarks: Funcion que imprime lo que contiene el arreglo "arreglo_estados"
     *
    */
    int i;
    for (i = 0; i < n; i++)
        printf("Id: %d | Posicion[%d][%d] | Transicion: %s | Estado Anterior: %d\n", arreglo_estados[i].id_estado, arreglo_estados[i].posicion[0], arreglo_estados[i].posicion[1], arreglo_estados[i].transicion, arreglo_estados[i].estado_anterior);
}

void imprimirPasosLaberinto(estado_posicion* arreglo_estados, int n){
    /*
     * Input:   -arreglo_estados: Arreglo de estado_posicion
                -n: Entero que contiene el tamaño del arreglo "arreglo_estados"
     * Output:  - Sin Retonro
     * Remarks: Funcion que imprime la traza del camino mas corto del arreglo "arreglo_estados"
     *
    */
    int i;
    int estado_anterior = n - 1;
    for (i = n - 1; i >= 0; i--)
        if (i == estado_anterior){
            printf("Id: %d | Posicion[%d][%d] | Transicion: %s | Estado Anterior: %d\n", arreglo_estados[i].id_estado, arreglo_estados[i].posicion[0], arreglo_estados[i].posicion[1], arreglo_estados[i].transicion, arreglo_estados[i].estado_anterior);
            estado_anterior = arreglo_estados[i].estado_anterior;
        }
}

int evaluaEstadoFinal(char** laberinto, estado_posicion estado, char elemento) {
    /*
     * Input:   -laberinto: Arreglo de dos dimensiones o Matriz de char que representa un mapa de un laberinto
     *          -estado: Strcut de estado_posicion
                -elemento: Char que contiene el elemento a buscar
     * Output:  -Entero que representa el resultado de la evaluacion(1 = Encontrado, 0 = No encontrado)
     * Remarks: Funcion que permite evaluar si el "estado" enviado contiene la "elemento" buscado.
     *
    */
    if(laberinto[estado.posicion[0]][estado.posicion[1]] == elemento)
        return 1;
    return 0;
}

//TODO: Verificiar buen funcionamiento de si existe un estado o no
int verificarEstado(estado_posicion* arreglo_estados, int n, estado_posicion estado){
    /*
     * Input:   -arreglo_estados: Arreglo de estado_posicion que contiene todos los estados_posicion que se desean evaluar
                -n: Entero que contiene el tamaño del arreglo "arreglo_estados".
                -estado: Struct de estado_posicion que se va a verificar
     * Output:  -Entero que representa el resultado de la evaluacion (1 = Se encontro el estado, 0 = No se encontro el estado)
     * Remarks: Funcion que permite verificar si un estado ya existe dentro del arreglo de estado_posicion.
     *
    */
    int i;
    for (i = 0; i < n; ++i) {
        if(arreglo_estados[i].posicion[0] == estado.posicion[0] && arreglo_estados[i].posicion[1] == estado.posicion[1]) {
            return 1;
        }
    }
    return 0;
}

int verificarMoverArriba(char** laberinto, estado_posicion estado){
    /*
     * Input:   -laberinto: Arreglo de dos dimensiones o Matriz de char que representa un mapa de un laberinto.
                -estado: Struct de estado_posicion.
     * Output:  -Entero que representa el resultado de la evaluacion (1 = Se puede mover, 0 = No se puede mover)
     * Remarks: Funcion que permite verificar si se puede mover hacia arriba en el laberinto, tanto en tamaño,
     *          como de sí encontro un muro.
     *
    */
    //No pase limites del laberinto y no sea un muro '*'
    if(estado.posicion[0] - 1 > 0 && laberinto[estado.posicion[0] - 1][estado.posicion[1]] != '*'){
        return 1;
    }
    return 0;
}

estado_posicion moverArriba(estado_posicion estado, int opcion) {
    /*
     * Input:   -estado: Struct de estado posicion.
     * Output:  -Nuevo Struct de estado posicion con nueva posicion.
     * Remarks: Funcion que permite crear un estado con nueva posicion luego de mover hacia arriba.
     *
    */
    estado.posicion[0] -= 1;
    return crearEstado(estado.posicion, "Arriba", estado.id_estado, opcion);
}

int verificarMoverDerecha(char** laberinto, estado_posicion estado){
    /*
     * Input:   -laberinto: Arreglo de dos dimensiones o Matriz de char que representa un mapa de un laberinto.
                -estado: Struct de estado_posicion.
     * Output:  -Entero que representa el resultado de la evaluacion (1 = Se puede mover, 0 = No se puede mover)
     * Remarks: Funcion que permite verificar si se puede mover hacia la derecha en el laberinto, tanto en tamaño,
     *          como de sí encontro un muro.
     *
    */
    //No pase limites del laberinto y  no sea un muro '*'
    //if(laberinto[estado.posicion[0]][estado.posicion[1] + 1] != '*') {
    if(((estado.posicion[1] + 1) < (col - 1)) && (laberinto[estado.posicion[0]][estado.posicion[1] + 1] != '*')){
        return 1;
    }
    return 0;
}

estado_posicion moverDerecha(estado_posicion estado, int opcion) {
    /*
     * Input:   -estado: Struct de estado posicion.
     * Output:  -Nuevo Struct de estado posicion con nueva posicion.
     * Remarks: Funcion que permite crear un estado con nueva posicion luego de mover hacia la derecha.
     *
    */
    estado.posicion[1] += 1;
    return crearEstado(estado.posicion, "Derecha", estado.id_estado, opcion);
}

int verificarMoverAbajo(char** laberinto, estado_posicion estado){
    /*
     * Input:   -laberinto: Arreglo de dos dimensiones o Matriz de char que representa un mapa de un laberinto.
                -estado: Struct de estado_posicion.
     * Output:  -Entero que representa el resultado de la evaluacion (1 = Se puede mover, 0 = No se puede mover)
     * Remarks: Funcion que permite verificar si se puede mover hacia abajo en el laberinto, tanto en tamaño,
     *          como de sí encontro un muro.
     *
    */
    //No pase limites del laberinto y  no sea un muro '*'
    if(((estado.posicion[0] + 1) < (row - 1)) && (laberinto[estado.posicion[0] + 1][estado.posicion[1]] != '*')){
        return 1;
    }
    return 0;
}

estado_posicion moverAbajo(estado_posicion estado, int opcion) {
    /*
     * Input:   -estado: Struct de estado posicion.
     * Output:  -Nuevo Struct de estado posicion con nueva posicion.
     * Remarks: Funcion que permite crear un estado con nueva posicion luego de mover hacia abajo.
     *
    */
    estado.posicion[0] += 1;
    return crearEstado(estado.posicion, "Abajo", estado.id_estado, opcion);
}

int verificarMoverIzquierda(char** laberinto, estado_posicion estado){
    /*
     * Input:   -laberinto: Arreglo de dos dimensiones o Matriz de char que representa un mapa de un laberinto.
                -estado: Struct de estado_posicion.
     * Output:  -Entero que representa el resultado de la evaluacion (1 = Se puede mover, 0 = No se puede mover)
     * Remarks: Funcion que permite verificar si se puede mover hacia la izquierda en el laberinto, tanto en tamaño,
     *          como de sí encontro un muro.
     *
    */
    //No pase limites del laberinto y  no sea un muro '*'
    if(((estado.posicion[1] - 1) > 0) && (laberinto[estado.posicion[0]][estado.posicion[1] - 1] != '*')){
        return 1;
    }
    return 0;
}

estado_posicion moverIzquierda(estado_posicion estado, int opcion) {
    /*
     * Input:   -estado: Struct de estado posicion.
     * Output:  -Nuevo Struct de estado posicion con nueva posicion.
     * Remarks: Funcion que permite crear un estado con nueva posicion luego de mover hacia la izquierda.
     *
    */
    estado.posicion[1] -= 1;
    return crearEstado(estado.posicion, "Izquierda", estado.id_estado, opcion);
}


char** leerArchivo(char* nombre_archivo) {
    /*
     * Input:   -nombre_archivo: Arreglo de caracteres que contiene el nombre del archivo a leer
     * Output:  -Matriz de caracteres que contiene los caracteres que representa un mapa extraido del archivo.
     * Remarks: Funcion que permite leer un archivo, extraer cada línea, crear una matriz del tamaño del laberinto
     *          y retornar esta matriz.
    */

    char** laberinto;

    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        perror("Error fopen: ");
        exit(EXIT_FAILURE);
    }

    //Evalua si se instancio bien el struct sb.
    struct stat sb;
    if (stat(nombre_archivo, &sb) == -1) {
        perror("Error stat: ");
        exit(EXIT_FAILURE);
    }

    char* linea_temp = malloc(sb.st_size);

    //lectura linea por linea
    int i = 0, j, l, k;
    while (fscanf(archivo, "%[^\n] ", linea_temp) != EOF) {
        //printf("%s", linea_temp);

        if (i == 0){
            sscanf(linea_temp, "%d %d\r", &row, &col);
            laberinto = (char**) malloc(sizeof(char*) * row);
            for (j = 0; j < row; j++)
                laberinto[j] = (char*) malloc(sizeof(char) * col);

        } else {
            strcpy(laberinto[i-1], linea_temp);
            /*for (k = 0; k < *col; k++) {
                laberinto[i-1][k] = linea_temp[k];
            }*/
        }
        i++;
    }
    return laberinto;
}

int main() {
    //Etapa previa Algoritmo.
    //Obtener laberinto de archivo de texto
    char** laberinto = leerArchivo(nombre_archivo_laberinto);
    correlativo_id_estado_abiertos_1 = 0;
    correlativo_id_estado_abiertos_2 = 0;
    //Buscar posiciones de elementos 'E', 'K', 'S' y lo guarda en variables globales.
    buscarElemento(laberinto, 'E', posicion_inicial);
    buscarElemento(laberinto, 'P', posicion_final);
    buscarElemento(laberinto, 'K', posicion_llave);
    //Imprimir laberinto
    printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
    printf("   Laberinto de %d[filas] x %d[columnas]", row, col);
    printf("\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c", laberinto[i][j]);
        }
        printf("\n");
    }

    /*
     * BEE por ANCHURA.
     *
     * Se utilizó un algoritmo de busqueda de espacio de estado por Anchura.
     * Estado: Es la posicion dentro del arreglo bidimensional de char, que representa al laberinto.
     * Estado_inicial: La posicion de donde se encuentra el lugar de partida.
     * Estado_final: La posicion de donde encuentra el elemento buscado que puedes ser la llave 'K' o la salida 'P'.
     * Transicion: Arriba, Derecha, Abajo, Izquierda (sentido horario).
     *
     * Explicacion del la eleccion del Algoritmo:
     *  - Este algoritmo de busqueda de espacio de estado por anchura se caracteriza porque es el algoritmo que encuentra
     *    la menor cantidad de transiciones desde un punto a otro.
     *  - No necesariamente es el algoritmo que se demora menos o que tenga menos transiciones, eso va a depender del tipo de laberinto
     *    al cual nos enfrentemos.
     *  - La eleccion viene dada, ya que al estar en un laberinto uno siempre desea llegar a la salida en la menor cantidad de pasos posibles y
     *    este algoritmo tiene esa caracteristica.
     *
     * Explicacion del funcionamiento del algoritmo.
     *  - Desde una posicion inicial intenta abrir todos los estados que permita las transiciones definidas (arriba, derecha, abajo, izquierda) y
     *    las caracteristicas del laberinto
     *  - Toma el primer estado abierto, lo pasa a la lista de cerrado y sobre ese intenta abrir todos los estados posibles que permitan las
     *    trancisiciones definidas (arriba, derecha, abajo, izquierda) y las caracteristicas del laberinto.
     *  - Al llegar al objetivo, se puede realizar una traza siguiendo los estados anteriores y que entregaran el camino más corto.
     */

    //Pasos Algoritmo (Busqueda Key)
    //1. Crear estructura y lista de estados abiertos y cerrados.
    int n_abiertos_1 = 0, n_cerrados_1 = 0;
    estado_posicion posicion_actual_1, posicion_siguiente_1;
    estado_posicion* estados_abiertos_1 = (estado_posicion*) malloc(sizeof(estado_posicion) * n_abiertos_1);
    estado_posicion* estados_cerrados_1 = (estado_posicion *) malloc(sizeof(estado_posicion) * n_cerrados_1);
    //Para esta primera iteracion el estado inicial es la posicion [filas][columnas] de donde se encuentra la entrada 'E'
    estado_posicion estado_inicial_1 = crearEstado(posicion_inicial, "-", -1, 1);
    estados_abiertos_1 = agregarEstado(estados_abiertos_1, &n_abiertos_1, estado_inicial_1);

    //Paso2. Mientras existan estados abiertos, agregar primer estado a lista cerrados (Anchura)
    while (n_abiertos_1 > 0) {
        //Como es busqueda por anchura, siempre se busca el primer estado abierto
        posicion_actual_1 = estados_abiertos_1[0];
        estados_abiertos_1 = quitarEstado(estados_abiertos_1, &n_abiertos_1, 0);
        estados_cerrados_1 = agregarEstado(estados_cerrados_1, &n_cerrados_1, posicion_actual_1);
        //Paso 3: Evaluar si es estado final
        if(evaluaEstadoFinal(laberinto, posicion_actual_1, 'K') == 1){
            //Un estado final es cuando se encuentra la posicion [filas][columnas] de la llave 'K'
            printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
            printf("         Llegamos a la Llave!! =D");
            printf("\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
            printf("\nEl camino mas corto para llegar a la llave 'K' desde la entrada 'E' es (lectura de abajo hacia arriba):\n");
            printf("-------------------------------------------------------------------------------------------------------\n");
            imprimirPasosLaberinto(estados_cerrados_1, n_cerrados_1);
            printf("\n\nTodos los estados cerrados para llegar a la llave 'K' desde la entrada 'E' son:\n");
            printf("-------------------------------------------------------------------------------\n");

            imprimirEstados(estados_cerrados_1, n_cerrados_1);
        } else {
            //Paso 4: Si no es estado final, aplicar todas las transiciones en orden.
            //Arriba
            if(verificarMoverArriba(laberinto, posicion_actual_1) == 1) {
                posicion_siguiente_1 = moverArriba(posicion_actual_1, 1);
                if((verificarEstado(estados_abiertos_1, n_abiertos_1, posicion_siguiente_1) == 0) && (verificarEstado(estados_cerrados_1, n_cerrados_1, posicion_siguiente_1) == 0)) {
                    estados_abiertos_1 = agregarEstado(estados_abiertos_1, &n_abiertos_1, posicion_siguiente_1);
                } else {
                    correlativo_id_estado_abiertos_1 -= 1;
                }
            }
            //Derecha
            if(verificarMoverDerecha(laberinto, posicion_actual_1) == 1) {
                posicion_siguiente_1 = moverDerecha(posicion_actual_1, 1);
                if((verificarEstado(estados_abiertos_1, n_abiertos_1, posicion_siguiente_1) == 0) && (verificarEstado(estados_cerrados_1, n_cerrados_1, posicion_siguiente_1) == 0)) {
                    estados_abiertos_1 = agregarEstado(estados_abiertos_1, &n_abiertos_1, posicion_siguiente_1);
                } else {
                    correlativo_id_estado_abiertos_1 -= 1;
                }
            }
            //Abajo
            if(verificarMoverAbajo(laberinto, posicion_actual_1) == 1) {
                posicion_siguiente_1 = moverAbajo(posicion_actual_1, 1);
                if((verificarEstado(estados_abiertos_1, n_abiertos_1, posicion_siguiente_1) == 0) && (verificarEstado(estados_cerrados_1, n_cerrados_1, posicion_siguiente_1) == 0)) {
                    estados_abiertos_1 = agregarEstado(estados_abiertos_1, &n_abiertos_1, posicion_siguiente_1);
                } else {
                    correlativo_id_estado_abiertos_1 -= 1;
                }
            }
            //Izquierda
            if(verificarMoverIzquierda(laberinto, posicion_actual_1) == 1) {
                posicion_siguiente_1 = moverIzquierda(posicion_actual_1, 1);
                if((verificarEstado(estados_abiertos_1, n_abiertos_1, posicion_siguiente_1) == 0) && (verificarEstado(estados_cerrados_1, n_cerrados_1, posicion_siguiente_1) == 0)) {
                    estados_abiertos_1 = agregarEstado(estados_abiertos_1, &n_abiertos_1, posicion_siguiente_1);
                } else {
                    correlativo_id_estado_abiertos_1 -= 1;
                }
            }
        }
    }

    //Pasos Algoritmo (Busqueda Puerta)
    //1. Crear estructura y lista de estados abiertos y cerrados.
    int n_abiertos_2 = 0, n_cerrados_2 = 0;
    estado_posicion posicion_actual_2, posicion_siguiente_2;
    estado_posicion* estados_abiertos_2 = (estado_posicion*) malloc(sizeof(estado_posicion) * n_abiertos_2);
    estado_posicion* estados_cerrados_2 = (estado_posicion *) malloc(sizeof(estado_posicion) * n_cerrados_2);
    estado_posicion estado_inicial_2 = crearEstado(posicion_llave, "-", -1, 0);
    estados_abiertos_2 = agregarEstado(estados_abiertos_2, &n_abiertos_2, estado_inicial_2);

    //Paso2. Mientras existan estados abiertos, agregar primer estado a lista cerrados (Anchura)
    while (n_abiertos_2 > 0) {
        //Como es busqueda por anchura, siempre se busca el primer estado abierto
        posicion_actual_2 = estados_abiertos_2[0];
        estados_abiertos_2 = quitarEstado(estados_abiertos_2, &n_abiertos_2, 0);
        estados_cerrados_2 = agregarEstado(estados_cerrados_2, &n_cerrados_2, posicion_actual_2);
        //Paso 3: Evaluar si es estado final
        if (evaluaEstadoFinal(laberinto, posicion_actual_2, 'P') == 1) {
            printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
            printf("         Llegamos a la Salida!! =D");
            printf("\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
            printf("\nEl camino mas corto para llegar a la salida 'P' desde la llave es 'K' (lectura de abajo hacia arriba):\n");
            printf("------------------------------------------------------------------------------------------------------\n");
            imprimirPasosLaberinto(estados_cerrados_2, n_cerrados_2);
            printf("\nTodos los estados cerrados para llegar a la salida 'P' desde la llave 'K' son:\n");
            printf("------------------------------------------------------------------------------\n");
            imprimirEstados(estados_cerrados_2, n_cerrados_2);
            return 0;
        } else {
            //Paso 4: Si no es estado final, aplicar todas las transiciones en orden.
            //Arriba
            if (verificarMoverArriba(laberinto, posicion_actual_2) == 1) {
                posicion_siguiente_2 = moverArriba(posicion_actual_2, 0);
                if ((verificarEstado(estados_abiertos_2, n_abiertos_2, posicion_siguiente_2) == 0) &&
                    (verificarEstado(estados_cerrados_2, n_cerrados_2, posicion_siguiente_2) == 0)) {
                    estados_abiertos_2 = agregarEstado(estados_abiertos_2, &n_abiertos_2, posicion_siguiente_2);
                } else {
                    correlativo_id_estado_abiertos_2 -= 1;
                }
            }
            //Derecha
            if (verificarMoverDerecha(laberinto, posicion_actual_2) == 1) {
                posicion_siguiente_2 = moverDerecha(posicion_actual_2, 0);
                if ((verificarEstado(estados_abiertos_2, n_abiertos_2, posicion_siguiente_2) == 0) &&
                    (verificarEstado(estados_cerrados_2, n_cerrados_2, posicion_siguiente_2) == 0)) {
                    estados_abiertos_2 = agregarEstado(estados_abiertos_2, &n_abiertos_2, posicion_siguiente_2);
                } else {
                    correlativo_id_estado_abiertos_2 -= 1;
                }
            }
            //Abajo
            if (verificarMoverAbajo(laberinto, posicion_actual_2) == 1) {
                posicion_siguiente_2 = moverAbajo(posicion_actual_2, 0);
                if ((verificarEstado(estados_abiertos_2, n_abiertos_2, posicion_siguiente_2) == 0) &&
                    (verificarEstado(estados_cerrados_2, n_cerrados_2, posicion_siguiente_2) == 0)) {
                    estados_abiertos_2 = agregarEstado(estados_abiertos_2, &n_abiertos_2, posicion_siguiente_2);
                } else {
                    correlativo_id_estado_abiertos_2 -= 1;
                }
            }
            //Izquierda
            if (verificarMoverIzquierda(laberinto, posicion_actual_2) == 1) {
                posicion_siguiente_2 = moverIzquierda(posicion_actual_2, 0);
                if ((verificarEstado(estados_abiertos_2, n_abiertos_2, posicion_siguiente_2) == 0) &&
                    (verificarEstado(estados_cerrados_2, n_cerrados_2, posicion_siguiente_2) == 0)) {
                    estados_abiertos_2 = agregarEstado(estados_abiertos_2, &n_abiertos_2, posicion_siguiente_2);
                } else {
                    correlativo_id_estado_abiertos_2 -= 1;
                }
            }
        }
    }

    return 0;
}