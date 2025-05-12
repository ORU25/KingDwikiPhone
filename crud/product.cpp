#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

string directoryProduct = "data/products.json";

struct Product {
    int id;
    string name;
    string brand;
    int stock;
    int price;
};

vector<Product> getAllProducts(){
    ifstream file(directoryProduct);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        cout << "Gagal membuka file!" << endl;
    }
    
    vector<Product> products;

    for (const auto &item : data) {
        Product product;
        product.id = item["id"];
        product.name = item["name"];
        product.brand = item["brand"];
        product.stock = item["stock"];
        product.price = item["price"];
        
        products.push_back(product);
    }
    return products;
}

bool addProduct(Product &product) {
    try{
        ifstream file(directoryProduct);
        json data;
        if (file.is_open()) {
            file >> data;
            file.close();
        } else {
            cerr << "Gagal membuka file!" << endl;
            return false;
        }
    
        json newproduct;
        newproduct["id"] = product.id;
        newproduct["name"] = product.name;
        newproduct["brand"] = product.brand;
        newproduct["stock"] = product.stock;
        newproduct["price"] = product.price;
    
        data.push_back(newproduct);
        
        ofstream outFile(directoryProduct);

    
        if (outFile.is_open()) {
            outFile << data.dump(4); // Menyimpan dengan indentasi 4 spasi
            outFile.close();
            cout << "Product berhasil ditambahkan!" << endl;
            
        } else {
            cerr << "Gagal membuka file untuk menyimpan data!" << endl;
        }    
    }
    catch(const exception& e){
        cerr << e.what() << '\n';
    }
    
    return true;
}