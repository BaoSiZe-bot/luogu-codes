#include <cstdio>

namespace Fujiwara
{
using ll = long long;
const int N = 1e5 + 5;

int n, k, l;
struct Bubble
{
    int b, d;
    char c;
} a[N];
static int Azusa();

static int Azusa()
{
    scanf("%d %d %d", &n, &k, &l);
    for (int i = 1; i <= n; ++i)
        scanf("%d %d %c", &a[i].b, &a[i].d, &a[i].c);
    return 0;
}
}  // namespace Fujiwara

int main()
{
    freopen("glow.in", "r", stdin);
    freopen("glow.out", "w", stdout);
    return Fujiwara::Azusa();
}
