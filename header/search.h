#ifndef SEARCH_H
#define SEARCH_H

#include "user.h"
#include "order.h"
#include "product.h"
#include <vector>

bool searchUser(std::vector<User> &users, const std::string &username, User &result);
bool searchProduct(std::vector<Product> &products, const std::string &name, Product &result);
bool searchOrder(std::vector<Order> &orders, int id, Order &result);

#endif