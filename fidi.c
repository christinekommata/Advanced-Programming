#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char move();

typedef enum kinisi
{
    up,
    left,
    right,
    down,
    stop
} kinisi_m;

int main(int argc, char *argv[])
{
    int size_p = atoi(argv[1]);
    char *plaisio[size_p];
    int game_over = 0;
    kinisi_m m;
    int prog_x, prog_y, prog_2x, prog_2y;
    int print;
    

    srand(1);
    int i = 0, j = 0, fagito_x, fagito_y, kefali_x, kefali_y, oura_x[100], oura_y[100];
    int score = 0, size_oura = 0;

    fagito_x = (rand() % (size_p - 2) + 1);
    fagito_y = (rand() % (size_p - 2) + 1);

    kefali_x = (rand() % (size_p - 2) + 1);
    kefali_y = (rand() % (size_p - 2) + 1);
   

    while (!game_over)
    {
        system("clear");

        printf("SCORE: %i\n", score);
        for (i = 0; i < size_p; i++)
        {
            plaisio[i] = (char *)malloc(size_p * sizeof(char));
        }

        for (i = 0; i < size_p; i++)
        {
            for (j = 0; j < size_p; j++)
            {
                if ((i == 0) || (i == size_p - 1))
                {
                    plaisio[i][j] = '-';
                }
                else if ((j == 0) || (j == size_p - 1))
                {
                    plaisio[i][j] = '|';
                }
                else
                {
                    plaisio[i][j] = ' ';
                }
            }
        }

        for (i = 0; i < size_p; i++)
        {
            for (j = 0; j < size_p; j++)
            {
                if (kefali_x == i && kefali_y == j)
                {
                    printf("@");
                }
                else if (fagito_x == i && fagito_y == j)
                {
                    printf("X");
                }
                else
                {
                    print = 0;
                    for (int k = 0; k < size_oura; k++)
                    {

                        if (oura_x[k] == i && oura_y[k] == j)
                        {
                            printf("*");
                            print = 1;
                        }
                    }
                    if (print == 0)
                    {
                        printf("%c", plaisio[i][j]);
                    }
                }
            }
            printf("\n");
        }

        switch (move())
        {
        case 'w':
        case 'W':
            m = up;
            break;
        case 'a':
        case 'A':
            m = left;
            break;
        case 'd':
        case 'D':
            m = right;
            break;
        case 's':
        case 'S':
            m = down;
            break;
        case 'x':
        case 'X':
            m = stop;
            break;
        }

        prog_x = oura_x[0];
        prog_y = oura_y[0];
        oura_x[0] = kefali_x;
        oura_y[0] = kefali_y;

        for (i = 1; i < size_oura; i++)
        {
            prog_2x = oura_x[i];
            prog_2y = oura_y[i];

            oura_x[i] = prog_x;
            oura_y[i] = prog_y;

            prog_x = prog_2x;
            prog_y = prog_2y;
        }

        switch (m)
        {
        case up:
            kefali_x--;
            break;
        case left:
            kefali_y--;
            break;
        case right:
            kefali_y++;
            break;
        case down:
            kefali_x++;
            break;
        case stop:
            game_over = 1;
        }

        usleep(100000);                 //h sleep den dexetai double omws h usleep metraei se milisec ara paei pio grigora

        for (int i = 0; i < size_p; i++)
        {
            for (int j = 0; j < size_p; j++)
            {
                if ((kefali_x == 0) || (kefali_y == 0) || (kefali_x == size_p - 1) || (kefali_y == size_p - 1))
                {
                    game_over = 1;
                }
                else if (kefali_x == fagito_x && kefali_y == fagito_y)
                {
                    score = score + 10;
                    size_oura++;

                    fagito_x = (rand() % (size_p - 1) + 1);
                    fagito_y = (rand() % (size_p - 1) + 1);

                    break;
                }
                else if (kefali_x == oura_x[i] && kefali_y == oura_y[i])
                {

                    game_over = 1;
                }
            }
        }

        if (game_over == 1)
        {
             system("clear");
             printf("\n\t\tGAME  OVER\n\t\t SCORE: %i",score);
            exit(0);
        }
    }
}


char move()
{
    int flags;
    char key[2];

    flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // To get the input from the terminal without pressing the enter button
    system("/bin/stty raw");
    read(STDIN_FILENO, key, 2);
    // Reset the "system ("/bin/stty raw")" to display correctly the output
    system("/bin/stty cooked");

    return key[0];
}