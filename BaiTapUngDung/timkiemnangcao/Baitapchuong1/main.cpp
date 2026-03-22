

#include <iostream>
using namespace std;

// Khai báo các hàm t? các file bài t?p
int Bai1_Lop1();
int Bai2_Lop2();
int Bai3_Lop3();
int Bai4_Lop4();



int main() {
    ios::sync_with_stdio(false); // T?ng t?c I/O
    cin.tie(nullptr);

    int choice;
    do {
        // Hi?n th? menu
        cout << "\n=== MENU CHON BAI TAP ===\n";
        cout << "1. Bai1_Lop1: Do phuc tap lop 1\n";
        cout << "2. Bai2_Lop2: Do phuc tap lop 2\n";
        cout << "3. Bai3_Lop3: Do phuc tap lop 3\n";
        cout << "4. Bai4_Lop4: Do phuc tap lop 3\n";

        cout << "0. Thoat\n";
        cout << "Nhap lua chon (1-10): ";
        cin >> choice;

        // X? lý l?a ch?n
        switch (choice) {
        case 1:
            cout << "\n=== Chay Bai 1_101 ===\n";
            Bai1_Lop1();
            break;
        case 2:
            cout << "\n=== Chay Bai 1_102 ===\n";
            Bai2_Lop2();
            break;
        case 3:
            cout << "\n=== Chay Bai 3_201 ===\n";
            Bai3_Lop3();
            break;
        case 4:
            cout << "\n=== Chay Bai 4_201 ===\n";
            Bai4_Lop4();
            break;
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }
    } while (choice != 0);

    return 0;
}