/*
 *  Universidad de Santiago de Chile _ Ing. Ejecucion en Computacion e Informatica
 *  Laboratorio 02: Accion Climatica
 *  Lenguaje aplicado: C.
 *  Alumno: Rodrigo Pereira Yañez
 *  Rut: 16.610.470-k
 *  Fecha: 03/12/2023
 */

//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>

//Macro que contiene el nombre archivo .txt
#define nombre_archivo_temperaturas "temperaturas.txt"
//arreglo global con meses del año
char meses[][10] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre","Noviembre", "Diciembre"};
//Condiciones limites
int limite_max = 30; //Limite de temperatura para ser considerada extremo calido
int limite_min = 10; //Limite de temperatura para ser considerada extremo frio
float dif_porcentual = 0.2; //Porcentaje definido para verificar diferencia porcentual de los años atipicos

//Struct de temperaturas
typedef struct registro_temperaturas {
    int fecha;
    int* temperaturas;
    int size;
} registro_temperaturas;

registro_temperaturas* agregarRegistroTemperaturas(registro_temperaturas* old_arreglo_registro_temperatura, int** n_rt, registro_temperaturas nuevo_registro_temperaturas) {
    /*
     * input:   - old_arreglo_aventuras_disponibles: Arreglo original que contiene los primeros struct 'registro_temperaturas'
     *          - n_rt: Entero puntero que contiene el tamaño del arreglo 'old_arreglo_registro_temperatura'
     *          - nuevo_registro_temperaturas: Struct registro_Temperaturas que se va a ingresar al nuevo arreglo
     * output:  - nuevo_arreglo_registro_temperaturas: Nuevo arreglo de struct que contiene el 'nuevo_registro_temperaturas'
     * remarks: Funcion que permite agregar de forma dinamica un nuevo 'registro_temperaturas' al arreglo y entrega un
     *          nuevo arreglo con 'registro_temperaturas', además modifica el puntero n_rt sumandole 1.
    */

    int i;

    registro_temperaturas* nuevo_arreglo_registro_temperaturas = (registro_temperaturas*)malloc(sizeof(registro_temperaturas) * (**n_rt + 1));

    for (i = 0; i < **n_rt; ++i) {
        nuevo_arreglo_registro_temperaturas[i] = old_arreglo_registro_temperatura[i];
    }
    nuevo_arreglo_registro_temperaturas[**n_rt] = nuevo_registro_temperaturas;
    **n_rt = **n_rt + 1;
    free(old_arreglo_registro_temperatura);

    return nuevo_arreglo_registro_temperaturas;
}

int* agregarEntero(int* old_arreglo_enteros, int* n, int num) {
    /*
     * Input:   - old_arreglo_enteros: Arreglo original que contiene enteros.
                - n: Entero puntero que contiene el tamaño del arreglo 'old_arreglo_entero';
                - num: Entero que contiene el número a agregar en el arreglo de enteros.
     * Output:  - nuevo_arreglo_enteros: Se retorna un nuevo arreglo de enteros que contiene los antiguos y nuevo numero.
     * Remarks: Funcion que permite agregar de forma dinamica un nuevo entero al arreglo del tipo entero puntero y lo
     *          retorna, además modifica el entero puntero n sumandole 1.
     *
    */

    int i;
    int* nuevo_arreglo_enteros = (int*) malloc(sizeof(int) * (*n + 1));
    for (i = 0; i < *n; ++i) {
        nuevo_arreglo_enteros[i] = old_arreglo_enteros[i];
    }
    nuevo_arreglo_enteros[*n] = num;
    *n++;
    free(old_arreglo_enteros);

    return nuevo_arreglo_enteros;
}

void buscarMes(int* arreglo, int n, int num, char* mes) {
    /*
     * Input:   - arreglo: Arreglo de enteros
                - n: Entero que indica el tamaño de arreglo de enteros
                - num: Entero que contiene la temperatura del mes a buscar.
                _ mes: Arreglo de char (String) que contendra el nombre del mes a buscar
     * Output:  - Sin retorno
     * Remarks: Funcion que busca en una arreglo de enteros una temperatura y con base en la posicion, busca en el arreglo
     *          global "meses" el nombre correspondiente y lo entrega por referencia al arreglo de char mes.
     *
    */
    int i;
    for (i = 0; i < n; i++) {
        if (arreglo[i] == num) {
            strcpy(mes, meses[i]);
            return;
        }
    }
}

