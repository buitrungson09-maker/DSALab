#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdio> // Can thiet cho remove()

using namespace std;

#define MAX_N 1000

// ----------------------------------------------------
// I. CAC HAM HO TRO VA TIM KIEM SO (Giu nguyen)
// ----------------------------------------------------

void DocFile(const char tenfile[], int a[], int& n) {
    ifstream filein(tenfile);
    if (!filein.is_open()) {
        // cerr << "Loi: Khong the mo tap tin " << tenfile << " de doc." << endl;
        n = 0;
        return;
    }
    // Doc so phan tu n
    if (!(filein >> n)) { /* cerr << "Loi: Khong doc duoc so phan tu n." << endl; */ n = 0; filein.close(); return; }
    if (n > MAX_N) { /* cerr << "Canh bao: n (" << n << ") lon hon gioi han." << endl; */ n = 0; filein.close(); return; }
    // Doc cac phan tu so
    for (int i = 0; i < n; ++i) {
        if (!(filein >> a[i])) { /* cerr << "Loi: Khong doc du so phan tu." << endl; */ n = i; filein.close(); return; }
    }
    filein.close();
}

int TimTuyenTinh(const int a[], int n, int x) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == x) return i;
        // Luu y: Dieu kien thoat som nay chi dung khi mang da duoc sap xep tang dan.
        // if (a[i] > x) return -1; 
    }
    return -1;
}

int TNPTang(const int a[], int n, int x) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == x) return mid;
        else if (a[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

string TrichSoTuTenFile(const string& tenfile_in) {
    size_t end = tenfile_in.find_last_of(".");
    string base_name = tenfile_in.substr(0, end);
    if (base_name.rfind("data", 0) == 0 && base_name.length() > 4) {
        return base_name.substr(4);
    }
    return base_name;
}

void GhiKetQuaFile_So(const string& tenfile_out, const int a[], int n, int x, int vi_tri) {
    ofstream fileout(tenfile_out);
    if (!fileout.is_open()) return;

    // Dong 1: Ghi mang a (neu co)
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            fileout << a[i] << (i < n - 1 ? "\t" : "");
        }
        fileout << endl;
    }

    // Dong 2: Ghi x va vi tri
    fileout << x << "\t" << vi_tri << endl;
    fileout.close();
}


// ----------------------------------------------------
// II. HAM TIM KIEM CHUOI KY TU (Tính năng mới)
// ----------------------------------------------------

// Tra ve vector cac so dong (index bat dau tu 1) chua chuoi tim kiem
vector<int> TimChuoiTrongFile(const string& tenfile, const string& chuoi_tim) {
    vector<int> vi_tri_dong;
    if (chuoi_tim.empty()) return vi_tri_dong;

    ifstream filein(tenfile);
    if (!filein.is_open()) return vi_tri_dong;

    string line;
    int so_dong = 0;

    // Doc tung dong trong file
    while (getline(filein, line)) {
        so_dong++;
        // Kiem tra xem chuoi tim kiem co trong dong hien tai khong
        if (line.find(chuoi_tim) != string::npos) {
            vi_tri_dong.push_back(so_dong);
        }
    }

    filein.close();
    return vi_tri_dong;
}

void GhiKetQuaFile_Chuoi(const string& tenfile_out, const string& chuoi_tim, const vector<int>& vi_tri_dong) {
    ofstream fileout(tenfile_out);
    if (!fileout.is_open()) return;

    // Dong 1: Ghi chuoi can tim
    fileout << "Chuoi can tim: " << chuoi_tim << endl;

    // Dong 2: Ghi so dong tim thay
    fileout << "So dong tim thay: " << vi_tri_dong.size() << endl;

    // Cac dong tiep theo: Ghi cac so dong tim thay (cach nhau boi dau phay)
    fileout << "Cac dong: ";
    if (!vi_tri_dong.empty()) {
        for (size_t i = 0; i < vi_tri_dong.size(); ++i) {
            fileout << vi_tri_dong[i] << (i < vi_tri_dong.size() - 1 ? ", " : "");
        }
    }
    else {
        fileout << "Khong tim thay";
    }
    fileout << endl;

    fileout.close();
}

// ----------------------------------------------------
// III. LOGIC XU LY NHIEU FILE TU DONG (Cập nhật)
// ----------------------------------------------------

