#include <iostream>
#include <memory>
#include "Inventory.h"
#include "TaxableProduct.h"
#include "DiscountedProduct.h"
#include "OrderProcessor.h"
#include <cctype>
#include <algorithm>

//IMPORTING COLOURS
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

void print() {
    cout << "========================================\n";
}

void printTopLines(string title) {
    print();
    cout << "   " << title << endl;
    print();
}
using namespace std;

Inventory inventory;
OrderProcessor processor(inventory);

// === FUNCTION DECLARATIONS ===
void mainMenue();
void inventoryManagement();
void orderManagement();
void processOrder();
void addProduct();
void removeProduct();
void displayAllProducts();
void searchByProductID();
void sortProducts();

// ===== MAIN =====
int main(){
    mainMenue();
    return 0;
}

// ===== MAIN MENU =====
void mainMenue() {
    int option;
    printTopLines("WELCOME TO INVENTORY SYSTEM");

    do {
        system("cls");
        printTopLines("INVENTORY AND ORDER SYSTEM");
        cout << "[1]. Inventory Management\n";
        cout << "[2]. Order Management\n";
        cout << "[3]. Process Orders (Multi-threaded)\n";
        cout << "[4]. Exit\n";
        cout << "Select option: ";
        cout << "\n>> Select option: ";
        cin >> option;

        switch(option){
            case 1: inventoryManagement(); break;
            case 2: orderManagement(); break;
            case 3: processOrder(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid option\n";
        }

    } while(option != 4);
}

// ===== INVENTORY MENU =====
void inventoryManagement() {
    int option;

    do {
        printTopLines("INVENTORY MANAGEMENT");
        cout << "[1]. Add Product\n";
        cout << "[2]. Remove Product\n";
        cout << "[3]. Display All Products\n";
        cout << "[4]. Search Product By ID\n";
        cout << "[5]. Sort Products\n";
        cout << "[6]. Back\n";
        cout << "\n>> Select option: ";

        cin >> option;

        switch(option){
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: displayAllProducts(); break;
            case 4: searchByProductID(); break;
            case 5: sortProducts(); break;
        }

    } while(option != 6);
}

// ===== ADD PRODUCT =====
void addProduct(){
    int type, id, quantity;
    double price, rate;
    string name;
    system("cls");
    printTopLines("ADD PRODUCT");
    cout << "1. Taxable Product\n";
    cout << "2. Discounted Product\n";
    cout << ">> Select option: ";
    cin >> type;
    while(type!=1 && type !=2){
    cout<<"Choose between 1 and 2\n";
    cout << "1. Taxable Product\n";
    cout << "2. Discounted Product\n";
    cout << ">> Select option: ";
    cin >> type;

    }
     id = inventory.IncrementID(); // remember our Product ID is auto generated
    cout << YELLOW << "Product ID: " << id << endl << RESET;

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter Price: ";
    cin >> price;
       while(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid input. Enter price: ";
        cin >> price;
    }


    cout << "Enter Quantity: ";
    cin >> quantity;
       while(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid input. Enter quantity: ";
        cin >> quantity;
    }

    if(type == 1){
        cout << "Enter Tax Rate: ";
        cin >> rate;

        inventory.addProduct(
            make_shared<TaxableProduct>(id, name, price, quantity, rate)
        );

    } else if(type == 2){
        cout << "Enter Discount Rate: ";
        cin >> rate;

        inventory.addProduct(
            make_shared<DiscountedProduct>(id, name, price, quantity, rate)
        );

    } else {
        cout << "The product is not Texable or Discounted";

    }
}



// ===== REMOVE PRODUCT =====
void removeProduct(){
    int id;
    cout << "Enter Product ID to remove: ";
    cin >> id;

    if(inventory.removeProduct(id)){
       cout << GREEN << " Product removed successfully\n" << RESET;
    } else {
      cout << RED << " Product not found\n" << RESET;
    }
}

// ===== DISPLAY PRODUCTS =====
void displayAllProducts(){
    printTopLines("ALL PRODUCTS");
    inventory.displayProducts();
}

// ===== SEARCH PRODUCT =====
void searchByProductID(){
    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    auto product = inventory.searchProduct(id);

    if(product != nullptr){
        cout << GREEN << "\n Product Found\n" << RESET;
        print();
        cout << "Name     : " << product->getName() << endl;
        cout << "Price    : " << product->getPrice() << endl;
        cout << "Quantity : " << product->getQuantity() << endl;
        print();
    } else {
        cout << "Product not found\n";
    }
}

// ===== SORT PRODUCTS =====
void sortProducts(){
    int option;

    printTopLines("SORT PRODUCTS");
    cout << "1. Sort by Price\n";
    cout << "2. Sort by Quantity\n";
    cout << "Select option: ";
    cin >> option;

    if(option == 1){
        inventory.sortByPrice();
    } else if(option == 2){
        inventory.sortByQuantity();
    } else {
        cout << "Invalid option\n";
    }
}

// ===== ORDER MANAGEMENT =====
void orderManagement(){
    int option;

    do {
       printTopLines("ORDER MANAGEMENT");
        cout << "1. View All Orders\n";
        cout << "2. Back\n";
        cout << "Select option: ";


        cin >> option;

        switch(option){
            case 1:
                processor.displayOrders();
                cout << "Successful Orders: " << processor.getSuccsesfulOrders() << endl;
                cout << "Failed Orders: " << processor.getFailedOrders() << endl;
                break;
        }

    } while(option != 2);
}

// ===== PROCESS ORDERS =====
void processOrder(){
    printTopLines("PROCESSING ORDERS");
    cout << CYAN << "Running multi-threaded processing...\n" << RESET;
    processor.processOrdersMultithread();
    cout << "\nPress Enter to go back to Main Menu...";
    cin.ignore();
    cin.get();
}
