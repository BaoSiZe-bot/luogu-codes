#include <map>
#include <math.h>
#include <stdio.h>
#include <string.h>

//--Vector definition start--
class Vector
{
public:
    int x, y;
    int operator*(const Vector &other) const
    {
        return x * other.y - y * other.x;
    }
    bool operator<(const Vector &other) const
    {
        return x ^ other.x ? x < other.x : y < other.y;
    }
} a[300005];
std::map<Vector, int> mp;
//--Vector definition end--

//--List forward-style star definition start--
struct Edge
{
    int v, p;
} e[1000005];
int ed[300005], s[300005], cnt, tot;
void add(int, int);
//--List forward-style star definition end--

//--UnionSet definition start--
int p[100005], h[100005];
int fd(int);
void mg(int, int);
//--UnionSet definition end--

//--misc definition start--
int get(int, int);
void upd(int, int);
//--misc definition end--

int main()
{
    memset(p, 0xff, sizeof p);

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y, u, v;
        char c;
        scanf("\n%d %d %c", &x, &y, &c);

        u = fd(get(x, y));
        v = fd(c ^ 'x' ? get(u, v + 1) : get(u + 1, v));

        if (u ^ v)
        {
            mg(u, v);
            printf("0\n");
        }
        else
            printf("%d\n", s[u] - s[v] + a[u] * a[v]);
    }
    return 0;
}

//--List forward-style star implement start--
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
//--List forward-style star implement end--

//--UnionSet implement start--
inline int fd(int x)
{
    return ~p[x] ? p[x] = fd(p[x]) : x;
}
inline void mg(int u, int v)
{
    if (h[u] > h[v])
        u ^= v ^= u ^= v;
    p[u] = v;
    h[v] += h[u];
    add(u, v);
    add(v, u);
    upd(u, v);
}
//--UnionSet implement end--

//--misc implement start--
void upd(int rt, int fa)
{
    s[rt] = s[fa] + a[rt] * a[fa];
    for (int i = ed[rt]; i; i = e[i].p)
        if (e[i].v ^ fa)
            upd(e[i].v, rt);
}
inline int get(int x, int y)
{
    if (mp.count({x, y}))
        return mp.at({x, y});
    a[++tot] = {x, y};
    return tot;
}
//--misc implement start--
