#include <iostream>

#include "crud/user.cpp"
#include "crud/product.cpp"
#include "crud/order.cpp"

using namespace std;

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

        // Tangani input bukan integer
        if (cin.fail())
        {
            cin.clear();  // Reset status error
            cin.ignore(); // Buang karakter sisa
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
                        user = currentUser; // Update variabel user utama dengan data user yang login
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
                // Kembali ke menu utama
                continue; // Langsung lanjut ke iterasi berikutnya (kembali ke menu login/register)
            }
            else
            {
                system("cls");
                cout << "Registrasi gagal. Silakan coba lagi." << endl;
            }
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

        // Tangani input bukan integer
        if (cin.fail())
        {
            cin.clear();  // Reset status error
            cin.ignore(); // Buang karakter sisa
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

        // Tangani input bukan integer
        if (cin.fail())
        {
            cin.clear();  // Reset status error
            cin.ignore(); // Buang karakter sisa
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
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail())
        {
            cin.clear();  // Reset status error
            cin.ignore(); // Buang karakter sisa
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

            for (const auto &user : users)
            {
                cout << "ID: " << user.id
                     << ", Username: " << user.username
                     << ", Password: " << user.password
                     << ", Role: " << user.role << endl;
            }
        }
        else if (pilihan == 3)
        {
            int id;
            User editedUser;

            vector<User> users = getAllUsers();

            for (const auto &user : users)
            {
                cout << "ID: " << user.id
                     << ", Username: " << user.username
                     << ", Password: " << user.password
                     << ", Role: " << user.role << endl;
            }

            cout << "Masukkan ID user: ";
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

            for (const auto &user : users)
            {
                cout << "ID: " << user.id
                     << ", Username: " << user.username
                     << ", Password: " << user.password
                     << ", Role: " << user.role << endl;
            }

            cout << "Masukkan ID user: ";
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
        else if (pilihan == 0)
        {
            cout << "Logout" << endl;
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
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail())
        {
            cin.clear();  // Reset status error
            cin.ignore(); // Buang karakter sisa
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

            for (const auto &product : products)
            {
                cout << "ID: " << product.id << ", Name: " << product.name << ", Brand: " << product.brand << ", Stock: " << product.stock << ", Price: " << product.price << endl;
            }
        }
        else if (pilihan == 3)
        {
            int id;
            Product editedproduct;

            vector<Product> products = getAllProducts();

            for (const auto &product : products)
            {
                cout << "ID: " << product.id
                     << ", Name: " << product.name
                     << ", Brand: " << product.brand
                     << ", Stock: " << product.stock
                     << ", Price: " << product.price << endl;
            }

            cout << "Masukkan ID product: ";
            cin >> id;

            try
            {
                cout << "Name: ";
                cin >> editedproduct.name;
                cout << "Brand: ";
                cin >> editedproduct.brand;
                cout << "Stock: ";
                cin >> editedproduct.stock;
                cout << "Price: ";
                cin >> editedproduct.price;
                if (EditProduct(id, editedproduct))
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

            for (const auto &product : products)
            {
                cout << "ID: " << product.id
                     << ", Name: " << product.name
                     << ", Brand: " << product.brand
                     << ", Stock: " << product.stock
                     << ", Price: " << product.price << endl;
            }

            cout << "Masukkan ID product: ";
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
        else if (pilihan == 0)
        {
            cout << "Logout" << endl;
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
        cout << "0. Back" << endl;
        cout << "Pilih opsi: ";

        cin >> pilihan;

        system("cls");

        // Tangani input bukan integer
        if (cin.fail())
        {
            cin.clear();  // Reset status error
            cin.ignore(); // Buang karakter sisa
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

            for (const auto &order : orders)
            {
                cout << "ID: " << order.id << ", User ID: " << order.user_id << ", Total Price: " << order.total_price << ", Status: " << order.status << endl;
                for (const auto &orderItem : order.products)
                {
                    cout << "   - Product ID: " << orderItem.product_id << ", Name: " << orderItem.name << ", Quantity: " << orderItem.quantity << ", Price: " << orderItem.price << endl;
                }
            }
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
        for (const auto &product : products)
        {
            if (product.stock == 0)
            {
                continue;
            }
            cout << "ID: " << product.id << ", Name: " << product.name << ", Brand: " << product.brand << ", Stock: " << product.stock << ", Price: " << product.price << endl;
        }

        cout << "\nPilih ID product yang ingin dipesan: ";
        int pilihan;
        cin >> pilihan;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
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
            cout << "Produk dengan ID " << pilihan << " tidak ditemukan.\n";
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

        // cout << "Product ID: " << product.id << ", Name: " << product.name << ", Brand: " << product.brand << ", Stock: " << product.stock << ", Price: " << product.price << endl;

        cout << "masukkan quantity: ";
        int quantity;
        cin >> quantity;

        if (cin.fail() || quantity <= 0)
        {
            cin.clear();
            cin.ignore();
            system("cls");
            cout << "Input tidak valid! / Quantity tidak boleh angka negatif.\n";
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

            cin.ignore();

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
        cout << "Total Price: " << order.total_price << endl;
        for (const auto &orderItem : order.products)
        {
            cout << "   - Product ID: " << orderItem.product_id << ", Name: " << orderItem.name << ", Quantity: " << orderItem.quantity << ", Price: " << orderItem.price << endl;
        }

        while (true)
        {
            cout << "Apakah pesanan sudah benar? (y/n): ";
            char confirm;
            cin >> confirm;

            cin.ignore();

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