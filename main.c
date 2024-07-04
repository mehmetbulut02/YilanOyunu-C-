#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define GENISLIK 20
#define YUKSEKLIK 20

int oyunBitti;
int x, y, yemX, yemY, skor;
int kuyrukX[100], kuyrukY[100];
int kuyrukUzunlugu;
enum Yon { DUR = 0, SOL, SAG, YUKARI, ASAGI };
enum Yon yon;

void AyarlariHazirla()
{
    oyunBitti = 0;
    yon = DUR;
    x = GENISLIK / 2;
    y = YUKSEKLIK / 2;
    srand(time(0));
    yemX = rand() % GENISLIK;
    yemY = rand() % YUKSEKLIK;
    skor = 0;
    kuyrukUzunlugu = 0;
}

void Ciz()
{
    system("cls");
    for (int i = 0; i < GENISLIK + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < YUKSEKLIK; i++)
    {
        for (int j = 0; j < GENISLIK; j++)
        {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == yemY && j == yemX)
                printf("Y");
            else
            {
                int kuyrukCiz = 0;
                for (int k = 0; k < kuyrukUzunlugu; k++)
                {
                    if (kuyrukX[k] == j && kuyrukY[k] == i)
                    {
                        printf("o");
                        kuyrukCiz = 1;
                    }
                }
                if (!kuyrukCiz)
                    printf(" ");
            }

            if (j == GENISLIK - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < GENISLIK + 2; i++)
        printf("#");
    printf("\n");
    printf("Skor: %d\n", skor);
}

void GirisAl()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            yon = SOL;
            break;
        case 'd':
            yon = SAG;
            break;
        case 'w':
            yon = YUKARI;
            break;
        case 's':
            yon = ASAGI;
            break;
        case 'x':
            oyunBitti = 1;
            break;
        }
    }
}

void Mantik()
{
    int oncekiX = kuyrukX[0];
    int oncekiY = kuyrukY[0];
    int onceki2X, onceki2Y;
    kuyrukX[0] = x;
    kuyrukY[0] = y;

    for (int i = 1; i < kuyrukUzunlugu; i++)
    {
        onceki2X = kuyrukX[i];
        onceki2Y = kuyrukY[i];
        kuyrukX[i] = oncekiX;
        kuyrukY[i] = oncekiY;
        oncekiX = onceki2X;
        oncekiY = onceki2Y;
    }

    switch (yon)
{
    case DUR:

        break;
    case SOL:
        x--;
        break;
    case SAG:
        x++;
        break;
    case YUKARI:
        y--;
        break;
    case ASAGI:
        y++;
        break;
}


    if (x >= GENISLIK || x < 0 || y >= YUKSEKLIK || y < 0)
        oyunBitti = 1;

    for (int i = 0; i < kuyrukUzunlugu; i++)
    {
        if (kuyrukX[i] == x && kuyrukY[i] == y)
            oyunBitti = 1;
    }

    if (x == yemX && y == yemY)
    {
        skor += 10;
        yemX = rand() % GENISLIK;
        yemY = rand() % YUKSEKLIK;
        kuyrukUzunlugu++;
    }
}

void KurallariYazdir()
{
    printf("Kurallar:\n");
    printf("1. Oyun \"W\", \"A\", \"S\", \"D\" tuslari ile oynanmaktadir.\n");
    printf("2. Duvara veya kuyruga carptiginizda oyun sonlanir.\n");
    printf("3. Oyuna baslamak icin \"X\" tusuna basiniz.\n");
    printf("4. Oyun bittikten sonra tekrar oynamak icin \"E\" tusuna basiniz.\n");
    printf("5. Oyun bittikten sonra tekrar oynamak istemiyorsaniz \"H\" tusuna basiniz.\n");
}

void OyunBitti()
{
    system("cls");
    printf("Oyun Bitti!\n");
    printf("Skorunuz: %d\n\n", skor);
    printf("Tekrar oynamak ister misiniz? (E/H)\n");
    char tekrarOyna;

    while (1)
    {
        if (_kbhit())
        {
            tekrarOyna = _getch();
            if (tekrarOyna == 'e' || tekrarOyna == 'E')
            {
                AyarlariHazirla();
                main();
            }
            else if (tekrarOyna == 'h' || tekrarOyna == 'H')
            {
                exit(0);
            }
        }
    }
}

int main()
{
    KurallariYazdir();
    printf("Baslamak icin \"X\" tusuna basiniz...\n");
    char baslaTusu;

    while (1)
    {
        if (_kbhit())
        {
            baslaTusu = _getch();
            if (baslaTusu == 'x' || baslaTusu == 'X')
                break;
        }
    }

    AyarlariHazirla();

    while (!oyunBitti)
    {
        Ciz();
        GirisAl();
        Mantik();
        Sleep(200);
    }

    OyunBitti();

    return 0;
}
