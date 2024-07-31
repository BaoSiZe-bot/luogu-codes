#include <stdio.h>
#include <queue>
#define int long long
int n, r, t;
bool vis[100005];
std::vector<int> g[100005];
struct Node
{
    int fa, w, z;
} nd[100005];
int p[100005];
inline int fd(int x)
{
    return p[x] ^ x ? p[x] = fd(p[x]) : x;
}
inline void dfs(int rt, int fa)
{
	nd[rt].fa = fa;
	for (int i : g[rt])
		if (i != fa)
			dfs(i, rt);
}
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        scanf("%lld%lld", &n, &r);
        std::priority_queue<std::pair<double, int>> pq;
        int res = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &nd[i].w);
            if (i ^ r)
                pq.push({nd[i].w, i});
            res += nd[i].w;
            nd[i].z = 1;
            vis[i] = 0;
            p[i] = i;
            g[i].clear();
        }
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            scanf("%lld%lld", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(r, 0);
        while (!pq.empty())
        {
            int nw = pq.top().second;
            pq.pop();
            if (!vis[nw])
            {
                vis[nw] = 1;
                int ff = fd(nd[nw].fa);
                res += nd[ff].z * nd[nw].w;
                nd[ff].w += nd[nw].w;
                nd[ff].z += nd[nw].z;
                p[nw] = ff;
                if (ff ^ r)
                    pq.push({1.0 * nd[ff].w / nd[ff].z, ff});
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
