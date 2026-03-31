# 🃏 Console Solitaire in C++

A fully functional, console-based implementation of the classic **Klondike Solitaire** card game, built from scratch using custom data structures in C++.

---

## 📖 About the Project

This project was developed as part of the **Data Structures (CS-2001)** course at FAST-NUCES. It implements Solitaire using a **doubly linked list**, **iterators**, and **stacks** — without relying on any STL containers.

The goal was to demonstrate deep understanding of pointer-based data structures, OOP principles, and efficient memory management (no new object creation or deletion during card moves).

---

## 🎮 How to Play

### Game Objective
Move all 52 cards to the 4 foundation piles, each sorted by suit from Ace (lowest) to King (highest).

### Controls

| Command | Action |
|---|---|
| `s` | Draw a card from the stockpile to the wastepile |
| `m <src>, <dest>, <count>` | Move card(s) from source to destination |
| `z` | Undo the last move |
| `q` | Quit the game |

### Move Command Examples

```
m c6, c1, 2     → Move 2 cards from Column 6 to Column 1
m w, c3, 1      → Move 1 card from Wastepile to Column 3
m c2, f1, 1     → Move 1 card from Column 2 to Foundation 1
m f2, c4, 1     → Move 1 card from Foundation 2 to Column 4
```

### Valid Sources/Destinations
- `c1` – `c7` : Tableau columns
- `f1` – `f4` : Foundation piles
- `w`         : Wastepile

---

## 🏗️ Data Structures Used

| Structure | Used For |
|---|---|
| **Doubly Linked List** (`Tableau<T>`) | Tableau columns (card sequences) |
| **Stack** (linked-list backed) | Stock, Waste, Foundation piles, Undo history |
| **Iterator** (`ListIterator<T>`) | Moving nodes between lists without creating/deleting |

> **Key Design Constraint:** All card movements relink existing nodes — no `new` or `delete` is called during gameplay.

---

## 📁 Project Structure

```
Solitaire-DS/
├── 23L-0527_BCS-3A_DS_Assignment_1.cpp   # Full source code
└── README.md
```

---

## ⚙️ Tech Stack

- **Language:** C++
- **Compiler:** MSVC / MinGW (Windows)
- **Standard:** C++11 or later
- **Dependencies:** `<windows.h>` (for UTF-8 console output of card suits)

---

## 🚀 Setup & Build

### Prerequisites
- Windows OS (uses `SetConsoleOutputCP` for Unicode suit symbols ♥ ♦ ♣ ♠)
- A C++ compiler (Visual Studio, MinGW, or similar)

### Compile

```bash
g++ -o solitaire 23L-0527_BCS-3A_DS_Assignment_1.cpp -std=c++11
```

### Run

```bash
./solitaire
```

---

## 📸 Sample Output

```
Stock                   Waste
[ ]                     5♠
(14 cards)              (8 cards)

Foundation 1    Foundation 2    Foundation 3    Foundation 4
A♥              A♠              [  ]            [  ]
(1 cards)       (1 cards)       (0 cards)       (0 cards)

Column 1 (2 cards) 7♠  6♥
Column 2 (1 cards) 7♦
Column 3 (2 cards) [ ] Q♠
...
```

---

## 🧩 Classes Overview

- **`card`** — Stores rank, suit, and visibility state of each card
- **`Command`** — Parses and stores game commands with full operand extraction
- **`Tableau<T>`** — Generic doubly linked list with nested `Node` and `ListIterator` classes
- **`Stack<T>`** — Stack abstraction built on top of `Tableau<T>`
- **`game`** — Orchestrates all piles, columns, game logic, undo, and win detection

---

## ✅ Features

- ♻️ Full **undo** support for all move types (including draw)
- 🎨 Color-coded output — red suits (♥ ♦) in red, black suits (♠ ♣) in white
- 🃏 Unicode card suit symbols rendered in console
- 🔀 Fisher-Yates shuffle for deck randomization
- 🏆 Automatic win detection

---

## 👤 Author

**Roll No:** 23L-0527  
**Section:** BCS-3A  
**Course:** Data Structures — FAST-NUCES  
