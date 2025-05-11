#include <iostream>
#include <string>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    int RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults {
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

string Tabs(int NumberOfTabs) {
    string Tabs = "";
    for (int i = 0; i <= NumberOfTabs; i++) {
        Tabs += "\t";
    }
    return Tabs;
}

void SetWinnerScreen(enWinner Winner) {
    if (Winner == enWinner::Player)
        system("color 20");
    else if (Winner == enWinner::Computer)
    {
        system("color 40");
        cout << "\a";
    }
    else
        system("color E0");
}

enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}

void PrintRoundResult(stRoundInfo RoundInfo) {
    cout << "\n_____________Round[ " << RoundInfo.RoundNumber << "] __________" << endl;
    cout << "\nPlayer Choice : " << RoundInfo.Player1Choice << endl;
    cout << "\nComputer Choice : " << RoundInfo.ComputerChoice << endl;
    cout << "\nRound Winner [: " << RoundInfo.WinnerName << "] " << endl;
    cout << "\n_____________________________________________ " << endl;
    SetWinnerScreen(RoundInfo.Winner);
}

enWinner WhoWinTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice) {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enWinner::Computer;
        break;
    }

    return enWinner::Player;
}

enGameChoice ReadPlayerChoice() {
    int PlayerChoice;
    do {
        cout << "Enter your choice: Stone [1] Paper [2] Scissors [3] \n";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);
    return (enGameChoice)PlayerChoice;
}

string WinnerName(enWinner Winner) {
    string arrWinner[3] = { "Player", "Computer", "Draw" };
    return arrWinner[Winner - 1];
}

enWinner WhoWinTheGame(short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (PlayerWinTimes < ComputerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short HowManyRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {
    stGameResults GameResults;

    GameResults.GameRounds = HowManyRounds;
    GameResults.Player1WinTimes = PlayerWinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWinTheGame(PlayerWinTimes, ComputerWinTimes, DrawTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

stGameResults PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins : \n";
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWinTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
    }

    return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "-------------------------------------------------------\n\n";
    cout << Tabs(2) << "                + + + G A M E  O V E R + + +             \n";
    cout << Tabs(2) << "-------------------------------------------------------\n\n";
}

short ReadHowManyRounds() {
    short GameRounds;
    do {
        cout << "How many rounds (1 to 10)? " << endl;
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void ShowFinalGameResults(stGameResults GameResults) {
    cout << Tabs(2) << "_____________________[GAME RESULTS]_________________" << endl;
    cout << Tabs(2) << "Game Rounds          : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 Win Times    : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer2 Win Times  : " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw Times           : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner         : " << GameResults.WinnerName << endl;
    SetWinnerScreen(GameResults.GameWinner);
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << endl << Tabs(3) << "Do you want to play again? Y/N ? " << endl;
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
}