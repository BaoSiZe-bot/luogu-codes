#include <bits/stdc++.h>
#define int long long
		
using namespace std;
		
struct Edge
{
	int v, d, p;
} e[100005];
int ed[10005], cnt;
inline void add(int u, int v, int d)
{
	e[++cnt] = {v, d, ed[u]};
	ed[u] = cnt;
}
int dis[10005][15], n, m, k;
bool vis[10005][15];
inline void dijkstra(int s)
{
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > q;
	memset(dis, 127, sizeof(dis));
	q.push({0, {s, 0}});
	dis[s][0] = 0;
	while (!q.empty())
	{
		auto nw = q.top().second;
#define x nw.first
#define tt nw.second
		q.pop();
		if (vis[x][tt])
			continue;
		vis[x][tt] = 1;
		for (int j = ed[x]; j; j = e[j].p)
		{
			int to = e[j].v, w = e[j].d;
			if (tt < k && dis[to][tt + 1] > dis[x][tt])
			{
				dis[to][tt + 1] = dis[x][tt];
				q.push({dis[to][tt + 1], {to, tt + 1}});
			}
			if (dis[to][tt] > dis[x][tt] + w)
			{
				dis[to][tt] = dis[x][tt] + w;
				q.push({dis[to][tt], {to, tt}});
			}
		}
#undef x
#undef tt
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cout.sync_with_stdio(0);
	cin.sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);
	scanf("%lld%lld%lld", &n, &m, &k);
	int s, t;
	scanf("%lld%lld", &s, &t);
	for (int i = 1; i <= m; ++i)
	{
		int u, v, d;
		scanf("%lld%lld%lld", &u, &v, &d);
		add(u, v, d);
		add(v, u, d);
	}
	dijkstra(s);
	int mn = LONG_LONG_MAX;
	for (int i = 0; i <= k; ++i)
		mn = min(mn, dis[t][k]);	
	printf("%lld", mn == 1 ? 0 : mn);
	return 0;
}
