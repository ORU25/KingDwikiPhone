#include <iostream>

#include "user.cpp"
#include "menu.cpp"

using namespace std;

int main() {
    system("cls");
    
    bool isLogin = false;
    int login_attempt = 3;
    int pilihanAwal;
    

    while (pilihanAwal != 0 && login_attempt > 0) {
        LoginMenu();
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
            cout << "berhasil login" << endl;

        }
    }

    return 0;
}