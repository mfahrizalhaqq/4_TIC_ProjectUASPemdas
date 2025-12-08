#include <iostream>
#include <fstream>
#include <string>
#include <ctime>    
using namespace std;

struct tugas{
    string NamaTugas;
    string Keterangan;
    string Deadline;
    string kategori;
};


void inputtugas(tugas *t){
    cout << "Masukkan nama tugas: ";
    cin.ignore();
    getline(cin, t->NamaTugas);

    cout << "Masukkan deadline tugas: ";
    getline(cin, t->Deadline);

    cout << "Masukkan keterangan tugas: ";
    getline(cin, t->Keterangan);

    cout << "Masukkan kategori tugas: ";
    getline(cin, t->kategori);
}

void tampilkantugas(const tugas *t){
    cout << "Nama Tugas: " << t->NamaTugas << endl;
    cout << "Deadline: " << t->Deadline << endl;
    cout << "Keterangan: " << t->Keterangan << endl;
    cout << "Kategori: " << t->kategori << endl;
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

