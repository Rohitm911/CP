#include <bits/stdc++.h>
using namespace std;

struct Set{
    char c;
    long long val;
    int index;
};



void update(int index,int n, int* bit, int val){
    for (; index <= n; index += (index&(-index))){
        bit[index] += val;
    }
}

int query(int index, int* bit){
    int count = 0;
    for (; index > 0; index -= (index&(-index))){
        count += bit[index];
    }
    return count;
}

void Insert(long long val, unordered_map<long long, int>& m, int* bit){
    if (query(m[val], bit) == query(m[val] - 1, bit)){
        update(m[val], m.size(), bit, 1);
    }
}

void Delete(long long val, unordered_map<long long, int> &m, int *bit){
   
    if (query(m[val], bit) != query(m[val] - 1, bit))
    {
        update(m[val], m.size(), bit, -1);
    }
}

long long kthSmallestElement(int *bit, int n, unordered_map<long long, int> &m, int k, vector<long long>& v){
    
    int start = 0, end = n - 1;
    while(start <= end){
        int mid = (start + end) / 2;
        if (query(m[v[mid]], bit) == k){
            return v[mid];
        }
        else if (query(m[v[mid]], bit) < k){
            start = mid + 1;
        }else{
            end = mid - 1;
        }
    }
    return -1;
}

int countSmallest(int *bit, unordered_map<long long, int> &m, vector<long long> &v, long long x){
   
    int j = lower_bound(v.begin(), v.end(), x) - v.begin();
    if (v[j] < x){
        return query(m[v[j]], bit);
    }else{
        return query(m[v[--j]], bit);
    }
}

int main()
{
    int q;
    cin >> q;
    Set* s = new Set[q];
    unordered_map<long long, int> m;
    vector<long long> v;
    set<long long> st;
    for (int i= 0; i < q; i++){
        cin >> s[i].c >> s[i].val;
        s[i].index = i;
        if (s[i].c == 'I')
            st.insert(s[i].val);
    }
    int p = 1;
    for (auto it = st.begin(); it != st.end(); ++it){
        m[*it] = p;
        v.push_back(*it);
        p++;
    }
    int n = st.size();
    int *bit = new int[n+1];
    
    for (int i = 1; i <=n; i++){
        bit[i] = 0;
    }

    for (int i = 0; i < q; i++){
        if (s[i].c == 'I'){
            Insert(s[i].val, m, bit);
        }else if (s[i].c == 'D'){
            Delete(s[i].val, m,  bit);
        }else if (s[i].c == 'K'){
            int x = kthSmallestElement(bit, n, m, s[i].val, v);
            if (x == -1){
                cout << "invalid" << endl;
            }else{
                cout << x << endl;
            }
        }else{
            cout << countSmallest(bit, m, v, s[i].val) << endl;
        }
    }
    return 0;
}