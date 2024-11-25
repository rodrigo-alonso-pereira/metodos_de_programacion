#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
	
	//Test time
	time_t t = time(NULL);
	printf(ctime(&t));

    struct tm date = *localtime(&t);

    printf("Dia actual (ctime): %d/%d/%d\n", date.tm_mday, date.tm_mon+1, date.tm_year+1900);
    printf("Hora actual (ctime): %d:%d:%d\n", date.tm_hour, date.tm_min, date.tm_sec);

    char dateString[200];
    strftime(dateString, 200, "%d/%m/%Y", &date);
    printf("Dia actual (strftime): %s\n", dateString);

    char str[] = "09/12/2023";
    char* cursor = str;
    int fecha[3];
    long int split_fecha = 0;
    //int fecha_hora
    int i = 0;
    while (cursor != str + strlen(str)) {
        split_fecha= strtol(cursor, &cursor, 10);
        fecha[i] = (int) split_fecha;
        while (*cursor == '/' || *cursor == ' ') {
            cursor++;
        }
        i++;
    }
    for (int j = 0; j < 3; j++) {
        printf("Fecha %d: %d\n", j, fecha[j]);
    }

	return 0;
}

