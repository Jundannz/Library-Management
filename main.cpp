#include <iostream>
using namespace std;

struct Buku{
    int id;
    string judul;
    string penulis;
    int tahunTerbit;
    bool dipinjam = false;
};

//variabel global rak buku
Buku rak1[100] = {}; // simpan buku dari alfabet A-F
Buku rak2[100] = {}; // G - L
Buku rak3[100] = {}; // M - S
Buku rak4[100] = {}; // T - Z
Buku rak5[250] = {}; // menampung buku dengan judul non-latin alfabet

// fitur reservasi (menggunakan array, bukan vector)
struct Reservasi {
    string nama;
    string judul;
};
Reservasi daftarReservasi[100] = {};
int jumlahReservasi = 0;

void tentukanRak(Buku varBuku) {
    // tentukan rak berdasarkan alfabet
    if(varBuku.judul.empty()) return;
    char c = varBuku.judul[0];
    if(c >= 'A' && c <= 'F'){
        for(int i = 0; i < 100; i++) {
            if(rak1[i].judul == "") {
                rak1[i] = varBuku;
                return;
            }
        }
        cout << "Rak 1 penuh!!\n";
    } else if(c >= 'G' && c <= 'L') {
        for(int i = 0; i < 100; i++) {
            if(rak2[i].judul == "") {
                rak2[i] = varBuku;
                return;
            }
        }
        cout << "Rak 2 penuh!!\n";
    } else if(c >= 'M' && c <= 'S') {
        for(int i = 0; i < 100; i++) {
            if(rak3[i].judul == "") {
                rak3[i] = varBuku;
                return;
            }
        }
        cout << "Rak 3 penuh!!\n";
    } else if(c >= 'T' && c <= 'Z') {
        for(int i = 0; i < 100; i++) {
            if(rak4[i].judul == "") {
                rak4[i] = varBuku;
                return;
            }
        }
        cout << "Rak 4 penuh!!\n";
    } else {
        for(int i = 0; i < 250; i++) {
            if(rak5[i].judul == "") {
                rak5[i] = varBuku;
                return;
            }
        }
        cout << "Rak 5 penuh!!\n";
    }
}

// cari lokasi buku di rak-rak berdasarkan id (atau judul jika id tidak tersedia)
string cariLokasi(const Buku &varBuku) {
    for(int i = 0; i < 100; i++){
        if(rak1[i].judul != "" && rak1[i].id == varBuku.id) return string("Rak 1, posisi ") + to_string(i);
        if(rak2[i].judul != "" && rak2[i].id == varBuku.id) return string("Rak 2, posisi ") + to_string(i);
        if(rak3[i].judul != "" && rak3[i].id == varBuku.id) return string("Rak 3, posisi ") + to_string(i);
        if(rak4[i].judul != "" && rak4[i].id == varBuku.id) return string("Rak 4, posisi ") + to_string(i);
    }
    for(int i = 0; i < 250; i++){
        if(rak5[i].judul != "" && rak5[i].id == varBuku.id) return string("Rak 5, posisi ") + to_string(i);
    }
    // fallback: try to deduce by first letter of title
    if(!varBuku.judul.empty()){
        char c = varBuku.judul[0];
        if(c >= 'A' && c <= 'F') return "Rak 1 (posisi tidak diketahui)";
        if(c >= 'G' && c <= 'L') return "Rak 2 (posisi tidak diketahui)";
        if(c >= 'M' && c <= 'S') return "Rak 3 (posisi tidak diketahui)";
        if(c >= 'T' && c <= 'Z') return "Rak 4 (posisi tidak diketahui)";
    }
    return "Lokasi tidak diketahui";
}