void ThucHienTimKiemTuDong(const string& input_file_path, int x_tt, int x_npt, const string& chuoi_tim) {
    int a[MAX_N];
    int n;
    int vi_tri_tt, vi_tri_npt;
    vector<int> vi_tri_chuoi;

    // Kiem tra su ton tai cua file
    ifstream test_file(input_file_path);
    if (!test_file.is_open()) {
        return;
    }
    test_file.close();

    // 1. Doc file (Chi doc so vi chi dung cho tim so)
    DocFile(input_file_path.c_str(), a, n);

    // 2. Tao ten file output
    string file_num = TrichSoTuTenFile(input_file_path);
    string tt_out_name = "tt" + file_num + ".out";
    string npt_out_name = "npt" + file_num + ".out";
    string chuoi_out_name = "str" + file_num + ".out"; // Ten file moi cho tim chuoi

    // --- TIM TUYEN TINH (SO) ---
    if (n > 0) {
        vi_tri_tt = TimTuyenTinh(a, n, x_tt);
        GhiKetQuaFile_So(tt_out_name, a, n, x_tt, vi_tri_tt);
    }
    else {
        // Neu khong doc duoc so, xoa file tt*.out (neu co) de tranh tao file trong
        remove(tt_out_name.c_str());
    }

    // --- TIM NHI PHAN TANG (SO) ---
    if (n > 0) {
        vi_tri_npt = TNPTang(a, n, x_npt);
        GhiKetQuaFile_So(npt_out_name, a, n, x_npt, vi_tri_npt);
    }
    else {
        remove(npt_out_name.c_str());
    }

    // --- TIM CHUOI KY TU (Tinh nang moi) ---
    if (!chuoi_tim.empty()) {
        vi_tri_chuoi = TimChuoiTrongFile(input_file_path, chuoi_tim);
        GhiKetQuaFile_Chuoi(chuoi_out_name, chuoi_tim, vi_tri_chuoi);
    }

    // Thong bao ket qua tim thay (Chi in ra khi co ket qua)
    if (vi_tri_tt != -1 || vi_tri_npt != -1 || !vi_tri_chuoi.empty()) {
        cout << "Ket qua tim thay tren file: " << input_file_path
            << " (TT: " << vi_tri_tt << ", NPT: " << vi_tri_npt
            << ", Chuoi: " << vi_tri_chuoi.size() << " dong)" << endl;
    }
}


int Bai2_Lop2() {
    int max_files;
    int x_tt_tim, x_npt_tim;
    string chuoi_tim_str;
    string exts_input;
    vector<string> extensions;

    cout << "NHAP SO LUONG FILE MAX (N) can xu ly (VD: 1000): ";
    if (!(cin >> max_files) || max_files <= 0) {
        cerr << "Loi nhap lieu so luong file." << endl;
        return 1;
    }

    cout << "NHAP CAC DUOI FILE muon quet (cach nhau boi dau phay, VD: in,txt,csv): ";
    cin >> exts_input;
    cin.ignore(10000, '\n');

    // Tach cac duoi file
    stringstream ss(exts_input);
    string ext;
    while (getline(ss, ext, ',')) {
        if (!ext.empty()) {
            extensions.push_back("." + ext);
        }
    }

    if (extensions.empty()) {
        cerr << "Khong co duoi file nao duoc nhap hop le." << endl;
        return 1;
    }

    cout << "\n--- TIM KIEM SO NGUYEN ---" << endl;
    cout << "NHAP GIA TRI X CAN TIM cho TT: ";
    if (!(cin >> x_tt_tim)) return 1;

    cout << "NHAP GIA TRI X CAN TIM cho NPT: ";
    if (!(cin >> x_npt_tim)) return 1;
    cin.ignore(10000, '\n'); // Xoa bo dem sau khi nhap so

    cout << "\n--- TIM KIEM CHUOI KY TU ---" << endl;
    cout << "NHAP CHUOI/KY TU CAN TIM (de trong de bo qua): ";
    getline(cin, chuoi_tim_str);

    cout << "\n--- BAT DAU XU LY TU DONG " << max_files << " FILE ---" << endl;

    // Vong lap tu i=1 den max_files
    for (int i = 1; i <= max_files; ++i) {
        stringstream name_ss;
        name_ss << "data" << setfill('0') << setw(3) << i;
        string base_name = name_ss.str();

        // Thu lan luot voi tung duoi file da nhap
        for (const string& current_ext : extensions) {
            string input_file_name = base_name + current_ext; // VD: data001.in
            ThucHienTimKiemTuDong(input_file_name, x_tt_tim, x_npt_tim, chuoi_tim_str);
        }
    }

    cout << "\nQUA TRINH XU LY TREN " << max_files << " TAP HOP FILE DA HOAN TAT." << endl;
    return 0;
}