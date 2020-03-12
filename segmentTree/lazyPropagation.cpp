#include <bits/stdc++.h>
using namespace std;

void buildTree(int* arr, int* tree, int start , int end, int treeNode){
    if (start == end){
        tree[treeNode] = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    buildTree(arr, tree, start, mid , 2*treeNode);
    buildTree(arr, tree, mid + 1, end, 2*treeNode + 1);
    tree[treeNode] = min(tree[2*treeNode] , tree[2*treeNode + 1]);
}

void updateSegmentTreeLazy(int* tree, int* lazy, int start, int end, int startR, int endR, int currPos, int inc){
    if (start > end){
        return;
    }

    if (lazy[currPos] != 0){
        tree[currPos] += lazy[currPos];

        if (start != end) // the curr node is not leaf so it must be having childs
        {
            lazy[2*currPos] += lazy[currPos];
            lazy[2*currPos + 1]+= lazy[currPos];
        }
        lazy[currPos] = 0;
    }

    // no overlap
    if (startR > end || endR < start){
        return;
    }
    // complete overlap
    if (startR <= start && endR >= end){
        tree[currPos] += inc;
        if (start != end){
            lazy[2*currPos] += inc;
            lazy[2*currPos + 1] += inc;
        }
        return;
    }
    // partial overlap
    int mid = (start + end) / 2;
    updateSegmentTreeLazy(tree, lazy, start, mid, startR, endR, 2*currPos, inc);
    updateSegmentTreeLazy(tree, lazy, mid + 1, end, startR, endR, 2*currPos + 1, inc);
    tree[currPos] = min(tree[2*currPos], tree[2*currPos + 1]);
}

int queryTree(int* tree, int* lazy, int start, int end, int left, int right, int treeNode){
    if (start > end){
        return INT_MAX;
    }
    if (lazy[treeNode] != 0){
        tree[treeNode] += lazy[treeNode];
        if (start != end){
            lazy[2*treeNode] += lazy[treeNode];
            lazy[2*treeNode + 1] += lazy[treeNode];
        }
        lazy[treeNode] = 0;
    }
    if (left > end || right < start){
        return INT_MAX;
    }
    if (left <= start && end <= right){
        return tree[treeNode];
    }
    int mid = (start + end) / 2;
    int ans1 = queryTree(tree, lazy, start , mid, left, right, 2*treeNode);
    int ans2 = queryTree(tree, lazy, mid + 1, end, left, right, 2*treeNode + 1);
    return min(ans1 , ans2);
}

int main(){
    int arr[] = {1, 3, -2 , 4};
    int* tree = new int[12]();
    buildTree(arr, tree, 0, 3, 1);
    int* lazy = new int[12]();
    updateSegmentTreeLazy(tree, lazy, 0, 3, 0, 3, 1, 3);
    updateSegmentTreeLazy(tree, lazy, 0, 3, 0, 1, 1, 2);
    // for (int i = 1; i < 12; i++)
    //     cout << lazy[i] <<" ";
    // cout << endl;
   cout << queryTree(tree, lazy, 0, 3, 1, 2,1) << endl;
    return 0;
}