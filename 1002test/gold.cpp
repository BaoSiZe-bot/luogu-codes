#include <map>
#include <vector>
#include <math.h>
#include <stdio.h>

int s[600005], p[600005], h[600005], tot;
std::map<std::pair<int, int>, int> mp;
std::pair<int, int> a[600005];
std::vector<int> g[600005];
int mul(std::pair<int, int> a, std::pair<int, int> b)
{
    return a.first * b.second - a.second * b.first;
}
void upd(int rt, int fa)
{
    s[rt] = s[fa] + mul(a[rt], a[fa]);
    for (int i : g[rt])
        if (i ^ fa)
            upd(i, rt);
}
inline int fd(int x)
{
    return p[x] ^ x ? p[x] = fd(p[x]) : x;
}
inline void mg(int u, int v)
{
    int uu = fd(u);
    int vv = fd(v);
    if (h[uu] > h[vv])
    {
        u ^= v ^= u ^= v;
        uu ^= vv ^= uu ^= vv;
    }
    p[uu] = vv;
    h[vv] += h[uu];
    h[uu] = 0;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
    upd(u, v);
}
inline int get(int x, int y)
{
    if (!mp[{x, y}])
        a[mp[{x, y}] = ++tot] = {x, y};
    return mp[{x, y}];
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n + n; ++i)
    {
        p[i] = i;
        h[i] = 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        int x, y, u, v;
        char c;
        scanf("\n%d %d %c", &x, &y, &c);
        u = get(x, y);
        v = get(x + (c == 'x'), y + (c == 'y'));
        if (fd(u) ^ fd(v))
        {
            mg(u, v);
            printf("0\n");
        }
        else
            printf("%d\n", abs(s[u] - s[v] - mul(a[u], a[v])) >> 1);
    }
    return 0;
}

