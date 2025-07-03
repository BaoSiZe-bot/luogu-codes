#include <set>
#include <stdio.h>
std::set<int> s;
inline int gcd(int a, int b)
{
    static int t;
    while(b)
    {
        t = a;
        a = b;
        b = t % b;
    }
    return a;
}
int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    while (q--)
    {
        char c;
        int x, y;
        scanf("\n%c %d", &c, &x);
        if (c == 'S')
        {
            if (s.count(x))
                s.erase(s.find(x));
            else
                s.insert(x);
            continue;
        }
        scanf("%d", &y);
        bool f = 0;
        auto el = s.lower_bound(x);
        auto er = s.upper_bound(y);
        for (auto it = el; it != er; ++it)
        {
            for (auto jt = next(it); jt != er; ++jt)
                if (gcd(*it, *jt) ^ 1)
                {
                    f = 1;
                    break;
                }
            if (f)
                break;
        }
        printf(f ? "yes\n" : "no\n");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
