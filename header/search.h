#ifndef SEARCH_H
#define SEARCH_H

#include "user.h"
#include "order.h"
#include "product.h"

bool searchUser(vector<User> &users, const string &username, User &result);
bool searchProduct(vector<Product> &products, const string &name, Product &result);
bool searchOrder(vector<Order> &orders, int id, Order &result);

#endif