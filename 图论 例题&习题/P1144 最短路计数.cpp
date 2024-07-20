#include <bits/stdc++.h>

using namespace std;

const int M = 100003;
vector<int> g[1000005];
int dis[1000005], cnt[1000005];
bool vis[1000005];
void bfs()
{
    queue<int> q;
    vis[1] = cnt[1] = 1;
    q.push(1);
    while (!q.empty())
    {
        int w = q.front();
        q.pop();
        for (int i : g[w])
        {
            if (!vis[i])
            {
                vis[i] = 1;
                dis[i] = dis[w] + 1;
                q.push(i);
            }
            dis[i] == dis[w] + 1 && (cnt[i] = (cnt[i] + cnt[w]) % M);
        }
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs();
    for (int i = 1; i <= n; ++i)
        printf("%d\n", cnt[i]);
    return 0;
}
