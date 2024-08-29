#include <stdio.h>
int n, res1 = 1, res2;
int main()
{
    scanf("%d", &n);
    while (((n % 3) ^ 1) && n)
    {
        ++res1;
        n = (n << 1) / 3.0;
    }
    if (n)
        n = (n << 1) / 3.0;
    while (n)
    {
        ++res2;
        n = (n << 1) / 3.0;

    }
    printf("%d %d", res1 + res2, res1);
    return 0;
}
