#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int a, b, c, d;
        cin>>a>>b;
        c = (a + b) / 2;
        d = (a - b) / 2;
        if (a < b || (a % 2 != b % 2) || c < 0 || d < 0)
        {
            puts("impossible");
            continue;
        }
        printf("%d %d\n", (a + b) / 2, (a - b) / 2);
    }
    return 0;
}
