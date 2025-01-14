#include <cstdio>
#include <cstring>
const int N = 1e6 + 5;
int a[N], fa[N];
inline int fd(int x)  // find parent
{
    return fa[x] ^ x ? fa[x] = fd(fa[x]) : x;
}
int main()
{
    memset(fa, 0xff, sizeof fa);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 1000000; ++i)
        fa[i] = i;
    for (int i = 1, x; i <= n; ++i)
    {
        scanf("%d", &x);
        ++fa[x = fd(x)];
        printf("%d ", x);
    }
    return 0;
}
