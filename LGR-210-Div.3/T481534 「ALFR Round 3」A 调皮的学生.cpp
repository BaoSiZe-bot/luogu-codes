#include <cstdio>
const int N = 1005;
int d[N], res = 0;
int main()
{
    int n, a, b, c;
    scanf("%d%d", &n, &a);
    for (int i = 1; i <= a; ++i)
    {
        int t;
        scanf("%d", &t);
        d[t]++;
    }
    scanf("%d", &b);
    for (int i = 1; i <= b; ++i)
    {
        int t;
        scanf("%d", &t);
        d[t]++;
    }
    scanf("%d", &c);
    for (int i = 1; i <= c; ++i)
    {
        int t;
        scanf("%d", &t);
        d[t]++;
    }
    for (int i = 1; i <= n; ++i)
        if (d[i] ^ 1)
            ++res;
    printf("%d\n", res);
    return 0;
}
