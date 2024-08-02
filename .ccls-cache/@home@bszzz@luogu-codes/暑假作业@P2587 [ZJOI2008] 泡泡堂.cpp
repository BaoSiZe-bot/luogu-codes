#include <stdio.h>
#include <bits/stl_algo.h>

int a[1000005], b[1000005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    std::sort(b + 1, b + n + 1);
    int ll = 1, lr = n, rl = 1, rr = n, mx = 0, dn = 0;
    while (ll <= lr && rl <= rr)
    {
        if (a[ll] > b[rl])
        {
            ++ll;
            ++rl;
            mx += 2;
        }
        else if (a[lr] > b[rr])
        {
            --lr;
            --rr;
            mx += 2;
        }
        else
            mx += (a[ll++] == b[rr--]);
    }
    ll = rl = 1;
    lr = rr = n;
    while (ll <= lr && rl <= rr)
    {
        if (a[rl] < b[ll])
        {
            ++ll;
            ++rl;
            mx += 2;
        }
        else if (a[rr] < b[lr])
        {
            --lr;
            --rr;
            mx += 2;
        }
        else
            mx += (a[rr--] == b[ll++]);
    }
    printf("%d\n%d", mx, n + n - dn);
    return 0;
}
