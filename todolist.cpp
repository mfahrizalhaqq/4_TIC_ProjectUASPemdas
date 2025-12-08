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

