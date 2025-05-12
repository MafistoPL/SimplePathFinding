#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HEIGHT 9
#define WIDTH 8

void display_horizontal_bar()
{
    printf("%c", '*');
    for (int x = 0; x < 8; x++)
    {
        printf("%-2c", '*');
    }
    printf("%-2c", '*');
    putchar('\n');
}

void display_map(char map[HEIGHT][WIDTH])
{
    printf("  ");
    for (int x = 0; x < WIDTH; x++)
    {
        printf("%d ", x);
    }
    printf(" \n ");

    display_horizontal_bar();

    for (int y = 0; y < HEIGHT; y++)
    {
        printf("%d*", y);
        for (int x = 0; x < WIDTH; x++)
        {
            if (map[y][x] == ' ' || map[y][x] == '*' || map[y][x] == 'A' || map[y][x] == 'B')
                printf("%-2c", map[y][x]);
            else
                printf("%-2d", map[y][x]);
        }
        printf("%-2c\n", '*');
    }

    putchar(' ');
    display_horizontal_bar();
}

void clear_map(char map[HEIGHT][WIDTH], int finalStep)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (map[y][x] != 0 && map[y][x] != finalStep && map[y][x] != '*')
            {
                map[y][x] = ' ';
            }
        }
    }
}

bool check_element(char map[HEIGHT][WIDTH], int y, int x, bool &stepTaken, bool &success, int step)
{
    int el = map[y][x];
    if (el == ' ') {
        map[y][x] = step + 1;
        stepTaken = true;
    }
    if (el == 'B') {
        success = true;
        map[y][x] = step + 1;
        clear_map(map, step + 1);
        return true;
    }
    return false;
}

int main()
{
    char map[HEIGHT][WIDTH] =
    {
        { ' ', ' ', ' ', '*', ' ', ' ', '*', ' ' },
        { ' ', ' ', ' ', '*', '*', '*', '*', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', '*', ' ', '*', '*', '*', '*' },
        { '*', '*', '*', ' ', '*', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', '*', '*', ' ', ' ' },
        { ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', '*', '*', '*', '*', '*', '*', '*' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
    };

    display_map(map);
    char pointsAreOk = 'n';
    do
    {
        printf("Podaj wspolrzedne pierwszego punku (x, y): ");
        int x1, y1;
        scanf_s("%d %d", &x1, &y1);

        printf("Podaj wspolrzedne drugiego punku (x, y): ");
        int x2, y2;
        scanf_s("%d %d", &x2, &y2);

        while (getchar() != '\n') continue;

        map[y1][x1] = 'A';
        map[y2][x2] = 'B';

        display_map(map);

        printf("Czy poprawnie wczytano punkty t/N: ");
        if ((pointsAreOk = getchar()) != 't')
        {
            map[y1][x1] = ' ';
            map[y2][x2] = ' ';
        }
        else
        {
            map[y1][x1] = 0;
        }
    } while (pointsAreOk != 't');

    printf("Super :) Czy wlaczyc wizualizacje rozwiazania w czasie rzeczywistym t/N: ");
    bool realTimeVisualization = false;
    while (getchar() != '\n') continue;
    if (getchar() == 't') realTimeVisualization = true;
    putchar('\n');

    bool stepTaken = false;
    bool success = false;
    int step = 0;
    do {
        stepTaken = false;
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (map[y][x] == step)
                {
                    if (x > 0)
                    {
                        if (check_element(map, y, x - 1, stepTaken, success, step)) break;
                    }
                    if (x < WIDTH - 1) {
                        if (check_element(map, y, x + 1, stepTaken, success, step)) break;
                    }
                    if (y > 0)
                    {
                        if (check_element(map, y - 1, x, stepTaken, success, step)) break;
                    }
                    if (y < HEIGHT - 1)
                    {
                        if (check_element(map, y + 1, x, stepTaken, success, step)) break;
                    }
                }
            }
            if (success) break;
        }
        step++;
        if (!success && realTimeVisualization)
        {
            display_map(map);
            system("pause");
        }
    } while (stepTaken && !success);

    
    if (success)
    {
        display_map(map);
        printf("\nUdalo sie dojsc do celu w %d krokach\n", step);
    }
    else {
        printf("\nNie da sie dojsc do celu z punku a do b.");
    }

    printf("\n\n");

    return 0;
}




