#include <stdio.h>
#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
int a[1000005];
long long s[1000005];
int main()
{
    int t;
    long long v = 0, res = 0;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        scanf("%d", &a[i]);
        v += a[i];
    }
    v /= t;
    for (int i = 1; i <= t; i++)
        s[i] = s[i - 1] + a[i] - v;
    std::sort(s + 1, s + t + 1);
    for (int i = 1; i <= t; i++)
        res += std::abs(s[i] - s[(t + 1) >> 1]);
    printf("%lld", res);
    return 0;
}