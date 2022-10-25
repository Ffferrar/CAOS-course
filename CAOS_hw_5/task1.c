/*
Реализуйте функцию на языке ассемблера x86 (IA-32) или x86-64 с сигнатурой:
extern void summ(int N, const int *A, const int *B, int *R);
Функция вычисляет значения Ri=Ai+Bi для всех i от 0 до N.
Память для хранения массива-результата уже выделена.
*/

#include <stdlib.h>
#include <stdio.h>

extern void sum(int N, const int *A, const int *B, int *R);

int main()
{

    int N = 0;
    scanf("%d", &N);

    int* A = malloc(sizeof(int) * N);
    int* B = malloc(sizeof(int) * N);
    int* R = malloc(sizeof(int) * N);

    for (int i = 0; i < N; ++i) {
        scanf("%d", A + i);
    }

    for (int i = 0; i < N; ++i) {
        scanf("%d", B + i);
    }
    
    sum(N, A, B, R);

    for (int i = 0; i < N; ++i) {
        printf("%d\n", R[i]);
    }

    free(A);
    free(B);
    free(R);

    return 0;
}

