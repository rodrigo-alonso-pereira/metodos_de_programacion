/*
 *  Universidad de Santiago de Chile _ Ing. Ejecucion en Computacion e Informatica
 *  Laboratorio 01: Aventuras Epicas
 *  Alumno: Rodrigo Pereira Yañez
 *  Rut: 16.610.470-k
 *  Fecha: 16/11/2023
 */


//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char* nombre_archivo_aventuras_programadas = "aventuras_programadas.txt";
const char* nombre_archivo_aventuras_disponibles = "aventuras_disponibles.txt";

typedef struct aventura_disponible {
	char* nombre_aventura;
	int* fecha;
	int* hora;
	int capacidad_max;
} aventura_disponible;

typedef struct aventura_programada {
	int* fecha;
	int* hora;
	char* nombre_aventura;
	char* nombre_cliente;
	int cantidad_personas;
	char* estado_reserva;
} aventura_programada;

aventura_disponible* agregarAventuraDisponible(aventura_disponible* old_arreglo_aventuras_disponibles, int* n_ad, aventura_disponible new_aventura_disponible) {
    /*
     * input:   old_arreglo_aventuras_disponibles: arreglo original de venturas disponibles
     *          n_ad: tamaño de arreglo old_arreglo_aventuras_disponibles
     *          new_aventura_disponible: Nueva Aventura Disponible a agregar en el arreglo old_arreglo_aventuras_disponibles
     * output:  Retorna un nuevo arreglo de aventuras disponibles
     * remarks: Esta función agrega un nuevo elemento al arreglo de aventuras disponibles.
    */

	aventura_disponible* nuevo_arreglo_aventuras_disponibles = (aventura_disponible*)malloc(sizeof(aventura_disponible) * (*n_ad + 1));
	
	for (int i = 0; i < *n_ad; ++i) {
		nuevo_arreglo_aventuras_disponibles[i] = old_arreglo_aventuras_disponibles[i];
	}
	
	nuevo_arreglo_aventuras_disponibles[*n_ad] = new_aventura_disponible;
	*n_ad = *n_ad + 1;
	free(old_arreglo_aventuras_disponibles);

	return nuevo_arreglo_aventuras_disponibles;
}

aventura_programada* agregarAventuraProgramada(aventura_programada* old_arreglo_aventuras_programadas, int* n_ap, aventura_programada new_aventura_programada) {
    /*
     * input:   old_arreglo_aventuras_programadas: arreglo original de aventuras programadas
     *          n_ap: tamaño de arreglo old_arreglo_aventuras_disponibles
     *          new_aventura_programada: Nueva Aventura programada a agregar en el arreglo old_arreglo_aventuras_programadas
     * output:  Retorna un nuevo arreglo de aventuras programadas
     * remarks: Esta función agrega un nuevo elemento al arreglo de aventuras programadas.
    */

	aventura_programada* nuevo_arreglo_aventuras_programadas = (aventura_programada*)malloc(sizeof(aventura_programada) * (*n_ap + 1));
	
	for (int i = 0; i < *n_ap; ++i) {
		nuevo_arreglo_aventuras_programadas[i] = old_arreglo_aventuras_programadas[i];
	}
	
	nuevo_arreglo_aventuras_programadas[*n_ap] = new_aventura_programada;
	*n_ap = *n_ap + 1;
	free(old_arreglo_aventuras_programadas);

	return nuevo_arreglo_aventuras_programadas;
}

int * agregaIndiceCliente (int* old_arreglo_aventura_programada_cliente, int* n_ap_cl, int nuevo_indice) {
    /*
     * input:   old_arreglo_aventura_programada_cliente: Arreglo original que contiene los indices de una aventura programada de un cliente
     *          n_ap_cl: Tamaño de arreglo old_arreglo_aventura_programada_cliente
     *          nuevo_indice: Nuevo indice a agregar en el arreglo old_arreglo_aventura_programada_cliente
     * output:  Retorna un nuevo arreglo de aventuras programadas
     * remarks: Esta función agrega un nuevo elemento al arreglo de aventuras programadas.
    */

    int* nuevo_arreglo_aventura_programada_cliente = (int*) malloc(sizeof(int) * (*n_ap_cl + 1));
    for (int i = 0; i < *n_ap_cl; ++i) {
        nuevo_arreglo_aventura_programada_cliente[i] = old_arreglo_aventura_programada_cliente[i];
    }
    nuevo_arreglo_aventura_programada_cliente[*n_ap_cl] = nuevo_indice;
    *n_ap_cl = *n_ap_cl + 1;
    free(old_arreglo_aventura_programada_cliente);

    return nuevo_arreglo_aventura_programada_cliente;
}

int evaluaEntero(int inicio, int fin) {
    /*
     * input:   inicio: Entero que contiene valor en ASCII de valor 1
     *          fin: Entero que contiene valor en ASCII de tamaño maximo que tiene un arreglo
     * output:  Entero que entrega numero original a evaluar
     * remarks: Esta función evalua si el usuario ingreso un numero entero y no otro caracter.
    */

    int num = 0, ch;
    printf("\n\nOpcion elegida: ");

    do {
    	ch = getchar();    
    	// Evalua si es entero entre 1 y 9
    	if (ch >= inicio && ch <= fin) {
 	    	// Vuelve a ser digito
        	num = num * 10 + (ch - 48);
    }
        // 13 is carriage return it breaks and return the input
        if (ch == '\n')
            break;
    } while (1);
 
    return (num);
}

