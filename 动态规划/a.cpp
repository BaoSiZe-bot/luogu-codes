#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>
struct Edge
{
    int v, d, p;
} e[3000005];
int dis[100005], ed[100005], cnt, n, m, c;
std::bitset<100005> vis;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
inline int dijkstra(int s, int t)
{
    memset(dis, 0x3f, sizeof dis);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, s});
    dis[s] = 0;
    while (!pq.empty())
    {
        int nw = pq.top().second;
        pq.pop();
        if (vis[nw])
            continue;
        vis[nw] = 1;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (dis[to] > dis[nw] + e[i].d)
            {
                dis[to] = dis[nw] + e[i].d;
                pq.push({dis[to], to});
            }
        }
    }
    return dis[t];
}
void add_edge()
{
    for (int i = 0; i <= n; ++i)
        for (int j = 1; j <= 20; ++j)
            if ((i ^ (1 << j)) <= n)
                add(i, i ^ (1 << j), c * (1 << j));
}
int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    add_edge();
    int s, t;
    scanf("%d%d", &s, &t);
    return printf("%d\n", dijkstra(s, t)) * 0;
}

/*
         -/oyddmdhs+:.                        
     -odNMMMMMMMMNNmhy+-`
   -yNMMMMMMMMMMMNNNmmdhy+-
 `omMMMMMMMMMMMMNmdmmmmddhhy/`
 omMMMMMMMMMMMNhhyyyohmdddhhhdo`
.ydMMMMMMMMMMdhs++so/smdddhhhhdm+`
 oyhdmNMMMMMMMNdyooydmddddhhhhyhNd.
  :oyhhdNNMMMMMMMNNNmmdddhhhhhyymMh
    .:+sydNMMMMMNNNmmmdddhhhhhhmMmy           
       /mMMMMMMNNNmmmdddhhhhhmMNhs:
    `oNMMMMMMMNNNmmmddddhhdmMNhs+`
  `sNMMMMMMMMNNNmmmdddddmNMmhs/.
 /NMMMMMMMMNNNNmmmdddmNMNdso:`
+MMMMMMMNNNNNmmmmdmNMNdso/-
yMMNNNNNNNmmmmmNNMmhs+/-`
/hMMNNNNNNNNMNdhs++/-`
`/ohdmmddhys+++/:.`
  `-//////:--.
*/
