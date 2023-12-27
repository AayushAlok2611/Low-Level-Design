# include<stdio.h>
# include<vector>
# include<map>
# include <string>

// need to use printf and scanf to get i/p and o/p
using namespace std;


// ========= required enums ====================
enum Colour {White , Black};

// ================== Chess Cell ============================
class ChessCell{
    private:
    char column;
    int row;
};

// ====================== Chess Pieces ==========================

// interface for Chess Pieces
class ChessPiece{
    private:
    Colour colour;

    public:
    // Since this is a virtual method , therfore runtime binding , i.e is a pointer of type CHessPiece has address of one of its 
    // derived classes then when we call ptr->isEndPositionValid. The isEndPositionValid function of the derived class is called;
    virtual bool isEndPositionValid(ChessMove move) = 0;
};

class Pawn: public ChessPiece{
    public:
    bool isEndPositionValid(ChessMove move){}
};

class Rook: public ChessPiece{
    public:
    bool isEndPositionValid(ChessMove move){}
};


class Knight: public ChessPiece{
    public:
    bool isEndPositionValid(ChessMove move){}
};


class Bishop: public ChessPiece{
    public:
    bool isEndPositionValid(ChessMove move){}
};


class Queen: public ChessPiece{
    public:
    bool isEndPositionValid(ChessMove move){}
};


class King: public ChessPiece{
    public:
    bool isEndPositionValid(ChessMove move){}
};

// ==================== ChessMove ==========================
class ChessMove{
    private:
    ChessCell start;
    ChessCell end;
    ChessPiece* piecePtr; // Here using pointers because we can use pointers of base class to point at derived classes.

    public:
    bool isValidMove(ChessBoard board){
        //1) Check if end of the move is in the board
        //2) Check if the ChessPiece can actually move to the end cell or not
    }
};

// ========================= Chess Board ====================================
class ChessBoard{
    private:
    vector<ChessCell> cells;
    map<ChessCell, ChessPiece*> cellToPiecePtrMap;
    void removePieceFromBoard(ChessPiece* piecePtr, ChessCell cell){}
    bool isCellInBoard(ChessCell cell){}

    public:
    ChessPiece* getPointerToPieceAtCell(ChessCell cell){}
    bool makeMove(ChessCell start, ChessCell end){
        //1)  Check is a ChessPiece present at start
        // 2) If ChessPiece present , create Move object and check if it is valid
    }
    void printBoard(){}
};

// ======================== Chess Game ================================
class ChessGame {
    private:
    ChessBoard board;
    vector<ChessMove> movesPlayed;
    ChessPlayer currentPlayer;
    vector<ChessPlayer> players;
    void changeCurrentPlayer(){}

    public:
    bool makeMove(ChessCell start, ChessCell end){}

};

// ========== Chess Service ==========

// Singleton Design Pattern to ensure that always a single ChessService exists
class ChessService{
    private:
    static ChessService* instance;
    vector<ChessGame> chessGames;

    public:
    static ChessService* getChessServiceInstance()
    {
        if(instance == NULL)
        {
            instance = new ChessService();
        }
        return instance;
    }
    ChessPlayer createChessPlayer(Colour colour, string name, string email){}
    ChessGame initialiseChessGame(ChessPlayer player1, ChessPlayer player2){}


};

// ======================= Player ======================
class ChessPlayer{
    private:
    Colour colour;
    string name;
    string email;
};

