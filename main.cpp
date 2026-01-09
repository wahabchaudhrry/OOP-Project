#include <iostream>
//For storing info in program
#include <vector>
#include <string>
//For file handling
#include <fstream>
//For making folders
#include <direct.h>
//For colors
#include <windows.h>
using namespace std;

// ---------- Color Functions ----------
//Code Color
//0 Black
//1 Blue
//2 Green
//3 Cyan
//4 Red
//5 Magenta
//6 Brown
//7 Light Gray
//8 Dark Gray
//9 Light Blue
//10 Light Green
//11 Light Cyan
//12 Light Red
//13 Light Magenta
//14 Yellow
//15 White




// Data Structures
struct User {
string username;
string password;
};

struct Message {
string sender;
string text;
};

// Vectors
string active_user = "";
vector<User> users;
vector<Message> messages;

class Text_Handler {
public:
void setColor(int color) {
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void Box_printer(string msg, bool wait, int color = 11) { // default cyan
system("cls");
if (msg.length() % 2 != 0) {
msg += " ";
}
string tab = "\t\t\t\t\t";
string spaces = string((30 - msg.length()) / 2, ' ');
string line = tab + "+" + string(30, '-') + "+\n";
string text = tab + "|" + spaces + msg + spaces + "|\n";

setColor(color);
cout << line;
cout << text;
cout << line;
setColor(7);

if (wait) {
cin.ignore();
cin.get();
}


}
void Colored_text(string msg, int color) {
setColor(color);
cout << msg;
setColor(7);
}
};

// Function to print messages in a box

// Class responsible for encryption and decryption : Wahab
class encryption {
private:
const int secret_code = 6;

public:
string encrypt(string normal_string) {
string encrypted = "";

// For each character in the string
for (char x : normal_string) {

// Only encrypts printable ASCII characters (32-126)
encrypted += char((x - 32 + secret_code) % 95 + 32);
}
return encrypted;
}

string decrypt(string encrypted_string) {
string normal = "";
for (unsigned char x : encrypted_string) {
normal += char((x - 32 - secret_code + 95) % 95 + 32);
}
return normal;
}
};

// Class responsible for file handling : Adeel
class FileHandler {
private:
encryption enc;
const string filename = "users.txt";
public:
// Save all existing users to file
void save_users() {
ofstream file(filename);
for (User& u : users) {
file << enc.encrypt(u.username) << " " << enc.encrypt(u.password) << "\n";
}
file.close();
}

// Load all users from file
void load_users() {
users.clear();
ifstream file_in(filename);
string uname, pword;

// Read until end of file
while (file_in >> uname >> pword) {
// Adding to vector array after decrypting
users.push_back({ enc.decrypt(uname), enc.decrypt(pword) });
}
file_in.close();
}

// Load chat messages between sender and receiver
void load_chats(string sender, string reciever) {
// Clear existing messages for new ones
messages.clear();
string chat_file = chatFile(sender, reciever);
ifstream file(chat_file);
if (!file) {
ofstream out_file(chat_file); // create if missing
}
else {
string line;
while (getline(file, line)) {
int pos = line.find("|");
// Checking the | separator
if (pos != string::npos) {
// Extract sender and text
string sender = line.substr(0, pos);
string text = line.substr(pos + 1);
messages.push_back({ enc.decrypt(sender), enc.decrypt(text) });
}
}
}
}

// Save chat messages between sender and receiver
void save_chats(string sender, string reciever) {
string chat_file = chatFile(sender, reciever);
ofstream out_file(chat_file);
for (Message m : messages) {
out_file << enc.encrypt(m.sender) << "|" << enc.encrypt(m.text) << endl;
}
}

// Generate chat file name based on usernames
string chatFile(string user1, string user2) {
if (user1 < user2)
return "ChatData/" + user1 + "_" + user2 + ".txt";
else
return "ChatData/" + user2 + "_" + user1 + ".txt";
}
};


// Class responsible for chat screen : Haseeb
class ChatScreen {
public:
ChatScreen() {
f.load_users();
selection_screen();
}

private:
int reciever;
FileHandler f;
Text_Handler th;

void selection_screen() {
if (users.empty()) {
th.Box_printer("No users available!", true, 12); // red for system message
return;
}

system("cls");
int choice = 1;
th.Box_printer("Select a user to chat with", false, 11); // cyan header
cout << "0. Exit\n";
for (User u : users) {
// Using Tenary Operator to show 'Yourself' for active user
cout << choice << ". " << ((u.username == active_user) ? "Yourself" : u.username) << "\n";
choice++;
}
th.Colored_text("\nChat With : ", 14);
cin >> choice;
cin.ignore(); // fix buffer

if (choice == 0) {
return;
}

reciever = choice - 1;
// Check for invalid selection
if (reciever < 0 || reciever >= users.size()) {
th.Box_printer("Invalid selection", true, 12);
selection_screen();
return;
}

chat_screen();
}

// Chat interface
void chat_screen() {
f.load_chats(active_user, users[reciever].username);
while (true) {
string text;
string name = users[reciever].username;
for (char& c : name) c = toupper(c);
th.Box_printer(name, false, 11); // cyan header
th.Colored_text("\t\t\t\t Write 'exit' to go back to user selection\n\n", 13);

// Display all messages from previous chat
for (Message m : messages) {
if (m.sender == active_user) {
th.Colored_text("\t\t\t\t\t\t\tYou : ", 10); // light green
cout << m.text << endl;
}
else {
th.Colored_text(m.sender + " : ", 14); // yellow
cout << m.text << endl;
}
}
th.Colored_text("\t\t\t\tMessage: ",2);
getline(cin, text); // safe getline

if (text == "exit") break;

messages.push_back({ active_user, text });
f.save_chats(active_user, users[reciever].username);
}
selection_screen();
}
};


// This class is responsible for home screen : Raja tayyab
class home_screen {
public:
home_screen() {
_mkdir("ChatData"); // ensure folder exists
file_handler.load_users();
home_page();
}

private:
Text_Handler th;
FileHandler file_handler;
string user, pass1, pass2;

void get_details(int x) {
if (x == 1) {
cout << "Enter Username: ";
cin >> user;
active_user = user;
}
else if (x == 2) {
cout << "Enter Password: ";
cin >> pass1;
}
else if (x == 3) {
cout << "Confirm Password: ";
cin >> pass2;
}
}

void home_page() {
int choice;
while (true) {
th.Box_printer("Chit Chat!", false, 11); // cyan header
cout << "\n1. Login\n2. Register\n3. Exit\nChoice: ";
cin >> choice;
cin.ignore(); // fix buffer

if (choice == 1) login_user();
else if (choice == 2) register_user();
else break;
}
}

void login_user() {
th.Box_printer("Log In", false, 11); // cyan header
bool found = false;
get_details(1);

for (const User& u : users) {
if (u.username == user) {
found = true;
get_details(2);
if (u.password == pass1) {
ChatScreen c;
}
else
th.Box_printer("Wrong Password", true, 12); // red
return;
}
}
if (!found) {
th.Box_printer("User not found", true, 12); // red
}
}

void register_user() {
th.Box_printer("Register User ", false, 11); // cyan header
get_details(1);
for (const User& u : users) {
if (u.username == user) {
th.Box_printer("User already exists", true, 12); // red
return;
}
}

get_details(2);
get_details(3);

if (pass1 == pass2) {
users.push_back({ user, pass1 });
file_handler.save_users();
ChatScreen c;
}
else {
th.Box_printer("Passwords do not match", true, 12); // red
}
}
};

int main() {
home_screen home;
}
