#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct tugas{
    string nama;
    string keterangan;
    string deadline;
};
    tugas daftar[100];
    int jumlahTugas = 0;

int loadfile() {
    ifstream file("tugas.txt");
    if (!file.is_open()) return 0;

    jumlahTugas = 0;
    while (getline(file, daftar[jumlahTugas].nama)) {
    getline(file, daftar[jumlahTugas].deadline);
    getline(file, daftar[jumlahTugas].keterangan);
    jumlahTugas++;
}
    file.close();
}
int simpanfile() {
    ofstream file("tugas.txt");
    for (int i = 0; i < jumlahTugas; i++) {
        file << daftar[i].nama << endl;
        file << daftar[i].deadline << endl;
        file << daftar[i].keterangan << endl;
    }
    file.close();
}
int tambahTugas() {
    cout << "Masukkan nama tugas: ";
    cin.ignore();
    getline(cin, daftar[jumlahTugas].nama);

    cout << "Masukkan deadline tugas: ";
    getline(cin, daftar[jumlahTugas].deadline);

    cout << "Masukkan keterangan tugas: ";
    getline(cin, daftar[jumlahTugas].keterangan);

    jumlahTugas++;
    simpanfile();
    cout << "\ntugas berhasil ditambahkan!\n";
}
int lihattugas() {
    cout << "\ndaftar tugas:\n";
     if (jumlahTugas == 0) {
        cout << "Belum ada tugas.\n";
        return;
    }

    tugas* ptr = daftar;

    for (int i = 0; i < jumlahTugas; i++) {
        cout << "\nTugas ke-" << (i + 1) << endl;
        cout << "Nama      : " << ptr[i].nama << endl;
        cout << "Deadline  : " << ptr[i].deadline << endl;
        cout << "Keterangan: " << ptr[i].keterangan << endl;
    }
}
int hapusTugas() {
    lihattugas();
    if (jumlahTugas == 0) {
        return;
    }
    int index;
    cout << "\nMasukkan nomor tugas yang ingin dihapus: ";
    cin >> index;
    index--;

    if (index < 0 || index >= jumlahTugas) {
        cout << "Nomor tidak valid!\n";
        return;
    }
    for (int i = index; i < jumlahTugas - 1; i++) {
        daftar[i] = daftar[i + 1];
    }
    jumlahTugas--;
    simpanfile();

    cout << "\nTugas berhasil dihapus!\n";
}

