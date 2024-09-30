#include <cstring>
#include <iostream>
struct Edge
{
    int v, p;
} e[200005];
int ed[100005], rd[100005], du[100005], cnt, n, m;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ++du[v];
    ed[u] = cnt;
}
int d[100005];
std::pair<int, std::string> q[100005];
inline void topo()
{
    memcpy(rd, du, sizeof rd);
    int hd = 1, tl = 0, tot = 0;
    std::string xp = "";
    for (int i = 1; i <= n; i++)
        if (!rd[i])
        {
            q[++tl].first = i;
            q[tl].second = 'A' + i - 1;
            ++tot;
        }
    while (hd <= tl)
    {
        auto p = q[hd++];
        for (int i = ed[p.first]; i; i = e[i].p)
        {
            int to = e[i].v;
            --rd[to];
            if (!rd[to])
            {
                ++tot;
                q[++tl].first = to;
                q[tl].second = p.second + char('A' + to - 1);
                if (q[tl].second.size() > xp.size())
                    xp = q[tl].second;
            }
        }
    }
    if (xp.size() == n)
    {
        std::cout << "Sorted sequence determined after " << cnt << " relations: " << xp << ".";
        exit(0);
    }
    if (tot != n)
    {
        std::cout << "Inconsistency found after " << cnt << " relations.";
        exit(0);
    }
}
int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        std::string st;
        std::cin >> st;
        add(st[0] - 'A' + 1, st[2] - 'A' + 1);
        topo();
    }
    printf("Sorted sequence cannot be determined.");
    return 0;
}
