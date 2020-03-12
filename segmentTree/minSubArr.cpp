#include <bits/stdc++.h>
using namespace std;

void buildTree(int* arr, int* tree, int start, int end, int treeNode){
    if (start > end)
        return;
    if (start == end){
        tree[treeNode] = arr[start];
        return;
    }
    int mid = start + (end - start) / 2;
    buildTree(arr, tree, start, mid, 2*treeNode + 1);
    buildTree(arr, tree, mid + 1, end, 2*treeNode + 2);
    tree[treeNode] = min(tree[2*treeNode + 1],tree[2*treeNode + 2]);
}

void updateTree(int* arr, int* tree, int start, int end, int treeNode, int idx, int val){
    if (start > end)
        return;
    if (start == end){
        arr[idx] = val;
        tree[treeNode] = val;
        return;
    }
    int mid = start + (end - start) / 2;
    if (idx > mid){
        updateTree(arr, tree, mid + 1, end, 2*treeNode + 2, idx, val);
    }else{
        updateTree(arr, tree, start, mid, 2*treeNode + 1, idx, val);
    }
    tree[treeNode] = min(tree[2 * treeNode + 1], tree[2 * treeNode + 2]);
}

int query(int* tree, int start, int end, int treeNode, int left, int right){
    
    if (start > right || end < left)
        return INT_MAX;
    if (start >= left && end <= right)
        return tree[treeNode];
    int mid = start + (end - start)/2;
    int ans1 = query(tree, start, mid, 2*treeNode + 1, left, right);
    int ans2 = query(tree, mid + 1, end, 2*treeNode + 2, left, right);
    return min(ans1, ans2);
}

int main(){
    int n, q;
    cin >> n >> q;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i] ;
    int x = (int)(ceil(log2(n)));
    int max = 2*(int)pow(2,x) - 1;
    int* tree = new int[max];
    for (int i = 0; i < max; i++)
        tree[i] = INT_MAX;
    buildTree(arr, tree, 0, n - 1, 0);
    string ent;
    getline(cin, ent);
    while(q--){
        
        string qry;
        getline(cin , qry);
        string l, r;
        int i  = 2;
        while(qry[i] != ' '){
            l.push_back(qry[i]);
            i++;
        }
        i++;
        r = qry.substr(i,qry.length());
        int l_val = stoi(l);
        int r_val = stoi(r);
        if (qry[0] == 'q'){
            cout << query(tree, 0, n - 1, 0, l_val - 1, r_val - 1) << endl;
        }
        if (qry[0] == 'u'){
            updateTree(arr, tree, 0, n - 1, 0, l_val - 1, r_val - 1);
        }
    }
    delete[] tree;
    return 0;
}