#include <iostream>
#include <limits>
#include <vector>

using namespace std;

//nondecreasing order
void INSERTION_SORT_ASC(vector<int>& arr){
    int len = arr.size(), i;
    for (int j = 0; j != len; ++j){
        // take item that want to operate
        int key = arr[j];
        // an index before
        i = j - 1;
        // go over to compare key and current item. 
        while (i >= 0 && arr[i] > key){
            arr[i + 1] = arr[i];
            i -= 1;
        }
        arr[i + 1] = key;
    }
    return;
};

// 2.1-2
// nonincreasing order
void INSERTION_SORT_DES(vector<int>& arr){
    int len = arr.size(), i;
    for (int j = 0; j != len; ++j){
        int key = arr[j];
        i = j - 1;
        while (i >= 0 && arr[i] < key){
            arr[i + 1] = arr[i];
            i -= 1;
        }
        arr[i + 1] = key;
    }
    return;
};

// 2.2-2
// selection sort
void SELECTION_SORT(vector<int>& arr){
    int n = arr.size();
    for (int i = 0; i != n - 1; ++i){
        int min_idx = i;
        for (int j = i; j != n; ++j){
            // find ith smallest item == find the smallest in the arr[i:]
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        // int temp = arr[i];
        // arr[i] = arr[min_idx];
        // arr[min_idx] = temp;
        swap(arr[i], arr[min_idx]);
    }
    return;
};

// merge sort
// merge function with sentinels
void MERGE(vector<int>& arr, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> left(n1);
    vector<int> right(n2);
    
    for (int i = 0; i != n1; ++i){
        left[i] = arr[p + i - 1];
    }
    for (int j = 0; j != n2; ++j){
        right[j] = arr[q + j];
    }

    left.push_back(numeric_limits<int>::max());
    right.push_back(numeric_limits<int>::max());
    int i = 0, j = 0;
    for (int k = p - 1; k != r; ++k){
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        }
        else{
            arr[k] = right[j];
            ++j;
        }
    }
    return;
};

// merge function without sentinel
void MERGE2(vector<int>& arr, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> left(n1);
    vector<int> right(n2);
    
    for (int i = 0; i != n1; ++i){
        left[i] = arr[p + i - 1];
    }
    for (int j = 0; j != n2; ++j){
        right[j] = arr[q + j];
    }

    int i = 0, j = 0, k = p - 1;
    while (i < n1 && j < n2){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            ++i;
        }
        else{
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }
    
    // check if anything left in the subarrays
    while (i < n1){
        arr[k] = left[i];
        ++i;
        ++k;
    }

    while (j < n2){
        arr[k] = right[j];
        ++j;
        ++k;
    }
}

// p = 1, r = arr.size()
void MERGE_SORT(vector<int>& arr, int p, int r){
    if (p < r){
        int q = int((p + r) / 2);
        MERGE_SORT(arr, p, q);
        MERGE_SORT(arr, q + 1, r);
        // MERGE(arr, p, q, r);
        MERGE2(arr, p, q, r);
    }
    return;
};

// inseration sort with binary serach
// binary search
int bin_search(int l, int r, vector<int>& arr, int v){
    if (l > r) return l;
    int mid = (l + r) / 2;
    if (arr[mid] > v) return bin_search(l, mid - 1, arr, v);
    if (arr[mid] < v) return bin_search(mid + 1, r, arr, v);
    return mid;
};
void insertion_sort(vector<int>& arr){
    for (int i = 1; i != arr.size(); ++i){
        int key = arr[i];
        int idx = bin_search(0, i - 1, arr, key);
        int j = i - 1;
        while (j >= idx){
            arr[j + 1] = arr[j];
            --j; 
        }
        arr[j + 1] = key;
    }
}

// bubble sort
void BUBBLESORT(vector<int>& arr){
    int n = arr.size();
    for (int i = 0; i != n - 2; ++i){
        for (int j = n - 1; j != i; --j){
            if (arr[j] < arr[j - 1]) swap(arr[j], arr[j - 1]); 
        }
    }
    return;
}

// Modified merge sort
int M_MERGE(vector<int>& arr, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int n_inv = 0;
    vector<int> left(n1);
    vector<int> right(n2);
    
    for (int i = 0; i != n1; ++i){
        left[i] = arr[p + i - 1];
    }
    for (int j = 0; j != n2; ++j){
        right[j] = arr[q + j];
    }

    left.push_back(numeric_limits<int>::max());
    right.push_back(numeric_limits<int>::max());
    int i = 0, j = 0;
    for (int k = p - 1; k != r; ++k){
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        }
        else{
            n_inv += n1 - i;
            arr[k] = right[j];
            ++j;
        }
    }
    return n_inv;
};

int Count_inv(vector<int>& arr, int p, int r){
    if (p >= r) return 0;
    int q = int((p + r) / 2);
    int left, right, n_invs;
    left = Count_inv(arr, p, q);
    right = Count_inv(arr, q + 1, r);
    n_invs = left + right + M_MERGE(arr, p, q, r);
    return n_invs;
};

int main(){
    vector<int> arr = {39, 28, 1, 9, 49, 51};
    // vector<int> arr = {1, 2, 3, 4, 5, 6};

    int res = Count_inv(arr, 1, arr.size());

    
    // for (int i = 0; i != arr.size(); ++i){
    //     cout << arr[i] << endl;
    // }

    cout << res << endl;

    return 0;
}