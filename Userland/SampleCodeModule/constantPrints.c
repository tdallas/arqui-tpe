#include <constantPrints.h>

static const char weekDays[7][10] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
static const char months[12][11] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

void printTime()
{
    int times[7];
    getAllTimes(times);
    printf("Hora: %d:%d:%d.\n", times[2], times[1], times[0]);
}

void printDate(){
    int times[7];
    getAllTimes(times);
    printf("Fecha: %s %d de %s de %d.\n", weekDays[times[3] - 1], times[4], months[times[5]-1], times[6]);
}

void printTimeUTC(){
    printf("Zona horaria: UTC %d.\n", getTimeUTC());
}