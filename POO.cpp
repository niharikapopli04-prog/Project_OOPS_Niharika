
#include <iostream>
#include <iomanip>
#include <string>
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

Product products[100];
int productCount = 0;

// Calculate category price
double finalPrice(const Product& p) {
    if (p.category == 1)
        return p.basePrice * 0.90;
    else if (p.category == 2)
        return p.basePrice * 1.05;
    else
        return p.basePrice;
}

// Discount function
double discount(const Product& p, double percent) {
    return finalPrice(p) * (1 - percent / 100);
}

// Discount with coupon
double discount(const Product& p, double percent, double coupon) {
    double amount = discount(p, percent) - coupon;
    return amount > 0 ? amount : 0;
}

// Billing functions
Bill makeBill(double amount) {
    Bill b = {amount};
    return b;
}

Bill addBills(const Bill& a, const Bill& b) {
    return makeBill(a.total + b.total);
}

// Add product
void addProduct() {
    if (productCount >= 100) {
        cout << "Store is full!\n";
        return;
    }

    Product p;

    cout << "\nEnter Product ID: ";
    cin >> p.id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == p.id) {
            cout << "Product ID already exists!\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter Product Name: ";
    getline(cin, p.name);

    cout << "Enter Base Price: Rs ";
    cin >> p.basePrice;

    if (p.basePrice < 0) {
        cout << "Invalid price!\n";
        return;
    }

    cout << "\nSelect Category:\n";
    cout << "1. Book (10% discount)\n";
    cout << "2. Accessory (5% extra charge)\n";
    cout << "Enter choice: ";
    cin >> p.category;

    if (p.category != 1 && p.category != 2) {
        cout << "Invalid category!\n";
        return;
    }

    products[productCount++] = p;

    cout << "\nProduct added successfully!\n";
}

// Display products
void displayProducts() {
    if (productCount == 0) {
        cout << "\nNo products registered yet!\n";
        return;
    }

    cout << "\n========== PRODUCT LIST ==========\n";

    for (int i = 0; i < productCount; i++) {
        cout << "\nID: " << products[i].id;
        cout << "\nName: " << products[i].name;
        cout << "\nBase Price: Rs " << products[i].basePrice;
        cout << "\nCategory: "
             << (products[i].category == 1 ? "Book" : "Accessory");
        cout << "\nFinal Price: Rs " << finalPrice(products[i]);
        cout << "\n----------------------------------\n";
    }
}

// Generate bill
void generateBill() {
    if (productCount == 0) {
        cout << "\nNo products available!\n";
        return;
    }

    int id;
    double percent, coupon;
    Bill grandTotal = makeBill(0);

    char choice;

    do {
        cout << "\nEnter Product ID: ";
        cin >> id;

        int index = -1;

        for (int i = 0; i < productCount; i++) {
            if (products[i].id == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Product not found!\n";
        }
        else {
            cout << "Product: " << products[index].name;
            cout << "\nCategory Price: Rs "
                 << finalPrice(products[index]);

            cout << "\nEnter discount percentage (0-100): ";
            cin >> percent;

            if (percent < 0 || percent > 100) {
                cout << "Invalid discount! Try again.\n";
                continue;
            }

            cout << "Apply coupon? (y/n): ";
            cin >> choice;

            double amount;

            if (choice == 'y' || choice == 'Y') {
                cout << "Enter coupon amount: Rs ";
                cin >> coupon;

                if (coupon < 0) {
                    cout << "Invalid coupon amount!\n";
                    continue;
                }

                amount = discount(products[index], percent, coupon);
            }
            else {
                amount = discount(products[index], percent);
            }

            cout << "\nFinal Product Price: Rs "
                 << amount << "\n";

            grandTotal = addBills(grandTotal, makeBill(amount));
        }

        cout << "\nAdd another product to bill? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\n========== FINAL BILL ==========\n";
    cout << "Grand Total: Rs "
         << fixed << setprecision(2) << grandTotal.total;
    cout << "\n================================\n";
}

// Audit product
void auditProduct() {
    int id;

    cout << "\nEnter Product ID for audit: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "\nAudit: ID = " << products[i].id;
            cout << "\nProduct Name = " << products[i].name;
            cout << "\nProduct found successfully!\n";
            return;
        }
    }

    cout << "Product not found!\n";
}

// Main function
int main() {
    int choice;

    cout << fixed << setprecision(2);

    do {
        cout << "\n\n====================================";
        cout << "\n       CAMPUS STORE MANAGEMENT";
        cout << "\n====================================";
        cout << "\n1. Add New Product";
        cout << "\n2. Display All Products";
        cout << "\n3. Generate Bill";
        cout << "\n4. Audit Product";
        cout << "\n5. Exit";
        cout << "\n====================================";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                generateBill();
                break;

            case 4:
                auditProduct();
                break;

            case 5:
                cout << "\nThank you for visiting Campus Store!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
