#include<iostream>
#include<stdlib.h>
#include<ctime>

using namespace std;

char board[][3]={
                {'1','2','3'},
                {'4','5','6'},
                {'7','8','9'}
                        };
char current_marker;
int current_player;

//Display the tic tac toe board
void drawBoard(){
    cout<<" "<< board[0][0]<<" | " << board[0][1] << " | "  << board[0][2] << "\n";
    cout<<" "<<"----------\n";
    cout<<" "<< board[1][0]<<" | " << board[1][1] << " | "  << board[1][2] << "\n";
    cout<<" "<<"----------\n";
    cout<<" "<< board[2][0]<<" | " << board[2][1] << " | "  << board[2][2] << "\n";
}

//Set the marker in postion
bool placemarker(int slot){
    int row;
    int col;

    //Converting postion given to corresponding index
    if(slot % 3 == 0){
        row = (slot / 3)-1;
        col = 2;
    }
    else{
        row = slot / 3;
        col = (slot % 3)-1;
    }
    
    //Checking weather the place is already fill
    if(board[row][col]!='X' && board[row][col]!='O'){
        board[row][col] = current_marker;
        return true;
    }
    else{
        return false;
    }
}

//Finding the winner function 
int winner(){
    for(int i = 0;i<3;i++){
        if(board[i][0]==board[i][1]  && board[i][1]==board[i][2]) return current_player;
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i]) return current_player;
    }
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2]) return current_player;
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0]) return current_player;

    return 0;
}

//Swaping the players on their corresponding chance
void swap(){
    if(current_player==1)current_player=2;
    else current_player=1;
    if(current_marker=='X')current_marker='O';
    else current_marker = 'X';
}

//This function play as computer , it is done by randomly selecting numbers b/w 1- 9
void com_input(){
    srand((unsigned)time(0));
    int slot;
    do{
        slot = (rand()%9)+1;
    }while(!placemarker(slot));
}


// Main game part
void game_com(int option){
    cout<<"Player one choose your marker(X/O): ";
    char marker;
    cin >> marker;
    current_marker = marker;
    current_player = 1;
    int i;
    drawBoard();
    for(i=0;i<9;i++){
        int slot;
        
        if((current_player==1 )|| (current_player==2 && option!=1) ){ //Check weather the computer or player is playing if player the inner block execute
            cout<<"Its player " << current_player << "'s turn. Enter the slot: ";
            cin>>slot;
            if(slot>9 || slot<1){
                cout<<"You have entered invalid slot!\n";
                i--;
                continue;
                }
            if(!placemarker(slot)){
                cout<<"You have entered in a preoccupied space!\n";
                i--;
                continue;
            }
        }else{ //Computer part execute
            com_input();
        }
        cout<<"\n";
        drawBoard();
        cout<<"\n\n";
        int win = winner();
        if(win==1){
            cout<<"The first player won the game!\n";
            break;
        }
        if(win==2){
            if(option==1){
                cout<<"The Computer won the game!\n";
                break;
            }else{
                cout<<"The Second player won the game!\n";
                break;
            }
        }
        swap();
    }
    if(i==9) cout<<"The game was a tie!\n"; // if 9 steps are complete and no winner then the game is consider as tie
    else cout<<"Thanks for playing!";
}

//Game interface
void interface(){
    cout<<"Hello welcome to tic-tac-toe!\n";
    int n;
    do{
        cout<<"Plz Enter the mode of game play require:\n";
        cout<<"1)Com VS Player\n2)Player VS Player\n";
        cout<<"Select a option: ";
        cin>>n;
        if(n!=1 && n!=2){
            cout<<"\nInvalid option\n";
        }
    }while(n!=1 && n!=2); 
    game_com(n);
}

int main(){
    interface();
}