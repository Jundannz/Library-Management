````markdown
# 📚 Program Manajemen Perpustakaan C++

Program Manajemen Perpustakaan berbasis C++ ini dibuat untuk mengelola data buku secara terstruktur menggunakan **array**, **struct**, serta algoritma **sorting** dan **searching**. Project ini merupakan implementasi konsep dasar struktur data dalam pengelolaan perpustakaan sederhana.

---

## ✨ Fitur Utama
- Menambahkan data buku baru
- Menampilkan seluruh koleksi buku
- Mengurutkan buku berdasarkan **ID** atau **Judul** (Bubble Sort)
- Mencari buku menggunakan **Binary Search** atau **Sequential Search**
- Peminjaman dan pengembalian buku
- Perhitungan denda keterlambatan otomatis
- Reservasi buku jika sedang dipinjam
- Penentuan rak penyimpanan berdasarkan huruf awal judul

---

## 📌 Struktur Data yang Digunakan
- `struct Buku` — menyimpan atribut buku (ID, Judul, Penulis, Tahun Terbit, Status pinjam)
- `struct Reservasi` — menyimpan antrean reservasi
- Array statis untuk rak buku `rak1`–`rak5`

---

## 📁 Pembagian Rak Buku
| Rak | Range Judul |
|------|------------|
| Rak 1 | A – F |
| Rak 2 | G – L |
| Rak 3 | M – S |
| Rak 4 | T – Z |
| Rak 5 | Non-alfabet (angka/simbol) |

---

## 🧠 Teknologi & Algoritma
| Kategori | Implementasi |
|---------|-------------|
| Sorting | Bubble Sort |
| Searching | Binary Search & Sequential Search |
| Penyimpanan | Array statis |

---

## 🖥️ Cara Menjalankan Program
### Compile
```bash
g++ main.cpp -o perpustakaan
````

### Jalankan

```bash
./perpustakaan
```

---

## 📍 Menu Utama

```
=== Menu Perpustakaan ===
1. Tambah Buku
2. Tampilkan Buku
3. Urutkan Item
4. Cari Buku
5. Pinjam Buku
6. Kembalikan Buku
7. Reservasi Buku
0. Keluar
```

---

## 🚀 Pengembangan Ke Depan

* Penyimpanan data ke file `.txt` / `.json`
* Penggunaan `vector` agar kapasitas dinamis
* Penambahan sistem login admin & user
* Implementasi GUI berbasis Qt atau web

---

## 👤 Dibuat oleh

*1. Jundan Saiful Haq (25/560768/PA/23633)*
*2. Sanjia Tirta Arraya (25/560949/PA/23645)*
*3. Naufal Abiyan Rizqullah Mashar (25/564266/PA/23753)*
*4. Ainun Nuriah (25/559746/PA/23559)*
---

```

