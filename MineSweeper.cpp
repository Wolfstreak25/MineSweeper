#include<bits/stdc++.h>
using namespace std;

enum CellType
{
  Safe = 0,
  Mine = -1,
  Count = 1
};

class Cell
{
  private:
    CellType cellType = Safe;
    int data = 0;
    friend class Board;
    friend class GameBoard;
};
  
class Board
{
  private:
    Cell board[9][9];
  public:
    Board(int inX, int inY)
    {
      addMine(inX,inY);
      initialize();
    }

    void addMine(int inX, int inY)
    {
      int mineCount = 0;
      while(mineCount <= 10)
      {
          int x = int(rand())%10;
          int y = int(rand())%10;
          if(( x != inX || y != inY ) && board[x][y].cellType != Mine) //x <= inX - 1 || y <= inY - 1 || x >= inX + 1 || y >= inY + 1 ) && 
              {
                  board[x][y].cellType = Mine;
                  board[x][y].data = -1 ;
                  mineCount++;
              }
      }
    }

    void initialize()
    {
      for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                AdjacentMine(i, j);
            }
        }
    }

    void AdjacentMine(int x, int y)
    {
      int count = 0;
      if(board[x][y].cellType != Mine)
      {
        for(int i = x-1; i<=x+1; i++)
        {
          for(int j = y-1; j <= y+1; j++)
          {
            if(i >= 0 && j >= 0 && i < 9 && j < 9)
            {
              if((i != x || j != y) && board[i][j].cellType == Mine)
                count++;
            }
          }
        }
        if(count != 0)
        {
          board[x][y].data = count;
          board[x][y].cellType = Count;
        }
      }
    }
  friend class GameBoard;
};

class GameBoard
{
  private:
    char showboard[9][9];
    Board *main;
bool gameOver = false;
  public:
    GameBoard(int inX, int inY)
    {
      for(int i = 0; i < 9; i++)
        {
          for(int j = 0; j < 9; j++)
          {
            showboard[i][j] = ' ';
          }
        }
      main = new Board(inX, inY);
      revealAll(inX, inY);
      Print(inX, inY);
    }

    void Print(int x, int y)
    {
      int count = 0;
      cout<<"\n ";
      for(int j = 0; j < 9; j++)
            {
                cout<<" | "<<j;
            }
      cout<<" |\n\n";
        for(int i = 0; i < 9; i++)
        {   cout<<i;
            for(int j = 0; j < 9; j++)
            {
              if(showboard[i][j] != ' ')
              {
                count ++;
              }
              if(i == x && j == y && showboard[i][j] != '*' )
                {cout<<" | X";}
              else{
              cout<<" | "<<showboard[i][j];}
            }
            cout<<" |\n";
        }
      if(count == 71){
        gameOver = true;}
    }
    
    void revealCurrent(int i, int j)
    {
      if(main->board[i][j].data == 0)
      {
        showboard[i][j] = char(main->board[i][j].data)+48;;
        revealAll(i, j);
      }
      if(main->board[i][j].cellType == Count)
      {
        showboard[i][j] = char(main->board[i][j].data)+48;
      }
      if(main->board[i][j].cellType == Mine)
      {
        cout<<"\nYou tripped on a mine\n";
        showboard[i][j] = '*';
        gameOver = true;
      }
      Print(i,j);
    }
    
    void revealAll(int x, int y)
    {
           
            for(int i = x-1; i<=x+1; i++)
            {
              for(int j = y-1; j <= y+1; j++)
              {
                if(i >= 0 && j >= 0 && i < 9 && j < 9)
                {
                  if((i != x || j != y))
                    showboard[i][j]= char(main->board[i][j].data)+48;
                } 
              }
            }
    }
bool GameOver()
{
  return gameOver;
}
};

class Gameplay
{
  private:
    GameBoard *showBoard;
    int newX, newY, x, y;
  public:
  Gameplay(int inX, int inY)
  {
    x = inX; y = inY;
    showBoard = new GameBoard(x, y);
    InputInstruction();
  }
  void InputInstruction()
  {
    cout<<"input direction according to numpad\n";
    cout<<"7: top left     8: up     9: top right\n\n4: left         player    6: right \n\n1: bottom left  2: down   3: bottom right\n";
  }
  void inputManager()
  {
    string getInput;
    int input;
    do
    {
      cout<<"Give Direction : ";
      cin>>getInput;
      input = stoi(getInput);
        cout<<input;
    }while(!checkMove(input) || !InputCheck());
    showBoard->revealCurrent(newX, newY);
    x = newX, y = newY;
  }
  bool checkMove(int input)
  {
    switch(input)
    {
      //int newX, newY;
      case 1:
              newX = x+1; newY = y-1;
              break;
      case 2:
              newX = x+1; newY = y;
              break;
      case 3:
              newX = x+1; newY = y+1;
              break;
      case 4:
              newX = x; newY = y-1;
              break;
      case 6:
              newX = x; newY = y+1;
              break;
      case 7:
              newX = x-1; newY = y-1;
              break;
      case 8:
              newX = x-1; newY = y;
              break;
      case 9:
              newX = x-1; newY = y+1;
              break;
      default:
              return 0;
    }
    return 1;
  }
  bool InputCheck()
  {
    if(newX >= 0 && newX <= 9 && newY >= 0 && newY <= 9)
      {
        return 1;
      }
    cout<<"Can't move to this direction";
    return 0;
  }
  bool GameOver()
  {
    return showBoard->GameOver();
  }
};

void GameLoop()
{
  int inX,inY;
    cout<<"Give the initial Adress\n";
    cout<<"Give X : ";cin>>inX;
    cout<<"Give Y : ";cin>>inY;
  Gameplay *game = new Gameplay(inX , inY);
  do
  {
    game->inputManager();
  }while(!game->GameOver());
  cout<<"\nThanks For Playing";
}
int main()
{
  srand(0);
  GameLoop();
  return 0;
}