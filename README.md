# Bank-Management-System (C++)
 
This is a simple console-based client management system written in C++.  
It allows you to perform basic CRUD operations (Create, Read, Update, Delete) on client records stored in a plain text file (`client.txt`).

## 📌 Features

- Add new clients
- List all clients
- Update existing client data
- Delete a client by account number
- Search for a client
- Data stored in a local file using custom text format

## 📂 File Structure

- `main.cpp` - The source code for the entire application
- `client.txt` - File where client data is saved

## 🔧 Technologies

- C++
- File I/O using fstream
- Console-based UI

## ✅ How to Use

1. Compile the code:
   ```bash
   g++ -o clientApp main.cpp
   
   int main() {
   printMenu();
   system("pause>0");
   return 0;
   }



