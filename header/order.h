#ifndef ORDER_H
#define ORDER_H


#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

extern string directoryOrder;


struct OrderItem {
    int product_id;
    string name;
    int quantity;
    int price;
};

struct Order {
    int id;
    int user_id;
    vector<OrderItem> products;
    int total_price;
    string status;
};


int generateNewOrderId(const vector<Order>& orders);
vector<Order> getAllOrders();
Order getOrder(int &id);
bool AddOrder(Order &order);


#endif