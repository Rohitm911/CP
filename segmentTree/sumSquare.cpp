#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node{
    ll ss;
    ll s;
};

struct lazyNode{
    ll value;
    int type = 0;
};

void buildTree(int* arr, node* tree, int start , int end, int treeNode){
    if (start == end){
        tree[treeNode].ss = pow(arr[start],2);
        tree[treeNode].s = arr[start];
        return;
    }
    int mid = (start + end)/2;
    buildTree(arr, tree, start, mid, 2*treeNode);
    buildTree(arr, tree, mid + 1, end, 2*treeNode + 1);
    tree[treeNode].ss = tree[2*treeNode].ss + tree[2*treeNode + 1].ss;
    tree[treeNode].s = tree[2*treeNode].s + tree[2*treeNode + 1].s;
}

void updateRange(node* tree, lazyNode* lazy, int start, int end, int treeNode,int left, int right, int val,int typ){
    if (start > end){
        return;
    }
    if (lazy[treeNode].type != 0){
        if (lazy[treeNode].type == 1){
            tree[treeNode].ss += 2 * lazy[treeNode].value * tree[treeNode].s + pow(lazy[treeNode].value,2)*(end - start + 1);
            tree[treeNode].s += lazy[treeNode].value * (end - start + 1);
            if (start != end){
                lazy[2*treeNode].value += lazy[treeNode].value;
                lazy[2*treeNode].type = lazy[treeNode].type;
                lazy[2*treeNode + 1].value += lazy[treeNode].value;
                lazy[2*treeNode + 1].type = lazy[treeNode].type;
            }
        }else{
            tree[treeNode].ss = lazy[treeNode].value * lazy[treeNode].value *(end - start + 1);
            tree[treeNode].s = lazy[treeNode].value* (end - start + 1);
            if (start != end){
                lazy[2 * treeNode].value = lazy[treeNode].value;
                lazy[2 * treeNode].type = lazy[treeNode].type;
                lazy[2 * treeNode + 1].value = lazy[treeNode].value;
                lazy[2 * treeNode + 1].type = lazy[treeNode].type;
            }
        }
        lazy[treeNode].value = 0;
        lazy[treeNode].type = 0;
    }

    if (start > right || end < left){
        return;
    }

    if (left <= start && end <= right){
        if (typ == 1){
            tree[treeNode].ss += 2*val*tree[treeNode].s + pow(val,2)*(end - start + 1);
            tree[treeNode].s += val*(end - start + 1);
            if (start != end){
                lazy[2*treeNode].value = val;
                lazy[2*treeNode].type = typ;
                lazy[2*treeNode + 1].value = val;
                lazy[2*treeNode + 1].type = typ;
            }
            return;
        }
        if (typ == 2){
            tree[treeNode].ss = val*val*(end - start + 1);
            tree[treeNode].s = val*(end - start + 1);
            if (start != end){
                lazy[2*treeNode].value = val;
                lazy[2*treeNode].type = 2;
                lazy[2* treeNode + 1].value = val;
                lazy[2*treeNode + 1].type = 2;
            }
            return;
        }
    }

    int mid = (start + end)/2;
    updateRange(tree, lazy, start, mid, 2*treeNode, left, right, val, typ);
    updateRange(tree,lazy, mid + 1, end, 2*treeNode + 1, left, right, val, typ);
    tree[treeNode].ss = tree[2*treeNode].ss + tree[2*treeNode + 1].ss;
    tree[treeNode].s = tree[2*treeNode].s + tree[2* treeNode + 1].s;
}

ll query(node* tree, lazyNode* lazy, int start, int end, int left, int right, int treeNode){
    if (start > end){
        return 0;
    }
    if (lazy[treeNode].type != 0)
    {
        if (lazy[treeNode].type == 1)
        {
            tree[treeNode].ss += 2 * lazy[treeNode].value * tree[treeNode].s + pow(lazy[treeNode].value, 2) * (end - start + 1);
            tree[treeNode].s += lazy[treeNode].value * (end - start + 1);
            if (start != end)
            {
                lazy[2 * treeNode].value += lazy[treeNode].value;
                lazy[2 * treeNode].type = lazy[treeNode].type;
                lazy[2 * treeNode + 1].value += lazy[treeNode].value;
                lazy[2 * treeNode + 1].type = lazy[treeNode].type;
            }
        }
        else
        {
            tree[treeNode].ss = lazy[treeNode].value * lazy[treeNode].value * (end - start + 1);
            tree[treeNode].s = lazy[treeNode].value * (end - start + 1);
            if (start != end)
            {
                lazy[2 * treeNode].value = lazy[treeNode].value;
                lazy[2 * treeNode].type = lazy[treeNode].type;
                lazy[2 * treeNode + 1].value = lazy[treeNode].value;
                lazy[2 * treeNode + 1].type = lazy[treeNode].type;
            }
        }
        lazy[treeNode].value = 0;
        lazy[treeNode].type = 0;
    }

    if (start > right || end < left){
        return 0;
    }

    if (left <= start && end <= right){
        return tree[treeNode].ss;
    }

    int mid = (start + end)/2;
    int ans1 = query(tree, lazy, start, mid, left, right, 2*treeNode);
    int ans2 = query(tree, lazy, mid + 1, end, left, right, 2*treeNode + 1);
    return ans1 + ans2;
}

int main(){
    int t;
    cin >> t;
    int i = 1;
    while(i <= t){
        int n, q;
        cin >> n >> q;
        int arr[n];
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        node *tree = new node[4 * n];
        lazyNode *lazy = new lazyNode[4 * n]();
        buildTree(arr, tree, 0, n - 1, 1);
        int Case, left, right;
        cout << "Case " << i <<":" <<endl;
        while (q--)
        {
            cin >> Case >> left >> right;
            if (Case == 2)
            {
                cout << query(tree, lazy, 0, n - 1, left - 1, right - 1, 1) << endl;
            }
            else if (Case == 1)
            {
                int val;
                cin >> val;
                updateRange(tree, lazy, 0, n - 1, 1, left - 1, right - 1, val, 1);
            }
            else
            {
                int val;
                cin >> val;
                updateRange(tree, lazy, 0, n - 1, 1, left - 1, right - 1, val, 2);
            }
        }

        i++;
    }
    return 0;
}