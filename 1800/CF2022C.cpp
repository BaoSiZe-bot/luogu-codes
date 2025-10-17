#include <algorithm>
#include <cstdio>
namespace Fujiwara
{
using std::sort;
const int N = 2e5 + 5;

struct Node
{
    int a, b;
    bool operator<(const Node &nbr) const
    {
        return b > nbr.b;
    }
} a[N];

static int get(int x)
{
    int res = 0;
    for (; x; x /= 10)
        ++res;
    return res;
}
static int chk(int x)
{
    int res = 0;
    for (; x % 10 == 0; x /= 10)
        ++res;
    return res;
}
static void solve()
{
    int n, m, s = 0, t = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i].a);
        a[i].b = chk(a[i].a);
        s += get(a[i].a);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i += 2)
        t += a[i].b;
    printf(t >= s - m ? "Anna\n" : "Sasha\n");
}
static int Azusa()
{
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    return Fujiwara::Azusa();
}
