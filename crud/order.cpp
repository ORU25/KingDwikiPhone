#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

struct OrderItem {
    int product_id;
    string name;
    int quantity;
    int price;
};

struct Order {
    int id;
    int user_id;
    vector<OrderItem> items;
    int total_price;
    string status;
};