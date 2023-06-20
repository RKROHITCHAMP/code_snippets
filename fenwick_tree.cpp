#include <bits/stdc++.h>
using namespace std;
int fen[(int)1e9+7];
int n;
void update(int i, int val)
{
    while (i <= n)
    {
        fen[i] += val;
        i += (i & (~i));
    }
}
int sum(int i)
{
    int sum = 0;
    while (i >= 0)
    {
        sum += fen[i];
        i -= (i & (~i));
    }
    return sum;
}
void fenwicktree()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        update(i, arr[i]);  //nlogn 
    }
    while (q--) //qlogn
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int i, val;
            cin >> i >> val;
            update(i, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << sum(r) - sum(l - 1) << endl;
        }
    }
}
int main()
{

    return 0;
}