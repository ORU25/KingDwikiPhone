#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

string directoryOrder = "data/orders.json";

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

vector<Order> getAllOrders() {
    ifstream file(directoryOrder);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        cout << "Gagal membuka file!" << endl;
        return {}; 
    }

    vector<Order> orders;

    for (const auto &item : data) {
        Order order;
        order.id = item["id"];
        order.user_id = item["user_id"];
        order.total_price = item["total_price"];
        order.status = item["status"];

        for (const auto &jsonItem : item["products"]) {
            OrderItem orderItem;
            orderItem.product_id = jsonItem["product_id"];
            orderItem.name = jsonItem["name"];
            orderItem.quantity = jsonItem["quantity"];
            orderItem.price = jsonItem["price"];
            order.products.push_back(orderItem);
        }

        orders.push_back(order);
    }

    return orders;
}