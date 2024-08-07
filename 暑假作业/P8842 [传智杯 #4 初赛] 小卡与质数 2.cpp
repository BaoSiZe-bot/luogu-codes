#include <stdio.h>
#include <vector>
std::vector<int> prm;
bool G[1000005];
int s[1000005];
inline void oba(const int &lim)
{
    for (int i = 2; i <= lim; ++i)
    {
        if (!G[i])
            prm.push_back(i);
        for (int j : prm)
        {
            if (i * j > lim)
                break;
            G[i * j] = 1;
            if (i % j == 0)
                break;
        }
    }
    for (int i = 2; i <= lim; ++i)
        s[i] = s[i - 1] + !G[i];
}
int main()
{
    int t;
    scanf("%d", &t);
    oba(1000000);
    while (t--)
    {
        int x, res = 0;
        scanf("%d", &x);
        for (; x; x -= x & -x)
            res += s[((x & -x) << 1) - 1] - s[(x & -x) - 1];
        printf("%d\n", res);
    }
    return 0;
}