// fitur reservasi (fungsi)
void reservasiBuku(Buku buku[], int jumlahBuku) {
    if (jumlahBuku == 0) {
        cout << "Tidak ada buku dalam perpustakaan." << "\n";
        return;
    }

    string judul, nama;
    cout << "Masukkan judul buku yang ingin direservasi: ";
    cin.ignore();
    getline(cin, judul);

    // ubah ke uppercase agar konsisten dengan penyimpanan
    for (size_t k = 0; k < judul.length(); k++) {
        if (judul[k] >= 'a' && judul[k] <= 'z') judul[k] = judul[k] + ('A' - 'a');
    }

    bool ditemukan = false;
    for (int i = 0; i < jumlahBuku; i++) {
        if (buku[i].judul == judul) {
            ditemukan = true;
            if (buku[i].dipinjam) {
                cout << "Buku sedang dipinjam. Masukkan nama Anda untuk reservasi: ";
                getline(cin, nama);
                if (jumlahReservasi < 100) {
                    daftarReservasi[jumlahReservasi].nama = nama;
                    daftarReservasi[jumlahReservasi].judul = judul;
                    jumlahReservasi++;
                    cout << "Reservasi berhasil! Anda akan diberi prioritas saat buku kembali." << "\n";
                } else {
                    cout << "Daftar reservasi penuh. Tidak dapat menambah reservasi." << "\n";
                }
            } else {
                cout << "Buku sedang tersedia, tidak perlu reservasi." << "\n";
            }
            break;
        }
    }

    if (!ditemukan) cout << "Buku tidak ditemukan." << "\n";
}

void cekReservasiSaatKembali(string judul) {
    for (int i = 0; i < jumlahReservasi; i++) {
        if (daftarReservasi[i].judul == judul) {
            cout << "\nBuku ini memiliki reservasi!" << "\n";
            cout << "Prioritas peminjam berikut: " << daftarReservasi[i].nama << "\n";
            // hapus entry dengan menggeser sisa array
            for (int j = i; j < jumlahReservasi - 1; j++) {
                daftarReservasi[j] = daftarReservasi[j+1];
            }
            jumlahReservasi--;
            return;
        }
    }
}

//display menu
void tampilanMenu(){
    cout << "=== Menu Perpustakaan ===" << '\n';
    cout << "1. Tambah Buku" << '\n';
    cout << "2. Tampilan buku" << '\n';
    cout << "3. Urutkan Item" << '\n';
    cout << "4. Cari Buku" << '\n';
    cout << "5. Pinjam Buku" << '\n';
    cout << "6. Kembalikan Buku" << '\n';
    cout << "7. Reservasi Buku" << '\n';
    cout << "0. Keluar" << '\n';
    cout << "Pilih menu: ";
}

//fungsi untuk menambah buku
void tambahBuku(Buku buku[], int &jumlahBuku){
    int n;
    int panjangBuku;
    cout << "Masukkan jumlah buku yang akan ditambahkan: ";
    cin >> n;
    for(int i = 0; i<n; i++){
        cout << "Masukkan ID Buku: ";
        cin >> buku[jumlahBuku].id;
        cout << "Masukkan Judul Buku: ";
        cin.ignore();
        getline(cin, buku[jumlahBuku].judul);
        //ganti semua karakter menjadi uppercase
        panjangBuku = buku[jumlahBuku].judul.length();
        for(int i = 0; i<panjangBuku; i++){
            if(buku[jumlahBuku].judul[i] >= 'a' && buku[jumlahBuku].judul[i] <= 'z'){
                buku[jumlahBuku].judul[i] = buku[jumlahBuku].judul[i] + ('A' - 'a');
            }
        }
        cout << "Masukkan Penulis Buku: ";
        getline(cin, buku[jumlahBuku].penulis);
        cout << "Masukkan Tahun Terbit: ";
        cin >> buku[jumlahBuku].tahunTerbit;
        jumlahBuku++;
        // tentukan rak setelah menambah ke array utama
        tentukanRak(buku[jumlahBuku-1]);
        cout << "Buku berhasil ditambahkan!" << '\n';
    }
}

