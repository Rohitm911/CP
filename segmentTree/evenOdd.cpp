#include <bits/stdc++.h>
using namespace std;

struct node{
    long evenCount = 0;
    long oddCount = 0;
};

void buildTree(long* arr, node* tree, int start, int end, int treeNode){
    if (start == end){
        if (arr[start] % 2 == 0){
            tree[treeNode].evenCount++;
        }else{
            tree[treeNode].oddCount++;
        }
        return;
    }

    int mid = (start + end) / 2;
    buildTree(arr, tree, start, mid, 2*treeNode);
    buildTree(arr, tree, mid+ 1, end, 2*treeNode + 1);
    tree[treeNode].evenCount = tree[2*treeNode].evenCount + tree[2*treeNode + 1].evenCount;
    tree[treeNode].oddCount = tree[2*treeNode].oddCount + tree[2*treeNode + 1].oddCount;
}

void updateTree(long* arr,node* tree, int start, int end, int treeNode, int idx, int val){
    if(start == end){
        if (val&1){
            if (arr[idx]&1 == 0){
                tree[treeNode].oddCount++;
                tree[treeNode].evenCount--;
            }
        }else{
            if (arr[idx]&1){
                tree[treeNode].evenCount++;
                tree[treeNode].oddCount--;
            }
        }
        arr[idx] = val;
        return;
    }
    int mid = (start + end)/2;
    if(mid >= idx){
        updateTree(arr,tree, start, mid, 2*treeNode, idx, val);
    }else{
        updateTree(arr, tree, mid + 1, end, 2*treeNode + 1, idx, val);
    }
    tree[treeNode].evenCount = tree[2 * treeNode].evenCount + tree[2 * treeNode + 1].evenCount;
    tree[treeNode].oddCount = tree[2 * treeNode].oddCount + tree[2 * treeNode + 1].oddCount;
}

node query(node* tree, int start, int end, int treeNode, int left, int right){
    if (start > right || end < left)
    {
        node t;
        t.evenCount = 0;
        t.oddCount = 0;
        return t;
    }

    if (left <= start && end <= right){
        return tree[treeNode];
    }
    int mid = (start + end) / 2;
    node l = query(tree, start, mid, 2*treeNode, left, right);
    node r = query(tree, mid + 1, end, 2*treeNode + 1, left, right);
    node temp;
    temp.evenCount = l.evenCount + r.evenCount;
    temp.oddCount = l.oddCount + r.oddCount;
    return temp;
}
int main(){
    int n;
    cin >> n;
     long arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    node* tree = new node[4*n]();
    buildTree(arr, tree, 0, n - 1, 1);
    int q;
    cin >> q;
    int Case, x, y;
    while(q--){
        cin >> Case >> x >> y;
        if (Case == 0){
            updateTree(arr,tree, 0, n-1, 1, x - 1, y);
        }else if (Case == 1){
            node ans = query(tree, 0, n - 1, 1, x-1, y-1);
            cout << ans.evenCount << endl;
        }else{
            node ans = query(tree, 0, n - 1, 1, x - 1, y - 1);
            cout << ans.oddCount << endl;
        }
    }
    delete[] tree;
    return 0;
}