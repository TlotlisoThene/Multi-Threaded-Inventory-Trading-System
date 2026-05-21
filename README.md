# Multi-Threaded-Inventory-Trading-System
A multi-threaded C++ inventory and order processing system that simulates real-time warehouse trading operations. The project demonstrates advanced Object-Oriented Programming, STL containers, smart pointers, mutex synchronization, and concurrent order processing using threads. The system safely manages products, processes multiple customer orders simultaneously, prevents race conditions, and maintains accurate inventory stock levels in a thread-safe environment.

## Overview
This project was developed for COMP315 and focuses on building a thread-safe inventory management system capable of processing multiple customer orders simultaneously.

The system simulates a real-world warehouse environment where several users or warehouses attempt to purchase products concurrently. Synchronization mechanisms are implemented to ensure data consistency, prevent race conditions, and maintain accurate stock levels during concurrent access.

## Key Features

- **Product Management** – Add, remove, search, display, and sort products by price or quantity
- **Polymorphic Pricing** – `TaxableProduct` and `DiscountedProduct` classes with overridden `calculateFinalPrice()`
- **Thread-Safe Order Processing** – 5+ concurrent threads process random orders without race conditions
- **Synchronized Inventory** – `std::mutex` with `lock_guard` prevents negative stock and data corruption
- **Smart Memory Management** – `std::shared_ptr` for all dynamic allocations (no raw `new`/`delete`)
- **Order Tracking** – Stores order ID, product ID, quantity, and status (SUCCESS/FAILED)
- **Interactive CLI** – Menu-driven console interface with clear output showing thread IDs and stock updates

---

## Technical Stack

| Concept | Implementation |
|---------|----------------|
| Language | C++17 |
| Data Structures | `std::map` (inventory), `std::vector` (orders) |
| Memory Management | `std::shared_ptr` |
| Concurrency | `std::thread`, `std::mutex`, `std::lock_guard` |
| Algorithms | `std::find_if`, `std::sort` |
| Randomization | `std::random_device`, `std::mt19937` |

---
## System Architecture

<img width="1001" height="781" alt="Screenshot (804)" src="https://github.com/user-attachments/assets/24b4e6d2-0621-4700-bd8d-c46892c699df" />

**Components:**
1. **Product Module** – Abstract Product base class with TaxableProduct and DiscountedProduct derived classes
2. **Inventory** – Central storage using std::map<int, std::shared_ptr<Product>> with mutex-protected operations
3. **Order** – Stores order ID, product ID, quantity, and status
4. **OrderProcessor** – Manages concurrent threads and collects order results
5. **User Interface** – Menu-driven CLI for user interaction

---

## Thread Safety Demonstration

When 15 threads attempt to purchase from limited stock (e.g., 13 items), the system ensures:
- Stock never goes negative
- Only successful orders reduce inventory
- Failed orders are correctly recorded
- Console output shows interleaved thread activity

---



## License

This project is for academic purposes.

