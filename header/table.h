#ifndef TABLE_H
#define TABLE_H

#include "user.h"
#include "order.h"
#include "product.h"

void displayUserTable(const vector<User> &users);
void displayProductTable(const vector<Product> &products);
void displayOrderItemTable(const vector<OrderItem> &orderItems, int indent = 2);
void displayOrderTable(const vector<Order> &orders);

#endif