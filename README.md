# Maze Game
Simple maze game written in C++ that uses standard output to draw the maze. 

# Build and run
To build the game C++ 20 is required. 

```
git clone https://github.com/Friday202/maze-game.git
cd maze-game
mkdir build
cd build
cmake ..
cmake --build .
```

# Notes 
The game loop is implemented as a simple input polling system within the engine, making it directly driven by player input. The Engine serves as the central class, responsible for handling input and delegating it to two primary components: the PlayerController and the GameManager.

The PlayerController processes movement-related input, while the GameManager is responsible for managing the overall game state, including loading, restarting, and saving the game.

All classes follow the Rule of Zero, with resources managed exclusively through smart pointers and standard library types such as vectors and strings, ensuring safe and maintainable memory management.