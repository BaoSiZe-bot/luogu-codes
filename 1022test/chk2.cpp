/*
 * @zhongyq 贺我 0 分代码，改了一个字符过了
 * 警钟长鸣
 * */
#include <stdio.h>
struct Edge
{
    int u, v;
} e[200005];
int main()
{
    int n, tp;
    scanf("%d%d", &n, &tp);
    if (tp & 1)
    {
        if (n & 1)
        {
            int cnt = 0;
            for (int i = n; i > n / 2 + 1; --i)
            {
                e[++cnt] = {n - i + 1, i};
                e[++cnt] = {i, n - i + 2};
            }
        }
        else
        {
            e[1] = {1, n};
            for (int i = 2; i + i <= n; ++i)
            {
                e[i + i - 1] = {i, n - i + 1};
                e[i + i - 2] = {n - i + 2, i};
            }
        }
    }
    else
    {
        int cnt = 0;
        for (int i = 2; i <= n / 2 + 1; ++i)
            e[++cnt] = {1, i};
        for (int i = n / 2 + 2; i <= n; ++i)
            e[++cnt] = {n / 2 + 1, i};
    }
    printf("%d\n", n / 2);
    for (int i = 1; i <= n / 2; ++i)
        for (int j = 1; j < n; ++j)
        {
            printf("%d %d\n", e[j].u, e[j].v);
            if (!--e[j].u)
                e[j].u = n;
            if (!--e[j].v)
                e[j].v = n;
        }
    return 0;
}
