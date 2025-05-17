#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include "crud/user.cpp"
#include "crud/product.cpp"
#include "crud/order.cpp"

using namespace std;

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

// Quick Sort untuk Product berdasarkan price (descending)
void quickSortProducts(vector<Product> &products, int low, int high)
{
    if (low < high)
    {
        int pivot = products[high].price;
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (products[j].price >= pivot)
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

// Fungsi untuk menampilkan user dalam bentuk tabel
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
void displayOrderItemTable(const vector<OrderItem> &orderItems, int indent = 2)
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

void AdminMenu(User &user);
void UserMenu(User &user);
void CrudUser();
void CrudProduct();
void CrudOrder(User &user);
void CreateOrder(User &user);

int main()
{
    system("cls");

    bool isLogin = false;
    int login_attempt = 3;
    int pilihanAwal = -1;
    User user;

    while (pilihanAwal != 0 && login_attempt > 0)
    {
        cout << "=================================" << endl;
        cout << "Selamat Datang di KING DWIKIPHONE" << endl;
        cout << "=================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihanAwal;

        system("cls");

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n"
                 << endl;
            continue;
        }

        if (pilihanAwal == 1)
        {
            cout << "=== Login ===" << endl;
            string username, password;
            bool loginSuccess = false;

            while (login_attempt > 0 && !loginSuccess)
            {
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                vector<User> users = getAllUsers();
                for (const auto &currentUser : users)
                {
                    if (currentUser.username == username && currentUser.password == password)
                    {
                        loginSuccess = true;
                        isLogin = true;
                        login_attempt = 3;
                        user = currentUser;
                        system("cls");
                        cout << "Login berhasil! Selamat datang, " << user.username << endl;
                        break;
                    }
                }

                if (!loginSuccess)
                {
                    login_attempt--;
                    system("cls");
                    if (login_attempt > 0)
                    {
                        cout << "Username atau password salah! Sisa percobaan: " << login_attempt << endl;
                    }
                    else
                    {
                        cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
                        return 0;
                    }
                }
            }
        }
        else if (pilihanAwal == 2)
        {
            cout << "=== Register ===" << endl;
            User newUser;

            // Validasi username unik
            bool usernameExists;
            do
            {
                usernameExists = false;
                cout << "Username: ";
                cin >> newUser.username;

                vector<User> users = getAllUsers();
                for (const auto &user : users)
                {
                    if (user.username == newUser.username)
                    {
                        system("cls");
                        cout << "Username sudah terdaftar! Silakan gunakan username lain." << endl;
                        usernameExists = true;
                        break;
                    }
                }
            } while (usernameExists);

            cout << "Password: ";
            cin >> newUser.password;

            // Set default role to "user" for new registrations
            newUser.role = "user";
            if (AddUser(newUser))
            {
                system("cls");
                cout << "Registrasi berhasil! Silakan login dengan akun baru Anda." << endl;
                continue;
            }
            else
            {
                system("cls");
                cout << "Registrasi gagal. Silakan coba lagi." << endl;
            }
        }
        else if (pilihanAwal == 0)
        {
            cout << "Program selesai!" << endl;
            return 0;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
        }

        if (isLogin)
        {
            if (user.role == "admin")
            {
                AdminMenu(user);
            }
            else if (user.role == "user")
            {
                UserMenu(user);
            }
        }
    }

    return 0;
}

void AdminMenu(User &user)
{
    int pilihan = -1;
    while (pilihan != 0)
    {
        cout << "=================================" << endl;
        cout << "Selamat Datang di KING DWIKIPHONE" << endl;
        cout << "=================================" << endl;
        cout << "Halo " << user.username << endl;
        cout << "=================================" << endl;
        cout << "1. Kelola user" << endl;
        cout << "2. Kelola produk" << endl;
        cout << "3. Kelola pesanan" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n"
                 << endl;
            continue;
        }

        if (pilihan == 1)
        {
            CrudUser();
        }
        else if (pilihan == 2)
        {
            CrudProduct();
        }
        else if (pilihan == 3)
        {
            CrudOrder(user);
        }
        else if (pilihan == 0)
        {
            bool login_attempt = 3;
            bool isLogin = false;
            cout << "Logout" << endl;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void UserMenu(User &user)
{
    int pilihan = -1;
    while (pilihan != 0)
    {
        cout << "=================================" << endl;
        cout << "Selamat Datang di KING DWIKIPHONE" << endl;
        cout << "=================================" << endl;
        cout << "Halo " << user.username << endl;
        cout << "=================================" << endl;
        cout << "1. Buat pesanan" << endl;
        cout << "2. Lihat history pesanan" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n"
                 << endl;
            continue;
        }

        if (pilihan == 1)
        {
            CreateOrder(user);
        }
        else if (pilihan == 2)
        {
            cout << "Lihat history pesanan" << endl;
        }
        else if (pilihan == 0)
        {
            bool login_attempt = 3;
            bool isLogin = false;
            cout << "Logout" << endl;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CrudUser()
{
    int pilihan = -1;
    while (pilihan != 0)
    {
        cout << "=================================" << endl;
        cout << "Kelola User" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah User" << endl;
        cout << "2. Tampilkan User" << endl;
        cout << "3. Ubah User" << endl;
        cout << "4. Hapus User" << endl;
        cout << "5. Cari User (berdasarkan username)" << endl;
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n"
                 << endl;
            continue;
        }

        if (pilihan == 1)
        {
            try
            {
                User user;
                cout << "Username: ";
                cin >> user.username;
                cout << "Password: ";
                cin >> user.password;
                cout << "Role: ";
                cin >> user.role;
                if (AddUser(user))
                {
                    system("cls");
                    cout << "User berhasil ditambahkan!" << endl;
                }
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (pilihan == 2)
        {
            vector<User> users = getAllUsers();
            if (!users.empty())
            {
                quickSortUsers(users, 0, users.size() - 1);
                displayUserTable(users);
            }
            else
            {
                cout << "Tidak ada user untuk ditampilkan!" << endl;
            }
        }
        else if (pilihan == 3)
        {
            int id;
            User editedUser;
            vector<User> users = getAllUsers();

            if (!users.empty())
            {
                quickSortUsers(users, 0, users.size() - 1);
                displayUserTable(users);
            }
            else
            {
                cout << "Tidak ada user untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID user: ";
            cin >> id;

            try
            {
                cout << "Username: ";
                cin >> editedUser.username;
                cout << "Password: ";
                cin >> editedUser.password;
                cout << "Role: ";
                cin >> editedUser.role;
                if (EditUser(id, editedUser))
                {
                    system("cls");
                    cout << "User Berhasil diubah!" << endl;
                }
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (pilihan == 4)
        {
            int id;
            vector<User> users = getAllUsers();

            if (!users.empty())
            {
                quickSortUsers(users, 0, users.size() - 1);
                displayUserTable(users);
            }
            else
            {
                cout << "Tidak ada user untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID user: ";
            cin >> id;

            try
            {
                if (DeleteUser(id))
                {
                    system("cls");
                    cout << "User Berhasil dihapus!" << endl;
                }
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (pilihan == 5)
        {
            string username;
            cout << "Masukkan username: ";
            cin >> username;
            User result;
            vector<User> users = getAllUsers();
            if (searchUser(users, username, result))
            {
                vector<User> singleUser = {result};
                cout << "User ditemukan:\n";
                displayUserTable(singleUser);
            }
            else
            {
                cout << "User tidak ditemukan!" << endl;
            }
        }
        else if (pilihan == 0)
        {
            cout << "Kembali" << endl;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CrudProduct()
{
    int pilihan = -1;
    while (pilihan != 0)
    {
        cout << "=================================" << endl;
        cout << "Kelola Produk" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Tampilkan Produk" << endl;
        cout << "3. Ubah Produk" << endl;
        cout << "4. Hapus Produk" << endl;
        cout << "5. Cari Produk (berdasarkan nama)" << endl;
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n"
                 << endl;
            continue;
        }

        if (pilihan == 1)
        {
            try
            {
                Product product;
                cout << "Name: ";
                cin >> product.name;
                cout << "Brand: ";
                cin >> product.brand;
                cout << "Stock: ";
                cin >> product.stock;
                cout << "Price: ";
                cin >> product.price;
                if (AddProduct(product))
                {
                    system("cls");
                    cout << "Product berhasil ditambahkan!" << endl;
                }
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (pilihan == 2)
        {
            vector<Product> products = getAllProducts();
            if (!products.empty())
            {
                quickSortProducts(products, 0, products.size() - 1);
                displayProductTable(products);
            }
            else
            {
                cout << "Tidak ada produk untuk ditampilkan!" << endl;
            }
        }
        else if (pilihan == 3)
        {
            int id;
            Product editedProduct;
            vector<Product> products = getAllProducts();

            if (!products.empty())
            {
                quickSortProducts(products, 0, products.size() - 1);
                displayProductTable(products);
            }
            else
            {
                cout << "Tidak ada produk untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID product: ";
            cin >> id;

            try
            {
                cout << "Name: ";
                cin >> editedProduct.name;
                cout << "Brand: ";
                cin >> editedProduct.brand;
                cout << "Stock: ";
                cin >> editedProduct.stock;
                cout << "Price: ";
                cin >> editedProduct.price;
                if (EditProduct(id, editedProduct))
                {
                    system("cls");
                    cout << "Product Berhasil diubah!" << endl;
                }
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (pilihan == 4)
        {
            int id;
            vector<Product> products = getAllProducts();

            if (!products.empty())
            {
                quickSortProducts(products, 0, products.size() - 1);
                displayProductTable(products);
            }
            else
            {
                cout << "Tidak ada produk untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID product: ";
            cin >> id;

            try
            {
                if (DeleteProduct(id))
                {
                    system("cls");
                    cout << "Product Berhasil dihapus!" << endl;
                }
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (pilihan == 5)
        {
            string name;
            cout << "Masukkan nama produk: ";
            cin >> name;
            Product result;
            vector<Product> products = getAllProducts();
            if (searchProduct(products, name, result))
            {
                vector<Product> singleProduct = {result};
                cout << "Produk ditemukan:\n";
                displayProductTable(singleProduct);
            }
            else
            {
                cout << "Produk tidak ditemukan!" << endl;
            }
        }
        else if (pilihan == 0)
        {
            cout << "Kembali" << endl;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CrudOrder(User &user)
{
    int pilihan = -1;
    while (pilihan != 0)
    {
        cout << "=================================" << endl;
        cout << "Kelola Pesanan" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah Pesanan" << endl;
        cout << "2. Tampilkan Pesanan" << endl;
        cout << "3. Verifikasi Pesanan" << endl;
        cout << "4. Cari Pesanan (berdasarkan ID)" << endl;
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n"
                 << endl;
            continue;
        }

        if (pilihan == 1)
        {
            CreateOrder(user);
        }
        else if (pilihan == 2)
        {
            vector<Order> orders = getAllOrders();
            if (!orders.empty())
            {
                quickSortOrders(orders, 0, orders.size() - 1);
                displayOrderTable(orders);
            }
            else
            {
                cout << "Tidak ada pesanan untuk ditampilkan!" << endl;
            }
        }
        else if (pilihan == 3)
        {
            cout << "Verifikasi Pesanan (belum diimplementasikan)" << endl;
        }
        else if (pilihan == 4)
        {
            int id;
            cout << "Masukkan ID pesanan: ";
            cin >> id;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Input tidak valid! Harus angka.\n"
                     << endl;
                continue;
            }
            Order result;
            vector<Order> orders = getAllOrders();
            if (searchOrder(orders, id, result))
            {
                vector<Order> singleOrder = {result};
                cout << "Pesanan ditemukan:\n";
                displayOrderTable(singleOrder);
            }
            else
            {
                cout << "Pesanan tidak ditemukan!" << endl;
            }
        }
        else if (pilihan == 0)
        {
            cout << "Kembali" << endl;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CreateOrder(User &user)
{
    bool pesan = true;
    Order order;
    order.total_price = 0;
    order.user_id = user.id;

    vector<Product> products = getAllProducts();

    while (pesan)
    {
        cout << "\nDaftar Produk:\n";
        if (!products.empty())
        {
            quickSortProducts(products, 0, products.size() - 1);
            displayProductTable(products);
        }
        else
        {
            cout << "Tidak ada produk untuk ditampilkan!" << endl;
        }

        cout << "\nPilih ID product yang ingin dipesan: ";
        int pilihan;
        cin >> pilihan;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n"
                 << endl;
            continue;
        }

        auto it = find_if(products.begin(), products.end(), [pilihan](const Product &p)
                          { return p.id == pilihan; });

        if (it == products.end() || it->stock == 0)
        {
            system("cls");
            cout << "Produk dengan ID " << pilihan << " tidak ditemukan atau stok habis.\n";
            continue;
        }

        Product &product = *it;

        bool sudahDipesan = false;
        for (const auto &item : order.products)
        {
            if (item.product_id == product.id)
            {
                sudahDipesan = true;
                break;
            }
        }

        if (sudahDipesan)
        {
            system("cls");
            cout << "Produk ini sudah ditambahkan ke pesanan sebelumnya. Tidak dapat dipesan dua kali.\n";
            continue;
        }

        cout << "Masukkan quantity: ";
        int quantity;
        cin >> quantity;

        if (cin.fail() || quantity <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Quantity tidak boleh angka negatif.\n";
            continue;
        }

        if (quantity > product.stock)
        {
            system("cls");
            cout << "Maaf, stok " << product.name << " tidak mencukupi. Stok tersedia: " << product.stock << endl;
            continue;
        }

        product.stock -= quantity;

        OrderItem orderItem;
        orderItem.product_id = product.id;
        orderItem.name = product.name;
        orderItem.quantity = quantity;
        orderItem.price = product.price;
        order.products.push_back(orderItem);

        order.total_price += orderItem.price * orderItem.quantity;

        cout << "Produk berhasil ditambahkan ke pesanan." << endl;

        char tambah;
        while (true)
        {
            cout << "Tambah produk lagi? (y/n): ";
            cin >> tambah;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (tambah == 'y' || tambah == 'Y')
            {
                break;
            }
            else if (tambah == 'n' || tambah == 'N')
            {
                pesan = false;
                break;
            }
            else
            {
                system("cls");
                cout << "Input tidak valid! Masukkan hanya 'y' atau 'n'.\n";
            }
        }
        system("cls");
    }

    if (!order.products.empty())
    {
        cout << "Detail Pesanan:\n";
        cout << "Total Price: " << order.total_price << "\n";
        displayOrderItemTable(order.products, 0); // Tabel OrderItem tanpa indentasi

        while (true)
        {
            cout << "Apakah pesanan sudah benar? (y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (confirm == 'y' || confirm == 'Y')
            {
                if (AddOrder(order))
                {
                    system("cls");
                    cout << "Pesanan berhasil ditambahkan." << endl;
                    for (auto &item : order.products)
                    {
                        UpdateProductStock(item.product_id, item.quantity);
                    }
                }
                else
                {
                    system("cls");
                    cout << "Pesanan gagal ditambahkan." << endl;
                }
                break;
            }
            else if (confirm == 'n' || confirm == 'N')
            {
                break;
            }
            else
            {
                system("cls");
                cout << "Input tidak valid! Masukkan hanya 'y' atau 'n'.\n";
            }
        }
    }
}