void sortingById(Buku buku[], int jumlahBuku){
    for(int i = 0; i<jumlahBuku-1; i++){
        for(int j = 0; j < jumlahBuku - i - 1; j++){
            if(buku[j].id > buku[j+1].id){
                Buku temp = buku[j];
                buku[j] = buku[j+1];
                buku[j+1] = temp;
            }
        }
    }
}

void sortingByJudul(Buku buku[], int jumlahBuku){
    for(int i = 0; i<jumlahBuku-1; i++){
        for(int j = 0; j < jumlahBuku - i - 1; j++){
            if(buku[j].judul > buku[j+1].judul){
                Buku temp = buku[j];
                buku[j] = buku[j+1];
                buku[j+1] = temp;
            }
        }
    }
}
void displayAllBuku(Buku buku[], int jumlahBuku){
    cout << "=== Daftar Buku ===" << '\n';
    for(int i = 0; i<jumlahBuku; i++){
        cout << "ID: " << buku[i].id << '\n';
        cout << "Judul: " << buku[i].judul << '\n';
        cout << "Penulis: " << buku[i].penulis << '\n';
        cout << "Tahun Terbit: " << buku[i].tahunTerbit << '\n';
        cout << "------------------------" << '\n';
        cout << "Status: " << (buku[i].dipinjam ? "Dipinjam" : "Tersedia") << '\n';
        cout << "-----------------------------\n";
    }
}
void selectSort(Buku buku[], int jumlahBuku){
    int pilihanSearch;
    cout << "Search by id(1) atau by judul(2): ";
    cin >> pilihanSearch;
    if(pilihanSearch == 1){
        sortingById(buku, jumlahBuku);
        displayAllBuku(buku, jumlahBuku);
    }
    else if(pilihanSearch == 2){
        sortingByJudul(buku, jumlahBuku);
        displayAllBuku(buku, jumlahBuku);
    }
}

