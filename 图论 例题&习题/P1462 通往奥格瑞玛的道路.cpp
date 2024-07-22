#include <bits/stdc++.h>
#define int long long

using namespace std;

struct Edge
{
	int v, d, p;
} e[1000005];
int f[1000005], ed[1000005], dis[1000005], cnt, mx;
int n, m, b;
bool vis[1000005];
inline void add(int u, int v, int d)
{
	e[++cnt] = {v, d, ed[u]};
	ed[u] = cnt;
}
void dijkstra(int lim)
{
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	dis[1] = 0;
	q.push({0, 1});
	while(!q.empty())
	{
		int nw = q.top().second;
		q.pop();
		if (vis[nw])
			continue;
		vis[nw] = 1;
		if (f[nw] > lim)
			continue;
		for (int i = ed[nw]; i; i = e[i].p)
		{
			int to = e[i].v;
			if (f[to] <= lim && dis[to] > dis[nw] + e[i].d)
			{
				dis[to] = dis[nw] + e[i].d;
				q.push({dis[to], to});
			}
		}
	}
}
signed main()
{
	scanf("%lld%lld%lld", &n, &m, &b);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", f + i);
		mx = max(mx, f[i]);
	}
	for (int i = 1, u, v, w; i <= m; ++i)
	{
		scanf("%lld%lld%lld", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	int l = 1, r = mx, res = -1;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		dijkstra(mid);
		if (dis[n] <= b)
		{
			r = mid - 1;
			res = mid;
		}
		else
			l = mid + 1;
	}
	if (~res)
		printf("%lld\n", res);
	else
		printf("AFK");
	return 0;
}
