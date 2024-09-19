#include <bits/stdc++.h>
#define int long long

using namespace std;

struct Edge
{
    int v, p;
} e[100005];

int n, k;
int ed[50005], dp[50005][505], cnt, res;
void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline void dfs(int x, int f)
{
    dp[x][0] = 1;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int y = e[i].v;
        if (y ^ f)
        {
            dfs(y, x);
            for (int j = 0; j < k; ++j)
                res += dp[x][j] * dp[y][k - j - 1];
            for (int j = 0; j < k; ++j)
                dp[x][j + 1] += dp[y][j];
        }
    }
}
signed main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1, u, v; i < n; ++i)
    {
        scanf("%lld%lld", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    return 0 * printf("%lld\n", res);
}
