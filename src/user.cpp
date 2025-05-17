#include "../header/user.h"

string directoryUser = "data/users.json";

int generateNewUserId(const vector<User>& users) {
    int maxId = 0;
    for (const auto& user : users) {
        if (user.id > maxId) {
            maxId = user.id;
        }
    }
    return maxId + 1;
}

vector<User> getAllUsers() {
    ifstream file(directoryUser);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        system("cls");
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

User getUser(int &id){
    ifstream file(directoryUser);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        system("cls");
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


bool AddUser(User &user) {
    vector<User> users = getAllUsers();
    try{
        ifstream file(directoryUser);
        json data;
        if (file.is_open()) {
            file >> data;
            file.close();
        } else {
            system("cls");
            cerr << "Gagal membuka file!" << endl;
            return false;
        }
    
        json newUser;
        newUser["id"] = generateNewUserId(users);
        newUser["username"] = user.username;
        newUser["password"] = user.password;
        newUser["role"] = user.role;
    
        data.push_back(newUser);
        
        ofstream outFile(directoryUser);

    
        if (outFile.is_open()) {
            outFile << data.dump(4); // Menyimpan dengan indentasi 4 spasi
            outFile.close();            
        } else {
            system("cls");
            cerr << "Gagal membuka file untuk menyimpan data!" << endl;
        }    
    }
    catch(const exception& e){
        cerr << e.what() << '\n';
    }
    
    return true;
}


bool EditUser(int id, User editedUser){
    vector<User> users = getAllUsers();
    bool found = false;

    for(auto &item : users){
        if(item.id == id){
            item.id = id;
            item.username = editedUser.username;
            item.password = editedUser.password;
            item.role = editedUser.role;
            found = true;
            break;
        }
    }

    if (!found) {
        system("cls");
        cerr << "User dengan ID " << id << " tidak ditemukan!" << endl;
        return false;
    }

    json data = json::array();
    for (const auto &user : users) {
        json userJson;
        userJson["id"] = user.id;
        userJson["username"] = user.username;
        userJson["password"] = user.password;
        userJson["role"] = user.role;
        data.push_back(userJson);
    }

    ofstream outFile(directoryUser);
    if (outFile.is_open()) {
        outFile << data.dump(4);
        outFile.close();
        return true;
    } else {
        system("cls");
        cerr << "Gagal menyimpan perubahan ke file!" << endl;
        return false;
    }
}

bool DeleteUser(int id) {
    vector<User> users = getAllUsers();
    bool found = false;

    for (auto user = users.begin(); user != users.end(); ++user) {
        if (user->id == id) {
            users.erase(user);
            found = true;
            break;
        }
    }

    if (!found) {
        system("cls");
        cerr << "User dengan ID " << id << " tidak ditemukan!" << endl;
        return false;
    }

    json data;
    for (const auto& user : users) {
        data.push_back({
            {"id", user.id},
            {"username", user.username},
            {"password", user.password},
            {"role", user.role}
        });
    }

    ofstream file(directoryUser);
    if (file.is_open()) {
        file << setw(4) << data;
        file.close();
        return true;
    } else {
        system("cls");
        cerr << "Gagal menyimpan file!" << endl;
        return false;
    }
}