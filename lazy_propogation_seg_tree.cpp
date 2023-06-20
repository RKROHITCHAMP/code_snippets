#include <bits/stdc++.h>
using namespace std;
class sgtree
{
private:
    vector<int> seg, lazy;

public:
    sgtree(int n)
    {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
    int range_query(int ind, int low, int high, int l, int r)
    {
        // update previous remaining updates
        if (lazy[ind] != 0)
        {
            seg[ind] += (high - low + 1) * lazy[ind];

            if (low != high) // means child is present so propgate down
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap
        if (r < low or l > high)
            return 0;
        // complete overlap
        if (low >= l and high <= r)
            return seg[ind];

        int mid = low + (high - low) / 2;
        int left = range_query(2 * ind + 1, low, mid, l, r);
        int right = range_query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }
    void range_update(int ind, int low, int high, int l, int r, int val)
    {
        // update previous remaining updates
        // propogate downward
        if (lazy[ind] != 0)
        {
            seg[ind] += (high - low + 1) * lazy[ind];

            if (low != high) // means child is present so propgate down
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
        // no overlap
        if (r < low or l > high)
            return;

        // complete overlap
        if (low >= l and high <= r)
        {
            seg[ind] += (high - low + 1) * val;
            if (low != high) // means child is present so propagate down
            {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }
        // partial overlap
        int mid = low + (high - low) / 2;
        range_update(2 * ind + 1, low, mid, l, r, val);
        range_update(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};

class sgtree_minimum
{
private:
    vector<int> seg, lazy;

public:
    sgtree_minimum(int n)
    {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    int range_query(int ind, int low, int high, int l, int r)
    {
        // update previous remaining updates
        if (lazy[ind] != 0)
        {
            seg[ind] += lazy[ind];

            if (low != high) // means child is present so propgate down
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap
        if (r < low or l > high)
            return INT_MAX;
        // complete overlap
        if (low >= l and high <= r)
            return seg[ind];

        int mid = low + (high - low) / 2;
        int left = range_query(2 * ind + 1, low, mid, l, r);
        int right = range_query(2 * ind + 2, mid + 1, high, l, r);
        return min(left, right);
    }
    void range_update(int ind, int low, int high, int l, int r, int val)
    {
        // update previous remaining updates
        // propogate downward
        if (lazy[ind] != 0)
        {
            seg[ind] += lazy[ind];

            if (low != high) // means child is present so propgate down
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
        // no overlap
        if (r < low or l > high)
            return;

        // complete overlap
        if (low >= l and high <= r)
        {
            seg[ind] += val;
            if (low != high) // means child is present so propagate down
            {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }
        // partial overlap
        int mid = low + (high - low) / 2;
        range_update(2 * ind + 1, low, mid, l, r, val);
        range_update(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};
int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sgtree st(n);
    st.build(0, 0, n - 1, arr);
    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << st.range_query(0, 0, n - 1, l, r) << endl;
        }
        else
        {
            int l, r, val;
            cin >> l >> r >> val;
            st.range_update(0, 0, n - 1, l, r, val);
        }
    }
}