# 📚 Dự Án C++: Cấu Trúc Dữ Liệu và Giải Thuật

> **Giáo trình:** Cấu trúc dữ liệu và Giải thuật  
> **Ngôn ngữ:** C++17

---

## 📁 Cấu Trúc Dự Án

```
CTDL_GT/
├── include/
│   └── utils.h                        # Hàm tiện ích dùng chung
│
├── Chuong1_TongQuan/
│   └── Chuong1_TongQuan.cpp           # Kiểu DL, CTDL, BigO
│
├── Chuong2_TimKiem_SapXep/
│   └── Chuong2_TimKiem_SapXep.cpp     # 2 TK + 5 sắp xếp
│
├── Chuong3_DanhSachLienKet/
│   └── Chuong3_DanhSachLienKet.cpp    # DSLK đơn, Stack, Queue
│
├── Chuong4_CauTrucCay/
│   └── Chuong4_CauTrucCay.cpp         # Cây nhị phân, BST
│
├── BaiTapTongHop/
│   └── BaiTapTongHop.cpp              # 5 ứng dụng thực tế
│
├── Makefile
└── README.md
```

---

## 📖 Nội Dung Từng File

### Chương 1 — Tổng Quan CTDL & GT
- Kiểu dữ liệu C/C++, nguyên tắc chọn KDL
- Minh họa mối liên hệ CTDL ↔ Giải thuật (bảng điểm)
- 7 phân lớp độ phức tạp Big-O: O(K), O(log N), O(N), O(N log N), O(N²), O(N³), O(2ᴺ)
- Bài tập: tính tổng chữ số, phương trình bậc nhất

### Chương 2 — Tìm Kiếm & Sắp Xếp
| Giải thuật | Độ phức tạp | Ghi chú |
|---|---|---|
| Linear Search | O(N) | Không yêu cầu sắp xếp |
| Binary Search | O(log N) | Cần mảng đã sắp xếp |
| Selection Sort | O(N²) | Đơn giản |
| Insertion Sort | O(N²) | Tốt với mảng gần sắp xếp |
| Bubble Sort | O(N²) | Dễ hiểu |
| Quick Sort | O(N log N) | Trung bình nhanh nhất |
| Heap Sort | O(N log N) | Ổn định |

### Chương 3 — Danh Sách Liên Kết
- Con trỏ, biến động, biến con trỏ
- DSLK đơn: tạo, xuất, thêm (đầu/cuối/sau/trước)
- Xóa (đầu/cuối/bất kỳ), duyệt, sắp xếp
- Nối/Tách danh sách
- **Stack**: Push, Pop + ứng dụng kiểm tra ngoặc, đổi nhị phân
- **Queue**: Enqueue, Dequeue + ứng dụng hàng đợi in ấn

### Chương 4 — Cây Nhị Phân
- Cây nhị phân: lưu trữ bằng mảng và con trỏ
- 3 phương pháp duyệt: Pre-order (NLR), In-order (LNR), Post-order (LRN)
- Duyệt theo mức (BFS)
- **BST**: Insert, Search, Delete
- Các thao tác: chiều cao, đếm nút, tổng, nút lớn thứ k

### Bài Tập Tổng Hợp — 5 Ứng Dụng Thực Tế
1. **Quản lý sinh viên** — mảng + sắp xếp + tìm kiếm
2. **Lịch sử trình duyệt** — Stack (quay lại/tiến)
3. **Hàng chờ in ấn** — Queue (FIFO)
4. **Tính biểu thức hậu tố** — Stack (Postfix calculator)
5. **Từ điển Anh-Việt** — BST (lưu trữ + tìm kiếm)

---

## ⚙️ Biên Dịch và Chạy

### Yêu cầu
- Trình biên dịch: **g++ (C++17)** hoặc Visual Studio, Code::Blocks, Dev-C++

### Biên dịch từng file (g++)
```bash
# Tạo thư mục bin
mkdir bin

# Biên dịch từng chương
g++ -std=c++17 Chuong1_TongQuan/Chuong1_TongQuan.cpp -o bin/Chuong1
g++ -std=c++17 Chuong2_TimKiem_SapXep/Chuong2_TimKiem_SapXep.cpp -o bin/Chuong2
g++ -std=c++17 Chuong3_DanhSachLienKet/Chuong3_DanhSachLienKet.cpp -o bin/Chuong3 -lm
g++ -std=c++17 Chuong4_CauTrucCay/Chuong4_CauTrucCay.cpp -o bin/Chuong4
g++ -std=c++17 BaiTapTongHop/BaiTapTongHop.cpp -o bin/TongHop

# Chạy
./bin/Chuong1
./bin/Chuong2
./bin/Chuong3
./bin/Chuong4
./bin/TongHop
```

### Dùng Makefile
```bash
make        # Biên dịch tất cả
make clean  # Xóa file đã build
```

### Dùng IDE (Visual Studio / Code::Blocks)
1. Mở từng file `.cpp`
2. Chọn **Build & Run** (F9 hoặc F5)

---

## 📝 Ghi Chú
- Tất cả code sử dụng **tiếng Việt không dấu** trong tên hàm/biến để tránh lỗi encoding
- Mỗi file có thể biên dịch **độc lập**, không phụ thuộc nhau
- Các hàm đặt tên theo phong cách **giáo trình** (HoanVi, ThemDau, XoaCuoi, ...)
---

## 📌 Quy Trình Fork và Nộp Bài

### Huong dan nop bai DSALab

```text
1. Fork repo goc:
   https://github.com/CocAgent/DSALab

2. Clone repo fork ve may

3. Lam bai dung thu muc duoc yeu cau

4. Commit day du va dat noi dung commit ro rang

5. Push len repo GitHub ca nhan

6. Nop bai bang mot trong hai cach:
   - Tao Pull Request ve repo goc
   - Hoac gui link repo fork len he thong hoc tap

Neu nop bang Pull Request, dat tieu de theo mau:
[MSSV] - [Ho ten] - Bai tap tuan X
----
1. git clone https://github.com/nguyenvana/DSALab.git
2. cd DSALab
3. git add .
4. git commit -m "Hoan thanh bai tap tuan 1"
5. git push origin main
---