float promedioTemperaturasExtremas(int num1, int num2) {
    /*
     * Input:   -   num1: Numero entero 1.
                -   num2: Numero entero 2.
     * Output:  - promedio: Numero decimal con valor promedio entre num1 y num2.
     * Remarks: Funcion que calcula el promedio entre dos numeros.
     *
    */
    float promedio = ((float)num1 + (float)num2) / 2;
    return promedio;
}

void mesesExtremos(int* arreglo, int n, char* str, int tipo) {
    /*
     * Input:   - arreglo: Arreglo de enteros que contienen temperaturas.
                - n: Entero que contiene el tamaño del arreglo de enteros
                - str: Arreglo de char en el cual se entregara el resultado con los meses extremos
                - tipo: Entero que contiene 1 o 0 y que indica si se busca los meses más calurosos o frios del arreglo
     * Output:  - Sin retorno
     * Remarks: Funcion que busca en un arreglo de enteros los meses más caluros o frios, segun el límite maximo o minimo
     *          que está definido como variable global. Definido estos meses arma la respuesta en un arreglo de caracteres
     *          que será entregado por referencia en str.
     *
    */
    int i;
    char mes[10];
    char aux[8];

    //Tipo 1: Calurosos >= 30[°C]
    str[0] = '\0';
    if (tipo == 1) {
        for (i = 0; i < n; i++) {
            aux[0] = '\0';
            if (arreglo[i] >= limite_max) {
                strncat(str, meses[i], 256 - strlen(str) - 1);
                sprintf(aux, " (%d°C), ", arreglo[i]);
                strncat(str, aux, 256 - strlen(str) - 1);
            }
        }
        if (str[0] == '\0') {
            strcpy(str, "No hay meses extremandamente calurosos");
        }

    } else { //Tipo 0: Frios <= 10[°C]
        for (i = 0; i < n; i++) {
            aux[0] = '\0';
            if (arreglo[i] <= limite_min) {
                strncat(str, meses[i], 256 - strlen(str) - 1);
                sprintf(aux, " (%d°C), ", arreglo[i]);
                strncat(str, aux, 256 - strlen(str) - 1);
            }
        }
        if (str[0] == '\0') {
            strcpy(str, "No hay meses extremandamente frios");
        }
    }
}

void frecuenciaTemperaturas(int* arreglo, int n, int tipo, float* frecuencia) {
    /*
     * Input:   - arreglo: Arreglo de enteros que contienen temperaturas.
                - n: Entero que contiene el tamaño del arreglo de enteros
                - tipo: Entero que contiene 1 o 0 y que indica si se busca los meses más calurosos o frios del arreglo
                - frecuencia: Float puntero que contiene la frecuencia de los meses más calurosos y frios
     * Output:  - Sin retorno.
     * Remarks: Funcion que calcula la frecuencia de los meses más calurosos y frios segun variable global límite maximo
     *          o minimo. Entrega la frecuencia calculada por referencia en variable frecuencia.
     *
    */

    int i;
    float count = 0;
    *frecuencia = 0;

    if (tipo == 1) {
        for (i = 0; i < n; i++) {
            if (arreglo[i] >= limite_max)
                count++;
        }
        *frecuencia = (count / (float)n) * 100;
        return;
    } else {
        for (i = 0; i < n; i++) {
            if (arreglo[i] <= limite_min)
                count++;
        }
        *frecuencia = (count / (float)n) * 100;
        return;
    }
}

