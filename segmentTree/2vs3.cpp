#include <bits/stdc++.h>
using namespace std;
#define m 3

void buildTree(int* arr, int *tree, int start, int end, int treeNode, int *twoPower)
{
    if (start == end){
        tree[treeNode] = arr[start];
        return;
    }

    int mid = (start + end) /2;
    buildTree(arr, tree, start, mid, 2 * treeNode, twoPower);
    buildTree(arr, tree, mid + 1, end, 2 * treeNode + 1, twoPower);
    tree[treeNode] = ((tree[2*treeNode] * twoPower[end - mid]) % m + tree[2*treeNode + 1]%m) % m;
}

void updateTree(int* arr, int *tree, int start, int end, int treeNode, int idx, int* twoPower)
{
    if (start  == end){
        if (arr[idx] == 0){
            arr[idx] = 1;
            tree[treeNode] = 1;
        }
        return ;
    }

    int mid = (start + end) / 2;
    if (idx > mid){
        updateTree(arr, tree, mid + 1, end, 2 * treeNode + 1, idx, twoPower);
    }else{
        updateTree(arr, tree, start, mid, 2 * treeNode, idx, twoPower);
    }
    tree[treeNode] = ((tree[2 * treeNode] * twoPower[end - mid]) % m + tree[2 * treeNode + 1] % m) % m;
}

int query(int *tree, int start, int end, int treeNode, int left, int right, int* twoPower)
{
    if (start > right || left > end){
        return 0;
    }
    if (left <= start && end <= right){
        return (tree[treeNode] * twoPower[right - end]) %m;
    }
    int mid = (start + end) / 2;
    int ans1 = query(tree, start, mid, 2 * treeNode, left, right, twoPower);
    int ans2 = query(tree, mid + 1, end, 2 * treeNode + 1, left, right, twoPower);
    return (ans1 + ans2) % m;
}

int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int arr[n];
    for (int i = 0; i < n; i++){
        if (s[i] == '0'){
            arr[i] = 0;
        }else{
            arr[i] = 1;
        }
    }
    int* tree = new int[4*n];
    int twoPower[1000001];
    twoPower[0] = 1;
    for (int i = 1; i <= 100000; i++){
        twoPower[i] = (twoPower[i - 1] * 2 ) % m;
    }
    buildTree(arr, tree, 0, n - 1, 1, twoPower);
    int q;
    cin >> q;
    while(q--){
        int typ, l, r;
        cin >> typ >> l;
        if (typ == 1){
            updateTree(arr, tree, 0, n - 1, 1, l, twoPower);
        }else{
            cin >> r;
            cout << query(tree, 0, n - 1, 1, l, r, twoPower) << endl;
        }
    }
    return 0;
}