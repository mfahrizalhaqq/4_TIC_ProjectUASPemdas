#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

struct Tugas {
    string nama;
    string keterangan;
    tm deadline;
    string kategori;
};

Tugas daftarTugas[1000];
int jumlahTugas = 0;

bool validasiTanggal(int hari, int bulan, int tahun) {
    if (tahun < 2025) return false;
    if (bulan < 1 || bulan > 12) return false;
    
    int hari_dalam_bulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if ((tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0)) {
        hari_dalam_bulan[1] = 29;
    }
    
    if (hari < 1 || hari > hari_dalam_bulan[bulan - 1]) return false;
    
    return true;
}

bool validasiWaktu(int jam, int menit) {
    return (jam >= 0 && jam <= 23 && menit >= 0 && menit <= 59);
}


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
        
        
        size_t pos1 = input.find('-');
        size_t pos2 = input.find('-', pos1 + 1);
        size_t pos3 = input.find(' ');
        size_t pos4 = input.find(':');
        
        if (pos1 == string::npos || pos2 == string::npos || 
            pos3 == string::npos || pos4 == string::npos) {
            cout << "Format salah! Gunakan format: DD-MM-YYYY HH:MM" << endl;
            continue;
        }
        
        try {
            hari = stoi(input.substr(0, pos1));
            bulan = stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
            tahun = stoi(input.substr(pos2 + 1, pos3 - pos2 - 1));
            jam = stoi(input.substr(pos3 + 1, pos4 - pos3 - 1));
            menit = stoi(input.substr(pos4 + 1));
        } catch (...) {
            cout << "Format salah! Gunakan format: DD-MM-YYYY HH:MM" << endl;
            continue;
        }
        
        if (!validasiTanggal(hari, bulan, tahun)) {
            cout << "Tanggal tidak valid!" << endl;
            continue;
        }
        
        if (!validasiWaktu(jam, menit)) {
            cout << "Waktu tidak valid!" << endl;
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


string formatDeadline(const tm& deadline) {
    char buffer[100];
    sprintf(buffer, "%02d-%02d-%04d %02d:%02d", 
            deadline.tm_mday, 
            deadline.tm_mon + 1, 
            deadline.tm_year + 1900,
            deadline.tm_hour,
            deadline.tm_min);
    return string(buffer);
}


void tambahTugas() {
    if (jumlahTugas >= 100) {
        cout << "Daftar tugas sudah penuh!" << endl;
        return;
    }
    
    cout << "\n====Masukkan Tugas Anda====" << endl;
    
    cin.ignore();
    cout << "Masukkan Nama Tugas: ";
    getline(cin, daftarTugas[jumlahTugas].nama);
    
    cout << "Masukkan Keterangan Tugas: ";
    getline(cin, daftarTugas[jumlahTugas].keterangan);
    
    daftarTugas[jumlahTugas].deadline = inputDeadline();
    
    cout << "Masukkan Kategori Tugas (contoh: Kuliah/Pekerjaan/Rumah/Dll): ";
    getline(cin, daftarTugas[jumlahTugas].kategori);
    
    jumlahTugas++;
    
    cout << "====Tugas Telah Ditambahkan====" << endl;
}


void tampilkanSemuaTugas() {
    cout << "\nBerikut adalah daftar tugas anda:" << endl;
    
    if (jumlahTugas == 0) {
        cout << "Belum ada tugas yang ditambahkan." << endl;
        return;
    }
    
    for (int i = 0; i < jumlahTugas; i++) {
        cout << (i + 1) << ". " 
             << daftarTugas[i].nama << " - "
             << daftarTugas[i].keterangan << " - "
             << formatDeadline(daftarTugas[i].deadline) << " - "
             << daftarTugas[i].kategori << endl;
    }
}
void tampilkanSemuaTugas() {
    if (jumlahTugas == 0) {
        cout << "Belum ada tugas.\n";
        return;
    }
     for (int i = 0; i < jumlahTugas; i++) {
        cout << "\nTugas ke-" << i + 1 << ":\n";
        tampilkantugas(&daftarTugas[i]);
    }
}
void hapusTugas() {
    if (jumlahTugas == 0) {
        cout << "Belum ada tugas.\n";
        return;
    }
    tampilkanSemuaTugas();

    int nomor;
    cout << endl << "Masukkan nomor tugas yang ingin dihapus: " << endl;
    cin >> nomor;

    if (nomor < 1 || nomor > jumlahTugas) {
        cout << "Nomor tidak valid!" << endl;
        return;
    }

    for (int i = nomor - 1; i < jumlahTugas - 1; i++) {
        daftarTugas[i] = daftarTugas[i + 1];
    }
    jumlahTugas--;
    cout << "Tugas nomor " << nomor << " berhasil dihapus!" << endl;
}


void hapusTugas() {
    if (jumlahTugas == 0) {
        cout << "\nBelum ada tugas yang bisa dihapus." << endl;
        return;
    }
    
    tampilkanSemuaTugas();
    
    cout << "\nPilih Nama Tugas yang ingin dihapus: ";
    cin.ignore();
    string namaTugas;
    getline(cin, namaTugas);
    
    bool ditemukan = false;
    for (int i = 0; i < jumlahTugas; i++) {
        if (daftarTugas[i].nama == namaTugas) {
            
            for (int j = i; j < jumlahTugas - 1; j++) {
                daftarTugas[j] = daftarTugas[j + 1];
            }
            jumlahTugas--;
            ditemukan = true;
            cout << "\nTugas " << namaTugas << " telah dihapus" << endl;
            break;
        }
    }
    
    if (!ditemukan) {
        cout << "\nTugas dengan nama \"" << namaTugas << "\" tidak ditemukan." << endl;
    }
}


void simpanKeFile() {
    ofstream file("todolist.txt");
    
    if (!file.is_open()) {
        return;
    }
    
    file << jumlahTugas << endl;
    
    for (int i = 0; i < jumlahTugas; i++) {
        file << daftarTugas[i].nama << endl;
        file << daftarTugas[i].keterangan << endl;
        file << daftarTugas[i].deadline.tm_mday << " "
             << daftarTugas[i].deadline.tm_mon << " "
             << daftarTugas[i].deadline.tm_year << " "
             << daftarTugas[i].deadline.tm_hour << " "
             << daftarTugas[i].deadline.tm_min << endl;
        file << daftarTugas[i].kategori << endl;
    }
    
    file.close();
}


void bacaDariFile() {
    ifstream file("todolist.txt");
    
    if (!file.is_open()) {
        return;
    }
    
    file >> jumlahTugas;
    file.ignore();
    
    for (int i = 0; i < jumlahTugas; i++) {
        getline(file, daftarTugas[i].nama);
        getline(file, daftarTugas[i].keterangan);
        
        file >> daftarTugas[i].deadline.tm_mday
             >> daftarTugas[i].deadline.tm_mon
             >> daftarTugas[i].deadline.tm_year
             >> daftarTugas[i].deadline.tm_hour
             >> daftarTugas[i].deadline.tm_min;
        file.ignore();
        
        getline(file, daftarTugas[i].kategori);
    }
    
    file.close();
}


void tampilkanMenu() {
    cout << "\nPROGRAM TO-DO-LIST - CATAT TUGASMU" << endl;
    cout << "===================================" << endl;
    cout << "1. Tambah Tugas" << endl;
    cout << "2. Tampilkan Semua Tugas" << endl;
    cout << "3. Hapus Tugas" << endl;
    cout << "4. Keluar" << endl;
    cout << "Pilih opsi: ";
}

int main() {
    
    bacaDariFile();
    
    int pilihan;
    bool running = true;
    
    while (running) {
        tampilkanMenu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tambahTugas();
                simpanKeFile();
                break;
            case 2:
                tampilkanSemuaTugas();
                break;
            case 3:
                hapusTugas();
                simpanKeFile();
                break;
            case 4:
                cout << "\nTerima Kasih telah memakai program TO-DO-LIST" << endl;
                simpanKeFile();
                running = false;
                break;
            default:
                cout << "\nPilihan tidak valid! Silahkan ulang kembali" << endl;
        }
    }
    
    return 0;
}