//Update searching funct
int binarySearch(Buku buku[], int jumlahBuku, int targetId, string targetJudul, int pilihanSearch){
    int left = 0;
    int right = jumlahBuku - 1;
    if(pilihanSearch == 1){
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(buku[mid].id == targetId){
                return mid;
            }
            else if(buku[mid].id < targetId){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
    }
    else if(pilihanSearch == 2){
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(buku[mid].judul == targetJudul){
                return mid;
            }
            else if(buku[mid].judul < targetJudul){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
    }
    return -1;
}

int sequencialSearch(Buku buku[], int jumlahBuku, int targetId, string targetJudul, int pilihanSearch){
    if(pilihanSearch == 1){
        for(int i = 0; i<jumlahBuku; i++){
            if(buku[i].id == targetId){
                return i;
            }
        }
    }
    else if(pilihanSearch == 2){
        for(int i = 0; i<jumlahBuku; i++){
            if(buku[i].judul == targetJudul){
                return i;
            }
        }
    }
    return -1;
}
void searchSelect(Buku buku[], int jumlahBuku, int targetId, string targetJudul, int pilihanSearch){
    int pilihanBuku = 0;
    cout << "=== Menu Pencarian Buku ===" << "\n\n";
    cout << "NOTE: Sebelum melakukan pencarian berdasarkan ID, pastikan data sudah diurutkan berdasarkan ID menggunakan opsi 'Urutkan Item'." << '\n';
    cout << "Dan juga untuk pencarian berdasarkan Judul, pastikan data sudah diurutkan berdasarkan Judul menggunakan opsi 'Urutkan Item'." << '\n';
    cout << "\nSearch by id(1) atau by judul(2): ";
    cin >> pilihanBuku;
    if(pilihanBuku == 1){
        cout << "Masukkan metode pencarian: Binary Search(1) atau Sequencial Search(2): ";
        cin >> pilihanSearch;
        if(pilihanSearch == 1){
            cout << "Masukkan ID buku yang dicari: ";
            cin >> targetId;
            int result = binarySearch(buku, jumlahBuku, targetId, targetJudul, pilihanBuku);
            if(result != -1){
                cout << "Buku dengan id " << targetId << " ditemukan pada index ke-" << result << '\n';
                for(int i = 0; i<jumlahBuku; i++){
                    if(buku[i].id == targetId){
                        cout << "ID: " << buku[i].id << '\n';
                        cout << "Judul: " << buku[i].judul << '\n';
                        cout << "Penulis: " << buku[i].penulis << '\n';
                        cout << "Tahun Terbit: " << buku[i].tahunTerbit << '\n';
                        cout << "Status: " << (buku[i].dipinjam ? "Dipinjam" : "Tersedia") << '\n';
                        cout << "Buku ini berada di rak: " << cariLokasi(buku[i]) << '\n';
                        cout << "------------------------" << '\n';
                    }
                }
            }
            else{
                cout << "Buku dengan id " << targetId << " tidak ditemukan." << '\n';
            }
        }
        else if(pilihanSearch == 2){
            cout << "Masukkan ID buku yang dicari: ";
            cin >> targetId;
            int result = sequencialSearch(buku, jumlahBuku, targetId, targetJudul, pilihanBuku);
            if(result != -1){
                cout << "Buku dengan id " << targetId << " ditemukan pada index ke-" << result << '\n';
                // tampilkan detail dan lokasi
                cout << "ID: " << buku[result].id << '\n';
                cout << "Judul: " << buku[result].judul << '\n';
                cout << "Penulis: " << buku[result].penulis << '\n';
                cout << "Tahun Terbit: " << buku[result].tahunTerbit << '\n';
                cout << "Status: " << (buku[result].dipinjam ? "Dipinjam" : "Tersedia") << '\n';
                cout << "Buku ini berada di rak: " << cariLokasi(buku[result]) << '\n';
            }
            else{
                cout << "Buku dengan id " << targetId << " tidak ditemukan." << '\n';
            }
        }
    }
    else if(pilihanBuku == 2){
        cout << "Masukkan metode pencarian: Binary Search(1) atau Sequencial Search(2): ";
        cin >> pilihanSearch;
        if(pilihanSearch == 1){
            cout << "Masukkan judul buku yang dicari: ";
            cin.ignore();
            getline(cin, targetJudul);
            // ubah ke uppercase untuk matching
            for (size_t k = 0; k < targetJudul.length(); k++) {
                if (targetJudul[k] >= 'a' && targetJudul[k] <= 'z') targetJudul[k] = targetJudul[k] + ('A' - 'a');
            }
            int result = binarySearch(buku, jumlahBuku, targetId, targetJudul, pilihanBuku);
            if(result != -1){
                cout << "Buku dengan judul " << targetJudul << " ditemukan pada index ke-" << result << '\n';
                cout << "ID: " << buku[result].id << '\n';
                cout << "Judul: " << buku[result].judul << '\n';
                cout << "Penulis: " << buku[result].penulis << '\n';
                cout << "Tahun Terbit: " << buku[result].tahunTerbit << '\n';
                cout << "Status: " << (buku[result].dipinjam ? "Dipinjam" : "Tersedia") << '\n';
                cout << "Buku ini berada di rak: " << cariLokasi(buku[result]) << '\n';
                cout << "------------------------" << '\n';
            }
            else{
                cout << "Buku dengan judul " << targetJudul << " tidak ditemukan." << '\n';
            }
        }
        else if(pilihanSearch == 2){
            cout << "Masukkan judul buku yang dicari: ";
            cin.ignore();
            getline(cin, targetJudul);
            // ubah ke uppercase untuk matching
            for (size_t k = 0; k < targetJudul.length(); k++) {
                if (targetJudul[k] >= 'a' && targetJudul[k] <= 'z') targetJudul[k] = targetJudul[k] + ('A' - 'a');
            }
            int result = sequencialSearch(buku, jumlahBuku, targetId, targetJudul, pilihanBuku);
            if(result != -1){
                cout << "Buku dengan judul " << targetJudul << " ditemukan pada index ke-" << result << '\n';
                cout << "ID: " << buku[result].id << '\n';
                cout << "Judul: " << buku[result].judul << '\n';
                cout << "Penulis: " << buku[result].penulis << '\n';
                cout << "Tahun Terbit: " << buku[result].tahunTerbit << '\n';
                cout << "Status: " << (buku[result].dipinjam ? "Dipinjam" : "Tersedia") << '\n';
                cout << "Buku ini berada di rak: " << cariLokasi(buku[result]) << '\n';
            }
            else{
                cout << "Buku dengan judul " << targetJudul << " tidak ditemukan." << '\n';
            }
        }
    }
}

void pinjamBuku(Buku buku[], int jumlahBuku) {
    sortingById(buku, jumlahBuku);
    displayAllBuku(buku, jumlahBuku);
    int id;
    cout << "Batas pinjam buku adalah 7 hari. Denda sebesar Rp 2000 per hari akan dikenakan jika terlambat mengembalikan.\n";
    cout << "Masukkan ID buku yang ingin dipinjam: ";
    cin >> id;

    for (int i = 0; i < jumlahBuku; i++) {
        if (buku[i].id == id) {
            if (buku[i].dipinjam) {
                cout << "Buku sudah dipinjam.\n";
            } else {
                buku[i].dipinjam = true;
                cout << "Buku berhasil dipinjam.\n";
            }
            return;
        }
    }
    cout << "Buku tidak ditemukan.\n";
}
int hitungDenda() {
    int hariTerlambat;
    cout << "Masukkan jumlah hari keterlambatan pengembalian: ";
    cin >> hariTerlambat;
    const int DENDA_PER_HARI = 2000;
    return hariTerlambat * DENDA_PER_HARI;
}

void returnBuku(Buku buku[], int jumlahBuku) {
    int id;
    cout << "Masukkan ID buku yang ingin dikembalikan: ";
    cin >> id;

    for (int i = 0; i < jumlahBuku; i++) {
        if (buku[i].id == id) {
            if (!buku[i].dipinjam) {
                cout << "Buku ini tidak sedang dipinjam.\n";
            } else {
                buku[i].dipinjam = false;
                cout << "Buku berhasil dikembalikan.\n";
                cout << "Apakah ada keterlambatan pengembalian? (1: Ya, 2: Tidak): ";
                int pilihan;
                cin >> pilihan;
                if(pilihan == 1) {
                    int denda = hitungDenda();
                    cout << "Total denda yang harus dibayar: Rp " << denda << "\n";
                } else {
                    cout << "Terima kasih telah mengembalikan tepat waktu.\n";
                }
                    // cek apakah ada reservasi untuk buku yang dikembalikan
                    cekReservasiSaatKembali(buku[i].judul);
            }
            return;
        }
    }
    cout << "Buku tidak ditemukan.\n";
}

int main(){
    Buku buku[100];
    int jumlahBuku = 0;
    int pilihan;
    int pilihanSorting;
    int targetId;
    string targetJudul;
    int pilihanSearch;

    do{
        tampilanMenu();
        cin >> pilihan;
        switch (pilihan){
            case 1:
                tambahBuku(buku, jumlahBuku);
                break;
            case 2:
                sortingByJudul(buku, jumlahBuku);
                displayAllBuku(buku, jumlahBuku);
                break;
            case 3:
                selectSort(buku, jumlahBuku);
                break;
            case 4:
                searchSelect(buku, jumlahBuku, targetId, targetJudul, pilihanSearch);
                break;
            case 5:
                pinjamBuku(buku, jumlahBuku);
                break;
            case 6:
                returnBuku(buku, jumlahBuku);
                break;
            case 7:
                reservasiBuku(buku, jumlahBuku);
                break;
            case 0:
                cout << "Keluar dari program." << '\n';
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << '\n';
                break;
        }
    }while(pilihan != 0);
    return 0;
}