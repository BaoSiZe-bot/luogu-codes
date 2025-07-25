#include <cstdio>
#include <cstring>
const int N = 3e7 + 5;

char a[N], d[N];
int r[N];
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int init(char *dst, char *src)
{
    int t = 0, n = strlen(src);
    dst[++t] = '#';
    for (int i = 0; i < n; ++i)
    {
        dst[++t] = src[i];
        dst[++t] = '#';
    }
    dst[0] = 5;
    dst[t + 1] = 20;
    return t;
}
int main()
{
    scanf("%11000000s", a);
    int l = init(d, a);

    int res = 0, p = 0, c = 0;
    for (int i = 1; i <= l; ++i)
    {
        r[i] = i > p ? 0 : min(r[2 * c - i], p - i);
        while (d[i - r[i] - 1] == d[i + r[i] + 1])
            ++r[i];
        if (i + r[i] > p)
        {
            c = i;
            p = i + r[i];
        }
        if (r[i] > res)
            res = r[i];
    }
    printf("%d\n", res);
    return !5201314;
}
