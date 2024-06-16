#include <iostream>

const int SIZE = 3;
char board[SIZE][SIZE];
char current_marker;
int current_player;

void drawBoard()
{
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
    std::cout << "---|---|---\n";
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    std::cout << "---|---|---\n";
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
}

bool placeMarker(int row, int col)
{
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ')
    {
        return false;
    }
    board[row][col] = current_marker;
    return true;
}

int winner()
{
    // Rows
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            return current_player;
        }
    }

    // Columns
    for (int i = 0; i < SIZE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return current_player;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return current_player;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return current_player;
    }

    return 0;
}

void swapPlayerAndMarker()
{
    if (current_marker == 'X')
    {
        current_marker = 'O';
    }
    else
    {
        current_marker = 'X';
    }
    current_player = (current_player == 1) ? 2 : 1;
}

void resetBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

int main()
{
    std::cout << "Welcome to Tic Tac Toe!\n";
    current_marker = 'X';
    current_player = 1;
    resetBoard();

    int winner_player = 0;
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        int row, col;
        drawBoard();
        std::cout << "Player " << current_player << "'s turn. Enter your move (row and column): ";
        std::cin >> row >> col;
        row--; // Convert to 0-based index
        col--;

        if (!placeMarker(row, col))
        {
            std::cout << "Invalid move! Try again.\n";
            i--;
            continue;
        }

        winner_player = winner();
        if (winner_player != 0)
        {
            drawBoard();
            std::cout << "Player " << winner_player << " wins!\n";
            break;
        }
        swapPlayerAndMarker();
    }

    if (winner_player == 0)
    {
        drawBoard();
        std::cout << "It's a tie!\n";
    }

    return 0;
}
