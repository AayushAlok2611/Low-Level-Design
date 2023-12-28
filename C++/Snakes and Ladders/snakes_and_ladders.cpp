# include<stdio.h>
# include<vector>
# include<map>
# include <string>
using namespace std;

//============ Snake and Ladder =========

// Here snake and ladder have common features this gives the hint that we can create some superclass which is extended
// by Snake and Ladder class
class Snake{
    private:
    int startCell;
    int endCell;
    public:
    int getEndCell(){}
};

class Ladder{
    private:
    int startCell;
    int endCell;
    public:
    int getEndCell(){}
};

// ============== Dice (Following Singleton Pattern)==============
class Dice{
    private:
    int min = 1;
    int max = 6;
    static Dice* instance;
    Dice(){}

    public:
    static Dice* getInstance()
    {
        if(instance == NULL)
        {
            instance = new Dice();
        }
        return instance;
    }

    int getRandomNumber(){}
};

// ============== Player ======================
class Player{
    private:
    string name;
    string email;
    public:
    int rollDice(Dice* dicePtr){
        return dicePtr->getRandomNumber();
    }
};

//============ Board =================================
class Board{
    private:
    int finish = 100;
    int start = 0;
    map<int, Snake> cellToSnake;
    map<int, Ladder> cellToLadder;
    map<Player, int> playerPositions;

    public:
    Board(){}
    Board(vector<Snake> snakes, vector<Ladder> ladders, vector<Player> players){}
    void updatePlayerPosition(Player player, int newPosition){}
    bool isMoveValid(int curPosition, int noOfMoves){}
    bool isThereSnakeInCell(int cell){}
    bool isThereLadderInCell(int cell){}
    int getEndCellConsideringSnakeAtCell(int cell){}
    int getEndCellConsideringLadderAtCell(int cell){}
    int getPlayerCurrentPosition(Player player){}
    bool isPostionTheFinalPosition(int cell){}
};

//================= Game ===============================
class Game{
    private:
    Board board;
    vector<Player> players;
    bool gameOver;
    int currentPlayerIndex;
    Dice* dicePtr;
    Player getCurrentPlayer(){}

    public:
    Game(){}
    Game(vector<Player> players, Dice* dicePtr){
        // We can add exception throwing logic that there should ne atleast 2 players
        currentPlayerIndex = 0;
        gameOver = false;
        for(Player player:players)this->players.push_back(player);
        this->dicePtr = dicePtr;
    }
    bool makeMoveForCurrentPlayer(){
        Player player = getCurrentPlayer();
        int curPosition = board.getPlayerCurrentPosition(player);
        int noOfMoves = player.rollDice(dicePtr);

        if(!board.isMoveValid(curPosition, noOfMoves)) return false;

        int endPosition = curPosition + noOfMoves;

        bool isSnakePresent = board.isThereSnakeInCell(endPosition);
        if(isSnakePresent)
        {
            endPosition = board.getEndCellConsideringSnakeAtCell(endPosition);
        }

        bool isLadderPresent = board.isThereLadderInCell(endPosition);
        if(isLadderPresent)
        {
            endPosition = board.getEndCellConsideringLadderAtCell(endPosition);
        }
        board.updatePlayerPosition(player, endPosition);

        bool shouldEndGame = board.isPostionTheFinalPosition(endPosition);

        if(shouldEndGame) endGame();

        return true;
    }
    void changeCurrentPlayer(){}
    void endGame(){
        gameOver = true;
    }
    bool isGameOver(){
        return gameOver;
    }
};

// ============= Game service (Follows singleton design pattern) =============

class GameService{
    private: 
    Game game;
    static GameService* instance;
    GameService(){}

    public:
    static GameService* getInstance(){
        if(instance == NULL)
        {
            instance = new GameService();
        }
        return instance;
    }
    Player createPlayer(string name, string email){}
    void startGame(vector<Player> players, Dice* dicePtr){
        game = Game(players, dicePtr);
        while(!game.isGameOver())
        {
            bool wasMoveCompleted = game.makeMoveForCurrentPlayer();
            if(wasMoveCompleted) game.changeCurrentPlayer();
        }
    }
};


