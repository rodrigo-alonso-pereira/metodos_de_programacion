#include <stdio.h>
#include <stdlib.h>

/*
 * Un abuelo quiere repartir sus monedas entre sus 3 nietos
 * tiene:
 *  - 10 monedas de 500
 *  _ 50 monedas de 100
 *  - 100 monedas de 50
 *  - 500 monedas de 10
 *  - teniendo un total de $20.000 y 660 monedas
 * Quiere que:
 * El nieto MAYOR tenga al menos el 50% del total del monto
 * El nieto MENOR que tiene menos nocion del valor del dinero que tenga la mayor cantidad de monedas que los 3.
 * el nieto del MEDIO quiere que tenga al menos un 20% del monto total.
 */

/*
 * Estructura de la soluciones
 * Hermano menor (x): x10 = cantidad de monedas de 10 que tiene el menor (x10, x50, x100, x500)
 * Hermano del medio (y) = y10, y50, y100, y500
 * Hermano mayor (z) = z10, z50, z100, z500
 */

/*
 * z10*10 + z50*50 + z100*100 + z500*500 >= 10.000 MAYOR
 * y10*10 + y50*50 + y100*100 + y500*500 >= 4.000 MEDIO
 * x10 + x50 + x100 + x500 > z10 + z50 + z100 + z500 + y10 + y50 + y100 + y500
 * x10 + y10 + z10 = 500
 * x50 + y50 + z50 = 100
 * x100 + y100 + z100 = 50
 * x500 + y500 + z500 = 10
 */
int verificar(int x10, int x50, int x100, int x500, int y10, int y50, int y100, int y500, int z10, int z50, int z100, int z500) {
    //printf("(x10:%d, x50:%d, x100:%d, x500:%d) - (y10:%d, y50:%d, y100:%d, y500:%d) - (z10:%d, z50:%d, z100:%d, z500:%d)", x10, x50, x100, x500, y10, y50, y100, y500, z10, z50, z100, z500);
    int v1 = z10 * 10 + z50 * 50 + z100 * 100 + z500 * 500 >= 10.000;
    int v2 = y10 * 10 + y50 * 50 + y100 * 100 + y500 * 500 >= 4.000;
    int v3 = (x10 + x50 + x100 + x500 >= y10 + y100 + y100 + y500) && (x10 + x50 + x100 + x500 >= z10 + z100 + z100 + z500);

    return (v1 && v2 && v3);
}

//Solucion (0, 0, 0,
int main() {
    int x10, x50, x100, x500, y10, y50, y100, y500, z10, z50, z100, z500;
    for (x10 = 0; x10 < 500; x10++) {
        for (x50 = 0; x50 < 100; x50++) {
            for (x100 = 0; x100 < 50; x100++) {
                for (x500 = 0; x500 < 10; x500++) {
                    for (y10 = 0; y10 < 500; y10++) {
                        for (y50 = 0; y50 < 100; y50++) {
                            for (y100 = 0; y100 < 50; y100++) {
                                for (y500 = 0; y500 < 10; y500++) {
                                    z10 = 500 - (x10 + y10);
                                    z50 = 100 - (x50 + y50);
                                    z100 = 50 - (x100 + y100);
                                    z500 = 10 - (x500 + y500);
                                    if (verificar(x10, x50, x100, x500, y10, y50, y100, y500, z10, z50, z100, z500)) {
                                        printf("Solucion encontrada: x10:%d, x50:%d, x100:%d, x500:%d, y10:%d, y50:%d, y100:%d, y500:%d, z10:%d, z50:%d, z100:%d, z500:%d", x10, x50, x100, x500, y10, y50, y100, y500, z10, z50, z100, z500);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}