#include <iostream>

using namespace std;


void UserMenu(string name){
    cout << "=================================" << endl;
    cout << "Selamat Datang di KING DWIKIPHONE" << endl;
    cout << "=================================" << endl;
    cout << "Hallo " << name << endl;
    cout << "=================================" << endl;
    cout << "1. Buat pesanan" << endl;
    cout << "2. Lihat history pesanan" << endl;
    cout << "0. Logout" << endl;
    cout << "Pilih opsi (1-0): ";
}

void AdminMenu(string name){
    cout << "=================================" << endl;
    cout << "Selamat Datang di KING DWIKIPHONE" << endl;
    cout << "=================================" << endl;
    cout << "Hallo " << name << endl;
    cout << "=================================" << endl;
    cout << "1. Kelola user" << endl;
    cout << "2. Kelola produk" << endl;
    cout << "3. Kelola pesanan" << endl;
    cout << "0. Logout" << endl;
    cout << "Pilih opsi (1-0): ";
}

void LoginMenu(){
    cout << "=================================" << endl;
    cout << "Selamat Datang di KING DWIKIPHONE" << endl;
    cout << "=================================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih opsi (1-0): ";
}