#include <cstdio>
#include <stdlib.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")  //ofast优化(优化到破坏标准合规性的点)，
#pragma GCC optimize("-fcaller-saves")  //负优化排除
#pragma GCC optimize("-fvpt")
#pragma GCC optimize("-funroll-loops")  //消除分支可以减少预测的可能性能：比如小的循环可以展开比如循环次数小于64次
#define N 2005
bool cnt[N][N], s[N];
int d[N], n, k, i, j, u, v, x, f;
#define Get() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 200000, stdin), p1 == p2) ? EOF : *p1++)
char buf[200000], *p1 = buf, *p2 = buf;
__always_inline int rd()
{
    x = 0;
    char c = Get();
    for (; c < 48 || c > 57; c = Get())
        ;
    for (; c > 47 && c < 58; c = Get())
        x = x * 10 + (c & 15);
    return x;
}
int main()
{
    n = rd();
    k = rd();
    for (i = 1; i <= k; ++i)
    {
        for (j = 1; j < n; ++j)
        {
            u = rd();
            v = rd();
            if (cnt[u][v])
                return printf("ERR1"), 0;
            cnt[u][v] = 1;
            cnt[v][u] = 1;
            d[u]++;
            d[v]++;
        }
        for (j = 1; j < n - 1; ++j)
            d[j] ^ !(d[j] = 0) && (s[j] ? exit((printf("ERR2"), 0)) : (s[j] = 1, void()), 1);
    }
    printf("OK");
}
