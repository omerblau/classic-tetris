# Console Tetris with AI and Bomb Mechanics

A console-based Tetris game written in C++, supporting up to two players with flexible human/computer combinations. Built using classic object-oriented principles and designed for educational and gameplay experimentation.

## 🎮 Game Features

- Classic Tetris experience in a Windows console
- Up to **2 players**: any player can be either **human** or **AI-controlled**
- Unique **"Bomb" block** that clears an area upon collision
- AI players can compete against humans or each other
- Real-time block movement and rotation
- Color rendering support (toggleable)

## 🧠 Technical Highlights

- Custom `Shape`, `Block`, and `Board` classes manage Tetris logic and rendering
- AI implemented in `player_computer`, with decision-making via `Move` evaluation
- Abstract `Player` base class supports polymorphic behavior
- Board collision, row removal, and scoring implemented manually
- Manual cursor control and drawing using `gotoxy` and `clrscr`

## 🗂️ Project Structure

- `tetris.sln` – Visual Studio solution
- `block.*`, `shape.*`, `point.*` – Represent Tetris blocks and their movement
- `board.*` – Game board logic (drawing, collision, score)
- `player_human.*`, `player_computer.*` – Human and AI player logic
- `move.*` – AI move evaluation and scoring
- `game.*` – Game loop and control flow
- `general.*` – Console drawing helpers

## 🛠️ Build Instructions

1. Open `tetris.sln` in **Visual Studio** (any recent version should work)
2. Make sure build target is set to **x86 Console Application**
3. Press `Ctrl + F5` to build and run

No external dependencies or libraries are required beyond the standard Windows console environment.

## 🚀 How to Play

- Control falling Tetris blocks in real-time
- Clear rows for points; bombs clear multiple rows/columns
- Customize player types (human/computer) via game menu
- Win by outlasting or outscoring the opponent

## 📋 Notes

- Project is designed for learning and experimentation
- AI uses a basic scoring system and can be extended
- Console rendering is Windows-specific (uses `gotoxy`)

## 📄 License

This project was created as part of an academic assignment and is intended for learning purposes.
