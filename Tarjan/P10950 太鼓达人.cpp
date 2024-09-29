#include <stdio.h>
int w[100005], f[100005], r[100005];
int k, n;
bool fd = 0;  // found
void dfs(int x)
{
    int hs = 0;
    if (x > k)
    {
        for (int i = x - k; i < x; i++)
            hs += w[i] * (1 << (x - i - 1));
        if (f[hs])
            return;
        f[hs]++;
    }
    if (x > n)
    {
        if (fd)
            return;
        for (int i = 1; i < k; ++i)
            w[i + n] = w[i];
        for (int i = n + 1; i <= n + k; ++i)
        {
            int hs = 0;
            for (int j = i - k; j < i; j++)
                hs += w[j] * (1 << (i - j - 1));
            f[hs]++;
        }
        for (int i = 0; i < n; i++)
            if (!f[i])
                return;
        fd = 1;
        for (int i = 1; i <= n; ++i)
            r[i] = w[i];
    }
    dfs(x + 1);
    w[x] = 1;
    if (fd)
        return;
    dfs(x + 1);
    w[x] = 0;
    f[hs]--;
}
int main()
{
    scanf("%d", &k);
    printf("%d ", n = (1 << k));
    dfs(1);
    for (int i = 1; i <= n; ++i)
        printf("%d", r[i]);
    return 0;
}
