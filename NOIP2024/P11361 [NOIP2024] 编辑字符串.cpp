#include <stdio.h>
const int N = 100005;
int ap[N], bp[N], a0[N], a1[N], b0[N], b1[N];
char s1[N], s2[N], t1[N], t2[N];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, res = 0;
        scanf("%d%100000s%100000s%100000s%100000s", &n, s1 + 1, s2 + 1, t1 + 1, t2 + 1);
        ap[1] = bp[1] = 0;
        for (int i = 2; i <= n; ++i)
            if (t1[i - 1] == '0' || t1[i] == '0')
                ap[i] = i;
            else
                ap[i] = ap[i - 1];
        for (int i = 2; i <= n; ++i)
            if (t2[i - 1] == '0' || t2[i] == '0')
                bp[i] = i;
            else
                bp[i] = bp[i - 1];
        for (int i = 1; i <= n; ++i)
        {
            if (s1[i] == '0')
                ++a0[ap[i]];
            else
                ++a1[ap[i]];
            if (s2[i] == '0')
                ++b0[bp[i]];
            else
                ++b1[bp[i]];
        }
        for (int i = 1; i <= n; ++i)
            if (a0[ap[i]] && b0[bp[i]])
            {
                ++res;
                --a0[ap[i]];
                --b0[bp[i]];
            }
            else if (a1[ap[i]] && b1[bp[i]])
            {
                ++res;
                --a1[ap[i]];
                --b1[bp[i]];
            }
            else if (a0[ap[i]])
            {
                --a0[ap[i]];
                --b1[bp[i]];
            }
            else
            {
                --a1[ap[i]];
                --b0[bp[i]];
            }
        printf("%d\n", res);
    }
    return 0;
}
