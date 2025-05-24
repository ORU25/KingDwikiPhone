#ifndef SORT_H
#define SORT_H

#include <vector>
#include "user.h"
#include "order.h"
#include "product.h"

void quickSortUsers(std::vector<User> &users, int low, int high);
void quickSortProducts(std::vector<Product> &products, int low, int high);
void quickSortOrders(std::vector<Order> &orders, int low, int high);
void quickSortOrdersById(std::vector<Order> &orders, int low, int high);

#endif