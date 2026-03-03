# 📘 Dictionary Management System in C  
## Hash Map-Based Word Storage with File Persistence

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Data Structure](https://img.shields.io/badge/Data%20Structure-Hash%20Map-orange.svg)
![Persistence](https://img.shields.io/badge/Storage-File%20Based-green.svg)

---

# 📌 Overview

This project implements a **Dictionary Management System in C** using a **Hash Map (Hash Table with Separate Chaining)** to efficiently store, retrieve, and manage words along with:

- Definitions  
- Synonyms  
- Persistent storage using file handling  

The system allows users to:

- Add new words
- Remove existing words
- Search for word definitions
- Retrieve synonyms
- Save and load dictionary data from a file

This project demonstrates strong fundamentals in:

- Data Structures
- Hashing techniques
- Linked Lists
- File Handling
- Dynamic Memory Management
- String manipulation in C

---

# 🎯 Problem Statement

Efficiently storing and retrieving dictionary entries requires:

- Fast lookup
- Collision handling
- Persistent storage
- Structured data organization

A simple array or list is inefficient for large datasets.  
Therefore, this project uses a **Hash Table with Separate Chaining** to achieve near O(1) average lookup time.

---

# 🧠 System Architecture

## Data Structure Design

The dictionary is implemented using:

### 1️⃣ Hash Map
```c
typedef struct HashMap {
    Node *table[HASHMAP_SIZE];
} HashMap;
```

- Fixed size table
- Each index stores a linked list
- Collision handled using **Separate Chaining**

---

### 2️⃣ Node Structure

```c
typedef struct Node {
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];
    char synonyms[MAX_SYNONYMS][MAX_WORD_LENGTH];
    struct Node *next;
} Node;
```

Each node contains:

- Word
- Definition
- List of synonyms
- Pointer to next node (for collision handling)

---

# 🔑 Hash Function

```c
unsigned int hash(const char *word)
```

- Uses bit shifting
- Generates numeric hash value
- Maps value to table index using modulo

```
hash = (hash << 5) + character
```

This ensures:

- Better distribution
- Reduced collisions
- Faster lookup

---

# ⚙️ Features

## ✅ Add Word
- Stores word
- Stores definition
- Stores multiple synonyms
- Inserts into correct hash index

## ✅ Remove Word
- Searches linked list
- Handles head and middle deletion
- Frees memory properly

## ✅ Search Word
- Retrieves definition in O(1) average time

## ✅ Search Synonyms
- Displays stored synonyms
- Handles no-synonym case

## ✅ File Persistence
- Saves dictionary to `dictionary.txt`
- Loads dictionary on program start
- Prevents data loss between sessions

## ✅ Memory Management
- Uses `malloc()` for dynamic allocation
- Properly frees memory before exit

---

# 📂 Project Structure

```
Dictionary-HashMap-C/
│
├── main.c
├── dictionary.txt   (Auto-generated)
└── README.md
```

---

# 💾 File Storage Format

Dictionary entries are stored as:

```
word:definition:synonym1,synonym2,synonym3
```

Example:

```
happy:feeling pleasure:joyful,content,cheerful
```

---

# ▶️ How to Compile and Run

## Compile

```bash
gcc main.c -o dictionary
```

## Run

```bash
./dictionary
```

---

# 🖥️ Menu Interface

When executed, the system provides:

```
1. Add word
2. Remove word
3. Search word
4. Search synonyms
5. Exit
```

The program runs continuously until the user selects Exit.

---

# 🧮 Time Complexity Analysis

| Operation | Average Case | Worst Case |
|------------|--------------|------------|
| Add Word | O(1) | O(n) |
| Search Word | O(1) | O(n) |
| Remove Word | O(1) | O(n) |

Worst case occurs when many collisions happen in a single bucket.

---

# 🔍 Collision Handling

This project uses:

> Separate Chaining via Linked Lists

If two words produce the same hash index:

- They are stored in a linked list
- Search traverses the list
- Ensures no data overwriting

---

# 🧠 Concepts Demonstrated

- Hash Tables
- Linked Lists
- String manipulation
- File I/O
- Dynamic Memory Allocation
- Pointer operations
- Data persistence
- Menu-driven CLI program

---

# 🚀 Possible Improvements

- Dynamic resizing of hash table
- Case-insensitive search
- Improved hash function
- Binary file storage
- GUI version
- Trie-based implementation comparison
- Performance benchmarking
- Input validation enhancements

---

# ⚠️ Limitations

- Fixed hash table size
- No automatic resizing
- Case-sensitive search
- Basic error handling
- No duplicate word prevention

---

# 🎓 Learning Outcomes

This project strengthens understanding of:

- How hash tables work internally
- Collision resolution strategies
- Memory allocation in C
- File persistence mechanisms
- Building interactive CLI programs

---

# 💼 Resume Description

Implemented a hash map-based dictionary system in C using separate chaining for collision handling, dynamic memory management, and file persistence. Demonstrated strong knowledge of data structures, hashing techniques, and low-level memory operations.

---

# 👩‍💻 Author

Ishwari Wakchaure  
GitHub: https://github.com/ishwariwakchaure5

---

# 📜 License

This project is for educational purposes.
