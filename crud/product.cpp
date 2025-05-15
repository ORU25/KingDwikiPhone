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

int generateNewProductId(const vector<Product>& products) {
    int maxId = 0;
    for (const auto& product : products) {
        if (product.id > maxId) {
            maxId = product.id;
        }
    }
    return maxId + 1;
}

vector<Product> getAllProducts(){
    ifstream file(directoryProduct);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        system("cls");
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

Product getProduct(int &id){
    ifstream file(directoryProduct);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    } else {
        system("cls");
        cout << "Gagal membuka file!" << endl;
    }
    
    Product product;

    for (const auto &item : data){
        if(item["id"] == id){
            product.id = item["id"];
            product.name = item["name"];
            product.brand = item["brand"];
            product.stock = item["stock"];
            product.price = item["price"];
        }
    }
    return product;
}

bool AddProduct(Product &product) {
    vector<Product> products = getAllProducts();
    try{
        ifstream file(directoryProduct);
        json data;
        if (file.is_open()) {
            file >> data;
            file.close();
        } else {
            system("cls");
            cerr << "Gagal membuka file!" << endl;
            return false;
        }
    
        json newproduct;
        newproduct["id"] = generateNewProductId(products);
        newproduct["name"] = product.name;
        newproduct["brand"] = product.brand;
        newproduct["stock"] = product.stock;
        newproduct["price"] = product.price;
    
        data.push_back(newproduct);
        
        ofstream outFile(directoryProduct);

    
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

bool EditProduct(int id, Product editedProduct){
    vector<Product> products = getAllProducts();
    bool found = false;

    for(auto &item : products){
        if(item.id == id){
            item.id = id;
            item.name = editedProduct.name;
            item.brand = editedProduct.brand;
            item.stock = editedProduct.stock;
            item.price = editedProduct.price;
            found = true;
            break;
        }
    }

    if (!found) {
        system("cls");
        cerr << "Product dengan ID " << id << " tidak ditemukan!" << endl;
        return false;
    }

    json data = json::array();
    for (const auto &product : products) {
        json productJson;
        productJson["id"] = product.id;
        productJson["name"] = product.name;
        productJson["brand"] = product.brand;
        productJson["stock"] = product.stock;
        productJson["price"] = product.price;

        data.push_back(productJson);
    }

    ofstream outFile(directoryProduct);
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

bool DeleteProduct(int id){
    vector<Product> products = getAllProducts();
    bool found = false;

    for (auto product = products.begin(); product != products.end(); ++product) {
        if (product->id == id) {
            products.erase(product);
            found = true;
            break;
        }
    }

    if (!found) {
        system("cls");
        cerr << "Product dengan ID " << id << " tidak ditemukan!" << endl;
        return false;
    }

    json data;
    for (const auto& product : products) {
        data.push_back({
            {"id", product.id},
            {"name", product.name},
            {"brand", product.brand},
            {"stock", product.stock},
            {"price", product.price}
        });
    }

    ofstream file(directoryProduct);
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


bool UpdateProductStock(int id, int quantity) {
    vector<Product> products = getAllProducts();
    bool found = false;

    for(auto &item : products){
        if(item.id == id){
            item.id = id;
            item.stock -= quantity;
        }
    }

    json data = json::array();
    for (const auto &product : products) {
        json productJson;
        productJson["id"] = product.id;
        productJson["name"] = product.name;
        productJson["brand"] = product.brand;
        productJson["stock"] = product.stock;
        productJson["price"] = product.price;

        data.push_back(productJson);
    }

    ofstream outFile(directoryProduct);
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