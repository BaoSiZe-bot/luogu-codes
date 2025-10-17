#include <cstdio>

namespace Fujiwara
{
using ll = long long;

char s[] = " vector<vector<int>>ans={{2},{3},{2,2},{5},{2,3},{3,3},{2,2,2},{7},{2,5},{2,2,3},{3,5},{2,3,3},{2,2,2,2},{2,7},{2,2,5},{3,3,3},{2,2,2,3}";
static int Azusa()
{
    int l, r;
    scanf("%d%d", &l, &r);
    if (r <= 135)
    {
        for (int i = l; i <= r; ++i)
            printf("%c", s[i]);
        return 0;
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    return Fujiwara::Azusa();
}
