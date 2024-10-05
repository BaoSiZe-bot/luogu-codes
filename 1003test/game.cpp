#include <cstdio>
#include <vector>
#define int long long
int ed[2000005], bsz[2000005], s[2000005], cnt[2000005], w, tot, n;
std::vector<int> g[2000005];
inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline void dfs(int rt, int fa)
{
    bsz[rt] = 1;
    int mx = 0;
    for (int i : g[rt])
        if (i ^ fa)
        {
            dfs(i, rt);
            bsz[rt] += bsz[i];
            mx = max(mx, bsz[i]);
        }
    mx = max(mx, n - bsz[rt]);
    if (mx <= (n / 2))
        w = rt;
}
bool f[2000005];
int q[2000005], d[2000005], hd, tl;
inline void bfs(int s)
{
    tl = 0;
    d[s] = 1;
    hd = f[s] = 1;
    q[++tl] = s;
    while (hd <= tl)
    {
        int nw = q[hd++];
        cnt[d[nw]]++;
        for (int i : g[nw])
            if (!f[i])
            {
                d[i] = d[nw] + 1;
                f[i] = 1;
                q[++tl] = i;
            }
    }
}

signed main()
{
    scanf("%lld", &n);
    for (int i = 1, u, v; i < n; ++i)
    {
        scanf("%lld%lld", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    bfs(w);
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + cnt[i];
    int res = 0;
    for (int i = 1; i <= n; ++i)
        res += cnt[i] * (s[n] - s[i - 1] - 1);
    printf("%lld", res);
    return 0;
}
