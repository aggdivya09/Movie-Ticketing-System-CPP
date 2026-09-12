# 🎬 Movie-Ticketing-System-CPP
A menu-driven C++ Movie Ticket Booking System demonstrating System Design and OOP concepts, with seat category-based pricing, show management, booking, payment, ticket generation, and cancellation.

## 📌 Overview

The Movie Ticketing System is designed for a single cinema and allows customers to:

- 🎬 View available movies
- 🕐 View shows and screens
- 💺 Check seat availability
- 💰 Calculate ticket prices based on seat category
- 🎟️ Book one or more seats
- 💳 Make payments using UPI, Card, or Cash
- 🧾 Generate booking tickets
- ❌ Cancel bookings
- 🔄 Make cancelled seats available again

---

## ✨ Features

### 🎬 Movie Management

- Displays available movies.
- Shows movie title, language, and duration.

### 🕐 Show Management

- Displays available shows for movies.
- Provides screen number and show start time.

### 💺 Seat Management

- Displays the seat layout.
- Shows seats as **AVAILABLE** or **BOOKED**.
- Prevents booking of already-booked seats.
- Releases seats when a booking is cancelled.

### 💰 Seat Category-Based Pricing

| Seat Category | Price |
|---------------|------:|
| Silver        | ₹150  |
| Gold          | ₹250  |
| Platinum      | ₹400  |

The total amount is calculated according to the categories of the selected seats.

### 💳 Payment System

The system supports:

- UPI Payment
- Card Payment
- Cash Payment

Payment is handled using an abstract `Payment` class and its derived payment classes.

### 🎟️ Ticket Generation

After successful payment, the ticket contains:

- Booking ID
- Movie
- Screen
- Show time
- Selected seats
- Total amount
- Booking status

### ❌ Booking Cancellation

Customers can cancel their bookings, after which the associated seats become **AVAILABLE** again.

---

## 🏗️ System Design

The system contains the following classes:

- `Movie`
- `Seat`
- `Screen`
- `Cinema`
- `Show`
- `ShowSeat`
- `Customer`
- `Booking`
- `Payment`
- `UpiPayment`
- `CardPayment`
- `CashPayment`
- `PriceCalculator`
- `TicketPrinter`
- `BookingService`
- `CinemaMenu`

---

## 📐 UML Class Diagram

The UML class diagram represents the classes, attributes, methods, and relationships used in the system.

### Relationships

- **Composition**
- **Aggregation**
- **Association**
- **Inheritance**
- **Dependency**

---

## 🔄 Sequence Diagram

The sequence diagram represents the flow of booking a ticket and completing the payment process.

**Customer → BookingService → Show → ShowSeat → PriceCalculator → Payment → Booking → TicketPrinter**

---

## 🧩 OOP Concepts Used

- **Encapsulation** – Data and methods are organized within classes.
- **Abstraction** – `Payment` defines the common payment contract.
- **Inheritance** – UPI, Card, and Cash payment classes inherit from `Payment`.
- **Runtime Polymorphism** – Different payment types implement `pay()` differently.
- **Compile-time Polymorphism** – Overloaded `calculatePrice()` methods are used.
- **Composition** – Cinema owns Screens, Screen owns Seats, and Show owns ShowSeats.
- **Aggregation** – Show uses Movie, and Booking references ShowSeats.
- **Association** – Relationships between Booking, Customer, Payment, and other classes.
- **Static Members** – Used for generating booking IDs.

---

## 🧱 SOLID Principles

### Single Responsibility Principle (SRP)

Different classes have separate responsibilities such as booking, pricing, payment, and ticket printing.

### Open/Closed Principle (OCP)

New payment types can be added by creating new `Payment` subclasses without modifying existing payment logic.

### Liskov Substitution Principle (LSP)

`UpiPayment`, `CardPayment`, and `CashPayment` can be used wherever a `Payment` object is expected.

### Interface Segregation Principle (ISP)

The payment abstraction contains only the common payment operation required by the payment classes.

### Dependency Inversion Principle (DIP)

The booking system depends on the abstract `Payment` type rather than directly depending on a specific payment implementation.

---

## 🛠️ Technologies Used

- **Language:** C++
- **Concepts:** Object-Oriented Programming, System Design
- **Compiler:** Any standard C++ compiler

---

