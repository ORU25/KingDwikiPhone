#include "../header/sort.h"
#include <algorithm>

// Quick Sort untuk User berdasarkan username (ascending)
void quickSortUsers(vector<User> &users, int low, int high)
{
    if (low < high)
    {
        string pivot = users[high].username;
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (users[j].username <= pivot)
            {
                i++;
                swap(users[i], users[j]);
            }
        }
        swap(users[i + 1], users[high]);

        int pi = i + 1;
        quickSortUsers(users, low, pi - 1);
        quickSortUsers(users, pi + 1, high);
    }
}

// Quick Sort untuk Product berdasarkan name (ascending)
void quickSortProducts(vector<Product> &products, int low, int high)
{
    if (low < high)
    {
        string pivot = products[high].name;
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (products[j].name <= pivot)
            {
                i++;
                swap(products[i], products[j]);
            }
        }
        swap(products[i + 1], products[high]);

        int pi = i + 1;
        quickSortProducts(products, low, pi - 1);
        quickSortProducts(products, pi + 1, high);
    }
}

// Quick Sort untuk Order berdasarkan total_price (descending)
void quickSortOrders(vector<Order> &orders, int low, int high)
{
    if (low < high)
    {
        int pivot = orders[high].total_price;
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (orders[j].total_price >= pivot)
            {
                i++;
                swap(orders[i], orders[j]);
            }
        }
        swap(orders[i + 1], orders[high]);

        int pi = i + 1;
        quickSortOrders(orders, low, pi - 1);
        quickSortOrders(orders, pi + 1, high);
    }
}