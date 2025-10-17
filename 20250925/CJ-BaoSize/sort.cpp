#include <algorithm>
#include <cstdio>

namespace Fujiwara
{
using std::swap;
using ll = long long;
const int N = 5e6 + 5;

int n, q, o, a[N], b[N];
struct Query
{
    int l, r, k, x;
} qr[N];
static int Azusa();
static void work1(int);

static int Azusa()
{
    scanf("%d%d%d", &n, &q, &o);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    for (int i = 1; i <= q; ++i)
        scanf("%d%d%d%d", &qr[i].l, &qr[i].r, &qr[i].k, &qr[i].x);
    for (int i = 1; i <= q; ++i)
        if (n <= 500 && q <= 500)
            work1(i);
    return 0;
}
static void work1(int id)
{
    for (int i = 1; i <= n; ++i)
        b[i] = a[i];
    for (int $ = 1; $ <= qr[id].k; ++$)
        for (int i = qr[id].l; i < qr[id].r; ++i)
            if (b[i] > b[i + 1])
                swap(b[i], b[i + 1]);
    if (o == 2)
    {
        printf("%d\n", b[qr[id].x]);
        return;
    }
    for (int i = 1; i <= n; ++i)
        if (b[i] == qr[id].x)
        {
            printf("%d\n", i);
            return;
        }
}
}
int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    return Fujiwara::Azusa();
}
