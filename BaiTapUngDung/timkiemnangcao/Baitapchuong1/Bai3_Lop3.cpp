#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define MAX_N 1000 

void DocFile3(const char tenfile[], int a[], int& n) {
    ifstream filein(tenfile);
    if (!filein.is_open()) {
        cerr << "Loi: Khong the mo tap tin " << tenfile << " de doc." << endl;
        n = 0;
        return;
    }

    if (!(filein >> n)) {
        cerr << "Loi: Khong doc duoc so phan tu n tu tap tin." << endl;
        n = 0;
        filein.close();
        return;
    }

    if (n > MAX_N) {
        cerr << "Canh bao: So phan tu n (" << n << ") lon hon gioi han cho phep (" << MAX_N << ")." << endl;
        n = 0;
        filein.close();
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!(filein >> a[i])) {
            cerr << "Loi: Khong doc du so phan tu cua mang." << endl;
            n = i;
            filein.close();
            return;
        }
    }

    filein.close();
    cout << "Doc thanh cong " << n << " phan tu tu tap tin " << tenfile << "." << endl;
}

void XuatMang3(const int a[], int n) {
    if (n <= 0) {
        cout << "Mang rong hoac co loi khi doc file." << endl;
        return;
    }
    cout << "Mang A gom " << n << " phan tu: [";
    for (int i = 0; i < n; ++i) {
        cout << a[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int TimTuyenTinh(const int a[], int n, int x, long long& ss) {
    ss = 0; 
    for (int i = 0; i < n; ++i) {

        ss++;
        if (a[i] == x) {
            return i;
        }

        ss++;
        if (a[i] > x) {
            return -1;
        }
    }
    return -1;
}

int TNPTang(const int a[], int n, int x, long long& ss) {
    ss = 0; 
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        ss++;
        if (a[mid] == x) {
            return mid;
        }

        ss++;
        if (a[mid] < x) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

void GhiKetQuaFile(const char tenfile[], const int a[], int n, int x, int vi_tri, long long ss) {
    ofstream fileout(tenfile);
    if (!fileout.is_open()) {
        cerr << "Loi: Khong the mo tap tin " << tenfile << " de ghi." << endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        fileout << a[i] << (i < n - 1 ? "\t" : "");
    }
    fileout << endl;

    fileout << x << "\t" << vi_tri << "\t" << ss << endl;

    fileout.close();
    cout << "Ghi ket qua tim kiem vao tap tin **" << tenfile << "** thanh cong." << endl;
}


int Bai3_Lop3() {
    int a[MAX_N];
    int n;
    int x;
    int vi_tri;
    long long so_sanh; 
    const char* INPUT_FILE = "data002.in"; 

    DocFile3(INPUT_FILE, a, n);

    if (n <= 0) {
        cerr << "Chuong trinh ket thuc do loi doc file hoac mang rong." << endl;
        return 1;
    }

    cout << "--- Kiem tra du lieu doc duoc ---" << endl;
    XuatMang3(a, n);
    cout << "----------------------------------" << endl;

    cout << "\n--- TIM TUYEN TINH ---" << endl;
    cout << "Nhap gia tri can tim x cho phuong phap TIM TUYEN TINH: ";
    if (!(cin >> x)) {
        cerr << "Loi nhap lieu." << endl;
        return 1;
    }

    vi_tri = TimTuyenTinh(a, n, x, so_sanh);
    cout << "Ket qua Tim Tuyen Tinh (x = " << x << "): Vi tri " << vi_tri << ", So lan so sanh: " << so_sanh << endl;

    GhiKetQuaFile("tt002.out", a, n, x, vi_tri, so_sanh);

    cout << "\n--- TIM NHI PHAN TANG ---" << endl;
    cout << "Nhap gia tri can tim x cho phuong phap TIM NHI PHAN TANG: ";
    if (!(cin >> x)) {
        cerr << "Loi nhap lieu." << endl;
        return 1;
    }

    vi_tri = TNPTang(a, n, x, so_sanh);
    cout << "Ket qua Tim Nhi Phan Tang (x = " << x << "): Vi tri " << vi_tri << ", So lan so sanh: " << so_sanh << endl;

    GhiKetQuaFile("npt002.out", a, n, x, vi_tri, so_sanh);

    return 0;
}