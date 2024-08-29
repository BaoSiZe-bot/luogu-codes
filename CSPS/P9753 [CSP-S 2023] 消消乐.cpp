#include <stdio.h>

char st[2000005];
int p[2000005], s[2000005], t[2000005][30];
int main()
{
    int n, res = 0;
    scanf("%d%s", &n, st + 1);
    for (int i = 1; i <= n; ++i)
    {
        p[i] = i;
        int g = t[p[i - 1]][st[i] ^ 97];
        if (g)
        {
            s[i] = s[g - 1] + 1;
            p[i] = p[g - 1];
        }
        t[p[i]][st[i] ^ 97] = i;
        res += s[i];
    }
    printf("%d", res);
    return 0;
}
