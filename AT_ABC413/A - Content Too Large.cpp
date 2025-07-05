#include <numeric>
#include <stdio.h>
int a[105];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    if (std::accumulate(a + 1, a + n + 1, 0) <= m)
        printf("Yes");
    else
        printf("No");
    return 0;
}
