#include <bitset>
#include <stdio.h>
#include <bits/stl_pair.h>
std::bitset<505> vis[505];
std::pair<int, int> sg[505];
int dp[505], res[505], a[505][505], n, m;
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline void dfs(int u, int v, int id)
{
    vis[u].set(v);
    if (u == n)
    {
        res[v] = 1;
        sg[id].first = min(sg[id].first, v);
        sg[id].second = max(sg[id].second, v);
    }
    if (u != 1 && !vis[u - 1][v] && a[u - 1][v] < a[u][v])
        dfs(u - 1, v, id);
    if (u != n && !vis[u + 1][v] && a[u + 1][v] < a[u][v])
        dfs(u + 1, v, id);
    if (v != 1 && !vis[u][v - 1] && a[u][v - 1] < a[u][v])
        dfs(u, v - 1, id);
    if (v != m && !vis[u][v + 1] && a[u][v + 1] < a[u][v])
        dfs(u, v + 1, id);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        dp[i] = sg[i].first = 30000;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= m; ++i)
    {
        if (a[1][i - 1] <= a[1][i] && a[1][i + 1] <= a[1][i])
            dfs(1, i, i);
        for (int j = 1; j <= n; ++j)
            vis[j].reset();
    }
    int t = 0;
    for (int i = 1; i <= m; ++i)
        t += !res[i];
    if (t)
        return 0 * printf("0\n%d", t);
    printf("%d\n", 1);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m; ++j)
            (sg[j].first <= i && i <= sg[j].second) && (dp[i] = min(dp[i], dp[sg[j].first - 1] + 1));
    printf("%d", dp[m]);
    return 0;
}
