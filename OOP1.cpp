#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Product {
private:
    int id;
    static int productCount;

protected:
    string name;
    double basePrice;

public:
    Product(int code, string n, double price)
        : id(code), name(n), basePrice(price < 0 ? 0 : price) {
        ++productCount;
    }

    Product(const Product&) = delete;
    Product& operator=(const Product&) = delete;

    virtual ~Product() {
        --productCount;
    }

    inline string getName() const {
        return name;
    }

    inline double getPrice() const {
        return basePrice;
    }

    inline int getId() const {
        return id;
    }

    static int getProductCount() {
        return productCount;
    }

    virtual double finalPrice() const {
        return basePrice;
    }

    double discount(double percent) const {
        return finalPrice() * (1.0 - percent / 100.0);
    }

    double discount(double percent, double coupon) const {
        double amount = discount(percent) - coupon;
        return amount > 0 ? amount : 0;
    }

    friend void auditProduct(const Product& p);
};

int Product::productCount = 0;

void auditProduct(const Product& p) {
    cout << "Audit: ID=" << p.id
         << ", Name=" << p.name << '\n';
}

class Book : public Product {
public:
    Book(int id, string n, double price)
        : Product(id, n, price) {}

    double finalPrice() const override {
        return basePrice * 0.90;
    }
};

class Accessory : public Product {
public:
    Accessory(int id, string n, double price)
        : Product(id, n, price) {}

    double finalPrice() const override {
        return basePrice * 1.05;
    }
};

class Bill {
    double total;

public:
    explicit Bill(double amount = 0) : total(amount) {}

    Bill operator+(const Bill& b) const {
        return Bill(total + b.total);
    }

    friend ostream& operator<<(ostream& os, const Bill& b) {
        return os << fixed << setprecision(2) << b.total;
    }
};

void displayProducts(const vector<Product*>& products) {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }

    cout << "\n--- PRODUCT LIST ---\n";

    for (const Product* p : products) {
        cout << "ID: " << p->getId()
             << " | Name: " << p->getName()
             << " | Base Price: Rs. " << p->getPrice()
             << " | Category Price: Rs. " << p->finalPrice()
             << '\n';
    }
}

int main() {
    vector<Product*> products;
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
            int id, type;
            string name;
            double price;

            cout << "Enter Product ID: ";
            cin >> id;

            cout << "Enter Product Name: ";
            cin >> name;

            cout << "Enter Base Price: Rs. ";
            cin >> price;

            cout << "Select Category (1=Book, 2=Accessory): ";
            cin >> type;

            if (type == 1) {
                products.push_back(new Book(id, name, price));
            }
            else if (type == 2) {
                products.push_back(new Accessory(id, name, price));
            }
            else {
                cout << "Invalid category. Product not added.\n";
                continue;
            }

            cout << "Product added successfully.\n";
            cout << "Live products: "
                 << Product::getProductCount() << '\n';
        }

        else if (choice == 2) {
            displayProducts(products);
        }

        else if (choice == 3) {
            int id;
            double percent, coupon;

            cout << "Enter Product ID to bill: ";
            cin >> id;

            bool found = false;

            for (const Product* p : products) {
                if (p->getId() == id) {
                    cout << "Product: " << p->getName() << '\n';
                    cout << "Category Price: Rs. "
                         << p->finalPrice() << '\n';

                    cout << "Discount percent: ";
                    cin >> percent;

                    cout << "Flat coupon (0 for none): Rs. ";
                    cin >> coupon;

                    Bill total(p->discount(percent, coupon));

                    cout << "Final Bill Amount: Rs. "
                         << total << '\n';

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

            for (const Product* p : products) {
                if (p->getId() == id) {
                    auditProduct(*p);
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

    for (Product* p : products) {
        delete p;
    }

    return 0;
}