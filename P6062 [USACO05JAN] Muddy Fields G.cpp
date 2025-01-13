#include <cstring>
#include <stdio.h>
char s[55][55];
int h[55][55], v[55][55], hcnt, vcnt;
int mp[2505][2505], md[2505], vs[2505], r, c;
inline bool Hungarian(int x)
{
    for (int i = 1; i <= vcnt; ++i)
        if (mp[x][i] && !vs[i])
        {
            vs[i] = 1;
            if (!md[i] || Hungarian(md[i]))
            {
                md[i] = x;
                return 1;
            }
        }
    return 0;
}

int main()
{
    scanf("%d%d", &r, &c);
    for (int i = 1; i <= r; ++i)
        scanf("%50s", s[i] + 1);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            if (s[i][j] ^ '.')
                h[i][j] = (hcnt += (j == 1 || s[i][j - 1] ^ '*'));
    for (int i = 1; i <= c; ++i)
        for (int j = 1; j <= r; ++j)
            if (s[j][i] ^ '.')
                v[j][i] = (vcnt += (j == 1 || s[j - 1][i] ^ '*'));
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            mp[h[i][j]][v[i][j]] = 1;
    int res = 0;
    for (int i = 1; i <= hcnt; ++i)
    {
        memset(vs, 0, sizeof vs);
        res += Hungarian(i);
    }
    printf("%d", res);
    return 0;
}
