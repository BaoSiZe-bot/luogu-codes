#include <map>
#include <cstdio>
const int N = 1e5 + 5;
int a[N];
std::map<int, int> cnt;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        cnt.clear();
        int n;
        scanf("%d", &n);
        bool f = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", a + i);
            cnt[a[i]]++;
            if (cnt[a[i]] > 1)
                f = 1;
        }
        if (a[1] == a[n])
        {
            printf("1\n");
            continue;
        }
        if (n == 2 || cnt[a[1]] > 1 || cnt[a[n]] > 1)
        {
            printf("2\n");
            continue;
        }
        if (f)
            printf("3\n");
        else
            printf("%d\n", n);
    }
    return 0;
}
