#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// Struktur untuk menyimpan data tugas
struct Tugas {
    string nama;
    string keterangan;
    tm deadline;
    string kategori;
};

// Fungsi untuk validasi tanggal
bool validasiTanggal(int hari, int bulan, int tahun) {
    if (tahun < 2024) return false;
    if (bulan < 1 || bulan > 12) return false;
    
    int hari_dalam_bulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Cek tahun kabisat
    if ((tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0)) {
        hari_dalam_bulan[1] = 29;
    }
    
    if (hari < 1 || hari > hari_dalam_bulan[bulan - 1]) return false;
    
    return true;
}

// Fungsi untuk validasi waktu
bool validasiWaktu(int jam, int menit) {
    return (jam >= 0 && jam <= 23 && menit >= 0 && menit <= 59);
}

// Fungsi untuk input deadline
tm inputDeadline() {
    tm deadline = {};
    string input;
    int hari, bulan, tahun, jam, menit;
    char sep1, sep2, sep3;
    
    cout << "Format: DD-MM-YYYY HH:MM (contoh: 25-12-2024 14:30)" << endl;
    
    bool valid = false;
    while (!valid) {
        cout << "Masukkan Deadline Tugas: ";
        getline(cin, input);
        
        // Parse string menggunakan stringstream
        stringstream ss(input);
        ss >> hari >> sep1 >> bulan >> sep2 >> tahun >> jam >> sep3 >> menit;
        
        if (ss.fail() || sep1 != '-' || sep2 != '-' || sep3 != ':') {
            cout << "Format salah! Gunakan format: DD-MM-YYYY HH:MM\n" << endl;
            continue;
        }
        
        if (!validasiTanggal(hari, bulan, tahun)) {
            cout << "Tanggal tidak valid!\n" << endl;
            continue;
        }
        
        if (!validasiWaktu(jam, menit)) {
            cout << "Waktu tidak valid!\n" << endl;
            continue;
        }
        
        valid = true;
    }
    
    deadline.tm_mday = hari;
    deadline.tm_mon = bulan - 1;
    deadline.tm_year = tahun - 1900;
    deadline.tm_hour = jam;
    deadline.tm_min = menit;
    deadline.tm_sec = 0;
    
    return deadline;
}

// Fungsi untuk mengkonversi tm ke string
string tmToString(const tm& waktu) {
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", &waktu);
    return string(buffer);
}

// Fungsi untuk mengkonversi string ke tm
tm stringToTm(const string& str) {
    tm waktu = {};
    int hari, bulan, tahun, jam, menit;
    char sep1, sep2, sep3;
    
    stringstream ss(str);
    ss >> hari >> sep1 >> bulan >> sep2 >> tahun >> jam >> sep3 >> menit;
    
    waktu.tm_mday = hari;
    waktu.tm_mon = bulan - 1;
    waktu.tm_year = tahun - 1900;
    waktu.tm_hour = jam;
    waktu.tm_min = menit;
    waktu.tm_sec = 0;
    
    return waktu;
}

// Fungsi untuk menyimpan tugas ke file
void simpanKeFile(const vector<Tugas>& daftarTugas) {
    ofstream file("todolist.txt");
    
    if (!file.is_open()) {
        cout << "Error: Tidak dapat membuka file untuk menyimpan!" << endl;
        return;
    }
    
    for (const auto& tugas : daftarTugas) {
        file << tugas.nama << "|"
             << tugas.keterangan << "|"
             << tmToString(tugas.deadline) << "|"
             << tugas.kategori << endl;
    }
    
    file.close();
}

// Fungsi untuk membaca tugas dari file
vector<Tugas> bacaDariFile() {
    vector<Tugas> daftarTugas;
    ifstream file("todolist.txt");
    
    if (!file.is_open()) {
        // File belum ada, return vector kosong
        return daftarTugas;
    }
    
    string baris;
    while (getline(file, baris)) {
        Tugas tugas;
        stringstream ss(baris);
        string deadlineStr;
        
        getline(ss, tugas.nama, '|');
        getline(ss, tugas.keterangan, '|');
        getline(ss, deadlineStr, '|');
        getline(ss, tugas.kategori, '|');
        
        tugas.deadline = stringToTm(deadlineStr);
        
        daftarTugas.push_back(tugas);
    }
    
    file.close();
    return daftarTugas;
}

