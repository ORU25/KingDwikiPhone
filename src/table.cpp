#include "../header/table.h"

void displayUserTable(const vector<User> &users)
{
    if (users.empty())
    {
        cout << "Tidak ada user untuk ditampilkan!" << endl;
        return;
    }

    // Lebar kolom
    const int idWidth = 5;
    const int usernameWidth = 15;
    const int passwordWidth = 15;
    const int roleWidth = 10;

    // Header tabel
    cout << "+" << string(idWidth, '-') << "+" << string(usernameWidth, '-') << "+"
         << string(passwordWidth, '-') << "+" << string(roleWidth, '-') << "+" << endl;
    cout << "|" << left << setw(idWidth) << "ID" << "|"
         << setw(usernameWidth) << "Username" << "|"
         << setw(passwordWidth) << "Password" << "|"
         << setw(roleWidth) << "Role" << "|" << endl;
    cout << "+" << string(idWidth, '-') << "+" << string(usernameWidth, '-') << "+"
         << string(passwordWidth, '-') << "+" << string(roleWidth, '-') << "+" << endl;

    // Data user
    for (const auto &user : users)
    {
        cout << "|" << left << setw(idWidth) << user.id << "|"
             << setw(usernameWidth) << user.username.substr(0, usernameWidth - 1) << "|"
             << setw(passwordWidth) << user.password.substr(0, passwordWidth - 1) << "|"
             << setw(roleWidth) << user.role.substr(0, roleWidth - 1) << "|" << endl;
    }

    // Footer tabel
    cout << "+" << string(idWidth, '-') << "+" << string(usernameWidth, '-') << "+"
         << string(passwordWidth, '-') << "+" << string(roleWidth, '-') << "+" << endl;
}

// Fungsi untuk menampilkan produk dalam bentuk tabel
void displayProductTable(const vector<Product> &products)
{
    if (products.empty())
    {
        cout << "Tidak ada produk untuk ditampilkan!" << endl;
        return;
    }

    // Lebar kolom
    const int idWidth = 5;
    const int nameWidth = 20;
    const int brandWidth = 15;
    const int stockWidth = 8;
    const int priceWidth = 10;

    // Header tabel
    cout << "+" << string(idWidth, '-') << "+" << string(nameWidth, '-') << "+"
         << string(brandWidth, '-') << "+" << string(stockWidth, '-') << "+"
         << string(priceWidth, '-') << "+" << endl;
    cout << "|" << left << setw(idWidth) << "ID" << "|"
         << setw(nameWidth) << "Name" << "|"
         << setw(brandWidth) << "Brand" << "|"
         << setw(stockWidth) << "Stock" << "|"
         << setw(priceWidth) << "Price" << "|" << endl;
    cout << "+" << string(idWidth, '-') << "+" << string(nameWidth, '-') << "+"
         << string(brandWidth, '-') << "+" << string(stockWidth, '-') << "+"
         << string(priceWidth, '-') << "+" << endl;

    // Data produk
    for (const auto &product : products)
    {
        cout << "|" << left << setw(idWidth) << product.id << "|"
             << setw(nameWidth) << product.name.substr(0, nameWidth - 1) << "|"
             << setw(brandWidth) << product.brand.substr(0, brandWidth - 1) << "|"
             << setw(stockWidth) << product.stock << "|"
             << setw(priceWidth) << product.price << "|" << endl;
    }

    // Footer tabel
    cout << "+" << string(idWidth, '-') << "+" << string(nameWidth, '-') << "+"
         << string(brandWidth, '-') << "+" << string(stockWidth, '-') << "+"
         << string(priceWidth, '-') << "+" << endl;
}

// Fungsi untuk menampilkan detail OrderItem dalam bentuk tabel
void displayOrderItemTable(const vector<OrderItem> &orderItems, int indent)
{
    if (orderItems.empty())
    {
        cout << string(indent, ' ') << "Tidak ada item pesanan!" << endl;
        return;
    }

    // Lebar kolom
    const int productIdWidth = 10;
    const int nameWidth = 20;
    const int quantityWidth = 10;
    const int priceWidth = 10;

    // Header tabel
    cout << string(indent, ' ') << "+" << string(productIdWidth, '-') << "+"
         << string(nameWidth, '-') << "+" << string(quantityWidth, '-') << "+"
         << string(priceWidth, '-') << "+" << endl;
    cout << string(indent, ' ') << "|" << left << setw(productIdWidth) << "Product ID" << "|"
         << setw(nameWidth) << "Name" << "|"
         << setw(quantityWidth) << "Quantity" << "|"
         << setw(priceWidth) << "Price" << "|" << endl;
    cout << string(indent, ' ') << "+" << string(productIdWidth, '-') << "+"
         << string(nameWidth, '-') << "+" << string(quantityWidth, '-') << "+"
         << string(priceWidth, '-') << "+" << endl;

    // Data OrderItem
    for (const auto &item : orderItems)
    {
        cout << string(indent, ' ') << "|" << left << setw(productIdWidth) << item.product_id << "|"
             << setw(nameWidth) << item.name.substr(0, nameWidth - 1) << "|"
             << setw(quantityWidth) << item.quantity << "|"
             << setw(priceWidth) << item.price << "|" << endl;
    }

    // Footer tabel
    cout << string(indent, ' ') << "+" << string(productIdWidth, '-') << "+"
         << string(nameWidth, '-') << "+" << string(quantityWidth, '-') << "+"
         << string(priceWidth, '-') << "+" << endl;
}

// Fungsi untuk menampilkan pesanan dalam bentuk tabel
void displayOrderTable(const vector<Order> &orders)
{
    if (orders.empty())
    {
        cout << "Tidak ada pesanan untuk ditampilkan!" << endl;
        return;
    }

    // Lebar kolom
    const int idWidth = 5;
    const int userIdWidth = 10;
    const int totalPriceWidth = 12;
    const int statusWidth = 15;

    // Header tabel
    cout << "+" << string(idWidth, '-') << "+" << string(userIdWidth, '-') << "+"
         << string(totalPriceWidth, '-') << "+" << string(statusWidth, '-') << "+" << endl;
    cout << "|" << left << setw(idWidth) << "ID" << "|"
         << setw(userIdWidth) << "User ID" << "|"
         << setw(totalPriceWidth) << "Total Price" << "|"
         << setw(statusWidth) << "Status" << "|" << endl;
    cout << "+" << string(idWidth, '-') << "+" << string(userIdWidth, '-') << "+"
         << string(totalPriceWidth, '-') << "+" << string(statusWidth, '-') << "+" << endl;

    // Data pesanan
    for (const auto &order : orders)
    {
        cout << "|" << left << setw(idWidth) << order.id << "|"
             << setw(userIdWidth) << order.user_id << "|"
             << setw(totalPriceWidth) << order.total_price << "|"
             << setw(statusWidth) << order.status.substr(0, statusWidth - 1) << "|" << endl;
        // Tabel detail OrderItem
        displayOrderItemTable(order.products, 2);
    }

    // Footer tabel
    cout << "+" << string(idWidth, '-') << "+" << string(userIdWidth, '-') << "+"
         << string(totalPriceWidth, '-') << "+" << string(statusWidth, '-') << "+" << endl;
}