void mostrarFechaHora(int* fecha, int* hora) {
    /*
     * input:   fecha: Arreglo de entero que contiene fecha de aventura.
     *          hora: Arreglo de entero que contiene hora de aventura.
     * output:  Sin retorno
     * remarks: Esta función imprime en pantalla con formato correcto la hora y fecha.
    */

    printf("Fecha: ");
    for (int i = 0; i < 3; ++i) {
    	fecha[i] < 10 ? printf("0%d", fecha[i]) : printf("%d", fecha[i]);
        if (i >= 0 & i < 2)
            printf("/");

    }

    printf("\nHora: ");
    for (int i = 0; i < 2; i++) {
        hora[i] < 10 ? printf("0%d", hora[i]) : printf("%d", hora[i]);
        if (i >= 0 & i < 1)
            printf(":");

    }
}

int evaluaExistencia(int* n, int tipo_arreglo) {
    /*
     * input:   n: Entero puntero de que es el tamaño de un arreglo a evaluar.
     *          tipo_arreglo: Entero que puede ser 1 o 2 y que representa si el arreglo a evaluar es de Aventura Programada o Aventura Disponible.
     * output:  Entero que puede ser 1 o 0.
     * remarks: Esta función evalua si el arreglo contiene elementos, en caso de contener 1 o mas elementos, entrega 1, sino 0.
    */

    int bool = 0;
    char ave_pro[22] = "Aventuras Programadas"; //1
    char ave_dis[22] = "Aventuras Disponibles"; //2

    if (*n > 0) {
        bool = 1;
    } else {
        printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
        tipo_arreglo == 1 ? printf("No existen %s para mostrar =(\n", ave_pro) : printf("No existen %s para mostrar =(\n", ave_dis);
        printf("xxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
    }

    return bool;
}

void mostrarAventurasDisponibles(aventura_disponible* arreglo_aventuras_disponibles, int* n_ad) {
    /*
     * input:   arreglo_aventuras_disponibles: Arreglo que contiene aventuras disponibles.
     *          n_ad: Tamaño de arreglo_aventuras_disponibles.
     * output:  Sin retorno.
     * remarks: Esta función imprime el arreglo_aventuras_disponibles por pantalla.
    */

    printf("\n************ Listado de Aventuras Disponibles ************\n");
    for (int i = 0; i < *n_ad; i++) {
        printf("\nAventura Disponible numero: %d\n", i + 1);
        printf("-----------------------------\n");
        printf("Nombre aventura: %s\n", arreglo_aventuras_disponibles[i].nombre_aventura);
        mostrarFechaHora(arreglo_aventuras_disponibles[i].fecha, arreglo_aventuras_disponibles[i].hora);
        printf("\nCapacidad maxima: %d\n\n", arreglo_aventuras_disponibles[i].capacidad_max);
    }
}

void mostrarAventurasProgramadas(aventura_programada* arreglo_aventuras_programadas, int* n_ap) {
    /*
     * input:   arreglo_aventuras_programadas: Arreglo que contiene aventuras programadas.
     *          n_ap: Tamaño de arreglo_aventuras_programadas.
     * output:  Sin retorno.
     * remarks: Esta función imprime el arreglo_aventuras_programadas por pantalla.
    */

    printf("\n************ Listado de Aventuras Programadas ************\n");
    for (int i = 0; i < *n_ap; i++) {
        printf("\nAventura Programada numero: %d\n", i + 1);
        printf("-----------------------------\n");
        mostrarFechaHora(arreglo_aventuras_programadas[i].fecha, arreglo_aventuras_programadas[i].hora);
        printf("\nNombre aventura: %s\n", arreglo_aventuras_programadas[i].nombre_aventura);
        printf("Nombre de Cliente: %s\n", arreglo_aventuras_programadas[i].nombre_cliente);
        printf("Cantidad de Personas: %d\n", arreglo_aventuras_programadas[i].cantidad_personas);
        printf("Estado de la Reserva: %s\n\n", arreglo_aventuras_programadas[i].estado_reserva);
    }
}

aventura_disponible cambiarFechaHoraEnteroDisponible(aventura_disponible nueva_aventura_disponible, char* arreglo_fecha, char* arreglo_hora) {
    /*
     * input:   nueva_aventura_disponible: Struct de Aventuras Disponible.
     *          arreglo_fecha: Arreglo de char (String) que contiene una fecha en caracteres.
     *          arreglo_hora: Arreglo de char (String) que contiene una hora en caracteres.
     * output:  Struct de Aventura Disponible.
     * remarks: Esta función extrae del String los enteros, los parsea y los guarda en el arreglo interno de fecha y
     *          hora del tipo entero, dentro del Struct de Aventura Disponible.
    */

    char *cursor = arreglo_fecha;
    char *cursor2 = arreglo_hora;
    long int split_date;
    int i = 0;

    nueva_aventura_disponible.fecha = (int*)malloc(sizeof(int) * 3);
    while (cursor != arreglo_fecha + strlen(arreglo_fecha)) {
        split_date = strtol(cursor, &cursor, 10);
        nueva_aventura_disponible.fecha[i] = (int)split_date;
        while (*cursor == '/' || *cursor == ' ') {
            cursor++;
        }
        i++;
    }

    i = 0;
    nueva_aventura_disponible.hora = (int*)malloc(sizeof(int) * 2);
    while (cursor2 != arreglo_hora + strlen(arreglo_hora)) {
        split_date = strtol(cursor2, &cursor2, 10);
        nueva_aventura_disponible.hora[i] = (int)split_date;
        while (*cursor2 == ':' || *cursor2 == ' ') {
            cursor2++;
        }
        i++;
    }

    return nueva_aventura_disponible;
}

aventura_programada cambiarFechaHoraEnteroProgramada(aventura_programada nueva_aventura_programada, char* arreglo_fecha, char* arreglo_hora) {
    /*
     * input:   nueva_aventura_programada: Struct de Aventuras Programada.
     *          arreglo_fecha: Arreglo de char (String) que contiene una fecha en caracteres.
     *          arreglo_hora: Arreglo de char (String) que contiene una hora en caracteres.
     * output:  Struct de Aventura Programada.
     * remarks: Esta función extrae del String los enteros, los parsea y los guarda en el arreglo interno de fecha y
     *          hora del tipo entero, dentro del Struct de Aventura Programada.
    */

    char *cursor = arreglo_fecha;
    char *cursor2 = arreglo_hora;
    long int split_date;
    int i = 0;

    nueva_aventura_programada.fecha = (int*)malloc(sizeof(int) * 3);
    while (cursor != arreglo_fecha + strlen(arreglo_fecha)) {
        split_date = strtol(cursor, &cursor, 10);
        nueva_aventura_programada.fecha[i] = (int)split_date;
        while (*cursor == '/' || *cursor == ' ') {
            cursor++;
        }
        i++;
    }

    i = 0;
    nueva_aventura_programada.hora = (int*)malloc(sizeof(int) * 2);
    while (cursor2 != arreglo_hora + strlen(arreglo_hora)) {
        split_date = strtol(cursor2, &cursor2, 10);
        nueva_aventura_programada.hora[i] = (int)split_date;
        while (*cursor2 == ':' || *cursor2 == ' ') {
            cursor2++;
        }
        i++;
    }

    return nueva_aventura_programada;
}

aventura_disponible crearAventuraDisponible() {
    /*
     * input:   Sin argumentos.
     * output:  Struct de Aventura Disponible.
     * remarks: Esta función crea un Struct de Aventura Disponible, preguntando al usuario por los datos.
    */

    aventura_disponible nueva_aventura_disponible;
    char arreglo_nombre[90];
    char arreglo_fecha[20];
    char arreglo_hora[10];
    long int posicion;

    printf("\n************ Creación de Aventura Disponible ************\n");
    nueva_aventura_disponible.nombre_aventura = (char*) malloc(sizeof(char) * 100);
    printf("\nIngrese el nombre de la nueva aventura: ");
    //En caso de error n:99
    fgets(arreglo_nombre, 90, stdin);

    posicion = strlen(arreglo_nombre);
    arreglo_nombre[posicion - 1] = '\0'; //Elimina '\n' de la cadena de caracteres leida, '\0' = 0;
    strcpy(nueva_aventura_disponible.nombre_aventura, arreglo_nombre); //Copia String

    printf("\nIngrese la fecha de la nueva aventura (formato DD/MM/YYYY): ");
    fgets(arreglo_fecha, 20, stdin);
    posicion = 0;
    posicion = strlen(arreglo_fecha);
    arreglo_fecha[posicion- 1] = '\0';

    printf("\nIngrese la hora en que se realizara la nueva aventura (formato HH:SS): ");
    fgets(arreglo_hora, 10, stdin);
    posicion = 0;
    posicion = strlen(arreglo_hora);
    arreglo_hora[posicion - 1] = '\0';

    //TODO: Verificar que la fecha tenga el formato DD/MM/YYYY y hora HH:MM y  que sean fechas y horas coherentes.
    /*
     * Code
     */

    nueva_aventura_disponible = cambiarFechaHoraEnteroDisponible(nueva_aventura_disponible, arreglo_fecha, arreglo_hora);

    printf("\nIngrese la capacidad maxima de la nueva aventura: ");
    scanf("%d", &nueva_aventura_disponible.capacidad_max);

    return nueva_aventura_disponible;
}

int agendarCuposAventurasDisponibles(aventura_disponible* arreglo_aventura_disponibles, int cupos, char* nombre_aventura, int n) {
    /*
     * input:   arreglo_aventura_disponibles: Arreglo que contiene Struct de Aventura Disponible
     *          cupos: Entero que representa los cupos a agendar de una Aventura Disponible
     *          nombre_aventura: Arreglo de char (String) que contiene el nombre de la aventura a agendar
     *          n: Tamaño del arreglo_aventura_disponibles.
     * output:  Entero que representa si se pudo agendar cupos de una Aventura Disponible.
     * remarks: Esta función permite evaluar si existen cupos y si estos no son menores que los cupos que quiere reservar
     *          un cliente.
    */

    int i, existe = 0, posicion = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(arreglo_aventura_disponibles[i].nombre_aventura, nombre_aventura) == 0) {
            posicion = i;
            if (arreglo_aventura_disponibles[i].capacidad_max >= cupos) {
                arreglo_aventura_disponibles[i].capacidad_max = arreglo_aventura_disponibles[i].capacidad_max - cupos;
                existe = 1;
            }
        }
    }
    if (existe == 1) {
        printf("\n-------------------- o --------------------\n");
        printf("Se han reservado %d cupos de la Aventura Disponible '%s'\n", cupos, nombre_aventura);
        printf("-------------------- o --------------------\n");
    } else {
        printf("\n-------------------- o --------------------\n");
        printf("La cantidad de cupos a reservar (%d) excede el limite disponible (%d) de la Aventura Disponible '%s'\n", cupos, arreglo_aventura_disponibles[posicion].capacidad_max, nombre_aventura);
        printf("-------------------- o --------------------\n");
    }

    return existe;
}

