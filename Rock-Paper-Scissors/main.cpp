#include<iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::unordered_set;

class Player {
    public:
        virtual string getPlayerName() = 0;
        virtual string makeMove() = 0;
};

class ComputerPlayer : public Player {
    public:
        virtual string getPlayerName() override {
            return "Computer";
        }
};

class HumanPlayer : public Player {
    private:
        string playerName;
    public:
        HumanPlayer(string playerName) : playerName(playerName) {}

        string getPlayerName() override {
            return playerName;
        }

        string makeMove() override {
            string move;
            unordered_set<string> validMoves = {"Rock", "Paper", "Scissors"};
            while (true) {
                cout << "Choose your move. (Rock, Paper, Scissors)"<<endl;
                cin >> move;
                if (validMoves.find(move) != validMoves.end()) {
                    break;
                } else {
                    cout << "Invalid move. Please try again." << endl;
                }
            }
            return move;
        }
};

class RandomComputerPlayer : public ComputerPlayer {
    public:
        string makeMove() override {
            string moves[3] = {"Rock", "Paper", "Scissors"};
            return moves[rand() % 3];
        }
};

string whoIsWinner(const string& move1, const string& move2) {
    if (move1 == move2) {
        return "Draw";
    }
    if ((move1 == "Rock" && move2 == "Scissors") ||
        (move1 == "Scissors" && move2 == "Paper") ||
        (move1 == "Paper" && move2 == "Rock")) {
        return "Player";
    } else {
        return "Computer";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    string playerName;
    cout << "Enter your player name: ";
    cin >> playerName;

    HumanPlayer human(playerName);
    RandomComputerPlayer computer;

    int playerScore = 0;
    int computerScore = 0;
    char playAgain;

    do {
        string playerMove = human.makeMove();
        string computerMove = computer.makeMove();

        cout << human.getPlayerName()<<" choose "<<playerMove<<"."<< endl;
        cout << computer.getPlayerName()<<" choose "<<computerMove<<"."<<endl;

        string result = whoIsWinner(playerMove, computerMove);
        if (result == "Player") {
            cout << "The winner of this round " << human.getPlayerName() << endl;
            playerScore++;
        } else if (result == "Computer") {
            cout << "The winner of this round " << computer.getPlayerName() << endl;
            computerScore++;
        } else {
            cout << "This round ended in a draw." << endl;
        }

        cout << "Current score - " << human.getPlayerName() << ": " << playerScore << " Computer: " << computerScore << endl;
        cout << "Would you like to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y');

    cout << "Total score - " << human.getPlayerName() << ": " << playerScore << " Computer: " << computerScore << endl;
    cout << "Thank you for playing!" << endl;

    return 0;
}