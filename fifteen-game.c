/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// tile locations
int blankRow;
int blankCol;
int blankTile;
int tileRow;
int tileCol;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile <= 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(1000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // get size of board (array)
    int size = d * d;
    
    // iterate across rows
    for (int row = 0; row < d; row++)
    {
        // iterate across columns
        for (int col = 0; col < d; col++)
        {
            // set tile number and decrement array size by 1
            board[row][col] = size - 1;
            size--;
        }
    }
    // assign underscore (ASCII 95) to blank tile
    board[d-1][d-1] = 95;
    
    // if array size is even, swap 1 and 2
    if ((d * d) % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // iterate across rows
    for (int row = 0; row < d; row++)
    {
        // iterate across columns
        for (int col = 0; col < d; col++)
        {
            // replace zero with underscore
            if (board[row][col] == 95)
            {
                printf("%2c", '_');
            }
            // else print values per init
            else 
            {
               printf("%2d ", board[row][col]); 
            }
        }
        // move to next row
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
 
bool move(int tile)
{
    // iterate across rows
    for (int row = 0; row < d; row++)
    {
        // iterate across columns
        for (int col = 0; col < d; col++)
        {
            // if tile is in array
            if (board[row][col] == tile)
            {
                // if blank tile is above tile (not exceeding array dimension)
                if (board[row - 1][col] == 95 && row - 1 >= 0)
                {
                    // swap them
                    board[row - 1][col] = tile;
                    board[row][col] = 95;
                    return true;
                }
                // if blank tile is below tile (not exceeding array dimension)
                else if (board[row + 1][col] == 95 && row + 1 < d)
                {
                    // swap them
                    board[row + 1][col] = tile;
                    board[row][col] = 95;
                    return true;
                    
                }
                 // if blank tile is right of tile (not exceeding array dimension)
                else if (board[row][col + 1] == 95 && col + 1 < d)
                {
                    // swap them
                    board[row][col + 1] = tile;
                    board[row][col] = 95;
                    return true;
                }
                 // if blank tile is left of tile (not exceeding array dimension)
                else if (board[row][col - 1] == 95 && col - 1 >= 0)
                {
                    // swap them
                    board[row][col - 1] = tile;
                    board[row][col] = 95;
                    return true;
                }   
            }
            
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // set counter
    int counter = 1;
    
    // iterate across rows
    for (int row = 0; row < d; row++)
    {
        // iterate across columns
        for (int col = 0; col < d; col++)
        {
            // if location isn't bottom right-hand corner
            if (board[row][col] != board[d-1][d-1])
            {
                // if number not same as counter
                if (board[row][col] != counter)
                {
                    return false;
                }
                else
                {
                    // increment counter and move to next number
                    counter++;
                }
                
            }
        }
    }
    return true;
}
