#include <algorithm>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include "../header/user.h"
#include "../header/order.h"
#include "../header/product.h"
#include "../header/table.h"
#include "../header/search.h"
#include "../header/sort.h"

using namespace std;

void AdminMenu(User &user);
void UserMenu(User &user);
void CrudUser(User &user);
void CrudProduct();
void CrudOrder(User &user);
void CreateOrder(User &user);

int main() {
    system("cls");

    bool isLogin = false;
    int login_attempt = 3;
    int pilihanAwal = -1;
    User user;

    while (pilihanAwal != 0 && login_attempt > 0) {
        cout << "=================================" << endl;
        cout << "Selamat Datang di KING DWIKIPHONE" << endl;
        cout << "=================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihanAwal;

        system("cls");

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if (pilihanAwal == 1) {
            cout << "=== Login ===" << endl;
            string username, password;
            bool loginSuccess = false;

            while (login_attempt > 0 && !loginSuccess) {
                cin.ignore();
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                
                vector<User> users = getAllUsers();
                for (const auto &currentUser : users) {
                    if (currentUser.username == username && currentUser.password == password) {
                        loginSuccess = true;
                        isLogin = true;
                        login_attempt = 3;
                        user = currentUser;
                        system("cls");
                        cout << "Login berhasil! Selamat datang, " << user.username << endl;
                        break;
                    }
                }

                if (!loginSuccess) {
                    login_attempt--;
                    system("cls");
                    if (login_attempt > 0) {
                        cout << "Username atau password salah! Sisa percobaan: " << login_attempt << endl;
                    } else {
                        cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
                        return 0;
                    }
                }
            }
        } else if (pilihanAwal == 2) {
            cout << "=== Register ===" << endl;
            User newUser;

            bool usernameExists;
            do {
                usernameExists = false;
                cout << "Username: ";
                cin >> newUser.username;

                vector<User> users = getAllUsers();
                for (const auto &user : users) {
                    if (user.username == newUser.username) {
                        system("cls");
                        cout << "Username sudah terdaftar! Silakan gunakan username lain." << endl;
                        usernameExists = true;
                        break;
                    }
                }
            } while (usernameExists);

            cout << "Password: ";
            cin >> newUser.password;

            newUser.role = "user";
            if (AddUser(newUser)) {
                system("cls");
                cout << "Registrasi berhasil! Silakan login dengan akun baru Anda." << endl;
                continue;
            } else {
                system("cls");
                cout << "Registrasi gagal. Silakan coba lagi." << endl;
            }
        } else if (pilihanAwal == 0) {
            cout << "Program selesai!" << endl;
            return 0;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }

        if (isLogin) {
            if (user.role == "admin") {
                AdminMenu(user);
            } else if (user.role == "user") {
                UserMenu(user);
            }
        }
    }

    return 0;
}

