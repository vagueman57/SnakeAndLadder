#include <iostream>
#include <map>
#include <queue>
#include <cstdlib> // For rand() function
#include <ctime>   // For time() function

using namespace std;

// Class representing a player
class Player {
public:
    string name;
    int position;

    Player(string name) {
        this->name = name;
        this->position = 1; // Start at position 1
    }
};

// Class representing the Snake and Ladder board
class SnakeLadder {
    map<int, int> snakes;   // Store head and tail of snakes
    map<int, int> ladders;  // Store bottom and top of ladders
    int boardSize;

public:
    SnakeLadder(int boardSize) {
        this->boardSize = boardSize;
        initializeBoard();
    }

    // Initialize snakes and ladders on the board
    void initializeBoard() {
        // Snakes: key is head, value is tail
        snakes[16] = 6;
        snakes[47] = 26;
        snakes[49] = 11;
        snakes[56] = 53;
        snakes[62] = 19;
        snakes[64] = 60;
        snakes[87] = 24;
        snakes[93] = 73;
        snakes[95] = 75;
        snakes[98] = 78;

        // Ladders: key is bottom, value is top
        ladders[2] = 38;
        ladders[7] = 14;
        ladders[8] = 31;
        ladders[15] = 26;
        ladders[28] = 84;
        ladders[21] = 42;
        ladders[36] = 44;
        ladders[51] = 67;
        ladders[71] = 91;
        ladders[78] = 98;
    }

    // Get the final position after encountering snakes or ladders
    int getNewPosition(int currentPosition) {
        if (snakes.find(currentPosition) != snakes.end()) {
            cout << "Oh no! Bitten by a snake at " << currentPosition << " down to " << snakes[currentPosition] << endl;
            return snakes[currentPosition];
        }
        if (ladders.find(currentPosition) != ladders.end()) {
            cout << "Yay! Climbed a ladder from " << currentPosition << " to " << ladders[currentPosition] << endl;
            return ladders[currentPosition];
        }
        return currentPosition;
    }

    int getBoardSize() {
        return boardSize;
    }
};

// Class representing the game logic
class Game {
    SnakeLadder board;
    queue<Player> players;
    bool gameOver;

public:
    Game(int boardSize, vector<string> playerNames) : board(boardSize) {
        for (string name : playerNames) {
            players.push(Player(name));
        }
        gameOver = false;
        srand(time(0)); // Seed random number generator
    }

    // Roll the dice
    int rollDice() {
        return (rand() % 6) + 1; // Generates a number between 1 and 6
    }

    // Play the game
    void play() {
        while (!gameOver) {
            Player currentPlayer = players.front();
            players.pop();

            cout << currentPlayer.name << "'s turn. Press enter to roll the dice." << endl;
            cin.ignore();

            int diceRoll = rollDice();
            cout << "Rolled a " << diceRoll << endl;

            int newPosition = currentPlayer.position + diceRoll;

            // Check if player exceeds board size
            if (newPosition > board.getBoardSize()) {
                cout << currentPlayer.name << " needs to roll the exact number to win." << endl;
            } else {
                newPosition = board.getNewPosition(newPosition);
                currentPlayer.position = newPosition;

                cout << currentPlayer.name << " moved to position " << currentPlayer.position << endl;

                // Check if player wins
                if (currentPlayer.position == board.getBoardSize()) {
                    cout << currentPlayer.name << " wins the game!" << endl;
                    gameOver = true;
                    return;
                }
            }

            // Push player back to the queue
            players.push(currentPlayer);
        }
    }
};

int main() {
    int boardSize = 100; 
    vector<string> playerNames = {"Raj", "Himanshu", "Priya"}; 

    Game snakeLadderGame(boardSize, playerNames);
    snakeLadderGame.play();
    
    return 0;
}