aventura_programada crearAventuraProgramada(aventura_disponible* arreglo_aventura_disponible, int* n_ad, int indice_aventura_disponible) {
    /*
     * input:   arreglo_aventura_disponibles: Arreglo que contiene Struct de Aventura Disponible
     *          n_ad: Entero puntero que representa el tamaño del arreglo_aventura_disponibles
     *          indice_aventura_disponible: Entero que indica la aventura disponible que quiere agendar un cliente
     * output:  Struct de una Aventura Programada.
     * remarks: Esta función permite crear una Aventura Programada, preguntando al usuario por sus datos y extrayendo los demas
     *          del arreglo_aventuras_disponibles.
    */

    aventura_programada nueva_aventura_programada;
    char programada[] = "Programada";
    char arreglo_nombre[90];
    long int posicion;
    int i = 0, tamano_arreglo_aventura_disponible = *n_ad;
    time_t t = time(NULL); //Evaluar si se puede enviar por parametros.
    struct tm date = *localtime(&t);

    //Ingresar y Guardar nombre
    printf("\n************ Creación de Aventura Programada ************\n");
    nueva_aventura_programada.nombre_cliente = (char*) malloc(sizeof(char) * 100);
    printf("\nIngrese el nombre del cliente: ");
    fgets(arreglo_nombre, 90, stdin);

    posicion = strlen(arreglo_nombre);
    arreglo_nombre[posicion - 1] = '\0'; //Elimina '\n' de la cadena de caracteres leida, '\0' = 0;
    strcpy(nueva_aventura_programada.nombre_cliente, arreglo_nombre); //Copia y asigna String

    //Obtener fecha y hora y asignar
    nueva_aventura_programada.fecha = (int*)malloc(sizeof(int) * 3);
    nueva_aventura_programada.fecha[0] = date.tm_mday;
    nueva_aventura_programada.fecha[1] = date.tm_mon+1;
    nueva_aventura_programada.fecha[2] = date.tm_year+1900;

    nueva_aventura_programada.hora = (int*)malloc(sizeof(int) * 2);
    nueva_aventura_programada.hora[0] = date.tm_hour;
    nueva_aventura_programada.hora[1] = date.tm_min;

    //Asignar nombre aventura
    nueva_aventura_programada.nombre_aventura = (char*)malloc(sizeof(char) * 100);
    strcpy(nueva_aventura_programada.nombre_aventura, arreglo_aventura_disponible[indice_aventura_disponible].nombre_aventura);

    //Asignar estado reserva
    nueva_aventura_programada.estado_reserva = (char*)malloc(sizeof(char) * 15);
    strcpy(nueva_aventura_programada.estado_reserva, programada);

    //Asignar cantidad de personas y cupos para la aventura
    do {
        printf("\nIngrese la cantidad de personas que van a participar en la aventura '%s': ", nueva_aventura_programada.nombre_aventura);
        scanf("%d", &nueva_aventura_programada.cantidad_personas);
        i = agendarCuposAventurasDisponibles(arreglo_aventura_disponible, nueva_aventura_programada.cantidad_personas, nueva_aventura_programada.nombre_aventura, tamano_arreglo_aventura_disponible);
    } while (i == 0);

    return nueva_aventura_programada;
}

