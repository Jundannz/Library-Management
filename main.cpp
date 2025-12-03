#include <iostream>
using namespace std;

struct Buku{
    int id;
    string judul;
    string penulis;
    int tahunTerbit;
    string kategori;
    bool dipinjam = false;
};

//display menu
void tampilanMenu(){
    cout << "=== Menu Perpustakaan ===" << '\n';
    cout << "1. Tambah Buku" << '\n';
    cout << "2. Tampilan buku" << '\n';
    cout << "3. Urutkan Item" << '\n';
    cout << "4. Cari Buku" << '\n';
    cout << "5. Pinjam Buku" << '\n';
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
        cout << "Status: "
             << (buku[i].dipinjam ? "Dipinjam" : "Tersedia") << '\n';
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
    int mid = left + (right - left) / 2;
    if(pilihanSearch == 1){
        while(left <= right){
            if(buku[mid].id == targetId){
                return mid;
            }
            else if(buku[mid].id < targetId){
                left = mid + 1;
            }
            else{
                right = mid + 1;
            }
            
        }
    }
    else if(pilihanSearch == 2){
        while(left <= right){
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
            }
            else{
                cout << "Buku dengan id " << targetId << " tidak ditemukan." << '\n';
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
    