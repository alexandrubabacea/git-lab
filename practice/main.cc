#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <sys/random.h>

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    // Metoda 1
    srand(time(NULL));
    int m1 = rand() % 100;

    // Metoda 2
    int m2 = (int)(rdtsc() % 100);

    // Metoda 3
    int stack_var;
    int m3 = (int)(((uintptr_t)&stack_var) % 100);

    // Metoda 4
    unsigned int val;
    getrandom(&val, sizeof(val), 0);
    int m4 = val % 100;

    // Metoda 5
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    int m5 = ts.tv_nsec % 100;

    printf("Metoda 1 (rand): %d\n", m1);
    printf("Metoda 2 (rdtsc): %d\n", m2);
    printf("Metoda 3 (address): %d\n", m3);
    printf("Metoda 4 (getrandom): %d\n", m4);
    printf("Metoda 5 (nanosec): %d\n", m5);

    return 0;
}