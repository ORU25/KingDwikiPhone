#ifndef SORT_H
#define SORT_H

#include "user.h"
#include "order.h"
#include "product.h"

void quickSortUsers(vector<User> &users, int low, int high);
void quickSortProducts(vector<Product> &products, int low, int high);
void quickSortOrders(vector<Order> &orders, int low, int high);

#endif