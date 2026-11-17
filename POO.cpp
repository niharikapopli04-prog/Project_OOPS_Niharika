#include <iomanip> #include <string> using namespace std; 
 
// ===== PART 1: DATA (struct instead of class) ===== struct Product {     int id;            // unique product ID     string name;       // product name     double basePrice;  // original price     int category;      // 1 = Book, 2 = Accessory 
}; 
 
struct Bill {     double total;      // total bill amount 
}; 
 
// ===== PART 2: LIVE PRODUCT COUNTER (global variable) ===== int productCount = 0; 
 
// ===== PART 3: CREATE / DESTROY PRODUCT ===== 
Product createProduct(int id, string name, double price, int category) {     if (price < 0) {                    // handle invalid price         cout << "Invalid price! Set to 0\n";         price = 0; 
    } 
    Product p = {id, name, price, category}; 
    productCount++;                     // one more live product     return p; 
} 
 
void destroyProduct() {     productCount--;                     // one less live product 
} 
 
// ===== PART 4: CATEGORY PRICE RULES (if/else on category code) ===== double finalPrice(const Product& p) {     if (p.category == 1) return p.basePrice * 0.90;      // Book     else if (p.category == 2) return p.basePrice * 1.05; // Accessory     else return p.basePrice;                             // unknown category 
} 
 
// ===== PART 5: DISCOUNTS (two versions = function overloading) ===== 
// Version 1: percentage discount only double discount(const Product& p, double percent) {     return finalPrice(p) * (1.0 - percent / 100.0); 
} 
// Version 2: percentage discount + flat coupon (never below 0) double discount(const Product& p, double percent, double coupon) {     double amount = discount(p, percent) - coupon;     return amount > 0 ? amount : 0; 
} 
 
// ===== PART 6: BILLING ===== 
Bill makeBill(double amount) {     Bill b = {amount};     return b; 
} 
Bill addBills(const Bill& a, const Bill& b) {   // combines two bills     return makeBill(a.total + b.total); 
} void printBill(const Bill& b) {     cout << fixed << setprecision(2) << b.total; 
} 
 
// ===== PART 7: AUDIT FUNCTION ===== 
void auditProduct(const Product& p) {     cout << "Audit: ID=" << p.id << ", Name=" << p.name << "\n"; 
} 
 
// ===== PART 8: MAIN (demo, matches the expected output) ===== int main() {     cout << fixed << setprecision(2); 
    Product b = createProduct(101, "C++ Textbook", 500, 1); 
    Product a = createProduct(202, "USB Mouse", 800, 2); 
 
    cout << "Products registered: " << productCount << "\n";     cout << b.name << " | Category price: " << finalPrice(b) << "\n";     cout << a.name << " | Category price: " << finalPrice(a) << "\n";     cout << "Book after 10% discount: " << discount(b, 10.0) << "\n";     cout << "Mouse after 10% and Rs 20 coupon: " << discount(a, 10.0, 20.0) << "\n"; 
 
    Bill grandTotal = addBills(makeBill(discount(b, 10.0)),                                makeBill(discount(a, 10.0, 20.0)));     cout << "Grand total (Rs): ";     printBill(grandTotal);     cout << "\n"; 
 
    auditProduct(b);     return 0; 
} 
//jhsjhdgfsjbccjdshvdcw