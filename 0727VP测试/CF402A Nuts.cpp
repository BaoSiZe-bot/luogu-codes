#include <algorithm>
#include <cstdio>

using namespace std;

int k, a, b, v;
inline int cl(int a, int b)
{
    return a / b + bool(a % b);
}
inline bool chk(int x)
{
    if (x == 1)
        return std::min(k, b + 1) * v >= a;
    else
        return std::min(k, cl(b, x) + 1) * (x - 1) * v + min(k, b - cl(b, x) *  (x - 1) + 1) * v >= a;
}
int main()
{
    scanf("%d%d%d%d", &k, &a, &b, &v);
    int l = 1, r = a, res = 0;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if (chk(mid))
        {
            r = mid - 1;
            res = mid;
        }
        else 
            l = mid + 1;
    }
    printf("%d\n", res);
    return 0;
}
