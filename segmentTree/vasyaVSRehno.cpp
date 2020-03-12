#include <bits/stdc++.h>
using namespace std;

struct node{
    long long  maxA;
    long long  minB;
    long long  index;
};

void buildTree(long long* A, long long* B, node* tree, int start, int end, int treeNode){
    if (start == end){
        tree[treeNode].index = start;
        tree[treeNode].maxA = A[start];
        tree[treeNode].minB = B[start];
        return;
    }
    int mid = (start + end) / 2;
    buildTree(A, B,tree, start, mid, 2*treeNode);
    buildTree(A,B,tree, mid+1, end, 2*treeNode + 1);
    node l = tree[2*treeNode];
    node r = tree[2* treeNode + 1];
    if (l.maxA > r.maxA){
        tree[treeNode] = l;
        return;
    }
    if (r.maxA > l.maxA){
        tree[treeNode] = r;
        return;
    }
    
    if (l.minB < r.minB){
        tree[treeNode] = l;
        return;
    }
    if (l.minB > r.minB){
        tree[treeNode] = r;
        return;
    }
    if (l.index < r.index){
        tree[treeNode] = l;
        return;
    }
    if (l.index > r.index){
        tree[treeNode] = r;
        return;
    }
}

node query(node* tree, int start, int end, int treeNode, int left,int right){
    if (start > right || end < left){
        node t;
        t.maxA = INT_MIN;
        t.minB = INT_MAX;
        t.index = INT_MAX;
        return t;
    }

    if (left <= start && end <= right){
        return tree[treeNode];
    }
    int mid = (start + end) / 2;
    node l = query(tree, start, mid, 2*treeNode, left , right);
    node r = query(tree, mid + 1, end, 2*treeNode + 1, left, right);
    node temp;
    if (l.maxA > r.maxA)
    {
        temp = l;
        return temp;
    }
    if (r.maxA > l.maxA)
    {
        temp = r;
        return temp;
    }

    if (l.minB < r.minB)
    {
        temp = l;
        return temp;
    }
    if (l.minB > r.minB)
    {
        temp = r;
        return temp;
    }
    if (l.index < r.index)
    {
        temp = l;
        return temp;
    }
    if (l.index > r.index)
    {
        temp = r;
        return temp;
    }
}

int main(){
    int n;
    cin >> n;
    long long a[n],b[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    node* tree = new node[4*n]();
    buildTree(a, b, tree, 0, n - 1, 1);
    int q;
    cin >> q;
    int l,r;
    while(q--){
        cin>> l >> r;
        node ans = query(tree, 0, n - 1, 1, l-1, r-1);
        cout << ans.index + 1 << endl;
    }
    return 0;
}