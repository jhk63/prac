
#include <stdio.h>


struct Calculator
{
    int (*op)(int, int);
};

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int main()
{
    int a = 5;
    int b = 2;

    struct Calculator calc;

    calc.op = add;
    printf("%d + %d = %d \n", a, b, calc.op(a, b));

    calc.op = sub;
    printf("%d - %d = %d \n", a, b, calc.op(a, b));

    return 0;
}
