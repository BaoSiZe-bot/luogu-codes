#include <algorithm>
#include <stdio.h>
int a[10000005], b[10000005];
struct Node
{
    int l, r, s, ld, rd;  //lson, rson
} tr[30000005];
int cnt, rt[10000005], rt_cnt;
inline int bld(int l, int r)
{
    int id = ++cnt;
    tr[id] = {l, r, 0, 0, 0};
    if (l == r)
        return id;
    int mid = (l + r) >> 1;
    tr[id].ld = bld(l, mid);
    tr[id].rd = bld(mid + 1, r);
    return id;
}
inline int add(int x, int p, int k)
{
    if (tr[x].l > p || p > tr[x].r)
        return x;
    int id = ++cnt;
    tr[id] = tr[x];
    tr[id].s += k;
    if (tr[x].l == tr[x].r)
        return id;
    int mid = (tr[x].l + tr[x].r) >> 1;
    if (mid >= p)
        tr[id].ld = add(tr[x].ld, p, k);
    else
        tr[id].rd = add(tr[x].rd, p, k);
    return id;
}
inline int qry(int lx, int rx, int tl, int tp, int qk)
{
    if (tl >= tp)
        return tl;
    int tot = tr[tr[rx].ld].s - tr[tr[lx].ld].s, mid = (tl + tp) >> 1;
    if (tot >= qk)
        return qry(tr[lx].ld, tr[rx].ld, tl, mid, qk);
    else
        return qry(tr[lx].rd, tr[rx].rd, mid + 1, tp, qk - tot);
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    int tot = std::unique(b + 1, b + n + 1) - b - 1;
    rt[rt_cnt] = bld(1, tot);
    for (int i = 1; i <= n; ++i)
    {
        int tmp = rt_cnt;
        a[i] = std::lower_bound(b + 1, b + tot + 1, a[i]) - b;
        rt[++rt_cnt] = add(rt[tmp], a[i], 1);
    }
    while (m--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", b[qry(rt[l - 1], rt[r], 1, tot, k)]);
    }
    return 0;
}
