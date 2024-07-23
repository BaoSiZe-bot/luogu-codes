#include <stdio.h>
#define Get() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, fi), p1 == p2) ? EOF : *p1++)
FILE *fi = stdin, *fo = stdout;
char buf[1 << 23], *p1 = buf, *p2 = buf;
int h[2005][2005], dp[2005][2005], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, r, c;
inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline void ur(int &x) 
{
    x = 0;
    char ch = Get();
    for (; ch < 48 || ch > 57; ch = Get());
    for (; ch > 47 && ch < 58; ch = Get())
        x = (x << 1) + (x << 3) + (ch ^ 48);
}
inline int dfs(int x, int y)
{
    if (dp[x][y])
        return dp[x][y];
    for (int i = 0; i < 4; ++i)
    {
        int u = x + dx[i], v = y + dy[i];
        if (h[x][y] > h[u][v] && u && v && u <= r && v <= c)
        	dp[x][y] = max(dp[x][y], dfs(u, v));
    }
    return ++dp[x][y];
}
signed main()
{
    ur(r);
    ur(c);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            ur(h[i][j]);
    int res = 0;
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            res = max(res, dfs(i, j));
    return 0 * fprintf(fo, "%d", res);
}
