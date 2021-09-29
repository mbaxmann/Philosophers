#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    printf("temps: %ld\n", time.tv_sec);
    sleep(3);
    gettimeofday(&time, NULL);
    printf("temps2: %ld\n", time.tv_sec);
    return (0);
}