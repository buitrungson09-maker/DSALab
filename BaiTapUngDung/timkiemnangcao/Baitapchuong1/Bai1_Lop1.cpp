#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> generate_sorted_array(int n) {
    if (n <= 0) return {};
    vector<int> a(n);

    srand(time(0));

    a[0] = rand() % 10 + 1;

    for (int i = 1; i < n; ++i) {
        a[i] = a[i - 1] + (rand() % 5 + 1);
    }
    return a;
}

int linear_search(const vector<int>& a, int x) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        if (a[i] == x) {
            return i;
        }
        if (a[i] > x) { 
            return -1;
        }
    }
    return -1;
}


int binary_search(const vector<int>& a, int x) {
    int left = 0;
    int right = a.size() - 1;

    while (left <= right) {

        int mid = left + (right - left) / 2;

        if (a[mid] == x) {
            return mid;
        }
        else if (a[mid] < x) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

void print_array(const vector<int>& a) {
    cout << "[";
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i] << (i < a.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;
}

void print_result(const string& method_name, int x, int index) {
    cout << "  -> " << method_name << " (Tim " << x << "): ";
    if (index != -1) {
        cout << "Tim thay tai vi tri **" << index << "**." << endl;
    }
    else {
        cout << "Khong tim thay." << endl;
    }
}
int Bai1_Lop1() {
    const int N = 15;
    vector<int> a = generate_sorted_array(N);

    cout << "## Mang A (N = " << N << "):" << endl;
    print_array(a);
    cout << "---" << endl;

    int x_in = a[N / 3];
    int x_out = a[N - 1] + 5;

    cout << "## I. Tim Tuyen Tinh (Linear Search)" << endl;
    int res_linear_in = linear_search(a, x_in);
    print_result("Linear Search (Co)", x_in, res_linear_in);

    int res_linear_out = linear_search(a, x_out);
    print_result("Linear Search (Khong)", x_out, res_linear_out);

    cout << "---" << endl;

    cout << "## II. Tim Nhi Phan (Binary Search)" << endl;
    int res_binary_in = binary_search(a, x_in);
    print_result("Binary Search (Co)", x_in, res_binary_in);

    int res_binary_out = binary_search(a, x_out);
    print_result("Binary Search (Khong)", x_out, res_binary_out);

    return 0;
}