aventura_programada* eliminarAventuraProgramada(aventura_programada* old_arreglo_aventura_programada, int* n_ap, int posicion_aventura) {
    /*
     * input:   old_arreglo_aventura_programada: Arreglo original que contiene Struct de Aventura Programadas
     *          n_ap: Entero puntero que representa el tamaño del old_arreglo_aventura_programada
     *          posicion_aventura: Entero que representa la aventura programada a eliminar
     * output:  Nuevo arreglo de Struct de Aventura Programada.
     * remarks: Esta función permite eliminar una Aventura Programada del arreglo old_arreglo_aventura_programada.
    */

    int cont = 0;
    int i;
    aventura_programada * nuevo_arreglo_aventura_programada = (aventura_programada *) malloc(sizeof(aventura_programada ) * (*n_ap - 1));
    for (i = 0; i < *n_ap; i++) {
        if (posicion_aventura != i) {
            nuevo_arreglo_aventura_programada[cont] = old_arreglo_aventura_programada[i];
            cont++;
        }
    }

    printf("\n-------------------- o --------------------\n");
    printf("Se ha eliminando la Aventura Programada numero: %d\n", posicion_aventura + 1);
    printf("-------------------- o --------------------\n");

    *n_ap = *n_ap - 1;
    free(old_arreglo_aventura_programada);

    return nuevo_arreglo_aventura_programada;
}

void liberarCuposAventurasDisponibles(aventura_disponible* arreglo_aventura_disponibles, int cupos, char* nombre_aventura, int n) {
    /*
     * input:   arreglo_aventura_disponibles: Arreglo que contiene Struct de Aventura Disponibles
     *          cupos: Entero puntero que representa los cupos a liberar en una Aventura Disponible
     *          nombre_aventura: Arreglo de char (String) que contiene el nombre de la aventura a la cual se le liberar cupos.
     *          n: Entero que contiene el tamaño del arreglo_aventura_disponibles.
     * output:  Sin Retorno.
     * remarks: Esta función permite liberar cupos de una Aventura Disponible.
    */

    int i, existe = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(arreglo_aventura_disponibles[i].nombre_aventura, nombre_aventura) == 0) {
            arreglo_aventura_disponibles[i].capacidad_max = arreglo_aventura_disponibles[i].capacidad_max + cupos;
            existe = 1;
        }
    }
    if (existe == 1) {
        printf("\n-------------------- o --------------------\n");
        printf("Se han liberado %d cupos de la Aventura Programada '%s'\n", cupos, nombre_aventura);
        printf("-------------------- o --------------------\n");
    } else {
        printf("\n-------------------- o --------------------\n");
        printf("No Se ha encontrado la Aventura Programada '%s' en el listado y no se han podido liberar cupos\n", nombre_aventura);
        printf("-------------------- o --------------------\n");
    }
}

