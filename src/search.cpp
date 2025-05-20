#include "../header/search.h"
#include <vector>
#include <string>

// Binary Search untuk User berdasarkan username (case-sensitive, ascending)
bool searchUser(std::vector<User> &users, const std::string &username, User &result) {
    int left = 0;
    int right = users.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (users[mid].username == username) {
            result = users[mid];
            return true;
        } else if (users[mid].username < username) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// Binary Search untuk Product berdasarkan name (case-sensitive, ascending)
bool searchProduct(std::vector<Product> &products, const std::string &name, Product &result) {
    int left = 0;
    int right = products.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (products[mid].name == name) {
            result = products[mid];
            return true;
        } else if (products[mid].name < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// Binary Search untuk Order berdasarkan id (ascending)
bool searchOrder(std::vector<Order> &orders, int id, Order &result) {
    int left = 0;
    int right = orders.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (orders[mid].id == id) {
            result = orders[mid];
            return true;
        } else if (orders[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}