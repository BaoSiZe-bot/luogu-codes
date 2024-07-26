#include <bits/stdc++.h>

using namespace std;

char ln[2 << 20], *tt = ln, *ss = ln;
inline char mygetchar()
{
    return tt == ss && (tt = (ss = ln) + fread(ln, 1, (long long)1 << 20, stdin), ss == tt) ? EOF : *ss++;
}
vector<vector<int>> v;
inline int read()
{
    int d = 0, f = 1;
    char c = mygetchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
        {
            f = ~f + 1;
        }
        c = mygetchar();
    }
    while (c >= '0' && c <= '9')
    {
        d = (d << 3) + (d << 1) + (c ^ 48);
        c = mygetchar();
    }
    return d * f;
}
inline void write(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = ~x + 1;
    }
    if (x > 9)
        write(x / 10);
    putchar(x - (x / 10 << 3) - (x / 10 << 1) + 48);
}
int main()
{
    ios::sync_with_stdio(0);
    long long n = read();
    for (int i = 1; i <= n; ++i)
    {
        vector<int> tmpvct;
        for (int j = 1; j <= i; ++j)
        {
            tmpvct.push_back(read());
        }
        v.push_back(tmpvct);
    }
    for (long long i = n - 2; i >= 0; i--)
    {
        for (long long j = 0; j <= i; ++j)
        {
            v[i][j] += v[i + 1][j] > v[i + 1][j + 1] ? v[i + 1][j] : v[i + 1][j + 1];
        }
    }
    write(v[0][0]);
    return 0;
}
