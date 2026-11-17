#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Product {
    int id;
    string name;
    double basePrice;
    int category;
};

struct Bill {
    double total;
};

int productCount = 0;

Product createProduct(int id, string name, double price, int category) {
    if (price < 0) {
        cout << "Invalid price! Price set to 0.\n";
        price = 0;
    }

    productCount++;
    return {id, name, price, category};
}

double finalPrice(const Product& p) {
    if (p.category == 1)
        return p.basePrice * 0.90;
    else if (p.category == 2)
        return p.basePrice * 1.05;
    else if (p.category == 3)
        return p.basePrice * 0.95;

    return p.basePrice;
}

double discount(const Product& p, double percent) {
    return finalPrice(p) * (1.0 - percent / 100.0);
}

double discount(const Product& p, double percent, double coupon) {
    double amount = discount(p, percent) - coupon;
    return amount > 0 ? amount : 0;
}

Bill makeBill(double amount) {
    return {amount};
}

Bill addBills(const Bill& a, const Bill& b) {
    return makeBill(a.total + b.total);
}

void printBill(const Bill& b) {
    cout << fixed << setprecision(2) << b.total;
}

void auditProduct(const Product& p) {
    cout << "Audit: ID=" << p.id
         << ", Name=" << p.name << '\n';
}

void displayProducts(const vector<Product>& products) {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }

    cout << "\n--- PRODUCT LIST ---\n";

    for (const auto& p : products) {
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Base Price: Rs. " << p.basePrice
             << " | Category Price: Rs. " << finalPrice(p) << '\n';
    }
}

int main() {
    vector<Product> products;
    int choice;

    cout << fixed << setprecision(2);

    do {
        cout << "\n========== CAMPUS STORE ==========\n";
        cout << "1. Add New Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Generate Bill\n";
        cout << "4. Audit Product\n";
        cout << "5. Exit\n";
        cout << "==================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        if (choice == 1) {
            int id, category;
            string name;
            double price;

            cout << "Enter Product ID: ";
            cin >> id;

            cout << "Enter Product Name: ";
            cin >> name;

            cout << "Enter Base Price: Rs. ";
            cin >> price;

            cout << "Select Category:\n";
            cout << "1. Book\n";
            cout << "2. Accessory\n";
            cout << "3. Stationery\n";
            cout << "Enter category: ";
            cin >> category;

            if (category < 1 || category > 3) {
                cout << "Invalid category. Product not added.\n";
            }
            else {
                products.push_back(
                    createProduct(id, name, price, category)
                );

                cout << "Product added successfully.\n";
                cout << "Live products: " << productCount << '\n';
            }
        }

        else if (choice == 2) {
            displayProducts(products);
        }

        else if (choice == 3) {
            if (products.empty()) {
                cout << "Add products before billing.\n";
                continue;
            }

            int id;
            double percent, coupon;

            cout << "Enter Product ID to bill: ";
            cin >> id;

            bool found = false;

            for (const auto& p : products) {
                if (p.id == id) {
                    cout << "Product: " << p.name << '\n';
                    cout << "Category Price: Rs. "
                         << finalPrice(p) << '\n';

                    cout << "Discount percent: ";
                    cin >> percent;

                    cout << "Flat coupon (0 for none): Rs. ";
                    cin >> coupon;

                    Bill bill = makeBill(
                        discount(p, percent, coupon)
                    );

                    cout << "Final Bill Amount: Rs. ";
                    printBill(bill);
                    cout << '\n';

                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Product ID not found.\n";
        }

        else if (choice == 4) {
            int id;

            cout << "Enter Product ID to audit: ";
            cin >> id;

            bool found = false;

            for (const auto& p : products) {
                if (p.id == id) {
                    auditProduct(p);
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Product ID not found.\n";
        }

        else if (choice == 5) {
            cout << "Thank you for using Campus Store!\n";
        }

        else {
            cout << "Invalid choice. Please select 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}