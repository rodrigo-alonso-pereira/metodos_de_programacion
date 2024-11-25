#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	
	//Test time
	time_t t = time(NULL);
	printf(ctime(&t));

    struct tm date = *localtime(&t);
    printf("Dia actual (ctime): %d/%d/%d\n", date.tm_mday, date.tm_mon+1, date.tm_year+1900);
    printf("Hora actual (ctime): %d:%d:%d\n", date.tm_hour, date.tm_min, date.tm_sec);

    char dateString[200];
    strftime(dateString, 200, "%d/%m/%Y", &date);
    printf("Dia actual (strftime): %s\n")



	return 0;
}