int* consultaReservasExistentesCliente(aventura_programada* arreglo_aventura_programada, int* n_ap, char* nombre_cliente, int* n_ap_cl) {
    /*
     * input:   arreglo_aventura_programada: Arreglo que contiene Struct de Aventura Programada.
     *          n_ap: Entero puntero que representa el tamaño del arreglo_aventura_programada.
     *          nombre_cliente: Arreglo de char (String) que contiene el nombre del cliente.
     *          n_ap_cl: Entero puntero que contiene el tamaño del nuevo_arreglo_aventura_programada_cliente.
     * output:  Arreglo de enteros que contiene el indice original de las reservas del cliente en arreglo_aventura_programada.
     * remarks: Esta función permite buscar las reservas de un cliente y guardar en un arreglo la posicion original de estas reservas
     *          en el arreglo_aventura_programada.
    */

    int cont = 0, i;
    *n_ap_cl = 0;

    int* nuevo_arreglo_aventura_programada_cliente = (int*) malloc(sizeof(int) * *n_ap_cl);
    printf("\n************ Listado de Aventuras Programadas del Cliente %s  ************\n", nombre_cliente);
    for (i = 0; i < *n_ap; ++i) {
        if (strcmp(arreglo_aventura_programada[i].nombre_cliente, nombre_cliente) == 0) {
            printf("\nAventura Programada numero: %d\n", cont + 1);
            printf("-----------------------------\n");
            mostrarFechaHora(arreglo_aventura_programada[i].fecha, arreglo_aventura_programada[i].hora);
            printf("\nNombre aventura: %s\n", arreglo_aventura_programada[i].nombre_aventura);
            printf("Nombre de Cliente: %s\n", arreglo_aventura_programada[i].nombre_cliente);
            printf("Cantidad de Personas: %d\n", arreglo_aventura_programada[i].cantidad_personas);
            printf("Estado de la Reserva: %s\n\n", arreglo_aventura_programada[i].estado_reserva);
            nuevo_arreglo_aventura_programada_cliente = agregaIndiceCliente(nuevo_arreglo_aventura_programada_cliente, n_ap_cl, i);
            cont++;
        }
    }

    if (cont == 0) {
        printf("\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        printf("El cliente de nombre %s no tiene aventuras programadas\n", nombre_cliente);
        printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
        nuevo_arreglo_aventura_programada_cliente = NULL;
    }

    return nuevo_arreglo_aventura_programada_cliente;
}

void cancelarAventuraProgramada(aventura_programada* arreglo_aventura_programada, int indice_aventura_cancelada, aventura_disponible* arreglo_aventura_disponible, int* n_ad) {
    /*
     * input:   arreglo_aventura_programada: Arreglo que contiene Struct de Aventura Programada.
     *          indice_aventura_cancelada: Entero que contiene el indice de la Aventura Programada a Cancelar.
     *          arreglo_aventura_disponible: Arreglo que contiene Struct de Aventura Disponible.
     *          n_ad: Entero puntero que tiene el tamaño del arreglo_aventura_disponible.
     * output:  Sin retorno.
     * remarks: Esta función permite cancelar una aventura programada y ademas llama a funcion para liberar cupos correspondientes
     *          a la Aventura Programda.
    */

    char cancelada[] = "Cancelada";
    char* nombre_aventura_cancelada = (char*) malloc(sizeof(char) * 110);
    int cantidad = *n_ad;

    strcpy(nombre_aventura_cancelada, arreglo_aventura_programada[indice_aventura_cancelada].nombre_aventura); //Copia String

    if (strcmp(arreglo_aventura_programada[indice_aventura_cancelada].estado_reserva, cancelada) != 0) {
        arreglo_aventura_programada[indice_aventura_cancelada].estado_reserva = "Cancelada";
        printf("\n-------------------- o --------------------\n");
        printf("Se ha cancelado la Aventura Programada del cliente '%s'\n", arreglo_aventura_programada[indice_aventura_cancelada].nombre_cliente);
        printf("-------------------- o --------------------\n");
        liberarCuposAventurasDisponibles(arreglo_aventura_disponible, arreglo_aventura_programada[indice_aventura_cancelada].cantidad_personas, nombre_aventura_cancelada, cantidad);
    } else {
        printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
        printf("La aventura seleccionada ya esta con Reserva Cancelada\n");
        printf("xxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
    }
}

aventura_programada* leerArchivoAventurasProgramadas(const char* nombre_archivo, int* n_ap) {
    /*
     * input:   nombre_archivo: Constante que es un arreglo de char (String) que contiene el nombre del archivo que tiene las aventuras programadas.
     *          n_ap: Entero puntero que contiene el tamaño del arreglo de Aventuras Programadas.
     * output:  Arreglo que contiene Struct de Aventura Programada.
     * remarks: Esta función permite leer el archivo 'aventuras_programadas.txt' que contiene la informacion de las Aventuras Programadas y entregar
     *          un arreglo con esta informacion.
    */

    int n, i;
    char arreglo_fecha[20];
    char arreglo_hora[10];
    FILE* in;

    in = fopen(nombre_archivo, "r");
    aventura_programada* arreglo_aventura_programada;

    if (in != NULL) {
        fscanf(in, "%d", n_ap);
        printf("AP: %d", *n_ap);
        arreglo_aventura_programada = (aventura_programada*) malloc(sizeof(aventura_programada) * *n_ap);

        for (i = 0; i < *n_ap ; i++) {
            arreglo_aventura_programada[i].fecha = (int*)malloc(sizeof(int) * 3);
            arreglo_aventura_programada[i].hora = (int*)malloc(sizeof(int) * 2);
            arreglo_aventura_programada[i].nombre_aventura = (char*)malloc(sizeof(char) * 100);
            arreglo_aventura_programada[i].nombre_cliente = (char*)malloc(sizeof(char) * 100);
            arreglo_aventura_programada[i].estado_reserva = (char*)malloc(sizeof(char) * 15);

            fscanf(in, "%19[^,], %9[^,], %99[^,], %99[^,], %d, %14[^\n]\n", arreglo_fecha, arreglo_hora, arreglo_aventura_programada[i].nombre_aventura, arreglo_aventura_programada[i].nombre_cliente, &arreglo_aventura_programada[i].cantidad_personas, arreglo_aventura_programada[i].estado_reserva);
            arreglo_aventura_programada[i] = cambiarFechaHoraEnteroProgramada(arreglo_aventura_programada[i], arreglo_fecha, arreglo_hora);
        }
        fclose(in);
    } else {
        printf("El archivo %s, no pudo ser leído correctamente", nombre_archivo_aventuras_programadas);
        fclose(in);
    }

    return arreglo_aventura_programada;
}

aventura_disponible* leerArchivoAventuraDisponible(const char* nombre_archivo, int* n_ad) {
    /*
     * input:   nombre_archivo: Constante que es un arreglo de char (String) que contiene el nombre del archivo que tiene las aventuras disponibles.
     *          n_ad: Entero puntero que contiene el tamaño del arreglo de Aventuras Disponibles.
     * output:  Arreglo que contiene Struct de Aventura Disponibles.
     * remarks: Esta función permite leer el archivo 'aventuras_disponibles.txt' que contiene la informacion de las Aventuras Disponibles y entregar
     *          un arreglo con esta informacion.
    */

    int i;
    char arreglo_fecha[20];
    char arreglo_hora[10];
    char arreglo_nombre[100];

    FILE* in;
    in = fopen(nombre_archivo, "r, css=UTF-8");
    aventura_disponible* arreglo_aventura_disponible;

    if (in != NULL) {
        fscanf(in, "%d", n_ad);
        printf("AD: %d", *n_ad);
        arreglo_aventura_disponible = (aventura_disponible*) malloc(sizeof(aventura_disponible ) * *n_ad);

        for (i = 0; i < *n_ad ; i++) {
            arreglo_aventura_disponible[i].fecha = (int*)malloc(sizeof(int) * 3);
            arreglo_aventura_disponible[i].hora = (int*)malloc(sizeof(int) * 2);
            arreglo_aventura_disponible[i].nombre_aventura = (char*)malloc(sizeof(char) * 100);

            fscanf(in, "%99[^,], %19[^,], %9[^,], %d\n", arreglo_nombre, arreglo_fecha, arreglo_hora, &arreglo_aventura_disponible[i].capacidad_max);
            //Elimina primer \n
            if (arreglo_nombre[0] == '\n')
                memmove(arreglo_nombre, arreglo_nombre+1, strlen(arreglo_nombre));

            strcpy(arreglo_aventura_disponible[i].nombre_aventura, arreglo_nombre); //Copia string
            arreglo_aventura_disponible[i] = cambiarFechaHoraEnteroDisponible(arreglo_aventura_disponible[i], arreglo_fecha, arreglo_hora);
        }
        fclose(in);
    } else {
        printf("El archivo %s, no pudo ser leído correctamente", nombre_archivo_aventuras_disponibles);
        fclose(in);
    }

    return arreglo_aventura_disponible;
}

void escribirAventuraProgramada(const char* nombre_archivo, aventura_programada* arreglo_aventura_programada, int* n_ap) {
    /*
     * input:   nombre_archivo: Constante que es un arreglo de char (String) que contiene el nombre del archivo que tiene las aventuras programadas.
     *          arreglo_aventura_programada: Arreglo que contiene Struct de Aventuras Programadas
     *          n_ap: Entero puntero que contiene el tamaño del arreglo de Aventuras Programadas.
     * output:  Sin Retorno.
     * remarks: Esta función permite escribir en el archivo 'aventuras_programadas.txt' con la informacion contenida en el arreglo_aventura_programada.
    */

    FILE* out;
    char c0= ',';
    char c1 = '/';
    char c2 = ':';

    out = fopen(nombre_archivo, "w, css=UTF-8");
    fprintf(out, "%d\n", *n_ap);

    for (int i = 0; i < *n_ap; i++) {
        for (int j = 0; j < 3; j++) {
            arreglo_aventura_programada[i].fecha[j] < 10 ? fprintf(out, "0%d", arreglo_aventura_programada[i].fecha[j]) : fprintf(out, "%d", arreglo_aventura_programada[i].fecha[j]);;
            if (j < 2) {
                fprintf(out, "%c", c1);
            } else {
                fprintf(out, "%c ", c0);
            }
        }

        for (int k = 0; k < 2; k++) {
            arreglo_aventura_programada[i].hora[k] < 10 ? fprintf(out, "0%d", arreglo_aventura_programada[i].hora[k]) : fprintf(out, "%d", arreglo_aventura_programada[i].hora[k]);
            if (k < 1) {
                fprintf(out, "%c", c2);
            } else {
                fprintf(out, "%c ", c0);
            }
        }
        fprintf(out, "%s, %s, %d, %s\n", arreglo_aventura_programada[i].nombre_aventura, arreglo_aventura_programada[i].nombre_cliente, arreglo_aventura_programada[i].cantidad_personas, arreglo_aventura_programada[i].estado_reserva);
    }
    fclose(out);
}

void escribirAventuraDisponible(const char* nombre_archivo, aventura_disponible* arreglo_aventura_disponible, int* n_ad) {
    /*
     * input:   nombre_archivo: Constante que es un arreglo de char (String) que contiene el nombre del archivo que tiene las Aventuras Disponibles.
     *          arreglo_aventura_disponible: Arreglo de Struct de Aventuras Disponibles.
     *          n_ad: Entero puntero que contiene el tamaño del arreglo de Aventuras Disponibles.
     * output:  Arreglo que contiene Struct de Aventura Disponibles.
     * remarks: Esta función permite escribir en el archivo 'aventuras_disponibles.txt' con la informacion contenida en el arreglo_aventura_programada.
    */

    FILE* out;
    char c0= ',';
    char c1 = '/';
    char c2 = ':';

    out = fopen(nombre_archivo, "w, css=UTF-8");
    fprintf(out, "%d\n", *n_ad);


    for (int i = 0; i < *n_ad; i++) {
        fprintf(out, "%s, ", arreglo_aventura_disponible[i].nombre_aventura);
        for (int j = 0; j < 3; j++) {
            arreglo_aventura_disponible[i].fecha[j] < 10 ? fprintf(out, "0%d", arreglo_aventura_disponible[i].fecha[j]) : fprintf(out, "%d", arreglo_aventura_disponible[i].fecha[j]);
            if (j < 2) {
                fprintf(out, "%c", c1);
            } else {
                fprintf(out, "%c ", c0);
            }
        }

        for (int k = 0; k < 2; k++) {
            arreglo_aventura_disponible[i].hora[k] < 10 ? fprintf(out, "0%d", arreglo_aventura_disponible[i].hora[k]) : fprintf(out, "%d", arreglo_aventura_disponible[i].hora[k]);
            if (k < 1) {
                fprintf(out, "%c", c2);
            } else {
                fprintf(out, "%c ", c0);
            }
        }
        fprintf(out, "%d\n", arreglo_aventura_disponible[i].capacidad_max);
    }
    fclose(out);
}

int main() {
    //Declaracion de variables globales
	int opcion, n_ad = 0, n_ap = 0;
    int n_ap_cl;
    int* arreglo_aventuras_programadas_cliente;
    long int posicion;

    //Se leen archivos .txt
    aventura_programada* arreglo_aventuras_programadas = leerArchivoAventurasProgramadas(nombre_archivo_aventuras_programadas, &n_ap);
    aventura_disponible * arreglo_aventuras_disponibles = leerArchivoAventuraDisponible(nombre_archivo_aventuras_disponibles, &n_ad);

    printf("\n\n************ Bienvenido a Aventuras Epicas! ************\n");

	do {
        //Imprimen opciones
		printf("\nSeleccione una de las siguientes opciones.\n");
		printf("\nOpciones para CLIENTES:\n");
		printf("1. Visualizacion de Aventuras Disponibles.\n");
		printf("2. Reserva de aventura.\n");
		printf("3. Consulta de Reservas Existentes.\n");
		printf("4. Cancelacion de Reservas.\n");
		printf("\nOpciones para ADMINISTRADORES:\n");
		printf("5. Visualizacion de Todas las Reservas.\n");
		printf("6. Cancelacion de reservas.\n");
		printf("7. Añadir nuevas aventuras.\n");
		printf("8. Eliminar aventuras programadas.\n");
		printf("\n9. Cerrar el programa y guardar cambios.\n");

        //Se lee y evalua que la opcion sea correcta
    	opcion = evaluaEntero(49, 57);

        //Switch con opciones del menu
		switch(opcion) {
			case 1:
                printf("\n************************************************\n");
                printf("     VISUALIZACION DE AVENTURAS DISPONIBLES     ");
                printf("\n************************************************\n");

                //Mostrar aventuras disponibles
                if (evaluaExistencia(&n_ad, 2) != 0) {
                    mostrarAventurasDisponibles(arreglo_aventuras_disponibles, &n_ad);
                }
                break;
			case 2:
                printf("\n************************************************\n");
                printf("               RESERVA DE AVENTURA               ");
                printf("\n************************************************\n");

                //Reserva de aventura
                if (evaluaExistencia(&n_ad, 2) != 0) {
                    mostrarAventurasDisponibles(arreglo_aventuras_disponibles, &n_ad);
                    opcion = 0;
                    do {
                        printf("Ingrese el numero de la Aventura Disponible a reservar");
                        opcion = evaluaEntero(49, n_ad + 48);
                        if (opcion == 0) {
                            printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
                            printf("Opcion no valida!, \n...vuelva a ingresar una opcion entre 1 y %d\n", n_ad);
                            printf("xxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
                        }
                    } while (opcion == 0);
                    if (arreglo_aventuras_disponibles[opcion - 1].capacidad_max > 0) {
                        aventura_programada nueva_aventura_programada = crearAventuraProgramada(arreglo_aventuras_disponibles, &n_ad, opcion - 1);
                        arreglo_aventuras_programadas = agregarAventuraProgramada(arreglo_aventuras_programadas, &n_ap, nueva_aventura_programada);
                    } else {
                        printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
                        printf("No quedan cupos para esta aventura!, \n...seleccione otra aventura que si tenga cupos disponibles.\n");
                        printf("xxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
                    }
                }

				break;
			case 3:
                printf("\n************************************************\n");
                printf("         CONSULTA DE RESERVAS EXISTENTES         ");
                printf("\n************************************************\n");

                //Consulta reservas de un cliente
                char nombre_cliente_consulta[50];
                posicion = 0;
                printf("\nIngrese el nombre del cliente: ");
                fgets(nombre_cliente_consulta, 50, stdin);
                posicion = strlen(nombre_cliente_consulta);
                nombre_cliente_consulta[posicion - 1] = '\0';
                arreglo_aventuras_programadas_cliente = consultaReservasExistentesCliente(arreglo_aventuras_programadas, &n_ap, nombre_cliente_consulta, &n_ap_cl);
                break;
			case 4:
                printf("\n************************************************\n");
                printf("       CANCELACION DE RESERVAS CLIENTE      ");
                printf("\n************************************************\n");

                //Cancela reservas de un cliente
                char nombre_cliente_cancelacion[50];
                posicion = 0;
                printf("\nIngrese el nombre del cliente: ");
                fgets(nombre_cliente_cancelacion, 50, stdin);
                posicion = strlen(nombre_cliente_cancelacion);
                nombre_cliente_cancelacion[posicion - 1] = '\0';

                if (evaluaExistencia(&n_ap, 1) != 0) {
                    arreglo_aventuras_programadas_cliente = consultaReservasExistentesCliente(arreglo_aventuras_programadas, &n_ap, nombre_cliente_cancelacion, &n_ap_cl);
                    if(arreglo_aventuras_programadas_cliente != NULL) {
                        opcion = 0;
                        do {
                            printf("Ingrese el numero de la Aventura Programada del cliente %s a cancelar", nombre_cliente_cancelacion);
                            opcion = evaluaEntero(49, n_ap_cl + 48);
                            if (opcion == 0) {
                                printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
                                printf("Opcion no valida!, \n...vuelva a ingresar una opcion entre 1 y %d\n", n_ap_cl);
                                printf("xxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
                            }
                        } while (opcion == 0);
                        cancelarAventuraProgramada(arreglo_aventuras_programadas, arreglo_aventuras_programadas_cliente[opcion - 1], arreglo_aventuras_disponibles, &n_ad);
                    }
                }
                break;
			case 5:
                printf("\n************************************************\n");
                printf("       VISUALIZACION DE TODAS LAS RESERVAS      ");
                printf("\n************************************************\n");

                //Visualiza todas las reservas
                if (evaluaExistencia(&n_ap, 1) != 0) {
                    mostrarAventurasProgramadas(arreglo_aventuras_programadas, &n_ap);
                }
                break;
			case 6:
                printf("\n************************************************\n");
                printf("          CANCELACION DE RESERVAS ADMIN        ");
                printf("\n************************************************\n");

                //Cancela las reservas para cualquier cliente
                if (evaluaExistencia(&n_ap, 1) != 0) {
                    mostrarAventurasProgramadas(arreglo_aventuras_programadas, &n_ap);
                    opcion = 0;
                    do {
                        printf("Ingrese el numero de la Aventura Programada a cancelar");
                        opcion = evaluaEntero(49, n_ap + 48);
                        if (opcion == 0) {
                            printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
                            printf("Opcion no valida!, \n...vuelva a ingresar una opcion entre 1 y %d\n", n_ap);
                            printf("xxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
                        }
                    } while (opcion == 0);
                    cancelarAventuraProgramada(arreglo_aventuras_programadas, opcion - 1, arreglo_aventuras_disponibles, &n_ad);
                }
				break;
			case 7:
                printf("\n************************************************\n");
                printf("             AÑADIR NUEVAS AVENTURAS            ");
                printf("\n************************************************\n");

                //Añadir nuevas aventuras
                aventura_disponible nueva_aventura_disponible = crearAventuraDisponible();
                arreglo_aventuras_disponibles = agregarAventuraDisponible(arreglo_aventuras_disponibles, &n_ad, nueva_aventura_disponible);
				break;
			case 8:
                printf("\n************************************************\n");
                printf("          ELIMINAR AVENTURAS PROGRAMADAS         ");
                printf("\n************************************************\n");

                //Elimina aventuras programadas
                if (evaluaExistencia(&n_ap, 1) != 0) {
                    mostrarAventurasProgramadas(arreglo_aventuras_programadas, &n_ap);
                    opcion = 0;
                    do {
                        printf("Ingrese el numero de la aventura programada a eliminar");
                        opcion = evaluaEntero(49, n_ap + 48);
                        if (opcion == 0) {
                            printf("\n\nxxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n");
                            printf("Opcion no valida!, \n...vuelva a ingresar una opcion entre 1 y %d\n", n_ap);
                            printf("xxxxxxxxxxxxxxxxxxxx X xxxxxxxxxxxxxxxxxxxx\n\n");
                        }
                    } while (opcion == 0);
                    arreglo_aventuras_programadas = eliminarAventuraProgramada(arreglo_aventuras_programadas, &n_ap, opcion - 1);
                }
                break;
			case 9:
	        	printf("\n\n\n************ Saliendo del programa! ************\n\n\n");
                //Guarda informacion antes de salir
                escribirAventuraProgramada(nombre_archivo_aventuras_programadas, arreglo_aventuras_programadas, &n_ap);
                escribirAventuraDisponible(nombre_archivo_aventuras_disponibles, arreglo_aventuras_disponibles, &n_ad);
                printf(". . . . cambios guardados ;)");
	        	printf("\n\nHasta luego...\n");
				break;
			default:
                //En caso de seleccionar una opcion no valida
                printf("\n\nxxxxxxxxxxxxxxxxxxxx x xxxxxxxxxxxxxxxxxxxx\n");
				printf("Opcion no valida!, \n...vuelva a ingresar una opcion entre 1 y 9\n");
                printf("xxxxxxxxxxxxxxxxxxxx x xxxxxxxxxxxxxxxxxxxx\n\n");
				break;

		}

	} while(opcion != 9);
	
	return 0;
}
