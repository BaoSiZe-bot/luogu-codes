#include <stdio.h>
#include <algorithm>
#define int long long
int stk[200005], pa[200005], bk[200005], tmp[200005], n;  //the stack, the parent of the node, the number of nodes
int v[200005];
//the graph, using list style forward-star
template <const int N> struct GR
{
private:
    struct Edge
    {
        int v;  //end node of the edge
        int p;  //the pointer to the next edge
    } e[N];
    int ed[N];  //the end edge of a node
    int cnt = 0;  //count of edges

public:
    // add a edge
    inline void add(int u, int v)
    {
        e[++cnt] = {v, ed[u]};  //init new edge
        ed[u] = cnt;  //change the end edge
    }
    //get edge
    inline Edge ge(int x)
    {
        return e[x];
    }
    //get end
    inline int gd(int x)
    {
        return ed[x];
    }
};
GR<100005> g;  //define a graph
struct Node
{
    int a, b, c, d;
} tr[200005];
struct node
{
    int val, id;
    bool operator<(const node &x) const
    {
        return val < x.val;
    }
} q[200005];
//find the parent of the node
void dfs(int x, int fa)
{
    pa[x] = fa;
    for (int i = g.gd(x); i; i = g.ge(i).p)
    {
        int to = g.ge(i).v;
        if (to ^ fa)
            dfs(to, x);
    }
}
//check the answer for dichotomy
inline __int128 calc(int st, int ed, __int128 B, __int128 C)
{
    __int128 res = (ed - st + 1) * B;
    res += C * (st + ed) * (ed - st + 1) >> 1;
    return res;
}
inline bool chk(int mid)
{
    for (int i = 1; i <= n; ++i)
    {
        q[i].id = i;
        if (tr[i].d >= 0)
        {
            if (mid - tr[i].d >= tr[i].a)
                q[i].val = mid - tr[i].a + 1;
            else
            {
                int t = mid >= tr[i].d ? tr[i].a - mid + tr[i].d : tr[i].a;
                int l = 1, r = mid >= tr[i].d ? tr[i].d : mid, ans = -1;
                while (l <= r)
                {
                    int md = (l + r) >> 1;
                    if (calc(md, mid >= tr[i].d ? tr[i].d : mid, tr[i].b, tr[i].c) >= t)
                    {
                        ans = md;
                        l = md + 1;
                    }
                    else
                        r = md - 1;
                }
                if (ans == -1)
                    return 0;
                q[i].val = ans;
            }
        }
        else
        {
            int l = 1, r = mid, ans = -1;
            while (l <= r)
            {
                int md = (l + r) >> 1;
                if (calc(md, mid, tr[i].b, tr[i].c) >= tr[i].a)
                {
                    ans = md;
                    l = md + 1;
                }
                else
                    r = md - 1;
            }
            if (ans == -1)
                return 0;
            q[i].val = ans;
        }
    }
    int tot = 0, top = 0;
    std::sort(q + 1, q + n + 1);
    v[0] = mid;
    for (int i = 1; i <= n; ++i)
        bk[q[i].id] = i;
    for (int i = 1; i <= n; ++i)
        if (v[q[i].id] ^ mid)
        {
            int pt = i;
            while (v[q[pt].id] ^ mid)
            {
                stk[++top] = q[pt].val;
                v[q[pt].id] = mid;
                pt = bk[pa[q[pt].id]];
            }
            while (top)
            {
                ++tot;
                tmp[tot] = stk[top--];
                if (tmp[tot] < tot)
                    return 0;
            }
        }
    return 1;
}
//dichotomy answer
inline int dichotomy()
{
    int lft = n, rgt = 0x3f3f3f3f, res = 0;
    while (lft <= rgt)
    {
        int mid = (lft + rgt) >> 1;
        if (chk(mid))
        {
            res = mid;
            rgt = mid - 1;
        }
        else
            lft = mid + 1;
    }
    return res;
}
//reading data and init
void init()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld%lld", &tr[i].a, &tr[i].b, &tr[i].c);
        tr[i].d = tr[i].c < 0 ? -1 : static_cast<int>((1.0 - static_cast<double>(tr[i].b)) / static_cast<double>(tr[i].c));
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%lld%lld", &u, &v);
        g.add(u, v);
        g.add(v, u);
    }
}
signed main()
{
    init();
    dfs(1, 0);
    printf("%lld", dichotomy());
    return 0;
}
