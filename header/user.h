#ifndef USER_H
#define USER_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

extern string directoryUser;


struct User {
    int id;
    string username;
    string password;
    string role;
};

int generateNewUserId(const vector<User>& users);
vector<User> getAllUsers();
User getUser(int &id);
bool AddUser(User &user);
bool EditUser(int id, User editedUser);
bool DeleteUser(int id);



#endif