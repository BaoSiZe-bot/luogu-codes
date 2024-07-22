#include <bits/stdc++.h>

using namespace std;

int dis[205][205], t[205];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%d", t + i);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			dis[i][j] = bool(i ^ j) * 0x3f3f3f3f;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		dis[u][v] = min(dis[u][v], w);
		dis[v][u] = min(dis[v][u], w);
	}
	int q, nw = 0;
	scanf("%d", &q);
	while (q--)
	{
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		while (nw < n && t[nw] <= k)
		{
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					dis[i][j] = min(dis[i][nw] + dis[nw][j], dis[i][j]);
			++nw;
		}
		if (t[x] > k || t[y] > k || dis[x][y] == 0x3f3f3f3f)
			printf("-1\n");
		else
			printf("%d\n", dis[x][y]);
	}
	return 0;
}
