#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <functional> // Cần thiết cho std::function
#include <limits>     // Cần thiết cho xử lý input cin
#include <cstring>    // Cần thiết cho strncpy/strncpy_s

// KHONG CAN #define _CRT_SECURE_NO_WARNINGS NUA
// Vì ta đã thay thế bằng localtime_s cho Windows

using namespace std;

// #1. Dinh nghia cau truc du lieu cho File
struct File
{
    string name;
    long long size; 
    time_t last_modified; 
    string extension; 
    bool is_dir; 
}; 

// Dinh nghia kieu du lieu cho ham so sanh (std::function)
using FileComparator = function<bool(const File&, const File&)>;


// #2. Dinh nghia cac Ham so sanh TANG DAN (Ascending)

// Macro kiem tra Folder: Folder luon dung truoc File
#define DIR_CHECK \
    if (a.is_dir != b.is_dir) { \
        return a.is_dir; /* Folder (a.is_dir=true) dung truoc File (b.is_dir=false) */ \
    }

// So sanh theo Ten (Tang dan)
bool compareByNameAsc(const File& a, const File& b) {
    DIR_CHECK
    // Tăng tính ổn định bằng cách so sánh toàn bộ tên
    return a.name < b.name;
}

// So sanh theo Kich thuoc (Tang dan)
bool compareBySizeAsc(const File& a, const File& b) {
    DIR_CHECK
    if (a.size != b.size) {
        return a.size < b.size;
    }
    // Nếu kích thước bằng nhau, dùng Tên để ổn định thứ tự
    return a.name < b.name;
}

// So sanh theo Ngay sua doi (Tang dan - tu cu nhat den moi nhat)
bool compareByDateAsc(const File& a, const File& b) {
    DIR_CHECK
    if (a.last_modified != b.last_modified) {
        return a.last_modified < b.last_modified;
    }
    // Nếu Ngày sửa đổi bằng nhau, dùng Tên để ổn định thứ tự
    return a.name < b.name;
}

// So sanh theo Loai file (Tang dan)
bool compareByTypeAsc(const File& a, const File& b) {
    DIR_CHECK
    if (a.extension != b.extension) {
        return a.extension < b.extension;
    }
    // Nếu Extension giong nhau, dùng Tên để ổn định thứ tự
    return a.name < b.name; 
}
#undef DIR_CHECK


// #3. Ham tien ich: Dinh dang kich thuoc
string formatSize(long long size) {
    if (size == 0) return "DIR";
    if (size < 1024) return to_string(size) + " B";
    if (size < 1024 * 1024) return to_string(size / 1024) + " KB";
    
    stringstream ss;
    if (size < 1024 * 1024 * 1024) {
        ss << fixed << setprecision(2) << (double)size / (1024 * 1024) << " MB";
    } else {
        ss << fixed << setprecision(2) << (double)size / (1024 * 1024 * 1024) << " GB";
    }
    return ss.str();
}

// #4. Ham tien ich: In danh sach file (GIAI PHAP TRIET DE CHO C4996)
void printFiles(const vector<File>& files) {
    cout << "\n---------------------------------------------------------------\n";
    cout << setw(30) << left << "Ten File"
         << setw(10) << left << "Loai"
         << setw(10) << right << "Kich thuoc"
         << setw(25) << right << "Ngay sua doi"
         << endl;
    cout << "---------------------------------------------------------------\n";

    for (const auto& file : files) {
        string dir_marker = file.is_dir ? "[DIR] " : "";
        
        char date_str[100];
        struct tm timeinfo;
        
        // Su dung localtime_s cho Windows de tranh C4996
        #ifdef _WIN32
            // localtime_s tra ve error code (0 neu thanh cong)
            if (localtime_s(&timeinfo, &file.last_modified) != 0) {
                 strncpy_s(date_str, 100, "---Loi thoi gian---", 100);
            }
            else {
                 strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S", &timeinfo);
            }
        // Su dung localtime chuan cho cac he dieu hanh khac
        #else 
            struct tm* tm_ptr = localtime(&file.last_modified);
            if (tm_ptr == nullptr) {
                // strncpy la ham chuan C
                strncpy(date_str, "---Loi thoi gian---", 100);
            } else {
                timeinfo = *tm_ptr;
                strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S", &timeinfo);
            }
        #endif


        cout << setw(30) << left << (dir_marker + file.name)
             << setw(10) << left << file.extension
             << setw(10) << right << formatSize(file.size)
             << setw(25) << right << date_str
             << endl;
    }
    cout << "---------------------------------------------------------------\n";
}

