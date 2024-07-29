#include <bits/stdc++.h>
#define int long double

using namespace std;

int a[5005], dp1[5005], dp2[5005];
int mx, s;
signed main()
{
    int n;
    scanf("%Lf", &n);
    for (signed i = 1; i <= n; i++)
        scanf("%Lf", a + i);
    for (signed i = 1; i <= n; i++)
    {
        dp1[i] = 1;
        for (signed j = 1; j < i; ++j)
            if (a[i] < a[j])
                dp1[i] = max(dp1[i], dp1[j] + 1);
        mx = max(mx, dp1[i]);
    }
    for (signed i = 1; i <= n; i++)
    {
        if (dp1[i] == 1)
            dp2[i] = 1;
        for (signed j = 1; j < i; ++j)
            if (dp1[i] == dp1[j] + 1 && a[i] < a[j])
                dp2[i] += dp2[j];
            else if (dp1[i] == dp1[j] && a[i] == a[j])
                dp2[i] = 0;
        if (dp1[i] == mx)
            s += dp2[i];
    }
    printf("%.0Lf %.0Lf", mx, s);
    return 0;
}
