#include <random>
#include <string>
#include <cassert>
#include "confine.h"

using std::mt19937;
using std::random_device;
using std::string;

random_device rd;
mt19937 rnd(rd());
void confine(int n)
{
    int p = n >> 1;
    string s(n, ' '), t = s;
    for (int f = 0; f != p;)
    {
        for (char &c : s)
            c = '0' + rnd() % 2;
        f = dodoco(s);
        if (f == n)
            return;
    }
    t[0] = s[0];
    for (int i = 1; i < n; ++i)
    {
        s[0] ^= 1, s[i] ^= 1;
        int x = dodoco(s);
        t[i] = s[i] ^ bool(x);
        if (x == n)
            return;
        s[0] ^= 1, s[i] ^= 1;
    }
    int x = dodoco(t);
    if (x == n)
        return;
    for (char &c : t)
        c ^= 1;
    assert(dodoco(t) == n);
}