// #5. Ham chinh: Tao du lieu va xu ly lua chon ngu dung
int main() {
    // Tao du lieu mau
    vector<File> files = {
        {"ProjectReport", 12000000, time(0) - 86400 * 5, ".pdf", false},
        {"vacation_photo", 3500000, time(0) - 86400 * 2, ".jpg", false},
        {"CodeBase", 0, time(0) - 86400 * 10, "", true}, 
        {"setup.py", 1250, time(0) - 3600 * 4, ".py", false},
        {"README", 5600, time(0) - 3600 * 2, ".md", false},
        {"document_A", 85000, time(0) - 86400 * 7, ".docx", false},
        {"data_01", 1024*1024*5, time(0) - 86400 * 1, ".bin", false},
        {"logs", 0, time(0) - 3600 * 1, "", true}, 
        {"config", 150, time(0) - 3600 * 5, ".ini", false},
        {"main_data", 5000000000LL, time(0), ".dat", false} 
    };

    int tieu_chi;
    int thu_tu;

    do {
        cout << "\nCHON TIEU CHI SAP XEP:\n";
        cout << "1. Sort by Name\n";
        cout << "2. Sort by Date modified\n";
        cout << "3. Sort by Size\n";
        cout << "4. Sort by Type\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";

        // Xử lý lỗi nhập liệu (non-numeric input)
        if (!(cin >> tieu_chi)) { 
             cout << "Loi nhap lieu. Vui long nhap so.\n";
             cin.clear(); 
             cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             tieu_chi = -1; 
             continue;
        }

        if (tieu_chi == 0) break;
        if (tieu_chi < 1 || tieu_chi > 4) {
            cout << "Lua chon tieu chi khong hop le.\n";
            continue;
        }

        cout << "\nCHON THU TU SAP XEP:\n";
        cout << "1. Tang dan (Ascending)\n";
        cout << "2. Giam dan (Descending)\n";
        cout << "Lua chon: ";
        
        if (!(cin >> thu_tu)) {
             cout << "Loi nhap lieu. Vui long nhap so.\n";
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             continue;
        }

        if (thu_tu < 1 || thu_tu > 2) {
            cout << "Thu tu sap xep khong hop le.\n";
            continue;
        }
        
        // Khai báo std::function (Khắc phục lỗi E0020 'function' undeclared)
        FileComparator comparator;

        // Buoc 1: Chon ham so sanh TANG DAN (default)
        switch (tieu_chi) {
            case 1: comparator = compareByNameAsc; break;
            case 2: comparator = compareByDateAsc; break;
            case 3: comparator = compareBySizeAsc; break;
            case 4: comparator = compareByTypeAsc; break;
        }

        // Buoc 2: Xu ly truong hop GIAM DAN (Descending)
        if (thu_tu == 2) {
            // Lambda function [comparator] khắc phục lỗi C3481 'comparator' lambda capture not found
            auto desc_comparator = [comparator](const File& a, const File& b) {
                return comparator(b, a); // Đảo ngược thứ tự
            };
            sort(files.begin(), files.end(), desc_comparator);
            cout << "\nKet qua sap xep (Giam dan):\n";
        } else {
            sort(files.begin(), files.end(), comparator);
            cout << "\nKet qua sap xep (Tang dan):\n";
        }

        // Buoc 3: In ket qua
        printFiles(files);

    } while (tieu_chi != 0);

    return 0;
}