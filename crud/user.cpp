#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

string directoryUser = "data/users.json";

struct User {
    int id;
    string username;
    string password;
    string role;
};

vector<User> getAllUsers() {
    ifstream file(directoryUser);
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

bool addUser(User &user) {
    try{
        ifstream file(directoryUser);
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
        
        ofstream outFile(directoryUser);

    
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

User getUser(int &id){
    ifstream file(directoryUser);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        cout << "Gagal membuka file!" << endl;
    }
    
    User user;

    for (const auto &item : data){
        if(item["id"] == id){
            user.id = item["id"];
            user.username = item["username"];
            user.password = item["password"];
            user.role = item["role"];
        }
    }

    return user;
}

bool EditUser(User &user, User editedUser){
    vector<User> users = getAllUsers();
    bool found = false;

    for(auto &item : users){
        if(item.id == user.id){
            item.id = editedUser.id;
            item.username = editedUser.username;
            item.password = editedUser.password;
            item.role = editedUser.role;
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "User dengan ID " << user.id << " tidak ditemukan!" << endl;
        return false;
    }

    json data = json::array();
    for (const auto &u : users) {
        json userJson;
        userJson["id"] = u.id;
        userJson["username"] = u.username;
        userJson["password"] = u.password;
        userJson["role"] = u.role;
        data.push_back(userJson);
    }

    ofstream outFile(directoryUser);
    if (outFile.is_open()) {
        outFile << data.dump(4);
        outFile.close();
        cout << "User berhasil diedit!" << endl;
        return true;
    } else {
        cerr << "Gagal menyimpan perubahan ke file!" << endl;
        return false;
    }
}