// Fungsi untuk menambah tugas
void tambahTugas(vector<Tugas>& daftarTugas) {
    Tugas tugas;
    
    cout << "\n====Masukkan Tugas Anda====" << endl;
    
    cout << "Masukkan Nama Tugas: ";
    getline(cin, tugas.nama);
    
    cout << "Masukkan Keterangan Tugas: ";
    getline(cin, tugas.keterangan);
    
    tugas.deadline = inputDeadline();
    
    cout << "Masukkan Kategori Tugas (contoh: Kuliah/Pekerjaan/Rumah/Dll): ";
    getline(cin, tugas.kategori);
    
    daftarTugas.push_back(tugas);
    simpanKeFile(daftarTugas);
    
    cout << "\n====Tugas Telah Ditambahkan====" << endl;
}

// Fungsi untuk menampilkan semua tugas
void tampilkanSemuaTugas(const vector<Tugas>& daftarTugas) {
    cout << "\nBerikut adalah daftar tugas anda:" << endl;
    
    if (daftarTugas.empty()) {
        cout << "Tidak ada tugas yang tersimpan." << endl;
        return;
    }
    
    for (size_t i = 0; i < daftarTugas.size(); i++) {
        cout << (i + 1) << ". " 
             << daftarTugas[i].nama << " - "
             << daftarTugas[i].keterangan << " - "
             << tmToString(daftarTugas[i].deadline) << " - "
             << daftarTugas[i].kategori << endl;
    }
}

// Fungsi untuk menampilkan daftar nama tugas
void tampilkanDaftarNama(const vector<Tugas>& daftarTugas) {
    for (size_t i = 0; i < daftarTugas.size(); i++) {
        cout << (i + 1) << ". " << daftarTugas[i].nama << endl;
    }
}

// Fungsi untuk menghapus tugas
void hapusTugas(vector<Tugas>& daftarTugas) {
    if (daftarTugas.empty()) {
        cout << "\nTidak ada tugas yang dapat dihapus." << endl;
        return;
    }
    
    cout << "\nDaftar Tugas:" << endl;
    tampilkanDaftarNama(daftarTugas);
    
    int pilihan;
    cout << "\nPilih nomor tugas yang ingin dihapus: ";
    cin >> pilihan;
    cin.ignore();
    
    if (pilihan < 1 || pilihan > (int)daftarTugas.size()) {
        cout << "Nomor tugas tidak valid!" << endl;
        return;
    }
    
    string namaTugas = daftarTugas[pilihan - 1].nama;
    daftarTugas.erase(daftarTugas.begin() + (pilihan - 1));
    simpanKeFile(daftarTugas);
    
    cout << "\nTugas \"" << namaTugas << "\" telah dihapus" << endl;
}

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    cout << "\n\nPROGRAM TO-DO-LIST - CATAT TUGASMU" << endl;
    cout << "===================================" << endl;
    cout << "1. Tambah Tugas" << endl;
    cout << "2. Tampilkan Semua Tugas" << endl;
    cout << "3. Hapus Tugas" << endl;
    cout << "4. Keluar" << endl;
    cout << "Pilih opsi: ";
}

int main() {
    vector<Tugas> daftarTugas = bacaDariFile();
    int pilihan;
    
    while (true) {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(); // Membersihkan newline dari buffer
        
        switch (pilihan) {
            case 1:
                tambahTugas(daftarTugas);
                break;
                
            case 2:
                tampilkanSemuaTugas(daftarTugas);
                break;
                
            case 3:
                hapusTugas(daftarTugas);
                break;
                
            case 4:
                cout << "\nTerima Kasih telah memakai program TO-DO-LIST" << endl;
                return 0;
                
            default:
                cout << "\nPilihan tidak valid! Silahkan ulang kembali" << endl;
        }
    }
    
    return 0;
}