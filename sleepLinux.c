#include <stdio.h>
#include <time.h>

void sleep( unsigned int );

int main(){
    printf("3\n");
    sleep(200000);
    printf("2\n");
    sleep(200000);
    printf("1\n");
    sleep(200000);
    printf("Go!");
    sleep(200000);
    
    return 0;
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
