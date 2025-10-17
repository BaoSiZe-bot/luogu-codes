#include <stdio.h>

int t, n, m, i;
int pa, pb, na, nb, cnt;

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        cnt = 0;
        scanf("%d%d", &n, &m);
        for (i = 1, pa = 0, pb = 0; i <= n; ++i)
        {
            scanf("%d%d", &na, &nb);
            cnt += (((na - pa) & 1) ^ ((nb - pb) & 1)), pa = na, pb = nb;
        }
        printf("%d\n", m - cnt);
    }
    return 0;
}
