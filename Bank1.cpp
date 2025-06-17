#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

void printMenu();

const string clientFileName = "client.txt";
struct Client {
    string accountNumber;
    string PinCode;
    string clientName;
    string phone;
    double balance;
    bool markForDelete = false;
};

enum enMainMenuOption {
    eListClients = 1, eAddNewClients = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eExit = 6
};

vector<string> SplitString(string S1, string Delim) {
  vector<string> vString;
  short pos = 0;
  string sWord;

  while ((pos = S1.find(Delim)) != std::string::npos) {
    sWord = S1.substr(0, pos);
    if (sWord != "") {
      vString.push_back(sWord);
    }
    S1.erase(0, pos + Delim.length());
  }
  if (S1 != "") {
    vString.push_back(S1);
  }
  return vString;
}

string convertRecordToLine(Client client, string seperator = "#//#") {
  string stClientRecord = "";
  stClientRecord += client.accountNumber + seperator;
  stClientRecord += client.PinCode + seperator;
  stClientRecord += client.clientName + seperator;
  stClientRecord += client.phone + seperator;
  stClientRecord += to_string(client.balance);

  return stClientRecord;
}

Client convertLineToRecord(string line, string seperator = "#//#") {
  Client client;
  vector<string> vClientData;

  vClientData = SplitString(line, seperator);
  client.accountNumber = vClientData[0];
  client.PinCode = vClientData[1];
  client.clientName = vClientData[2];
  client.phone = vClientData[3];
  client.balance = stod(vClientData[4]);
  return client;
}

bool clientExistsByAccountNumber(string accountNumber, string fileName) {
  vector<Client> vClient;
  fstream myFile;
  myFile.open(fileName, ios::in);
  if (myFile.is_open()) {
    string line;
    Client client;

    while (getline(myFile, line)) {
      client = convertLineToRecord(line);
      if (client.accountNumber == accountNumber) {
        myFile.close();
        return true;
      }
      vClient.push_back(client);
    }
    myFile.close();
  }
  return false;
}

Client readNewClient() {
  cout << "Adding new client... " << endl;
  Client client;
  cout << "Enter Account Number? ";
  getline(cin >> ws, client.accountNumber);

  while (clientExistsByAccountNumber(client.accountNumber, clientFileName)) {
    cout << "\nclient with [" << client.accountNumber << "] already exists, Enter another account number: ";
    getline(cin, client.accountNumber);
  }

  cout << "Enter Pin code? ";
  getline(cin, client.PinCode);
  cout << "Enter Name? ";
  getline(cin, client.clientName);
  cout << "Enter Phone? ";
  getline(cin, client.phone);
  cout << "Enter Balance?";
  cin >> client.balance;

  return client;
}

vector<Client> loadClientsDataFromFile(string fileName) {
  vector<Client> vclient;
  fstream myFile;
  myFile.open(fileName, ios::in);
  if (myFile.is_open()) {
    string line;
    Client client;
    while (getline(myFile, line)) {
      client = convertLineToRecord(line);
      vclient.push_back(client);
    }
    myFile.close();
  }
  return vclient;
}

void printClientRecord(Client client) {
  cout << "| " << setw(15) << left << client.accountNumber;
  cout << "| " << setw(10) << left << client.PinCode;
  cout << "| " << setw(40) << left << client.clientName;
  cout << "| " << setw(12) << left << client.phone;
  cout << "| " << setw(12) << left << client.balance;
}

void printAllClientsData() {
  vector<Client> vClients = loadClientsDataFromFile(clientFileName);
  cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  cout << "| " << left << setw(15) << "Account Number";
  cout << "| " << left << setw(10) << "Pin Code";
  cout << "| " << left << setw(40) << "Client Name";
  cout << "| " << left << setw(12) << "Phone";
  cout << "| " << left << setw(12) << "Balance";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
  if (vClients.size() == 0) {
    cout << "\t\t\tNo clients available in the system!";
  } else {
    for (Client client: vClients) {
      printClientRecord(client);
      cout << endl;
    }
  }
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
}

void printClientCard(Client client) {
  cout << "\nThe following are the client details:\n";
  cout << "\nAccount Number: " << client.accountNumber;
  cout << "\nPin Code : " << client.PinCode;
  cout << "\nName : " << client.clientName;
  cout << "\nPhone : " << client.phone;
  cout << "\nAccount Balance: " << client.balance << endl;
}

bool findClientByAccountNumber(string accountNumber, vector<Client> vClient, Client &client) {
  for (Client _client: vClient) {
    if (_client.accountNumber == accountNumber) {
      client = _client;
      return true;
    }
  }
  return false;
}

Client changeClientLineToRecord(string accountNumber) {
  cout << "-------------------------------------" << endl;
  cout << "\t \t Update client " << endl;
  cout << "-------------------------------------" << endl;

  Client client;
  client.accountNumber = accountNumber;
  cout << "Enter Pin code? ";
  getline(cin >> ws, client.PinCode);
  cout << "Enter Name? ";
  getline(cin, client.clientName);
  cout << "Enter Phone? ";
  getline(cin, client.phone);
  cout << "Enter Balance?";
  cin >> client.balance;

  return client;
}

bool markClientForDeleteAccountNumber(string accountNumber, vector<Client> &vClient) {
  for (Client &c: vClient) {
    if (c.accountNumber == accountNumber) {
      c.markForDelete = true;
      return true;
    }
  }
  return false;
}

vector<Client> saveClientDataToFile(string fileName, vector<Client> vClient) {
  fstream myFile;
  myFile.open(fileName, ios::out);
  string dataLine;

  if (myFile.is_open()) {
    for (Client c: vClient) {
      if (c.markForDelete == false) {
        dataLine = convertRecordToLine(c);
        myFile << dataLine << endl;
      }
    }
    myFile.close();
  }
  return vClient;
}

