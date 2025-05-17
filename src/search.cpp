#include "../header/search.h"

// Search User berdasarkan username (case-sensitive)
bool searchUser(vector<User> &users, const string &username, User &result)
{
    for (const auto &user : users)
    {
        if (user.username == username)
        {
            result = user;
            return true;
        }
    }
    return false;
}

// Search Product berdasarkan name (case-sensitive)
bool searchProduct(vector<Product> &products, const string &name, Product &result)
{
    for (const auto &product : products)
    {
        if (product.name == name)
        {
            result = product;
            return true;
        }
    }
    return false;
}

// Search Order berdasarkan id
bool searchOrder(vector<Order> &orders, int id, Order &result)
{
    for (const auto &order : orders)
    {
        if (order.id == id)
        {
            result = order;
            return true;
        }
    }
    return false;
}
