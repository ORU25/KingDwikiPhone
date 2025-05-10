#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

struct User {
    int id;
    string username;
    string password;
    string role;
};

vector<User> getAllUsers(string directory) {
    ifstream file(directory);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        cout << "Gagal membuka file!" << endl;
    }
    
    vector<User> users;

    for (const auto &item : data) {
        User user;
        user.id = item["id"];
        user.username = item["username"];
        user.password = item["password"];
        user.role = item["role"];
        users.push_back(user);
    }
    return users;
}

bool addUser(User &user, string directory) {
    try{
        ifstream file(directory);
        json data;
        if (file.is_open()) {
            file >> data;
            file.close();
        } else {
            cerr << "Gagal membuka file!" << endl;
            return false;
        }
    
        json newUser;
        newUser["id"] = user.id;
        newUser["username"] = user.username;
        newUser["password"] = user.password;
        newUser["role"] = user.role;
    
        data.push_back(newUser);
        
        ofstream outFile(directory);

    
        if (outFile.is_open()) {
            outFile << data.dump(4); // Menyimpan dengan indentasi 4 spasi
            outFile.close();
            cout << "User berhasil ditambahkan!" << endl;
            
        } else {
            cerr << "Gagal membuka file untuk menyimpan data!" << endl;
        }    
    }
    catch(const exception& e){
        cerr << e.what() << '\n';
    }
    
    return true;
}