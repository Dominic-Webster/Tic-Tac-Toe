#include <iostream>
#include <ctime>
#include <thread>
#include <queue>
#include <vector>
using namespace std;

void display(); void player(); void computer(); void make_move(); void play();
void is_over(); int evaluate(int spot); bool is_legal(string &move); void menu();
int TURN, SPOT;
bool game_over;
char winner;

char grid[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

int main(){
    srand(time(0));
    menu();
    exit(0);
}

void menu(){ //game menu
    system("clear");
    string x;
    cout << "  TIC TAC TOE\n\n";
    cout << " (1): Play Game\n (2): Exit Game\n -> ";
    cin >> x;
    if(x == "1"){play();}
    else{exit(0);}
}

void play(){ //control game
    game_over = false;
    for(int i = 0; i < 9; i++){ //clear board
        grid[i] = ' ';
    }
    TURN = 0;
    while(!game_over){ //iterate through moves till game over
        if(TURN == 0){player();}
        else{computer();}
        is_over();
    }
    system("clear");
    display();
    if(winner == 'X'){cout << "\n YOU WIN!\n";}
    else if(winner == 'O'){cout << "\n COMPUTER WINS!\n";}
    else{cout << "\n TIED GAME\n";}
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    string x;
    cout << "\n (1): Return to Menu\n -> ";
    cin >> x;
    menu();
}

void display(){ //show board
    cout << "     A   B   C " << endl;
    cout << "    ——— ——— ———" << endl;
    cout << " 1 | " << grid[0] << " | " << grid[1] << " | " << grid[2] << " |" << endl;
    cout << "   |———|———|———|" << endl;
    cout << " 2 | " << grid[3] << " | " << grid[4] << " | " << grid[5] << " |" << endl;
    cout << "   |———|———|———|" << endl;
    cout << " 3 | " << grid[6] << " | " << grid[7] << " | " << grid[8] << " |" << endl;
    cout << "    ——— ——— ———" << endl;
}

void player(){ //player turn
    string move;
    SPOT = 0;
    do{
        system("clear");
        display();
        cout << "\n Your turn\n Place an 'X' (A1, B2, etc)\n -> ";
        cin >> move;
    }while(!is_legal(move));
    grid[SPOT] = 'X';
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    TURN = 1;
}

bool is_legal(string &move){ //checks for a valid move
    if(move.length() != 2){return false;}
    char a = toupper(move.at(0)), b = toupper(move.at(1));
    if(a != 'A' && a != 'B' && a != 'C'){return false;}
    if(b != '1' && b != '2' && b != '3'){return false;}
    if(b == '1'){
        switch(a){
            case 'A': SPOT = 0;
                break;
            case 'B': SPOT = 1;
                break;
            default: SPOT = 2;
        }
    }
    else if(b == '2'){
        switch(a){
            case 'A': SPOT = 3;
                break;
            case 'B': SPOT = 4;
                break;
            default: SPOT = 5;
        }
    }
    else{
        switch(a){
            case 'A': SPOT = 6;
                break;
            case 'B': SPOT = 7;
                break;
            default: SPOT = 8;
        }
    }
    if(grid[SPOT] != ' '){return false;}
    return true;
}

void computer(){ //computer turn
    system("clear");
    display();
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    cout << "\n Computer's turn\n";
    queue <int> moves;
    vector <int> the_list;
    for(int i = 0; i < 9; i++){ //get possible moves
        if(grid[i] == ' '){the_list.push_back(i);}
    }
    while(!the_list.empty()){ //add to queue randomly
        int i = rand() % the_list.size();
        moves.push(the_list.at(i));
        the_list.erase(the_list.begin() + i);
    }
    int best = moves.front();
    moves.pop();
    while(!moves.empty()){ //figure out best move
        if(evaluate(moves.front()) > evaluate(best)){best = moves.front();}
        moves.pop();
    }
    SPOT = best;
    grid[SPOT] = 'O';
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    cout << " Computer plays: ";
    switch (SPOT){
        case 0: cout << "A1"; break;
        case 1: cout << "B1"; break;
        case 2: cout << "C1"; break;
        case 3: cout << "A2"; break;
        case 4: cout << "B2"; break;
        case 5: cout << "C2"; break;
        case 6: cout << "A3"; break;
        case 7: cout << "B3"; break;
        default: cout << "C3"; break;
    }
    cout << endl;
    this_thread::sleep_for(chrono::seconds(1)); //wait briefly
    TURN = 0;
}

int evaluate(int spot){ //figure out how good a move is
    int factor = 0;
    grid[spot] = 'O'; //test turn
    if(spot == 4){factor += 10;} //middle space
    if(spot == 0 || spot == 2 || spot == 6 || spot == 8){factor += 5;} //corners
    //check to block
    //top row
    if(grid[0] == 'X' && grid[1] == 'X' && grid[2] != 'O'){factor -= 20;}
    if(grid[0] == 'X' && grid[2] == 'X' && grid[1] != 'O'){factor -= 20;}
    if(grid[1] == 'X' && grid[2] == 'X' && grid[0] != 'O'){factor -= 20;}
    //middle row
    if(grid[3] == 'X' && grid[4] == 'X' && grid[5] != 'O'){factor -= 20;}
    if(grid[3] == 'X' && grid[5] == 'X' && grid[4] != 'O'){factor -= 20;}
    if(grid[4] == 'X' && grid[5] == 'X' && grid[3] != 'O'){factor -= 20;}
    //bottom row
    if(grid[6] == 'X' && grid[7] == 'X' && grid[8] != 'O'){factor -= 20;}
    if(grid[6] == 'X' && grid[8] == 'X' && grid[7] != 'O'){factor -= 20;}
    if(grid[7] == 'X' && grid[8] == 'X' && grid[6] != 'O'){factor -= 20;}
    //left column
    if(grid[0] == 'X' && grid[3] == 'X' && grid[6] != 'O'){factor -= 20;}
    if(grid[0] == 'X' && grid[6] == 'X' && grid[3] != 'O'){factor -= 20;}
    if(grid[3] == 'X' && grid[6] == 'X' && grid[0] != 'O'){factor -= 20;}
    //middle column
    if(grid[1] == 'X' && grid[4] == 'X' && grid[7] != 'O'){factor -= 20;}
    if(grid[1] == 'X' && grid[7] == 'X' && grid[4] != 'O'){factor -= 20;}
    if(grid[4] == 'X' && grid[7] == 'X' && grid[1] != 'O'){factor -= 20;}
    //right column
    if(grid[2] == 'X' && grid[5] == 'X' && grid[8] != 'O'){factor -= 20;}
    if(grid[2] == 'X' && grid[8] == 'X' && grid[5] != 'O'){factor -= 20;}
    if(grid[5] == 'X' && grid[8] == 'X' && grid[2] != 'O'){factor -= 20;}
    //pos-slope
    if(grid[6] == 'X' && grid[4] == 'X' && grid[2] != 'O'){factor -= 20;}
    if(grid[6] == 'X' && grid[2] == 'X' && grid[4] != 'O'){factor -= 20;}
    if(grid[4] == 'X' && grid[2] == 'X' && grid[6] != 'O'){factor -= 20;}
    //neg-slope
    if(grid[0] == 'X' && grid[4] == 'X' && grid[8] != 'O'){factor -= 20;}
    if(grid[0] == 'X' && grid[8] == 'X' && grid[4] != 'O'){factor -= 20;}
    if(grid[4] == 'X' && grid[8] == 'X' && grid[0] != 'O'){factor -= 20;}
    
    //check for win
    if(grid[0] == 'O' && grid[1] == 'O' && grid[2] == 'O'){factor += 100;}
    if(grid[3] == 'O' && grid[4] == 'O' && grid[5] == 'O'){factor += 100;}
    if(grid[6] == 'O' && grid[7] == 'O' && grid[8] == 'O'){factor += 100;}
    if(grid[0] == 'O' && grid[3] == 'O' && grid[6] == 'O'){factor += 100;}
    if(grid[1] == 'O' && grid[4] == 'O' && grid[7] == 'O'){factor += 100;}
    if(grid[2] == 'O' && grid[5] == 'O' && grid[8] == 'O'){factor += 100;}
    if(grid[6] == 'O' && grid[4] == 'O' && grid[2] == 'O'){factor += 100;}
    if(grid[0] == 'O' && grid[4] == 'O' && grid[8] == 'O'){factor += 100;}
  
    grid[spot] = ' '; //revert test

    return factor;
}

void is_over(){ //checks for game over
    if(grid[0] != ' ' && grid[0] == grid[1] && grid[1] == grid[2]){game_over = true; winner = grid[0];} //top row
    if(grid[3] != ' ' && grid[3] == grid[4] && grid[4] == grid[5]){game_over = true; winner = grid[3];} //middle row
    if(grid[6] != ' ' && grid[6] == grid[7] && grid[7] == grid[8]){game_over = true; winner = grid[6];} //bottom row
    if(grid[0] != ' ' && grid[0] == grid[3] && grid[3] == grid[6]){game_over = true; winner = grid[0];} //left column
    if(grid[1] != ' ' && grid[1] == grid[4] && grid[4] == grid[7]){game_over = true; winner = grid[1];} //middle column
    if(grid[2] != ' ' && grid[2] == grid[5] && grid[5] == grid[8]){game_over = true; winner = grid[2];} //right column
    if(grid[0] != ' ' && grid[0] == grid[4] && grid[4] == grid[8]){game_over = true; winner = grid[0];} //neg-slope
    if(grid[6] != ' ' && grid[6] == grid[4] && grid[4] == grid[2]){game_over = true; winner = grid[6];} //pos-slope
    
    //check for full board
    if(grid[0] != ' ' && grid[1] != ' ' && grid[2] != ' '){
        if(grid[3] != ' ' && grid[4] != ' ' && grid[5] != ' '){
            if(grid[6] != ' ' && grid[7] != ' ' && grid[8] != ' '){
                game_over = true; winner = '-';
            }
        }
    }
}
