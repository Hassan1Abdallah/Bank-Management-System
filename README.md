# 🏦 Bank Management System (C++)

A simple console-based banking system written in C++ that allows you to manage clients and perform banking operations like deposit, withdraw, and balance inquiry.

---

## 🚀 Features

- ✅ Add, Update, Delete Clients  
- ✅ Search Clients by Account Number  
- ✅ Deposit Money to Accounts  
- ✅ Withdraw Money from Accounts  
- ✅ View Total Balances of All Clients  
- ✅ User Confirmation Before Transactions  
- ✅ Data Persistence in File (`clients.txt`)  
- ✅ Main Menu and Transactions Menu for Navigation

---

### 🔹 Main Menu Options:

- **[1] Show Client List** – View all clients.
- **[2] Add New Client** – Add a new client to the system.
- **[3] Delete Client** – Delete client by account number.
- **[4] Update Client Info** – Edit client's info.
- **[5] Find Client** – Search for a client.
- **[6] Transactions Menu** – Deposit / Withdraw / View Balances.
- **[7] Exit** – Close the program.

---

### 🔹 Transactions Menu Options:

- **[1] Deposit** – Add money to a client account.
- **[2] Withdraw** – Withdraw from a client account.
- **[3] Total Balances** – View all balances and total sum.
- **[4] Main Menu** – Return to main menu.

---

```Run Main
 
   int main() {
   printMenu();
   system("pause>0");
   return 0;
   }
