#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace std;

const int MAX_TICKETS = 100; // Maximum number of tickets

struct Passenger {
    string name;
};

struct Ticket {
    string pnr;
    Passenger passenger;
    string destination;
    string journeyDate;
};

string generatePNR() {
    return to_string(rand() % 1000000000); // Simple PNR generation
}

bool isValidPhoneNumber(string phoneNumber) {
    return phoneNumber.length() == 10 && phoneNumber.find_first_not_of("0123456789") == string::npos;
}

void displayTicket(const Ticket& ticket) {
    cout << "Ticket Details:" << endl;
    cout << "PNR: " << ticket.pnr << endl;
    cout << "Passenger: " << ticket.passenger.name << endl;
    cout << "Destination: " << ticket.destination << endl;
    cout << "Journey Date: " << ticket.journeyDate << endl;
}

void printTicket(const Ticket& ticket) {
    cout << "\n--- Ticket Print ---" << endl;
    cout << "PNR: " << ticket.pnr << endl;
    cout << "Passenger: " << ticket.passenger.name << endl;
    cout << "Destination: " << ticket.destination << endl;
    cout << "Journey Date: " << ticket.journeyDate << endl;
    cout << "--------------------" << endl;
}

// User management
unordered_map<string, string> users; // Stores username and password

void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    if (users.find(username) != users.end()) {
        cout << "Username already exists! Please choose a different username." << endl;
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    users[username] = password; // Store the username and password
    cout << "Registration successful!" << endl;
}

bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        return true; // Login successful
    }

    cout << "Invalid username or password!" << endl;
    return false; // Login failed
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random PNR generation

    Ticket tickets[MAX_TICKETS];
    int ticketCount = 0;

    string destinations[] = { "ZANZIBAR TOWN", "ZANZIBAR NORTH", "ZANZIBAR SOUTH" };
    string journeyDays[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

    while (true) {
    	 cout << "Welcome to the Bus ticketing Booking system" << endl;
    	  cout << "  " << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            if (!login()) {
                cout << "Login failed! Please try again." << endl;
                continue;
            }

            cout << "Login successful!" << endl;

            cout << "Enter your name: ";
            Passenger passenger;
            cin.ignore(); // Clear the input buffer
            getline(cin, passenger.name);

            while (true) {
                cout << "1. Book Ticket" << endl;
                cout << "2. Display Ticket" << endl;
                cout << "3. Print Ticket" << endl;
                cout << "4. Logout" << endl;
                cout << "Enter your choice: ";

                int innerChoice;
                cin >> innerChoice;

                if (innerChoice == 1) {
                    if (ticketCount >= MAX_TICKETS) {
                        cout << "Cannot book more tickets!" << endl;
                        continue;
                    }

                    string phoneNumber;
                    cout << "Enter your phone number: ";
                    cin >> phoneNumber;

                    if (!isValidPhoneNumber(phoneNumber)) {
                        cout << "Invalid phone number! Ticket booking failed." << endl;
                        continue;
                    }

                    cout << "Available destinations:" << endl;
                    for (int i = 0; i < 3; i++) {
                        cout << (i + 1) << ". " << destinations[i] << endl;
                    }
                    cout << "Enter the destination choice (1-3): ";
                    int destChoice;
                    cin >> destChoice;

                    if (destChoice < 1 || destChoice > 3) {
                        cout << "Invalid choice! Ticket booking failed." << endl;
                        continue;
                    }

                    cout << "Available journey days:" << endl;
                    for (int i = 0; i < 7; i++) {
                        cout << (i + 1) << ". " << journeyDays[i] << endl;
                    }
                    cout << "Enter the journey day choice (1-7): ";
                    int dayChoice;
                    cin >> dayChoice;

                    if (dayChoice < 1 || dayChoice > 7) {
                        cout << "Invalid choice! Ticket booking failed." << endl;
                        continue;
                    }

                    Ticket ticket;
                    ticket.pnr = generatePNR();
                    ticket.passenger = passenger;
                    ticket.destination = destinations[destChoice - 1];
                    ticket.journeyDate = journeyDays[dayChoice - 1];

                    tickets[ticketCount++] = ticket;

                    cout << "Ticket booked successfully!" << endl;
                    cout << "PNR: " << ticket.pnr << endl;
                    cout << "Passenger: " << ticket.passenger.name << endl;
                    cout << "Destination: " << ticket.destination << endl;
                    cout << "Journey Date: " << ticket.journeyDate << endl;

                } else if (innerChoice == 2) {
                    cout << "Enter PNR: ";
                    string pnr;
                    cin >> pnr;

                    bool found = false;
                    for (int i = 0; i < ticketCount; i++) {
                        if (tickets[i].pnr == pnr) {
                            displayTicket(tickets[i]);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Ticket not found!" << endl;
                    }

                } else if (innerChoice == 3) {
                    cout << "Enter PNR for printing: ";
                    string pnr;
                    cin >> pnr;

                    bool found = false;
                    for (int i = 0; i < ticketCount; i++) {
                        if (tickets[i].pnr == pnr) {
                            printTicket(tickets[i]);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Ticket not found for printing!" << endl;
                    }

                } else if (innerChoice == 4) {
                    cout << "Logged out successfully!" << endl;
                    break;

                } else {
                    cout << "Invalid choice! Please try again." << endl;
                }
            }
        } else if (choice == 3) {
            cout << "Thank you for using the ticket booking system. Goodbye!" << endl;
            break;

        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
