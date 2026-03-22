#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_N 1000 

// ----------------------------------------------------
// I. HAM HO TRO
// ----------------------------------------------------

void DocFile4(const char tenfile[], int a[], int& n) {
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

void XuatMang4(const int a[], int n) {
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

// ----------------------------------------------------
// II. HAM KIEM TRA THU TU
// ----------------------------------------------------

int KiemTraTang(const int a[], int n) {
    if (n <= 1) return 1;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            return -1;
        }
    }
    return 1;
}

int KiemTraGiam(const int a[], int n) {
    if (n <= 1) return 1;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] < a[i + 1]) {
            return -1;
        }
    }
    return 1;
}

// ----------------------------------------------------
// III. HAM TIM KIEM CO DEM SS
// ----------------------------------------------------

int TimTuyenTinh4(const int a[], int n, int x, long long& ss) {
    ss = 0;
    for (int i = 0; i < n; ++i) {
        ss++;
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}

int TNPTang4(const int a[], int n, int x, long long& ss) {
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

int TNPGiam(const int a[], int n, int x, long long& ss) {
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
        if (a[mid] > x) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// ----------------------------------------------------
// IV. HAM GHI KET QUA
// ----------------------------------------------------

void GhiKetQuaFile(const char tenfile[], const string& phuong_phap, int x, int vi_tri, long long ss) {
    ofstream fileout(tenfile);
    if (!fileout.is_open()) {
        cerr << "Loi: Khong the mo tap tin " << tenfile << " de ghi." << endl;
        return;
    }

    fileout << phuong_phap << endl;

    fileout << x << "\t" << vi_tri << "\t" << ss << endl;

    fileout.close();
    cout << "Ghi ket qua tim kiem vao tap tin **" << tenfile << "** thanh cong." << endl;
}

// ----------------------------------------------------
// V. HAM CHINH MAIN LOGIC
// ----------------------------------------------------

void RunTestCase(const char* input_file, const char* tt_output, const char* npt_output, const char* npg_output) {
    int a[MAX_N];
    int n, x;
    int vi_tri;
    long long so_sanh = 0;
    string phuong_phap;
    string output_file;

    cout << "\n==================================================" << endl;
    cout << "BAT DAU XU LY FILE: " << input_file << endl;

    DocFile4(input_file, a, n);
    if (n <= 0) return;

    XuatMang4(a, n);

    cout << "Nhap gia tri can tim x: ";
    if (!(cin >> x)) {
        cerr << "Loi nhap lieu." << endl;
        return;
    }

    int check_tang = KiemTraTang(a, n);
    int check_giam = KiemTraGiam(a, n);

    if (check_tang == 1) {
        vi_tri = TNPTang4(a, n, x, so_sanh);
        phuong_phap = "Tim Nhi Phan Tang";
        output_file = npt_output;

    }
    else if (check_giam == 1) {
        vi_tri = TNPGiam(a, n, x, so_sanh);
        phuong_phap = "Tim Nhi Phan Giam";
        output_file = npg_output;

    }
    else {
        vi_tri = TimTuyenTinh4(a, n, x, so_sanh);
        phuong_phap = "Tim Tuyen Tinh";
        output_file = tt_output;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "Phuong phap da chon: **" << phuong_phap << "**" << endl;
    cout << "Ket qua (x = " << x << "): Vi tri " << vi_tri << ", So lan so sanh: " << so_sanh << endl;

    GhiKetQuaFile(output_file.c_str(), phuong_phap, x, vi_tri, so_sanh);
    cout << "==================================================" << endl;
}

int Bai4_Lop4() {
    RunTestCase("data003.in", "tt003.out", "npt003.out", "npg003.out");
    RunTestCase("data004.in", "tt004.out", "npt004.out", "npg004.out");

    return 0;
}