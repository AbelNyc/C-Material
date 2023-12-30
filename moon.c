#include <stdio.h>
#include <time.h>

//determine moon phase using moon's predictable cycle
//map to days, months and years
int moon_phase(int year,int month,int day)
{
    int d,g,e;
 
    d = day;
    if(month == 2)
        d += 31;
    else if(month > 2)
        d += 59+(month-3)*30.6+0.5;
    g = (year-1900)%19;
    e = (11*g + 29) % 30;
    if(e == 25 || e == 24)
        ++e;
    int moon_index = ((((e + d)*6+5)%177)/22 & 7);
    
    printf("The moon index is %d\n", + moon_index);
   
    return moon_index;
};

int main( int argc, char *argv[])
{
    time_t now;
    char message[80];
    struct tm *clock;
    char *phase[] = {
        "waxing crescent", "at first quarter",
        "waxing gibbous", "full", "waning gibbous",
        "at last quarter", "waning crescent", "new"
    };  
    time(&now);
    clock = localtime(&now);
    int mp =  moon_phase( clock->tm_year + 1900, clock->tm_mon, clock->tm_mday);
    sprintf(message, "The moon is %s",phase[mp]);
    puts(message);
};
