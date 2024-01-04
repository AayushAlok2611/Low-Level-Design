#include <stdio.h>
#include <vector>
#include <exception>
#include <stdexcept>
#include <string>
#include <mutex>
#include <iostream>
using namespace std;

mutex myMutex;

// =============== PieceTypeEnum =======
enum PieceType{X=1, O=-1,N=0}; // Here I am assigning default value intergers 

// ========= Exceptions of the program =======
class InvalidMoveError: public exception{
    private:
    string errorMsg;
    public:
    InvalidMoveError(string errorMsg): errorMsg(errorMsg){}
    string getErrorMsg(){return errorMsg;}
};

class GameNotOverError: public exception{
    private:
    string errorMsg;
    public:
    GameNotOverError(string errorMsg): errorMsg(errorMsg){}
    string getErrorMsg(){return errorMsg;}
};

// ================= Player ==================
class Player{
    private:
    string name;
    PieceType pieceType;

    public:
    Player(){}
    Player(string name, PieceType pieceType):name(name), pieceType(pieceType){}
    PieceType getPieceTypeForPlayer(){return pieceType;}
};

// ================== Move =================
class Move{
    private:
    Player player;
    int row;
    int col;

    public:
    Move(Player player, int row, int col):player(player),row(row), col(col){}
    int getRow(){return row;}
    int getCol(){return col;}
    Player getPlayer(){return player;}
    PieceType getPieceTypeForMove(){
        return player.getPieceTypeForPlayer();
    }
};

// ============= Board ================
class Board {
    private:
    int rows;
    int cols;
    vector<vector<PieceType>> board;
    bool isMoveValid(Move move){
        int row = move.getRow();
        int col = move.getCol();
        if(row < 1 || row > rows || col < 1 || col > cols) return false;
        return true;
    }

    public:
    Board(){}
    Board(int rows, int cols): rows(rows), cols(cols), board(rows, vector<PieceType>(cols, N)){}

    bool isCurrentMoveWinningMove(Move currentMove)
    {
        int moveRow = currentMove.getRow();
        int moveCol = currentMove.getCol();
        PieceType pieceType = currentMove.getPieceTypeForMove();

        bool isWinningMove = false;

        // Check if in same there are 3 or not, including move cell

        // Check if in same col there are 3 or not, including move cell

        // Check if in diagonal there are 3 or not, including move cell

        return isWinningMove;
    }

    void makeMove(Move move) noexcept(false){
        if(!isMoveValid(move))
        {
            throw InvalidMoveError("Invalid move: Out of bounds.");
        }
        int moveRow = move.getRow();
        int moveCol = move.getCol();
        PieceType pieceType = move.getPieceTypeForMove();
        board[moveRow][moveCol] = pieceType;
    }
    void printBoard(){}

};

// ==================== Game ========================
class Game{
    private:
    vector<Move> moves;
    Board gameBoard;
    vector<Player> players;
    int currentPlayerIndex;
    bool gameOver = false;
    Player winner;

    void changeCurrentPlayer(){
        int n = players.size();
        currentPlayerIndex = (currentPlayerIndex + 1)%n;
    }
    void endGame(Player winner){
        gameOver = true;
        this->winner = winner;
    }
    Player getCurrentPlayer()
    {
        return players[currentPlayerIndex];
    }
    Move makeMoveObject(int row, int col)
    {
        Player currentPlayer = getCurrentPlayer();
        return Move(currentPlayer, row, col);
    }

    public:
    Game(int rows, int cols, vector<Player> players)
    {
        this->gameBoard = Board(rows, cols);
        this->players = players;
    }

    void makeMove(int row, int col) noexcept(false)
    {
        Move moveObj = makeMoveObject(row, col);
        gameBoard.makeMove(moveObj);

        if(gameBoard.isCurrentMoveWinningMove(moveObj))
        {   
            Player winner = moveObj.getPlayer();
            endGame(winner);
        }
    }

    Player getWinnerOfGame() noexcept(false){
        if(!isGameOver())
        {
            throw GameNotOverError("Game is Not yet over");
        }
        return winner;
    }

    bool isGameOver(){return gameOver;}

    void printBoard(){
        gameBoard.printBoard();
    }
};


// =========== GameService (Uses Thread safe Singleton design pattern) =================

class GameService{
    private:
    static GameService* instance;
    GameService(){}

    public:
    static GameService* getInstance()
    {   
        lock_guard<mutex> lock(myMutex);
        if(instance == NULL)
        {
            instance = new GameService();
        }
        return instance;
    }
    Player createPlayer(string name, PieceType pieceType)
    {
        return Player(name, pieceType);
    }
    Game initialiseGame(int rows, int cols, vector<Player> players)
    {
        Game game = Game(rows, cols, players);
        return game; 
    }
    void playGame(Game game)
    {
        while(!game.isGameOver())
        {   
            int row, col;
            cout<<"Enter the number of rows: ";
            cin>>row;

            cout<<"Enter the number of columns: ";
            cin>>col;
            try{
                game.makeMove(row, col);
                game.printBoard();
            } catch(InvalidMoveError &err){
                cout<<err.getErrorMsg();
            } 
        }
        // print the winning player
    }
};


GameService* GameService::instance = nullptr;

int main(){
    GameService* gameServicePtr = GameService::getInstance();

    // Input for player 1
    int p1;
    string n1;
    cout << "Enter piece type and name for player 1 (e.g., 1 John): Here 1 is for X";
    cin>>p1>>n1;
    PieceType piece1 = (PieceType)p1;
    Player player1 = gameServicePtr->createPlayer(n1, piece1);

    // Input for player 2
    int p2;
    string n2;
    cout << "Enter piece type and name for player 2 (e.g., O Jane): ";
    cin >> p2 >> n2;
    PieceType piece2 = (PieceType)p2;
    Player player2 = gameServicePtr->createPlayer(n2, piece2);

    // Initialize the game with players
    Game myGame = gameServicePtr->initialiseGame(3, 3, {player1, player2});

    // Play the game
    gameServicePtr->playGame(myGame);

    return 0;
}