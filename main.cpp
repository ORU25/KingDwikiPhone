#include <iostream>

#include "crud/user.cpp"

using namespace std;

void AdminMenu(User &user);
void UserMenu(User &user);
void CrudUser();
void CrudProduct();
void CrudOrder();


int main() {
    system("cls");
    
    bool isLogin = false;
    int login_attempt = 3;
    int pilihanAwal = -1;
    

    while (pilihanAwal != 0 && login_attempt > 0) {
        cout << "=================================" << endl;
        cout << "Selamat Datang di KING DWIKIPHONE" << endl;
        cout << "=================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih opsi (1-0): ";

        cin >> pilihanAwal;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail()) {
            cin.clear(); // Reset status error
            cin.ignore(); // Buang karakter sisa
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }
        
        if (pilihanAwal == 1) {
            cout << "Login" << endl;
            isLogin = true;
        } else if (pilihanAwal == 2) {
            cout << "Register" << endl;
        } else if (pilihanAwal == 0) {
            cout << "Program selesai!" << endl;
            return 0;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
        

        if(isLogin){
            
            // user sementara
            User user = {1, "dwiki", "123", "admin"};
            
            if(user.role == "admin"){
                AdminMenu(user);
            }else if(user.role == "user"){
                UserMenu(user);
            }
        }
    }

    return 0;
}

void AdminMenu(User &user){
    int pilihan = -1;
    while(pilihan != 0){
        cout << "=================================" << endl;
        cout << "Selamat Datang di KING DWIKIPHONE" << endl;
        cout << "=================================" << endl;
        cout << "Hallo " << user.username << endl;
        cout << "=================================" << endl;
        cout << "1. Kelola user" << endl;
        cout << "2. Kelola produk" << endl;
        cout << "3. Kelola pesanan" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilih opsi (1-0): ";

        cin >> pilihan;

        system("cls");
        
        // Tangani input bukan integer
        if (cin.fail()) {
            cin.clear(); // Reset status error
            cin.ignore(); // Buang karakter sisa
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if(pilihan == 1){
            CrudUser();
        }else if(pilihan == 2){
            CrudProduct();
        }else if(pilihan == 3){
            CrudOrder();
        }else if(pilihan == 0){
            cout << "Logout" << endl;
        }else{
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void UserMenu(User &user){
    int pilihan = -1;
    while(pilihan != 0){
        cout << "=================================" << endl;
        cout << "Selamat Datang di KING DWIKIPHONE" << endl;
        cout << "=================================" << endl;
        cout << "Hallo " << user.username << endl;
        cout << "=================================" << endl;
        cout << "1. Buat pesanan" << endl;
        cout << "2. Lihat history pesanan" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilih opsi (1-0): ";
        
        cin >> pilihan;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail()) {
            cin.clear(); // Reset status error
            cin.ignore(); // Buang karakter sisa
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }
    }
}

void CrudUser(){
    int pilihan = -1;
    while(pilihan != 0){
        cout << "=================================" << endl;
        cout << "Kelola User" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah User" << endl;
        cout << "2. Tampilkan User" << endl;
        cout << "3. Ubah User" << endl;
        cout << "4. Hapus User" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilih opsi (1-0): ";

        cin >> pilihan;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail()) {
            cin.clear(); // Reset status error
            cin.ignore(); // Buang karakter sisa
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if(pilihan == 1){
            try{
                User user;
                cout << "ID: ";
                cin >> user.id;
                cout << "Username: ";
                cin >> user.username;
                cout << "Password: ";
                cin >> user.password;
                cout << "Role: ";
                cin >> user.role;
                if(!addUser(user, "data/users.json")){
                    cout << "User gagal ditambahkan!" << endl;
                }
            }catch(const exception& e){
                cerr << "Error: " << e.what() << endl;
            }

        }else if(pilihan == 2){
            vector<User> users = getAllUsers("data/users.json");
            
            for (const auto &user : users) {
                cout << "ID: " << user.id << ", Username: " << user.username << ", Password: " << user.password << ", Role: " << user.role << endl;
            }
        }else if(pilihan == 3){
            //update user
        }else if(pilihan == 3){
            //delete user
        }else if(pilihan == 0){
            cout << "Logout" << endl;
        }else{
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CrudProduct(){
    int pilihan = -1;
    while(pilihan != 0){
        cout << "=================================" << endl;
        cout << "Kelola Produk" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Tampilkan Produk" << endl;
        cout << "3. Ubah Produk" << endl;
        cout << "4. Hapus Produk" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilih opsi (1-0): ";

        cin >> pilihan;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail()) {
            cin.clear(); // Reset status error
            cin.ignore(); // Buang karakter sisa
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }
    }
}

void CrudOrder(){
    int pilihan = -1;
    while(pilihan != 0){
        cout << "=================================" << endl;
        cout << "Kelola Pesanan" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah Pesanan" << endl;
        cout << "2. Tampilkan Pesanan" << endl;
        cout << "3. Ubah Pesanan" << endl;
        cout << "4. Hapus Pesanan" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilih opsi (1-0): ";

        cin >> pilihan;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail()) {
            cin.clear(); // Reset status error
            cin.ignore(); // Buang karakter sisa
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }
    }
}