#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node
{
    ll maxSum;
    ll sum;
    ll bestPrefixSum;
    ll bestSuffixSum;
};

void buildTree(int *arr, node *tree, int start, int end, int treeNode)
{
    if (start == end)
    {
        tree[treeNode].maxSum = arr[start];
        tree[treeNode].sum = arr[start];
        tree[treeNode].bestPrefixSum = arr[start];
        tree[treeNode].bestSuffixSum = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    buildTree(arr, tree, start, mid, 2 * treeNode);
    buildTree(arr, tree, mid + 1, end, 2 * treeNode + 1);
    node left = tree[2 * treeNode];
    node right = tree[2 * treeNode + 1];
    ll LMS = left.maxSum;
    ll RMS = right.maxSum;
    ll LS = left.sum;
    ll RS = right.sum;
    ll BLPS = left.bestPrefixSum;
    ll BRPS = right.bestPrefixSum;
    ll BLSS = left.bestSuffixSum;
    ll BRSS = right.bestSuffixSum;
    tree[treeNode].maxSum = max(LMS, max(RMS, max(LS + BRPS, max(RS + BLSS, BLSS + BRPS))));
    tree[treeNode].sum = LS + RS;
    tree[treeNode].bestPrefixSum = max(BLPS, LS + BRPS);
    tree[treeNode].bestSuffixSum = max(BRSS, RS + BLSS);
    return;
}

node queryTree(node *tree, int start, int end, int treeNode, int left, int right)
{
    if (right < start || end < left)
    {
        node t;
        t.maxSum = -16000;
        t.sum = -16000;
        t.bestPrefixSum = -16000;
        t.bestSuffixSum = -16000;
        return t;
    }
    if (left <= start && right >= end)
    {
        return tree[treeNode];
    }
    int mid = (start + end) / 2;
    node ans1 = queryTree(tree, start, mid, 2 * treeNode, left, right);
    node ans2 = queryTree(tree, mid + 1, end, 2 * treeNode + 1, left, right);
    ll LMS = ans1.maxSum;
    ll RMS = ans2.maxSum;
    ll LS = ans1.sum;
    ll RS = ans2.sum;
    ll BLPS = ans1.bestPrefixSum;
    ll BRPS = ans2.bestPrefixSum;
    ll BLSS = ans1.bestSuffixSum;
    ll BRSS = ans2.bestSuffixSum;
    node temp;
    temp.maxSum = max(LMS, max(RMS, max(LS + BRPS, max(RS + BLSS, BLSS + BRPS))));
    temp.sum = LS + RS;
    temp.bestPrefixSum = max(BLPS, LS + BRPS);
    temp.bestSuffixSum = max(BRSS, RS + BLSS);
    return temp;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    node *tree = new node[4 * n];
    buildTree(arr, tree, 0, n - 1, 1);

    int m;
    cin >> m;
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        node ans = queryTree(tree, 0, n - 1, 1, l - 1, r - 1);
        cout << ans.maxSum << endl;
    }
    return 0;
}