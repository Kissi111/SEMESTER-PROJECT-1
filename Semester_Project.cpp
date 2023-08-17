
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

// Product class
class Product {
public:
    int id;
    std::string name;
    double price;
    int quantity;
};

// Inventory class
class Inventory {
private:
    sqlite3* db;
public:
    Inventory();
    ~Inventory();
    void addProduct(const Product& product);
    void deleteProduct(int productId);
    void modifyProduct(int productId, const Product& product);
    void displayInventory();
    void searchProduct(const std::string& productName);
    void displayLowStockProducts();
};

Inventory::Inventory() {
    int rc = sqlite3_open("inventory.db", &db);
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS products (id INTEGER PRIMARY KEY, name TEXT, price REAL, quantity INTEGER);";
    sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr);
}

Inventory::~Inventory() {
    sqlite3_close(db);
}

void Inventory::addProduct(const Product& product) {
    std::string addProductSQL = "INSERT INTO products (name, price, quantity) VALUES ('" + product.name + "', " + std::to_string(product.price) + ", " + std::to_string(product.quantity) + ");";
    sqlite3_exec(db, addProductSQL.c_str(), nullptr, nullptr, nullptr);
}

void Inventory::deleteProduct(int productId) {
    std::string deleteProductSQL = "DELETE FROM products WHERE id = " + std::to_string(productId) + ";";
    sqlite3_exec(db, deleteProductSQL.c_str(), nullptr, nullptr, nullptr);
}

void Inventory::modifyProduct(int productId, const Product& product) {
    std::string modifyProductSQL = "UPDATE products SET name = '" + product.name + "', price = " + std::to_string(product.price) + ", quantity = " + std::to_string(product.quantity) + " WHERE id = " + std::to_string(productId) + ";";
    sqlite3_exec(db, modifyProductSQL.c_str(), nullptr, nullptr, nullptr);
}

void Inventory::displayInventory() {
    const char* displayInventorySQL = "SELECT * FROM products;";
    sqlite3_exec(db, displayInventorySQL, nullptr, nullptr, nullptr);
}

void Inventory::searchProduct(const std::string& productName) {
    std::string searchProductSQL = "SELECT * FROM products WHERE name LIKE '%" + productName + "%';";
    sqlite3_exec(db, searchProductSQL.c_str(), nullptr, nullptr, nullptr);
}

void Inventory::displayLowStockProducts() {
    const char* lowStockSQL = "SELECT * FROM products WHERE quantity < 10;";
    sqlite3_exec(db, lowStockSQL, nullptr, nullptr, nullptr);
}

int main() {
    Inventory inventory;

    // Example usage
    Product product1 = {1, "Item A", 10.99, 50};
    inventory.addProduct(product1);

    // Display inventory
    inventory.displayInventory();

    // Search for a product
    inventory.searchProduct("Item A");

    // Display low stock products
    inventory.displayLowStockProducts();

    return 0;
}
