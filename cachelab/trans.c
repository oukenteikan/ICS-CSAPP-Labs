/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"
#include "contracts.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. The REQUIRES and ENSURES from 15-122 are included
 *     for your convenience. They can be removed if you like.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, l;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    int a0, a1, a2, a3, a4, a5, a6, a7;

    if (M == 32 && N == 32)
    for (i = 0 ; i < N ; i += 8) {
	for (j = 0 ; j < M ; j += 8) {
            for (k = i ; k < i + 8 ; k ++) { 
                a0 = A[k][j];
                a1 = A[k][j+1];
                a2 = A[k][j+2];
                a3 = A[k][j+3];
                a4 = A[k][j+4];
                a5 = A[k][j+5];
                a6 = A[k][j+6];
                a7 = A[k][j+7];
                B[j][k] = a0;
                B[j+1][k] = a1;
                B[j+2][k] = a2;
                B[j+3][k] = a3;
                B[j+4][k] = a4;
                B[j+5][k] = a5;
                B[j+6][k] = a6;
                B[j+7][k] = a7;
            }
        }
    }
    else
    if (M == 64 && N == 64)
    {
    for (i = 0 ; i < N ; i += 8) {
        for (j = 0 ; j < M ; j += 8) {
            for (k = i ; k < i + 4 ; k ++) {
                a0 = A[k][j];
                a1 = A[k][j+1];
                a2 = A[k][j+2];
                a3 = A[k][j+3];
                a4 = A[k][j+4];
                a5 = A[k][j+5];
                a6 = A[k][j+6];
                a7 = A[k][j+7];
                B[j][k] = a0;
                B[j+1][k] = a1;
                B[j+2][k] = a2;
                B[j+3][k] = a3;
                B[j][k+4] = a4;
                B[j+1][k+4] = a5;
                B[j+2][k+4] = a6;
                B[j+3][k+4] = a7;
            }
            for (k = j ; k < j + 4; k ++) {
                a0 = B[k][i+4];
                a1 = B[k][i+5];
                a2 = B[k][i+6];
                a3 = B[k][i+7];
                a4 = A[i+4][k];
                a5 = A[i+5][k];
                a6 = A[i+6][k];
                a7 = A[i+7][k];
                B[k][i+4] = a4;
                B[k][i+5] = a5;
                B[k][i+6] = a6;
                B[k][i+7] = a7;
                B[k+4][i] = a0;
                B[k+4][i+1] = a1;
                B[k+4][i+2] = a2;
                B[k+4][i+3] = a3;
            }
            for (k = i + 4 ; k < i + 8 ; k ++) {
                l = j + 4;
                a0 = A[k][l];
                a1 = A[k][l+1];
                a2 = A[k][l+2];
                a3 = A[k][l+3];
                B[l][k] = a0;
                B[l+1][k] = a1;
                B[l+2][k] = a2;
                B[l+3][k] = a3;
            }
        }
    }
    } 
    else
    if (M == 61 && N == 67)
    {
        for (i = 0 ; i < N ; i += 23) {
            for( j = 0 ; j < M ; j += 23) {
                for (k = i ; k < i+23 && k < N ; k ++) {
                    for ( l = j ; l < j+23 && l < M ; l++) {
                        B[l][k]=A[k][l];
                    }
                }
            }
        }
    }
    else
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            B[j][i] = A[i][j];
        }
    }



    ENSURES(is_transpose(M, N, A, B));
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

