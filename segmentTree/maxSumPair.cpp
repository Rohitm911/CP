#include <bits/stdc++.h>
using namespace std;

struct node{
    long max;
    long smax;
};

void buildTree(long *arr, node* tree, int start , int end, int treeIndex){
    if (start == end){
        tree[treeIndex].max = arr[start];
        tree[treeIndex].smax = INT_MIN;
        return;
    }

    int mid = (start + end) / 2;
    buildTree(arr, tree, start, mid ,2*treeIndex);
    buildTree(arr, tree, mid + 1, end, 2*treeIndex + 1);
    node left = tree[2*treeIndex];
    node right = tree[2*treeIndex + 1];
    tree[treeIndex].max = max(left.max, right.max);
    tree[treeIndex].smax = min(max(left.max, right.smax), max(right.max, left.smax));
}

void updateTree(long* arr, node* tree, int start, int end, int treeIndex, int idx, int val){
    if (start == end){
        tree[treeIndex].max = val;
        arr[idx] = val;
        return;
    }

    int mid = (start + end) / 2;
    if (idx > mid){
        updateTree(arr, tree, mid + 1, end, 2*treeIndex + 1, idx, val);
    }else{
        updateTree(arr, tree, start, mid, 2*treeIndex, idx, val);
    }
    node left = tree[2 * treeIndex];
    node right = tree[2 * treeIndex + 1];
    tree[treeIndex].max = max(left.max, right.max);
    tree[treeIndex].smax = min(max(left.max, right.smax), max(right.max, left.smax));
}

node queryTree(node* tree, int start, int end, int treeIndex, int left, int right){
    if (left > end || right < start){
        node t;
        t.max = INT_MIN;
        t.smax = INT_MIN;
        return t;
    }
    if (left <= start && end <= right){
        return tree[treeIndex];
    }
    int mid = (start + end)/2;
    node ans1 = queryTree(tree, start, mid, 2*treeIndex, left, right);
    node ans2 = queryTree(tree, mid + 1, end, 2*treeIndex + 1, left, right);
    node temp;
    temp.max = max(ans1.max , ans2.max);
    temp.smax = min(max(ans1.max, ans2.smax), max(ans2.max,ans1.smax));
    return temp;
}

int main(){
    int n;
    cin >> n;
    long arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    node *tree = new node[4 * n];
    buildTree(arr, tree, 0, n - 1, 1);
    int q;
    cin >> q;
    while (q--){
        string s;
        int l, r;
        cin >> s >> l >> r;
        if (s == "Q"){
            node ans = queryTree(tree, 0, n - 1, 1, l - 1, r - 1);
            cout << ans.max + ans.smax << endl;
        }
        if (s == "U"){
            updateTree(arr, tree, 0, n - 1, 1, l - 1, r);
        }
    }
    
    return 0;
}