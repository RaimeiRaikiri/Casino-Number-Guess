#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Can bet 10, 50, 100
// LOW = 1 - 10 1.5x , Medium = 1 - 50 5x, HIGH = 1 - 100 10x

class player
{
    private:
        int accountBalance;
        int currentBet;
        int guessedNumber;

    public:

        player() {
            accountBalance = 100;
        }
        void printBalance()
        {
            cout << "Account balance: £" << accountBalance << '\n' << '\n';
        }
        int getBalance()
        {
            return accountBalance;
        }
        void addToBalance(int wonMoney)
        {
            accountBalance += wonMoney;
        }
        void betOnRound()
        {
            int moneyBet;
            if (accountBalance >= 100)
            {
                cout << "You can bet 10, 50 or 100 on this round \n";
                cout << "Type 10, 50 or 100 to place the bet: ";
                cin >> moneyBet;
                cout << '\n';
            }
            else if (accountBalance >= 50)
            {
                cout << "You can bet 10 or 50 on this round \n";
                cout << "Type 10, 50 to place the bet: ";
                cin >> moneyBet;
                cout << '\n';
            }
            else {
                cout << "You can bet 10 on this round";
                cout << "Type 10 to place the bet: ";
                cin >> moneyBet;
                cout << '\n';
            }

            if (moneyBet == 10 || moneyBet == 50 || moneyBet == 100)
            {
                accountBalance -= moneyBet;
                currentBet = moneyBet;
            }
            else {
                cout << "You have not typed an applicable bet, defaulting to 10 \n";
                accountBalance -= 10;
                currentBet = 10;
            }
        }
        int getBet()
        {
            return currentBet;
        }
        void guessNumber(int level)
        {
            int guess;
            switch (level){
                case 0:
                    cout << "Guess a number between 1-10: ";
                    cin >> guess;
                    cout << '\n';
                    break;
                case 1:
                    cout << "Guess a number between 1-50: ";
                    cin >> guess;
                    cout << '\n';
                    break;
                case 2:
                    cout << "Guess a number between 1-100: ";
                    cin >> guess;
                    cout << '\n';
                    break;
                default:
                    break;
            }
            if (guess)
            {
                guessedNumber = guess;
            }
        }
        int getGuessedNumber()
        {
            return guessedNumber;
        }
};

class game
{
    private:
        int generatedNumber;
        enum Level {
            LOW,
            MEDIUM,
            HIGH
        };
        enum Level level;
        int roundNumber;
    public:
        game() {
            roundNumber = 1;
            level = LOW;
        }
        Level getCurrentLevel()
        {
            return level;
        }
        void setCurrentLevel()
        {
            string levelString;
            cout << "There are 3 levels of difficulty to select from: \n";
            cout << "Low: guess from 1 - 10, Medium: guess from 1 - 50, High: guess from 1 - 100 \n" << '\n';
            cout << "Each level gives a different multiplier to your placed bet on a win: \n";
            cout << "Low: 2x, Medium: 5x, High: 10x \n";
            cout << "Type Low, Medium or High to select the difficulty: ";
            cin >> levelString;
            cout << '\n';

            // Convert user input to upper so it matches enum
            for (int i = 0; i < levelString.length(); i++)
                levelString[i] = toupper(levelString[i]);

            if (levelString == "LOW")
            {
                level = LOW;
            }
            else if (levelString == "MEDIUM")
            {
                level = MEDIUM;
            } 
            else if (levelString == "HIGH")
            {
                level = HIGH;
            }

        }
        void generateNumber(enum Level level)
        {
            srand(time(0));

            switch (level)
            {
            case LOW:
                generatedNumber = rand() % 11 + 1;
                break;
            case MEDIUM:
                generatedNumber = rand() % 51 + 1;
                break;
            case HIGH:
                generatedNumber = rand() % 101 + 1;
            default:
                break;
            }
        }
        int gameWin(player player1)
        {
            int winnings;
            cout << "The computer chose: " << generatedNumber << '\n';
            cout << "You chose: " << player1.getGuessedNumber() << '\n';

            if (player1.getGuessedNumber() == generatedNumber)
            {
                cout << "You guessed correctly!" << '\n';
                switch (level)
                {
                    case LOW:
                        winnings = player1.getBet() * 2;
                        cout << "You win: £" << winnings << '\n';
                        return winnings;
                    case MEDIUM:
                        winnings = player1.getBet() * 5;
                        cout << "You win: £" << winnings << '\n';
                        return winnings;
                    case HIGH:
                        winnings = player1.getBet() * 10;
                        cout << "You win: £" << winnings << '\n';
                        return winnings;
                }
            }
            else
            {
                cout << "You guessed incorrectly and lose the money you bet" << '\n';
                return 0;
            }
        }
        void incrementRound()
        {
            roundNumber++;
        }
        bool ensurePlayerHasMoney(player player1)
        {
            if (player1.getBalance() < 10)
            {
                return false;
            }
            else{
                return true;
            }
        }
        void playGame(player player1)
        {
            bool playerGotMoney = true;
            do 
            {
                if (roundNumber == 1)
                {
                    player1.printBalance();
                    setCurrentLevel();
                    player1.betOnRound();
                    generateNumber(getCurrentLevel());
                    player1.guessNumber(getCurrentLevel());
                    int winnings = gameWin(player1);
                    if (winnings != 0)
                    {
                        player1.addToBalance(winnings);
                    }
                    incrementRound();
                }
                else {
                    cout << '\n';
                    if (ensurePlayerHasMoney(player1) == false)
                    {
                        cout << "You have no money to continue playing, come back another day with deeper pockets!";
                        playerGotMoney = false;
                        break;
                    }
                    player1.printBalance();
                    setCurrentLevel();
                    player1.betOnRound();
                    generateNumber(getCurrentLevel());
                    player1.guessNumber(getCurrentLevel());
                    int winnings = gameWin(player1);
                    if (winnings != 0)
                    {
                        player1.addToBalance(winnings);
                    }
                    incrementRound();
                }
            }
            while (playerGotMoney);
        }

};

int main()
{
    game game1;
    player player1;
    game1.playGame(player1);
    return 0;
}