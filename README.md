# 🎮 Lonely Cells: A Hexagonal Strategy Game  


<div align="center">
  <img 
    src="https://github.com/user-attachments/assets/bcef4cd5-4be2-4868-a40a-5b56fe2153bf" 
    alt="Lucid_Origin_Topdown_view_of_a_scifi_hexagonal_grid_game_board_2" 
    width="800" 
    height="500"
  >
</div>



## 📖 About  
**Final Project for Fundamental Programming**  
Under the Supervision of **Prof. Bahador Bakhshi**  
*Fall 2019 | Computer Engineering*  

---

## 🏆 Project Overview  
Lonely Cells is a turn-based strategy game where players control cells on a hexagonal grid. The goal is to maximize energy by moving, splitting cells, and collecting resources. The game supports single-player and multiplayer modes, with dynamic map interactions and strategic decision-making.  

### ✨ Key Features:  
- **🧭 Hexagonal Grid Movement**: Cells navigate six directions (N, NE, SE, S, SW, NW).  
- **🔧 Cell Actions**:  
  - *🚶 Move*: Traverse non-forbidden blocks.  
  - *🔄 Split*: Divide cells in Mitosis blocks (requires ≥80 energy).  
  - *⚡ Boost Energy*: Collect resources (+15 energy) in Source blocks.  
- **🗺️ Custom Maps**: Load pre-generated binary maps or design your own.  
- **⏪ Undo Functionality**: Revert moves in single-player mode.  
- **💾 Save/Load**: Preserve game states for future sessions.  

---

## 🎲 Game Mechanics  
### 🗺️ Map Structure  
**Block Types**:  
- `1/E` 🔋: Source (energy collection).  
- `2/M` 🧬: Mitosis (cell division).  
- `3/-` 🚫: Forbidden (inaccessible).  
- `4/0` ⬜: Normal (traversable).  

**📍 Coordinates**: Southwestern corner is `(0, 0)`; grid follows row-major order.  

### 🦠 Cell Rules  
- **🔋 Energy Cap**: 100 units per cell.  
- **🧪 Splitting**:  
  - Requires Mitosis block + adjacent empty space.  
  - Parent cell splits into two cells with 40 energy each.  
- **🎭 Player Symbols**: `X` (Player 1), `Y` (Player 2).  

---

## 🕹️ How to Play  
1. **🎯 Launch the Game**:  
   - Choose *New Game* (single/multiplayer) or *Load* a saved state.  
2. **📍 Place Cells**:  
   - Specify initial cell count; cells spawn randomly.  
3. **🔄 Take Turns**:  
   - Select a cell → choose action (*Move*/*Split*/*Boost*).  
   - In multiplayer, players alternate turns.  
4. **🏆 Win Condition**: Maximize total energy by game end.  

---

## 💻 Technical Implementation  
- **📊 Data Structures**: Linked lists for dynamic cell management.  
- **📂 File Handling**:  
  - Binary maps: `unsigned int` (size) + `n×n` chars (blocks).  
  - Save files store cell positions, energy, and map state.  
- **🧩 Modular Code**: Separated into `*.h/*.c` files (e.g., `map.c`, `cell.c`).  

---

## 🚀 Bonus Features (Extended Functionality)  
- **✏️ Map Editor**: Design and save custom maps.  
- **🎨 Graphical UI**: Optional libraries (e.g., SDL, OpenGL).  
- **🤖 AI Opponent**: Computer-controlled player in single-player mode.  
- **📝 Text-Based Maps**: Human-readable map files.  

---

## 📂 Repository Structure  
```plaintext
Lonely-Cells/  
├── src/                  # Source code  
│   ├── map.c             # Map loading/rendering  
│   ├── cell.c            # Cell operations  
│   └── game.c            # Main game logic  
├── maps/                 # Pre-built maps (binary/text)  
├── saves/                # Saved game states  
├── README.md             # This file  
└── docs/                 # Project PDF (specifications)  
```



---

## 🛠️ Getting Started  
1. **🔨 Compile**: Use `gcc` with linked files (e.g., `gcc src/*.c -o game`).  
2. **▶️ Run**: Execute binary + map file (e.g., `./game maps/default.bin`).
