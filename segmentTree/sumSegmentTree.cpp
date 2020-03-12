#include <bits/stdc++.h>
using namespace std;

void buildTree(int* arr, int* tree, int start, int end, int treeNode){
    if (start == end){
        tree[treeNode] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    buildTree(arr, tree, start, mid, 2*treeNode);
    buildTree(arr, tree, mid + 1, end, 2*treeNode + 1);
    tree[treeNode] = tree[2*treeNode] + tree[2*treeNode + 1];
}

void updateTree(int* arr, int* tree, int start, int end, int treeNode, int idx, int val){
    if (start == end){
        arr[idx] = val ;
        tree[treeNode] = val;
        return;
    }
    int mid = (end + start) / 2;
    if (idx > mid){
        updateTree(arr, tree, mid + 1, end, 2*treeNode + 1, idx, val);
    }else{
        updateTree(arr, tree, start, mid, 2*treeNode, idx, val);
    }
    tree[treeNode] = tree[2*treeNode] + tree[2*treeNode + 1];
}

int query(int* tree, int start, int end, int treeNode, int left, int right){
    // completely outside of the range
    if (start > right || end < left)
        return 0;
    // completely inside of the range
    if (start >= left && end <= right)
        return tree[treeNode];
    // partially inside and partially outside of the range
    int mid = (start + end) / 2;
    int ans1 = query(tree, start, mid, 2*treeNode, left, right);
    int ans2 = query(tree, mid + 1, end, 2*treeNode + 1, left, right);
    return ans1 + ans2;
}

int main(){
    int n; 
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int *tree = new int[2*n];
    buildTree(arr, tree, 0, n-1, 1);
    updateTree(arr, tree, 0, n - 1, 1, 2, 4);
    for (int i = 1; i < 2*n; i++){
        cout << tree[i] <<endl;
    }
    int ans = query(tree, 0, n - 1, 1, 2, 4);
    cout << "Sum of the range from 2 to 4 is : " << ans << endl;
    delete[] tree;
    return 0;
}