int buscarExtremos(int* arreglo, int inicio, int fin, int tipo) {
    /*
     * Input:   - arreglo: Arreglo de enteros
                - inicio: Entero que contiene la posicion inicial del arreglo de enteros.
                - fin: Entero que contiene la posicion final del arreglo de enteros.
                - tipo: Entero que contiene 1 o 0 y que indica si se busca el maximo o minimo del arreglo
     * Output:  - Entero que contiene el valor maximo o minimo del arreglo.
     * Remarks: Funcion que utiliza Division y Conquista para entregar el valor maximo o minimo de un arreglo. Con la
     *          el entero tipo, define si se busca el extremo mayor (1) o extremo inferior (0)
     *
    */

    if (inicio >= fin) { //Caso base: Arreglo vacio o de 1 elemento.
        return arreglo[inicio];
    } else { //Caso Recursivo: Division en sublistas
        int pivote = (inicio + fin) / 2; //Divide lista a la mitad
        if (tipo == 1) { //1: En caso de busqueda de max.
            int max_izq = buscarExtremos(arreglo, inicio, pivote, tipo); //Busca lista a la izquierda
            int max_der = buscarExtremos(arreglo, pivote + 1, fin, tipo); //Busca lista a la derecha
            return max_izq > max_der ? max_izq : max_der; //Compara maximos y retorna.
        } else { // 0: Busqueda de min.
            int min_izq = buscarExtremos(arreglo, inicio, pivote, tipo); //Busca lista a la izquierda
            int min_der = buscarExtremos(arreglo, pivote + 1, fin, tipo); //Busca lista a la derecha
            return min_izq > min_der ? min_der : min_izq; //Compara minimos y retorna.
        }
    }
}

int aniosAtipicos(float temp_anual, float temp_promedio_total) {
    /*
     * Input:   - temp_anual: Flotante que contiene una temperatura anual
                - temp_promedio_total: Flotante que contiene el promedio de temperaturas anuales
     * Output:  - Entero que puede ser un 1 que indicando si es año atipico o 0 si no es atipico.
     * Remarks: Funcion que define si una temperatura anual es un año atipico, entregando un 1 que indicando si la
     *          diferencia entre el promedio de temperatura anual y una temperatura anual es mayor a un rango definido
     *          en la variable golbal dif_porcentual o 0 si es menor que la diferencia.
     *
    */
    if (fabs((double)(temp_anual - temp_promedio_total)) >= (temp_promedio_total * dif_porcentual))
        return 1;
    return 0;
}

void mostrarRegistroTemperaturas(registro_temperaturas* arreglo_registro_temperaturas, int n) {
    /*
     * Input:   - arreglo_registro_temperatura: Arreglo del tipo registro_temperatura que contiene todos los registros
     *            de temperaturas leidos en el archivo temperaturas.txt
                - n: Entero que contiene el tamaño del arreglo arreglo_registro_temperaturas.
     * Output:  - Sin retorno
     * Remarks: Funcion que recorre el arreglo arreglo_registro_temperaturas y muestra la informacion solicitada, llamando
     *          a cada funcion que realiza un calculo o determina ciertos valores de interes para el usuario.
     *
    */

    int i, max, min, contador = 0;
    float max_f, min_f, suma = 0.0;
    char mes[10];
    char str[256];
    float* temp_extremas = (float*) malloc(sizeof(float) * n + 1);

    //Recorrer registros de temperaturas e imprime
    for (i = 0; i < n; i++) {
        printf("\n");
        printf("Año:%d\n", arreglo_registro_temperaturas[i].fecha);
        max = buscarExtremos(arreglo_registro_temperaturas[i].temperaturas, 0, arreglo_registro_temperaturas[i].size - 1, 1);
        buscarMes(arreglo_registro_temperaturas[i].temperaturas, arreglo_registro_temperaturas[i].size,max, mes);
        printf("Año mas caluroso: %s (%d°C)\n", mes, max);
        min = buscarExtremos(arreglo_registro_temperaturas[i].temperaturas, 0, arreglo_registro_temperaturas[i].size - 1, 0);
        buscarMes(arreglo_registro_temperaturas[i].temperaturas, arreglo_registro_temperaturas[i].size, min, mes);
        printf("Año mas frio: %s (%d°C)\n", mes, min);
        temp_extremas[i] = promedioTemperaturasExtremas(max, min);
        suma += temp_extremas[i];
        printf("Promedio de temperaturas extremas: %.1f°C\n", temp_extremas[i]);
        mesesExtremos(arreglo_registro_temperaturas[i].temperaturas, arreglo_registro_temperaturas[i].size, str, 1);
        printf("Meses extremadamente calurosos: %s\n", str);
        mesesExtremos(arreglo_registro_temperaturas[i].temperaturas, arreglo_registro_temperaturas[i].size, str, 0);
        printf("Meses extremadamente frios: %s\n", str);
        frecuenciaTemperaturas(arreglo_registro_temperaturas[i].temperaturas, arreglo_registro_temperaturas[i].size, 1, &max_f);
        frecuenciaTemperaturas(arreglo_registro_temperaturas[i].temperaturas, arreglo_registro_temperaturas[i].size, 0, &min_f);
        printf("Frecuencia de meses extremos: Calido %.1f%, frio %.1f%\n", max_f, min_f);
    }

    //Imprimir ultimos datos
    temp_extremas[n + 1] = suma / (float)(n); //Guarda promedio de temperaturas extremas por año
    printf("\n\nPromedio temperaturas extremas (%d-%d): %.1f°C\n", arreglo_registro_temperaturas[0].fecha, arreglo_registro_temperaturas[n - 1].fecha, temp_extremas[i + 1]);
    printf("Años atipicos en extremos climaticos: ");

    // Busca años atipicos
    for (int j = 0; j < n; j++) {
        if (aniosAtipicos(temp_extremas[j], temp_extremas[n + 1])) {
            printf("%d ", arreglo_registro_temperaturas[j].fecha);
            contador++;
        }
    }
    //Si no hay años atipicos, imprime
    if (contador == 0)
        printf("No hay años atipicos");
    printf("\n");
}

