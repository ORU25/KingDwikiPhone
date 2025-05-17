#ifndef PRODUCT_H
#define PRODUCT_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "../libs/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

extern string directoryProduct;


struct Product {
    int id;
    string name;
    string brand;
    int stock;
    int price;
};

int generateNewProductId(const vector<Product>& products);
vector<Product> getAllProducts();
Product getProduct(int &id);
bool AddProduct(Product &product);
bool EditProduct(int id, Product editedProduct);
bool DeleteProduct(int id);
bool UpdateProductStock(int id, int quantity);

#endif