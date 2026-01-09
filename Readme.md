# Chit Chat 🗨️

Welcome to **Chit Chat** – a console-based C++ chat application project implementing OOP, encryption, file management, colors, and screens! 

---

## 🚀 Features

- **User registration & login**  
- **Encrypted password & chat messages**  
- **Chat between multiple users**  
- **Colorful CLI interface**  
- **File-based persistent storage (users & chat)**  
- **Separation of concerns (screens, data, files, encryption)**  
- **Modular OOP design**

---

## 📚 How It Works

**1. Register or Login**  
- On start, create/register an account or login if you already exist.

**2. Select a User to Chat**  
- Choose who you want to chat with from the available user list.

**3. Encrypted Messaging**  
- All chat messages and credentials are stored encrypted in files.

**4. Colorful User Experience**  
- Enjoy colored prompts for better readability and style.

---

## 💡 Code Architecture

- **Text_Handler**: Manages all colored text and box printing for the command-line interface.
- **encryption**: Handles encryption and decryption of sensitive info (passwords and messages).
- **FileHandler**: Reads/writes users and chats from/to text files.
- **ChatScreen**: The core chat interface.
- **home_screen**: Main menu: login/register, user navigation.

---

## 🛠️ Getting Started

### Compile & Run

1. Clone the repo
2. Compile `main.cpp` using a compiler that supports Windows headers and libraries (e.g., Visual Studio, MinGW, etc.)
3. Run the generated executable

```sh
g++ main.cpp -o ChitChat.exe
ChitChat.exe
```

> **Note:**  
> Requires **Windows OS** (`windows.h` and `_mkdir` are used).

---

## 📄 File Structure

- **main.cpp** — Source code entry point
- **users.txt** — Encrypted usernames and passwords
- **ChatData/** — Encrypted chat messages between users

---

## 🙌 Contributors

- **Wahab** — Encryption & project lead
- **Adeel** — File handling
- **Haseeb** — Chat screen interface
- **Raja Tayyab** — Home screen

---

## ❤️ License

This project is open-source for learning purposes.