void addDataLineToFile(string fileName, string stDataLine) {
  fstream myFile;
  myFile.open(fileName, ios::out | ios::app);
  if (myFile.is_open()) {
    myFile << stDataLine << endl;
    myFile.close();
  }
}

void addNewClient() {
  Client client;
  client = readNewClient();
  addDataLineToFile(clientFileName, convertRecordToLine(client));
}

void addNewClients() {
  char addMore = 'y';
  do {
    system("cls");
    cout << "adding new client :\n\n";
    addNewClient();
    cout << "\nclient added successfully, do you want add more clients Y/N? ";
    cin >> addMore;
  } while (toupper(addMore) == 'Y');
}

bool deleteClientByAccount(string accountNumber, vector<Client> &vClient) {
  Client client;
  char answer = 'n';
  if (findClientByAccountNumber(accountNumber, vClient, client)) {
    printClientCard(client);
    cout << "\n\nAre you sure you want delete this client y/n ? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      markClientForDeleteAccountNumber(accountNumber, vClient);
      saveClientDataToFile(clientFileName, vClient);

      vClient = loadClientsDataFromFile(clientFileName);
      cout << "\n\nClient delete successfully.";
      return true;
    }

  } else {
    cout << "\nClient with account number(" << accountNumber << ") is NOT found!";
    return false;
  }
  return false;
}

bool updateClientByAccount(string accountNumber, vector<Client> &vClient) {
  Client client;
  char answer = 'n';
  if (findClientByAccountNumber(accountNumber, vClient, client)) {
    printClientCard(client);

    cout << "\n\nAre you sure you want update this client y/n ? ";
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {
      for (Client &c: vClient) {
        if (c.accountNumber == accountNumber) {
          c = changeClientLineToRecord(accountNumber);
          break;
        }
      }
      saveClientDataToFile(clientFileName, vClient);
      vClient = loadClientsDataFromFile(clientFileName);
      cout << "\n\nClient update successfully.";
      return true;
    }

  } else {
    cout << "\nClient with account number(" << accountNumber << ") is NOT found!";
    return false;
  }
  return false;
}

string readClientAccountNumber() {
  string accountNumber = "";
  cout << "\nPlease enter AccountNumber? ";
  cin >> accountNumber;
  return accountNumber;
}

void showAddNewClients() {
  cout << "-------------------------------------" << endl;
  cout << "\t \t Add new client " << endl;
  cout << "-------------------------------------" << endl;
  addNewClients();
}

void showDeleteClientScreen() {
  cout << "\n-----------------------------------\n";
  cout << "\tDelete Client Screen";
  cout << "\n-----------------------------------\n";
  vector<Client> vClient = loadClientsDataFromFile(clientFileName);
  string AccountNumber = readClientAccountNumber();
  deleteClientByAccount(AccountNumber, vClient);
}

void showUpdateClientScreen() {
  cout << "\n-----------------------------------\n";
  cout << "\tUpdate Client Info Screen";
  cout << "\n-----------------------------------\n";
  vector<Client> vClient = loadClientsDataFromFile(clientFileName);
  string AccountNumber = readClientAccountNumber();
  updateClientByAccount(AccountNumber, vClient);
}

void showFindClientScreen() {
  cout << "\n-----------------------------------\n";
  cout << "\tFind Client Screen";
  cout << "\n-----------------------------------\n";
  vector<Client> vClient = loadClientsDataFromFile(clientFileName);
  Client client;
  string accountNumber = readClientAccountNumber();
  if (findClientByAccountNumber(accountNumber, vClient, client))
    printClientCard(client);
  else
    cout << "\nClient with Account Number[" << accountNumber << "] is not found!";
}

void showEndScreen() {
  cout << "\n-----------------------------------\n";
  cout << "\tProgram Ends :-)";
  cout << "\n-----------------------------------\n";
}


void goBackMenu() {
  cout << "\n\nPress any kay to go back to main menu...";
  system("pause>0");
  printMenu();
}

int readMainMenuOption() {
  cout << "Choose what do you want to do? [1 to 6 ]? ";
  int choose;
  cin >> choose;
  return choose;
}

void performMainMenuOption(enMainMenuOption mainMenuOption) {
  switch (mainMenuOption) {
    case enMainMenuOption::eListClients: {
      system("cls");
      printAllClientsData();
      goBackMenu();
      break;
    }
    case enMainMenuOption::eAddNewClients: {
      system("cls");
      showAddNewClients();
      goBackMenu();
      break;
    }
    case enMainMenuOption::eDeleteClient: {
      system("cls");
      showDeleteClientScreen();
      goBackMenu();
      break;
    }
    case enMainMenuOption::eUpdateClient: {
      system("cls");
      showUpdateClientScreen();
      goBackMenu();
      break;
    }
    case enMainMenuOption::eFindClient: {
      system("cls");
      showFindClientScreen();
      goBackMenu();
      break;
    }
    case enMainMenuOption::eExit: {
      system("cls");
      showEndScreen();
      break;
    }
  }
}

void printMenu() {
  cout << "================================================" << endl;
  cout << "\t\t Main Menu Screen" << endl;
  cout << "================================================" << endl;
  cout << "[1] Show Client list. " << endl;
  cout << "[2] Add new Client. " << endl;
  cout << "[3] Delete Client. " << endl;
  cout << "[4] Update Client Info." << endl;
  cout << "[5] Find Client. " << endl;
  cout << "[6] Exit." << endl;
  cout << "================================================" << endl;
  performMainMenuOption((enMainMenuOption) readMainMenuOption());

}
