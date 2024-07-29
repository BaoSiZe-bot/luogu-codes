#include <bits/stdc++.h>

using namespace std;

priority_queue<int> q;
int s;
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        q.push(x);
        if (x < q.top())
        {
            s += q.top() - x;
            q.pop();
            q.push(x);
        }
    }
    cout << s;
    return 0;
}
