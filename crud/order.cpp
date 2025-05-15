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


int generateNewOrderId(const vector<Order>& orders) {
    int maxId = 0;
    for (const auto& order : orders) {
        if (order.id > maxId) {
            maxId = order.id;
        }
    }
    return maxId + 1;
}

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

Order getOrder(int &id) {
    ifstream file(directoryOrder);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        system("cls");
        cout << "Gagal membuka file!" << endl;
    }
    
    Order order;

    for (const auto &item : data){
        if(item["id"] == id){
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
        }
    }
    return order;
}

bool AddOrder(Order &order){
    vector<Order> orders = getAllOrders();

    try{
        ifstream file(directoryOrder);
        json data;
        if (file.is_open()) {
            file >> data;
            file.close();
        } else {
            system("cls");
            cout << "Gagal membuka file!" << endl;
            return false; 
        }
        
        json newOrder;
        newOrder["id"] = generateNewOrderId(orders);
        newOrder["user_id"] = order.user_id;
        newOrder["total_price"] = order.total_price;
        newOrder["status"] = "pending";
    
        for (const auto &product : order.products) {
            json newProduct;
            newProduct["product_id"] = product.product_id;
            newProduct["name"] = product.name;
            newProduct["quantity"] = product.quantity;
            newProduct["price"] = product.price;
            newOrder["products"].push_back(newProduct);
        }
    
        data.push_back(newOrder);
    
        ofstream outFile(directoryOrder);
    
        if (outFile.is_open()) {
            outFile << data.dump(4);
            outFile.close();
        } else {
            system("cls");
            cerr << "Gagal membuka file untuk menyimpan data!" << endl;
            return false;
        } 
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    return true;
}


// bool ConfirmOrder(int id, string status){}