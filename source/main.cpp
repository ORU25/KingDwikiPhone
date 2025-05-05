#include <iostream>
#include <fstream>
#include <vector>
#include "../header/user.h"
#include "json.hpp"

using namespace std;

using json = nlohmann::json;


vector<User> parseUsers(const json &data) {
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
};

int main() {
    ifstream file("../data/users.json");
    json data_user;
    file >> data_user;

    vector<User> users = parseUsers(data_user);

    for(const auto &user : users) {
        cout << "ID: " << user.id << endl;
        cout << "Username: " << user.username << endl;
        cout << "Password: " << user.password << endl;
        cout << "Role: " << user.role << endl;
    }
    return 0;
}