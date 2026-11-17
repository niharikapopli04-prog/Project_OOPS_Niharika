#include <iostream> 
#include <iomanip> #include <string> using namespace std; 
 
// ===== PART 1: BASE CLASS Product (class, constructor, static, inline, virtual) ===== class Product { private: 
    int id;                       // private: only Product (and friends) can access     static int productCount;      // STATIC DATA: one shared live-object counter protected: 
    string name;                  // protected: visible to derived classes     double basePrice; public: 
    // CONSTRUCTOR: sets id, name, price and increases the live count 
    Product(int code, string n, double price) 
        : id(code), name(n), basePrice(price < 0 ? 0 : price) { ++productCount; } 
 
    // Copying is disabled so the live counter never becomes inaccurate 
    Product(const Product&) = delete; 
    Product& operator=(const Product&) = delete; 
 
    // VIRTUAL DESTRUCTOR: safe deletion through a base pointer     virtual ~Product() { --productCount; } 
 
    // INLINE accessor functions (small, const)     inline string getName() const { return name; }     inline double getPrice() const { return basePrice; } 
 
    // STATIC FUNCTION: called as Product::getProductCount()     static int getProductCount() { return productCount; } 
 
    // VIRTUAL FUNCTION: derived classes override this (runtime polymorphism)     virtual double finalPrice() const { return basePrice; } 
 
    // FUNCTION OVERLOADING: two discount() versions     double discount(double percent) const {         return finalPrice() * (1.0 - percent / 100.0); 
    } 
    double discount(double percent, double coupon) const {         double amount = discount(percent) - coupon;         return amount > 0 ? amount : 0;     // never below zero 
    } 
 
    // FRIEND FUNCTION: allowed to read private id     friend void auditProduct(const Product& p); 
}; 
 
int Product::productCount = 0;   // definition of the static member 
 
// FRIEND FUNCTION definition void auditProduct(const Product& p) {     cout << "Audit: ID=" << p.id << ", Name=" << p.name << "\n"; 
} 
 
// ===== PART 2: DERIVED CLASSES (INHERITANCE + overriding) ===== 
class Book : public Product { public: 
    Book(int id, string n, double price) : Product(id, n, price) {}     double finalPrice() const override { return basePrice * 0.90; } }; 
 
class Accessory : public Product { public: 
    Accessory(int id, string n, double price) : Product(id, n, price) {}     double finalPrice() const override { return basePrice * 1.05; } 
}; 
 
// ===== PART 3: Bill (OPERATOR OVERLOADING) ===== 
class Bill {     double total; public: 
    explicit Bill(double a = 0) : total(a) {} 
    // OPERATOR +: combines two bills 
    Bill operator+(const Bill& b) const { return Bill(total + b.total); } 
    // OPERATOR <<: prints the bill total     friend ostream& operator<<(ostream& os, const Bill& b) {         return os << fixed << setprecision(2) << b.total; 
    } 
}; 
 
// ===== PART 4: MAIN (demo, matches the expected output) ===== int main() {     cout << fixed << setprecision(2); 
    Book b(101, "C++ Textbook", 500);          // OBJECT creation 
    Accessory a(202, "USB Mouse", 800); 
 
    cout << "Products registered: " << Product::getProductCount() << "\n";     cout << b.getName() << " | Category price: " << b.finalPrice() << "\n";     cout << a.getName() << " | Category price: " << a.finalPrice() << "\n";     cout << "Book after 10% discount: " << b.discount(10.0) << "\n";     cout << "Mouse after 10% and Rs 20 coupon: " << a.discount(10.0, 20.0) << "\n";     Bill grandTotal = Bill(b.discount(10.0)) + Bill(a.discount(10.0, 20.0));     cout << "Grand total (Rs): " << grandTotal << "\n"; 
 
    auditProduct(b);     return 0; 
} 
