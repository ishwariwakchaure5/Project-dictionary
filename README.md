# 📚 Dictionary Project in C

Welcome! This is a simple command-line dictionary app built in C. 🧠📖  
It lets you **add**, **search**, and **remove** words along with their **definitions** and **synonyms** — just like your own mini vocabulary trainer.

All your data is saved in a text file, so you won’t lose it when you close the app!

---

## 🛠 What You Can Do

- ✅ Add a new word with its definition and synonyms  
- 🔍 Look up a word’s definition  
- 🧠 Find synonyms for a word  
- ❌ Remove a word from the dictionary  
- 💾 Save and load everything from a file (`dictionary.txt`), so your data sticks around

---

## ⚙️ How It Works

Behind the scenes, the app uses a **hash map** for super-fast lookups. Each word is stored in a custom structure, and we use **separate chaining** to handle collisions (when two words hash to the same value).

You can add **up to 10 synonyms per word** — plenty for any word nerd! 😄

---

## 🧰 Tech Stuff

- Language: **C**
- Hash Map (custom-built)
- File I/O (for saving and loading your words)
- Command Line Interface (text-based menu system)

---

## 🚀 How to Run the Program

Make sure you have GCC or any C compiler installed. Then:

1. **Compile the code**:
   ```bash
   gcc -o dictionary dictionary.c
   
2.Run it:

./dictionary

3.Use the menu to start building your dictionary!



