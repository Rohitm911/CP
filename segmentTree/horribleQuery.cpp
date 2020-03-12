#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// void buildTree(ll* tree, int start, int end, int treeNode){
//     if (start == end){
//         tree[treeNode] = 0;
//         return;
//     }

//     int mid = (start + end) / 2;
//     buildTree(tree, start, mid, 2* treeNode);
//     buildTree(tree, mid + 1, end, 2*treeNode + 1);
//     tree[treeNode] = tree[2*treeNode] + tree[2*treeNode + 1];
// }

void updateRange(ll* tree,ll* lazy, int start, int end, int treeNode, int left, int right, int val){
    if (start > end){
        return;
    }
    if (lazy[treeNode] != 0){
        tree[treeNode] += (end - start + 1)* lazy[treeNode];
        if (start != end){
            lazy[2*treeNode] += lazy[treeNode];
            lazy[2*treeNode + 1] += lazy[treeNode];
        }
        lazy[treeNode] = 0;
    }

    if (start > right || end < left){
        return ;
    }

    if (left <= start && end <= right){
        tree[treeNode] += (end - start + 1)* val;
        if (start != end){
            lazy[2*treeNode] += val;
            lazy[2*treeNode + 1] += val;
        }
        return;
    }

    int mid = (start + end) / 2;
    updateRange(tree, lazy, start, mid, 2*treeNode, left, right, val);
    updateRange(tree, lazy, mid + 1, end, 2*treeNode + 1, left, right, val);
    tree[treeNode] = tree[2*treeNode] + tree[2*treeNode + 1];
}

ll query(ll* tree, ll* lazy, int start, int end, int treeNode, int left, int right){

    if (start > end)
        return 0;
    if (lazy[treeNode] != 0){
        tree[treeNode] += (end - start + 1)* lazy[treeNode];
        if (start != end){
            lazy[2 * treeNode] += lazy[treeNode];
            lazy[2*treeNode + 1] += lazy[treeNode];
        }
        lazy[treeNode] = 0;
    }

    if (start > right || left > end)
        return 0;

    if (left <= start && end <= right){
        return tree[treeNode];
    }

    int mid = (start + end) / 2;
    int ans1 = query(tree, lazy, start, mid, 2*treeNode, left, right);
    int ans2 = query(tree, lazy, mid + 1, end, 2*treeNode + 1, left, right);
    return ans1 + ans2;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, c;
        cin >> n >> c;
        ll *tree = new ll[4*n]();
        
        ll *lazy = new ll[4*n]();
        while(c--){
            int typ, l , r, v;
            cin >> typ;
            if (typ == 1)
            {
                cin >> l >> r;
                cout << query(tree, lazy, 0, n - 1, 1, l - 1, r - 1) << endl;
            }else{
                cin >> l >> r >> v;
                updateRange(tree, lazy, 0, n -1, 1, l - 1, r - 1, v);
            }
        }

    }
    return 0;
}