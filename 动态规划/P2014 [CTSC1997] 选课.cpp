#include <stdio.h>

#define int long long
#pragma clang diagnostic ignored "-Wregister"
#pragma clang diagnostic ignored "-Wshift-op-parentheses"

template <class T> inline void rd(T &x)
{
    x = 0;
    register signed f = 1;
    register char c = getchar();
    for (; c < 48 || c > 57; c = getchar())
        c == 45 && (f = ~f + 1);
    for (; c > 47 && c < 58; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    x *= f;
}
template <class T, class... S> inline void rd(T &x, S &...y)
{
    rd(x);
    rd(y...);
}

struct Edge
{
    int v, p;
} e[605];
int ed[305], cnt, n, m;

inline void add_edge(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline int max(int a, int b)
{
    return a < b ? a : b;
}
int s[305];

int dp[305][305];
inline void dfs(int ro, int m)
{
    if(m < 1)
        return;
    for (int i = ed[ro]; i; i = e[i].p)
    {
        int to = e[i].v;
        for (int j = 0; j < m; ++j)
            dp[to][j] = dp[ro][j] + s[to];
        dfs(to, m - 1);
        for(int j = 1; j <= m; ++j)
            dp[ro][j] = max(dp[ro][j], dp[to][j - 1]);
    }
}

signed main()
{
    rd(n, m);
    for (int i = 1; i <= n; ++i) {
        int u;
        rd(u, s[i]);
        add_edge(u, i);
    }
    dfs(0, m);
    printf("%lld\n", dp[0][m]);
    return 0;
}
