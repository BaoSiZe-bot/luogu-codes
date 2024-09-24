#include <cstring>
#include <stdio.h>
const int N = 1005;
struct Edge
{
    int v, w, p;
} e[N];
int ed[N], cnt = 0;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
inline int cmin(int &a, int b)
{
    return a = (a < b ? a : b);
}
int n, m, k, dp[305][305][2], tmp[305][2];

inline void dfs(int rt, int fa)
{
    dp[rt][0][0] = dp[rt][1][1] = 0;
    for (int i = ed[rt]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to == fa)
            continue;
        dfs(to, rt);
        memcpy(tmp, dp[rt], sizeof tmp);
        memset(dp[rt], 0x3f, sizeof dp[rt]);
        for (int j = 0; j <= k; ++j)
            for (int p = 0; p <= j; ++p)
            {
                cmin(dp[rt][j][0], dp[to][p][1] + tmp[j - p][0]);
                cmin(dp[rt][j][1], dp[to][p][0] + tmp[j - p][1]);
                cmin(dp[rt][j][1], dp[to][p][1] + tmp[j - p][1] + e[i].w);
                cmin(dp[rt][j][0], dp[to][p][0] + tmp[j - p][0] + !(m ^ 2) * e[i].w);
            }
    }
}
int main()
{
    memset(dp, 0x3f, sizeof dp);
    scanf("%d%d%d", &n, &m, &k);
    if (n - k + 1 < m)
        return 0 * printf("-1\n");
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0);
    printf("%d", dp[1][k][1]);
    return 0;
}
