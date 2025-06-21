#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 24

int Score = 0;
int GameOver = 0;
int SnakeLength = 1;
char LastPressedKey;
char* Display[DISPLAY_HEIGHT][DISPLAY_WIDTH];

typedef struct
{
    int x;
    int y;
}Pos;

Pos Snake[(DISPLAY_WIDTH - 1) * (DISPLAY_HEIGHT - 1)];
Pos Apple;

//functions declarations
void Setup(void);
void Input(void);
void Update(void);
void Draw(void);
void Restart(void);

//main function
int main(void){

    while (1)
    {
        Setup();
        while (GameOver != 1)
        {
            Draw();
            Input();
            Update();
            Sleep(1);
        }
        Restart();
        continue;

    }
    

    return 1;
}

//seting up the game
void Setup(void){
    system("cls");
    srand(time(NULL));
    Snake[0].x = DISPLAY_WIDTH/2;
    Snake[0].y = DISPLAY_HEIGHT/2;
    Apple.x = (rand() % (DISPLAY_WIDTH - 2)) + 1;
    Apple.y = (rand() % (DISPLAY_HEIGHT - 2)) + 1;

    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            if(y == 0 || y == DISPLAY_HEIGHT - 1){
                Display[y][x] = "#";
            }
            else if(x == 0 || x == DISPLAY_WIDTH - 1){
                Display[y][x] = "#";
            }
            else if(x == Apple.x &&  y == Apple.y){
                Display[y][x] = "A";
            }
            else if(x == Snake[0].x && y == Snake[0].y){
                Display[y][x] = "O";
            }
            else{
                Display[y][x] = " ";
            }
        }
        
    }
    return;
}

//drawing the display matrix
void Draw(void){
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    printf("\n");
    printf("\n");
    printf("\n");

    printf("SCORE:%d",Score);
    printf("\n");
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for(int x = 0; x < DISPLAY_WIDTH; x++)
        {
            printf(Display[y][x]);
        }
        printf("\n");
    }
    return;
}

//saving keyboard input
void Input(void){
    if(_kbhit()){
        char key = _getch();
        if(key == 'a' || key == 's' || key == 'd' || key == 'w'){
            LastPressedKey = key;
        }
    }
    return;
}

//updating display and movement
void Update(void){
    for (int i = 1; i < SnakeLength; i++)
    {
        if (Snake[i].x == Snake[0].x && Snake[i].y == Snake[0].y)
        {
            GameOver = 1;
            return;
        }
    }
    
    for (int i = SnakeLength - 1; i > 0; i--) {
        Snake[i] = Snake[i - 1];
    }

    if (LastPressedKey == 'a') Snake[0].x--;
    else if (LastPressedKey == 'd') Snake[0].x++;
    else if (LastPressedKey == 's') Snake[0].y++;
    else if (LastPressedKey == 'w') Snake[0].y--;

    if (Snake[0].x <= 0) Snake[0].x = DISPLAY_WIDTH - 2;
    else if (Snake[0].x >= DISPLAY_WIDTH - 1) Snake[0].x = 1;
    if (Snake[0].y <= 0) Snake[0].y = DISPLAY_HEIGHT - 2;
    else if (Snake[0].y >= DISPLAY_HEIGHT - 1) Snake[0].y = 1;

    if (Apple.x == Snake[0].x && Apple.y == Snake[0].y) {
        Score += 5;
        Apple.x = -1;
        Apple.y = -1;
        SnakeLength++;
    }

    if (Apple.x == -1 && Apple.y == -1) {
        Apple.x = (rand() % (DISPLAY_WIDTH - 2)) + 1;
        Apple.y = (rand() % (DISPLAY_HEIGHT - 2)) + 1;
    }

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            if (y == 0 || y == DISPLAY_HEIGHT - 1 || x == 0 || x == DISPLAY_WIDTH - 1) {
                Display[y][x] = "#";
            } else if (x == Apple.x && y == Apple.y) {
                Display[y][x] = "A";
            } else {
                Display[y][x] = " ";
            }
        }
    }

    for (int i = 0; i < SnakeLength; i++) {
        int sx = Snake[i].x;
        int sy = Snake[i].y;
        if (sx > 0 && sx < DISPLAY_WIDTH - 1 && sy > 0 && sy < DISPLAY_HEIGHT - 1) {
            if(i == 0){
                Display[sy][sx] = "O";
            }else{
              Display[sy][sx] = "o";
            }
        }
    }
    return;
}

void Restart(void){
    for (int i = 1; i < SnakeLength; i++)
    {
        Snake[i].x = -1;
        Snake[i].y = -1;
    }
    SnakeLength = 1;
    Score = 0;
    Snake[0].x = DISPLAY_WIDTH/2;
    Snake[0].y = DISPLAY_HEIGHT/2;
    GameOver = 0;
}