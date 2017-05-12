#include <stdio.h>

#define GREGORIAN_START_YEAR 1583

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day);
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (year < GREGORIAN_START_YEAR)
        return -1;
    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > daytab[leap][month])
        return -1;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday);
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (year < GREGORIAN_START_YEAR)
        return -1;
    if (yearday < 1 || (!leap && yearday > 365) || (leap && yearday > 366))
        return -1;

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;

    return 1;
}

int main ()
{
    int month, day;

    printf("day_of_year(2017, 2, 29) = %d\n", day_of_year(2017, 3, 32));
    printf("day_of_year(2017, 2, 28) = %d\n", day_of_year(2017, 3, 31));

    printf("month_day(2017, 366, &month, &day) = %d\n",
           month_day(2017, 366, &month, &day));
    printf("month_day(2017, 365, &month, &day) = %d, ",
           month_day(2017, 360, &month, &day));
    printf("month = %d, day = %d\n", month, day);

    return 0;
}