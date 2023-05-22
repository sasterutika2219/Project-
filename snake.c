#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int height = 20, width = 40, x, y, fruitX, fruitY, flag, end, score;
int tailX[100], tailY[100];
int piece = 0;
int static count=300;
void setTimeout(int milliseconds)
{
    // If milliseconds is less or equal to 0
    // will be simple return from function without throw error
    if (milliseconds <= 0) {
        fprintf(stderr, "Count milliseconds for timeout is less or equal to 0\n");
        return;
    }

    // a current time of milliseconds
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;

    // needed count milliseconds of return from this timeout
    int end = milliseconds_since + milliseconds;

    // wait while until needed time comes
    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}
void logic()
{
    int i;
    int prevx, prevy, prev2x, prev2y;
    prevx = tailX[0];
    prevy = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for (i = 1; i <= piece; i++)
    {
        prev2x = tailX[i];
        prev2y = tailY[i];
        tailX[i] = prevx;
        tailY[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch (flag)
    {
    case 1:
    {
        x--;
        break;
    }
    case 2:
    {
        x++;
        break;
    }
    case 3:
    {
        y--;
        break;
    }
    case 4:
    {
        y++;
        break;
    }
    }
    if (x == 0 || x == height || y == 0 || y == width)
    {
        end = 1;
    }
    if (x == fruitX && y == fruitY)
    {
    label3:
        fruitX = rand() % 20;
        if (fruitX == 0)
            goto label3;

    label4:
        fruitY = rand() % 20;
        if (fruitY == 0)
            goto label4;
        score = score + 10;
        
        piece++;
    }

    
    setTimeout(count);
}
void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
        {
            flag = 1;
            break;
        }
        case 's':
        {
            flag = 2;
            break;
        }
        case 'a':
        {
            flag = 3;
            break;
        }
        case 'd':
        {
            flag = 4;
            break;
        }
        }
    }
}
void setup()
{
    x = height / 2;
    y = width / 2;

label1:
    fruitX = rand() % 20;
    if (fruitX == 0)
        goto label1;

label2:
    fruitY = rand() % 20;
    if (fruitX == 0)
        goto label2;

    end = 0;
    score = 0;
    piece++;
}
void draw()
{
    system("cls");
    int i, j, k, ch;
    for (i = 0; i <= height; i++)
    {
        for (j = 0; j <= width; j++)
        {
            if (i == 0 || i == height || j == 0 || j == width)
            {
                printf("*");
            }
            else
            {
                if (i == x && j == y)
                {
                    printf("0");
                }
                else if (i == fruitX && j == fruitY)
                {
                    printf("@");
                }
                else
                {
                    ch = 0;
                    for (k = 0; k < piece; k++)
                    {
                        if (i == tailX[k] && j == tailY[k])
                        {
                            printf("o");
                            ch = 1;
                        }
                    }
                    if (ch == 0)
                    {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("Score is\t %d", score);
}
int main()
{
    setup();
    while (!end)
    {
        input();
        draw();
        logic();
       
    }
}
