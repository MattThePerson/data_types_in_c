#include "fib.h"
#include "types.h"
#include <stdio.h>

void clear_stdin() {
    char ch = '*';
    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

int main() {
    while (1) {
        // user input
        u32 n;
        printf("Give an integer: ");
        if (scanf("%d", &n) != 1) {
            printf("bad boy\n");
            clear_stdin();
            continue;
        }

        // compute fib
        u64 num = fib(n);
        printf("The %dth Fibonacci number is: %llu\n", n, num);
    }
    return 0;
}
