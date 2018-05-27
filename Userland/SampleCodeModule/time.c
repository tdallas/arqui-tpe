#include <time.h>

static int UTC = -3;

static const int monthsDays[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static const int lastDayMonths[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const char weekDays[7][10] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

long int time(void *value)
{
    int times[7];
    long int result;
    getAllTimes(times);
    result += times[0];                //Add actual seconds
    result += times[1] * 60;           //Add seconds of minute
    result += times[2] * 60 * 60;      //Add seconds of hour
    result += times[4] * 24 * 60 * 60; //Add seconds of day
    int year = times[6];
    int month = times[5];
    result += monthsDays[month] * 24 * 60 * 60; //Add seconds of month without leaps
    if ((year % 4) == 0 && month > 2)           //if year is leap and we are past febrary adds one day in seconds
    {
        result += 24 * 60 * 60;
    }
    int leapDays = ((int)year / (int)4 - (int)1970 / (int)4) - 1; //Calculate total leap days
    result += leapDays * 24 * 60 * 60;                            //Add seconds of leap days
    year -= 1971;
    result += year * 365 * 24 * 60 * 60; //Adds seconds of year without leaps
    return result;
}

int getSecond()
{
    return systemCall(0, 0, 0, 0, 0, 0);
}

int getMinute()
{
    return systemCall(0, 2, 0, 0, 0, 0);
}

int getHour()
{
    return systemCall(0, 4, 0, 0, 0, 0);
}

int getWeekDay()
{
    return systemCall(0, 6, 0, 0, 0, 0);
}

int getDay()
{
    return systemCall(0, 7, 0, 0, 0, 0);
}

int getMonth()
{
    return systemCall(0, 8, 0, 0, 0, 0);
}

int getYear()
{
    return systemCall(0, 9, 0, 0, 0, 0) + 2000;
}

void getAllTimes(int times[7])
{
    int hour, weekDay, day, month, year, flag = 0;

    times[0] = getSecond();
    times[1] = getMinute();

    hour = getHour() + UTC;
    weekDay = getWeekDay();
    day = getDay();
    month = getMonth();
    year = getYear();

    if (hour < 0)
    {
        hour = 24 + hour;
        flag = -1;
    }
    else if (hour >= 24)
    {
        hour = hour - 24;
        flag = 1;
    }
    times[2] = hour;
    if (flag == -1)
    {
        if (weekDay > 1)
        {
            weekDay--;
        }
        else
        {
            weekDay = 7;
        }
        if (day > 1)
        {
            day--;
        }
        else
        {
            if (month > 1)
            {
                month--;
            }
            else
            {
                year--;
                month = 12;
            }
            day = lastDayMonths[month];
            if (year % 4 == 0 && month == 2)
            { // Leap Year
                day = 29;
            }
        }
    }
    else if (flag == 1)
    {
        if (weekDay < 7)
        {
            weekDay++;
        }
        else
        {
            weekDay = 1;
        }
        if ((day < lastDayMonths[month]) || (year % 4 == 0 && month == 2 && day < 29)) //Last condition is leap year
        {
            day++;
        }
        else
        {
            day = 1;
            if (month < 12)
            {
                month++;
            }
            else
            {
                month = 1;
                year++;
            }
        }
    }
    times[3] = weekDay;
    times[4] = day;
    times[5] = month;
    times[6] = year;

    return;
}

int getTimeUTC()
{
    return UTC;
}

void setTimeUTC(int newUTC)
{
    UTC = newUTC;
}

void printTime(){
    int times[7];
    getAllTimes(times);
    printf("Zona horaria: UTC %d. ", UTC);
    printf("%s %d/%d/%d. ", weekDays[times[3]-1], times[4], times[5], times[6]);
    printf("%d:%d:%d.", times[2], times[1], times[0]);
}