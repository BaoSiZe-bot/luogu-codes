#include <bits/stdc++.h>

using namespace std;

int a[5005], dp1[5005], dp2[5005];
int mx, s;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
    {
        dp1[i] = 1;
        for (int j = 1; j < i; ++j)
            if (a[i] < a[j])
                dp1[i] = max(dp1[i], dp1[j] + 1);
        mx = max(mx, dp1[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (dp1[i] == 1)
            dp2[i] = 1;
        for (int j = 1; j < i; ++j)
            if (dp1[i] == dp1[j] + 1 && a[i] < a[j])
                dp2[i] += dp2[j];
            else if (dp1[i] == dp1[j] && a[i] == a[j])
                dp2[i] = 0;
        if (dp1[i] == mx)
            s += dp2[i];
    }
    printf("%d %d", mx, s);
    return 0;
}
