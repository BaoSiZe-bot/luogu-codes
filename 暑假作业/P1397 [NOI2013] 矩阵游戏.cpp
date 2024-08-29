#include <stdio.h>
#include <string.h>
#define int long long
const int M = 1e9 + 7;
char s1[1000005], s2[1000005];
int l1, l2, n, m, a, b, c, d;
struct Matrix
{
    int a[2][2]{};
    Matrix operator*(const Matrix &x) const
    {
        return {(a[0][0] * x.a[0][0] % M + a[0][1] * x.a[1][0] % M) % M, (a[0][0] * x.a[0][1] % M + a[0][1] * x.a[1][1] % M) % M, (a[1][0] * x.a[0][0] % M + a[1][1] * x.a[1][0] % M) % M, (a[1][0] * x.a[0][1] % M + a[1][1] * x.a[1][1] % M) % M};
    }
} A, B, C, D;
inline Matrix qp(Matrix a, int b)
{
    Matrix res = {{1, 0, 0, 1}};
    while (b)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
signed main()
{
    scanf("%s%s", s1 + 1, s2 + 1);
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    l1 = static_cast<int>(strlen(s1 + 1));
    l2 = static_cast<int>(strlen(s2 + 1));
    const int MOD = M - (a != 1);
    for (int i = 1; i <= l2; ++i)
        m = ((m << 1) + (m << 3) + (s2[i] ^ 48)) % MOD;
    A.a[0][0] = a;
    A.a[0][1] = b;
    B.a[0][0] = c;
    B.a[0][1] = d;
    A.a[1][1] = 1;
    B.a[1][1] = 1;
    C.a[0][0] = 1;
    C.a[1][0] = 1;
    D = qp(A, m - 1) * B;
    int MD = M - (D.a[0][0] != 1);
    for (int i = 1; i <= l1; ++i)
        n = ((n << 1) + (n << 3) + (s1[i] ^ 48)) % MD;
    C = qp(D, n - 1) * qp(A, m - 1) * C;
    printf("%lld\n", C.a[0][0]);
    return 0;
}