void AdminMenu(User &user) {
    int pilihan = -1;
    while (pilihan != 0) {
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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
            system("cls");
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if (pilihan == 1) {
            CrudUser(user);
        } else if (pilihan == 2) {
            CrudProduct();
        } else if (pilihan == 3) {
            CrudOrder(user);
        } else if (pilihan == 0) {
            cout << "Logout" << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void UserMenu(User &user) {
    int pilihan = -1;
    while (pilihan != 0) {
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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
            system("cls");
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if (pilihan == 1) {
            CreateOrder(user);
        } else if (pilihan == 2) {
            cout << "Lihat history pesanan" << endl;
            vector<Order> userOrders = getOrdersByUserId(user.id);
            if (!userOrders.empty()) {
                displayOrderTable(userOrders);
                while (true) {
                    cout << "Tampilkan detail produk dalam pesanan? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (confirm == 'y' || confirm == 'Y') {
                        cout << "Masukkan ID pesanan: ";
                        int id;
                        cin >> id;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            system("cls");
                            cout << "Input tidak valid! Harus angka.\n" << endl;
                            continue;
                        }
                        Order result = {0};

                        for (auto &item : userOrders) {
                            if (item.id == id) {
                                result = item;
                                break;
                            }
                        }

                        if (result.id != 0) {
                            cout << "=================================" << endl;
                            cout << "Pesanan ID: " << result.id << endl;
                            cout << "User ID: " << result.user_id << endl;
                            cout << "Total Price: " << result.total_price << endl;
                            cout << "Status: " << result.status << endl;
                            cout << "=================================" << endl;
                            cout << "Detail Produk dalam Pesanan:\n";
                            displayOrderItemTable(result.products, 0);
                        } else {
                            cout << "Detail pesanan tidak ditemukan!" << endl;
                        }
                    } else if (confirm == 'n' || confirm == 'N') {
                        system("cls");
                        break;
                    } else {
                        system("cls");
                        cout << "Input tidak valid! Masukkan hanya 'y' atau 'n'.\n";
                    }
                }
            } else {
                cout << "Tidak ada pesanan untuk ditampilkan!" << endl;
            }
        } else if (pilihan == 0) {
            cout << "Logout" << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CrudUser(User &user) {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "=================================" << endl;
        cout << "Kelola User" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah User" << endl;
        cout << "2. Tampilkan User" << endl;
        cout << "3. Ubah User" << endl;
        cout << "4. Hapus User" << endl;
        cout << "5. Cari User (berdasarkan username)" << endl;
        cout << "6. Urutkan User (berdasarkan username)" << endl;
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if (pilihan == 1) {
            try {
                cin.ignore();
                User newUser;
                cout << "Username: ";
                getline(cin, newUser.username);
                cout << "Password: ";
                getline(cin, newUser.password);
                cout << "Role: ";
                cin >> newUser.role;

                if (AddUser(newUser)) {
                    system("cls");
                    cout << "User berhasil ditambahkan!" << endl;
                }
            } catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (pilihan == 2) {
            vector<User> users = getAllUsers();
            if (!users.empty()) {
                displayUserTable(users);
            } else {
                cout << "Tidak ada user untuk ditampilkan!" << endl;
            }
        } else if (pilihan == 3) {
            int id;
            User editedUser;
            vector<User> users = getAllUsers();

            if (!users.empty()) {
                displayUserTable(users);
            } else {
                cout << "Tidak ada user untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID user: ";
            cin >> id;

            if (id == user.id) {
                system("cls");
                cout << "Anda tidak dapat mengubah data diri sendiri!" << endl;
                continue;
            }

            bool userFound = false;

            for(auto &item : users) {
                if(item.id == id) {
                    userFound = true;
                }
            }

            if(!userFound) {
                system("cls");
                cout << "User dengan ID " << id << " tidak ditemukan!" << endl;
                continue;
            }

            try {
                cin.ignore();
                cout << "*kosongkan untuk tidak mengubah*" << endl;
                cout << "Username: ";
                getline(cin, editedUser.username);
                cout << "Password: ";
                getline(cin, editedUser.password);
                cout << "Role: ";
                getline(cin, editedUser.role);
                
                if (EditUser(id, editedUser)) {
                    system("cls");
                    cout << "User Berhasil diubah!" << endl;
                }
            } catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (pilihan == 4) {
            int id;
            vector<User> users = getAllUsers();

            if (!users.empty()) {
                displayUserTable(users);
            } else {
                cout << "Tidak ada user untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID user: ";
            cin >> id;

            try {
                if (DeleteUser(id)) {
                    system("cls");
                    cout << "User Berhasil dihapus!" << endl;
                }
            } catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (pilihan == 5) {
            string username;
            cout << "Masukkan username: ";
            cin >> username;
            User result;
            vector<User> users = getAllUsers();
            if (!users.empty()) {
                quickSortUsers(users, 0, users.size() - 1); // Urutkan berdasarkan username
                if (searchUser(users, username, result)) {
                    vector<User> singleUser = {result};
                    cout << "User ditemukan:\n";
                    displayUserTable(singleUser);
                } else {
                    cout << "User tidak ditemukan!" << endl;
                }
            } else {
                cout << "Tidak ada user untuk dicari!" << endl;
            }
        } else if (pilihan == 6) {
            vector<User> users = getAllUsers();
            if (!users.empty()) {
                cout << "Sebelum sorting:\n";
                displayUserTable(users);
                quickSortUsers(users, 0, users.size() - 1);
                cout << "Setelah sorting:\n";
                displayUserTable(users);
                cout << "User berhasil diurutkan berdasarkan username!" << endl;
            } else {
                cout << "Tidak ada user untuk diurutkan!" << endl;
            }
        } else if (pilihan == 0) {
            cout << "Kembali" << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CrudProduct() {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "=================================" << endl;
        cout << "Kelola Produk" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Tampilkan Produk" << endl;
        cout << "3. Ubah Produk" << endl;
        cout << "4. Hapus Produk" << endl;
        cout << "5. Cari Produk (berdasarkan nama)" << endl;
        cout << "6. Urutkan Produk (berdasarkan nama)" << endl;
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if (pilihan == 1) {
            try {
                cin.ignore();
                Product product;
                cout << "Name: ";
                getline(cin, product.name);
                cout << "Brand: ";
                getline(cin, product.brand);
                cout << "Stock: ";
                cin >> product.stock;
                if(cin.fail() || product.stock < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "Input tidak valid! Stock harus angka positif.\n" << endl;
                    continue;
                }
                
                cout << "Price: ";
                cin >> product.price;
                if(cin.fail() || product.price < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "Input tidak valid! Price harus angka positif.\n" << endl;
                    continue;
                }
                
                if (AddProduct(product)) {
                    system("cls");
                    cout << "Product berhasil ditambahkan!" << endl;
                }
            } catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (pilihan == 2) {
            vector<Product> products = getAllProducts();
            if (!products.empty()) {
                displayProductTable(products);
            } else {
                cout << "Tidak ada produk untuk ditampilkan!" << endl;
            }
        } else if (pilihan == 3) {
            int id;
            Product editedProduct;
            vector<Product> products = getAllProducts();

            if (!products.empty()) {
                displayProductTable(products);
            } else {
                cout << "Tidak ada produk untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID product: ";
            cin >> id;

            bool productFound = false;

            for (const auto &product : products) {
                if (product.id == id) {
                    editedProduct = product;
                    productFound = true;
                    break;
                }
            }
            if (!productFound) {
                system("cls");
                cout << "Product dengan ID " << id << " tidak ditemukan!" << endl;
                continue;
            }

            try {
                cin.ignore();
                cout << "*kosongkan untuk tidak mengubah*" << endl;
                cout << "Name: ";
                getline(cin, editedProduct.name);
                cout << "Brand: ";
                getline(cin, editedProduct.brand);
                cout << "*Jika stock dan harga tidak diubah, masukkan -1 untuk tidak mengubahnya.*" << endl;
                cout << "Stock: ";
                cin >> editedProduct.stock;
                cout << "Price: ";
                cin >> editedProduct.price;
                
                if(editedProduct.stock < -1 || editedProduct.price < -1) {
                    system("cls");
                    cout << "Stock dan harga tidak boleh negatif!" << endl;
                    continue;
                }

                if (EditProduct(id, editedProduct)) {
                    system("cls");
                    cout << "Product Berhasil diubah!" << endl;
                }
            } catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (pilihan == 4) {
            int id;
            vector<Product> products = getAllProducts();

            if (!products.empty()) {
                displayProductTable(products);
            } else {
                cout << "Tidak ada produk untuk ditampilkan!" << endl;
            }

            cout << "\nMasukkan ID product: ";
            cin >> id;

            try {
                if (DeleteProduct(id)) {
                    system("cls");
                    cout << "Product Berhasil dihapus!" << endl;
                }
            } catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (pilihan == 5) {
            string name;
            cout << "Masukkan nama produk: ";
            cin >> name;
            Product result;
            vector<Product> products = getAllProducts();
            if (!products.empty()) {
                quickSortProducts(products, 0, products.size() - 1); // Urutkan berdasarkan name
                if (searchProduct(products, name, result)) {
                    vector<Product> singleProduct = {result};
                    cout << "Produk ditemukan:\n";
                    displayProductTable(singleProduct);
                } else {
                    cout << "Produk tidak ditemukan!" << endl;
                }
            } else {
                cout << "Tidak ada produk untuk dicari!" << endl;
            }
        } else if (pilihan == 6) {
            vector<Product> products = getAllProducts();
            if (!products.empty()) {
                cout << "Sebelum sorting:\n";
                displayProductTable(products);
                quickSortProducts(products, 0, products.size() - 1);
                cout << "Setelah sorting:\n";
                displayProductTable(products);
                cout << "Produk berhasil diurutkan berdasarkan nama!" << endl;
            } else {
                cout << "Tidak ada produk untuk diurutkan!" << endl;
            }
        } else if (pilihan == 0) {
            cout << "Kembali" << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CrudOrder(User &user) {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "=================================" << endl;
        cout << "Kelola Pesanan" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah Pesanan" << endl;
        cout << "2. Tampilkan Pesanan" << endl;
        cout << "3. Verifikasi Pesanan" << endl;
        cout << "4. Cari Pesanan (berdasarkan ID)" << endl;
        cout << "5. Urutkan Pesanan (berdasarkan total price)" << endl;
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        if (pilihan == 1) {
            CreateOrder(user);
        } else if (pilihan == 2) {
            vector<Order> orders = getAllOrders();
            if (!orders.empty()) {
                displayOrderTable(orders);
                while (true) {
                    cout << "Tampilkan detail produk dalam pesanan? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (confirm == 'y' || confirm == 'Y') {
                        cout << "Masukkan ID pesanan: ";
                        int id;
                        cin >> id;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            system("cls");
                            cout << "Input tidak valid! Harus angka.\n" << endl;
                            continue;
                        }
                        Order result = {0};

                        for (auto &item : orders) {
                            if (item.id == id) {
                                result = item;
                                break;
                            }
                        }

                        if (result.id != 0) {
                            cout << "=================================" << endl;
                            cout << "Pesanan ID: " << result.id << endl;
                            cout << "User ID: " << result.user_id << endl;
                            cout << "Total Price: " << result.total_price << endl;
                            cout << "Status: " << result.status << endl;
                            cout << "=================================" << endl;
                            cout << "Detail Produk dalam Pesanan:\n";
                            displayOrderItemTable(result.products, 0);
                        } else {
                            cout << "Detail pesanan tidak ditemukan!" << endl;
                        }
                    } else if (confirm == 'n' || confirm == 'N') {
                        system("cls");
                        break;
                    } else {
                        system("cls");
                        cout << "Input tidak valid! Masukkan hanya 'y' atau 'n'.\n";
                    }
                }
            } else {
                cout << "Tidak ada pesanan untuk ditampilkan!" << endl;
            }
        } else if (pilihan == 3) {
            vector<Order> orders = getAllOrders();
            if (!orders.empty()) {
                vector<Order> pendingOrders;
                for (auto &order : orders) {
                    if (order.status == "pending") {
                        pendingOrders.push_back(order);
                    }
                }
                displayOrderTable(pendingOrders);
                cout << "\nMasukkan ID pesanan yang ingin diverifikasi: ";
                int id;
                cin >> id;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "Input tidak valid! Harus angka.\n" << endl;
                    continue;
                }

                Order order = {0};
                for (auto &item : pendingOrders) {
                    if (item.id == id) {
                        order = item;
                        break;
                    }
                }

                if (order.id != 0) {
                    int pilihanVerify = -1;
                    while (pilihanVerify != 0) {
                        system("cls");
                        cout << "Pesanan ID: " << order.id << endl;
                        cout << "User ID: " << order.user_id << endl;
                        cout << "Total Price: " << order.total_price << endl;
                        cout << "Status: " << order.status << endl;

                        displayOrderItemTable(order.products, 0);

                        cout << "\nVerifikasi Pesanan:" << endl;
                        cout << "1. Accept" << endl;
                        cout << "2. Reject" << endl;
                        cout << "0. Kembali" << endl;
                        cout << "Pilih opsi: ";

                        cin >> pilihanVerify;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            system("cls");
                            cout << "Input tidak valid! Harus angka.\n" << endl;
                            continue;
                        }
                        system("cls");
                        if (pilihanVerify == 1) {
                            if (verifyOrder(id, "accepted")) {
                                cout << "Pesanan berhasil diverifikasi!" << endl;
                            } else {
                                cout << "Pesanan gagal diverifikasi!" << endl;
                            }
                            break;
                        } else if (pilihanVerify == 2) {
                            if (verifyOrder(id, "rejected")) {
                                cout << "Pesanan berhasil ditolak!" << endl;
                            } else {
                                cout << "Pesanan gagal ditolak!" << endl;
                            }
                            break;
                        } else if (pilihanVerify == 0) {
                            system("cls");
                        } else {
                            system("cls");
                            cout << "Input tidak valid!" << endl;
                        }
                    }
                } else {
                    system("cls");
                    cout << "Pesanan dengan ID " << id << " tidak ditemukan!" << endl;
                }
            } else {
                cout << "Tidak ada pesanan untuk ditampilkan!" << endl;
            }
        } else if (pilihan == 4) {
            int id;
            cout << "Masukkan ID pesanan: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Input tidak valid! Harus angka.\n" << endl;
                continue;
            }
            Order result;
            vector<Order> orders = getAllOrders();
            if (!orders.empty()) {
                quickSortOrdersById(orders, 0, orders.size() - 1); // Urutkan berdasarkan id
                if (searchOrder(orders, id, result)) {
                    vector<Order> singleOrder = {result};
                    cout << "Pesanan ditemukan:\n";
                    displayOrderTable(singleOrder);
                    cout << "\nDetail Produk dalam Pesanan:\n";
                    displayOrderItemTable(result.products, 0);
                } else {
                    cout << "Pesanan tidak ditemukan!" << endl;
                }
            } else {
                cout << "Tidak ada pesanan untuk dicari!" << endl;
            }
        } else if (pilihan == 5) {
            vector<Order> orders = getAllOrders();
            if (!orders.empty()) {
                cout << "Sebelum sorting:\n";
                displayOrderTable(orders);
                quickSortOrders(orders, 0, orders.size() - 1);
                cout << "Setelah sorting:\n";
                displayOrderTable(orders);
                cout << "Pesanan berhasil diurutkan berdasarkan total price!" << endl;
            } else {
                cout << "Tidak ada pesanan untuk diurutkan!" << endl;
            }
        } else if (pilihan == 0) {
            cout << "Kembali" << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void CreateOrder(User &user) {
    bool pesan = true;
    Order order;
    order.total_price = 0;
    order.user_id = user.id;

    vector<Product> products = getAllProducts();

    while (pesan) {
        cout << "\nDaftar Produk:\n";
        if (!products.empty()) {
            displayProductTable(products);
        } else {
            cout << "Tidak ada produk untuk ditampilkan!" << endl;
        }

        cout << "\nPilih ID product yang ingin dipesan: ";
        int pilihan;
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Harus angka.\n" << endl;
            continue;
        }

        auto it = find_if(products.begin(), products.end(), [pilihan](const Product &p) { return p.id == pilihan; });

        if (it == products.end() || it->stock == 0) {
            system("cls");
            cout << "Produk dengan ID " << pilihan << " tidak ditemukan atau stok habis.\n";
            continue;
        }

        Product &product = *it;

        bool sudahDipesan = false;
        for (const auto &item : order.products) {
            if (item.product_id == product.id) {
                sudahDipesan = true;
                break;
            }
        }

        if (sudahDipesan) {
            system("cls");
            cout << "Produk ini sudah ditambahkan ke pesanan sebelumnya. Tidak dapat dipesan dua kali.\n";
            continue;
        }

        cout << "Masukkan quantity: ";
        int quantity;
        cin >> quantity;

        if (cin.fail() || quantity <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid! Quantity tidak boleh angka negatif.\n";
            continue;
        }

        if (quantity > product.stock) {
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
        while (true) {
            cout << "Tambah produk lagi? (y/n): ";
            cin >> tambah;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (tambah == 'y' || tambah == 'Y') {
                break;
            } else if (tambah == 'n' || tambah == 'N') {
                pesan = false;
                break;
            } else {
                system("cls");
                cout << "Input tidak valid! Masukkan hanya 'y' atau 'n'.\n";
            }
        }
        system("cls");
    }

    if (!order.products.empty()) {
        cout << "Detail Pesanan:\n";
        cout << "Total Price: " << order.total_price << "\n";
        displayOrderItemTable(order.products, 0);

        while (true) {
            cout << "Apakah pesanan sudah benar? (y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (confirm == 'y' || confirm == 'Y') {
                if (AddOrder(order)) {
                    system("cls");
                    cout << "Pesanan berhasil ditambahkan." << endl;
                    for (auto &item : order.products) {
                        UpdateProductStock(item.product_id, item.quantity);
                    }
                } else {
                    system("cls");
                    cout << "Pesanan gagal ditambahkan." << endl;
                }
                break;
            } else if (confirm == 'n' || confirm == 'N') {
                break;
            } else {
                system("cls");
                cout << "Input tidak valid! Masukkan hanya 'y' atau 'n'.\n";
            }
        }
    }
}