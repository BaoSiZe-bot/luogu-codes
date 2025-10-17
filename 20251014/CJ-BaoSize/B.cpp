#include <cstdio>
#include <vector>

namespace Fujiwara
{
using ll = long long;

using std::vector;
const int P = 1e4;

struct Seq
{
    int l, r;
};
struct Oper
{
    int op, x;
    ll v;
};

static ll qp(ll a, ll b, ll p = P)
{
    ll res = 1;
    for (; b; b >>= 1)
    {
        (b & 1) && ((res *= a) %= P);
        (a *= a) %= p;
    }
    return res;
}

vector<Oper> oq;
vector<Seq> qrs;
vector<ll> a, s, d;
int n, m, q;

static int Azusa()
{
    scanf("%d%d%d", &n, &m, &q);

    s.resize(m + 1);
    oq.resize(m + 1);
    qrs.resize(q + 1);

    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &oq[i].op);
        s[i] += s[i - 1] + bool(oq[i].op == 2);
        oq[i].op == 1 && scanf("%d%lld", &oq[i].x, &oq[i].v);
    }
    for (int i = 1; i <= q; ++i)
        scanf("%d%d", &qrs[i].l, &qrs[i].r);

    d.resize(m + 1);
    for (ll i = q, t = 0; i; --i)
    {
        int l = qrs[i].l, r = qrs[i].r;

        (d[r] += qp(2, t)) %= P;
        t += s[r] - s[l - 1];

        (d[l - 1] += P - qp(2, t)) %= P;
    }

    a.resize(n + 1);
    for (ll i = m, nw = d[m]; i; (nw += d[--i]) %= P)
        (oq[i].op == 1) ? (a[oq[i].x] += oq[i].v * nw % P) %= P : (nw <<= 1) %= P;

    for (int i = 1; i <= n; ++i)
        printf("%lld ", a[i]);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    // freopen("B.in", "r", stdin);
    // freopen("B.out", "w", stdout);
    return Fujiwara::Azusa();
}
