#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "json.hpp"

using namespace std;

using json = nlohmann::json;

struct Product {
    int id;
    string name;
    string brand;
    int stock;
    int price;
};