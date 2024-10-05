#include <algorithm>
#include <stdio.h>
#include <vector>
#include <bits/stl_algo.h>
std::vector<int> g[1000005], cc[1000005];
inline int min(int a, int b)
{
    return a < b ? a : b;
}
int ep[1000005], dfn[1000005], low[1000005], du[1000005], stk[1000005], pos[1000005], top, gtm, pts;
inline void tarjan(int x, int fa)
{
    dfn[x] = low[x] = ++gtm;
    stk[++top] = x;
    for (int i : g[x])
    {
        if (fa == i)
        {
            fa = -1;
            continue;
        }
        if (!dfn[i])
        {
            tarjan(i, x);
            low[x] = min(low[x], low[i]);
        }
        else
            low[x] = min(low[x], dfn[i]);
    }
    if (dfn[x] == low[x])
    {
        ++pts;
        int t = 0;
        do
            pos[t = stk[top--]] = pts;
        while (t != x);
    }
}
int c[1000005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", c + i);
        cc[c[i]].emplace_back(i);
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < (int)cc[i].size() - 1; ++j)
        {
            g[cc[i][j]].emplace_back(cc[i][j + 1]);
            g[cc[i][j + 1]].emplace_back(cc[i][j]);
        }
    tarjan(1, -1);
    //    printf("output started.\n");
    for (int i = 1; i <= n; ++i)
        for (int j : g[i])
        {
            //        	printf("%d %d\n", i, j);
            if (pos[i] ^ pos[j])
                du[pos[i]]++;
        }
    int res = 0;
    for (int i = 1; i <= pts; ++i)
        if (du[i] == 1)
            ++res;
    //    for (int i = 1; i <= pts; ++i)
    //		printf("%d:%d\n", i, du[i]);
    return 0 * printf("%d", (res + 1) >> 1);
}