registro_temperaturas* leerArchivoTemperaturas(char* nombre_archivo, int* n_rt) {
    /*
     * Input:   - nombre_arechivo: Arreglo de char que contiene el nombre del archivo a leer.
                - n_rt: Entero puntero que contiene el tamaño del arreglo de registro de temperaturas
     * Output:  - Arreglo de registro_temperaturas
     * Remarks: Funcion que lee un archivo de temperaturas y lo guarda en un arreglo de registro de temperaturas para luego
     *          ser analizado segun criterios de interes del usuario.
     *
    */

    int i = 0, n_t;
    long int split_num;
    char* cursor;

    //Evalua si se abrio bien el archivo.
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
    registro_temperaturas* nuevo_arreglo_registro_temperaturas = (registro_temperaturas*) malloc(sizeof(registro_temperaturas) * *n_rt);

    //lectura linea por linea
    while (fscanf(archivo, "%[^\n] ", linea_temp) != EOF) {
        cursor = linea_temp; //Define cursor
        n_t = -1; //cantidad de temperaturas, se inicia en -1 por primer valor de lectura.
        registro_temperaturas nuevo_registro_temperaturas;
        int* arreglo_temperaturas = (int*) malloc(sizeof(int) * n_t);

        //Toma elementos de cada linea
        while (cursor != linea_temp + strlen(linea_temp)) {
            if (i == 0) { //Si es linea 0
                split_num = strtol(cursor, &cursor, 10);
                while (*cursor == ',' || *cursor == ' ') {
                    cursor++;
                }
            } else { //Desde linea 1 en adelante
                split_num = strtol(cursor, &cursor, 10);
                if (n_t == -1) { //Si es primer elemento, guarda fecha
                    nuevo_registro_temperaturas.fecha = (int)split_num;
                } else { //Guardado resto de elementos que son temperaturas
                    arreglo_temperaturas = agregarEntero(arreglo_temperaturas, &n_t, (int)split_num);
                }
                while (*cursor == ',' || *cursor == ' ') {
                    cursor++;
                }
            }
            n_t++;
        }
        nuevo_registro_temperaturas.size = n_t;
        nuevo_registro_temperaturas.temperaturas = arreglo_temperaturas;
        if (i != 0)
            nuevo_arreglo_registro_temperaturas = agregarRegistroTemperaturas(nuevo_arreglo_registro_temperaturas, &n_rt, nuevo_registro_temperaturas);
        i++;
    }

    //Cierre archivo y retorna arreglo
    fclose(archivo);
    return nuevo_arreglo_registro_temperaturas;

}

int main() {
    int n_rt = 0;

    //Imprime titulo
    printf("\n\n************ Bienvenido a Analisis Climatico! ************\n");
    //Lee archivo
    registro_temperaturas* arreglo_registro_temperaturas = leerArchivoTemperaturas(nombre_archivo_temperaturas, &n_rt);
    //muestra los registro de temperaturas segun analisis requerido
    mostrarRegistroTemperaturas(arreglo_registro_temperaturas, n_rt);

    return 0;
}