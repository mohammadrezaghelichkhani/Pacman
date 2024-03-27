#include <bits/stdc++.h>
#include <unistd.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
using namespace std;
int const m = 20;
int const n = 20;
void SetCursorPosition(unsigned short int x, unsigned short int y)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(output, pos);
}
void menue()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 19; i++)
    {
        std::cout << "GAME STARTS IN ";
        std::cout << 19 - i << "\n";
        for (int j = 0; j < 20; j++)
        {
            SetConsoleTextAttribute(h, 0xFF);
            std::cout << " ";
            SetConsoleTextAttribute(h, 0x07);
        }
        std::cout << "\n";
        for (int j = 0; j < 20; j++)
        {
            if (j == 0 || j == 19)
            {
                SetConsoleTextAttribute(h, 0xFF);
                std::cout << " ";
                SetConsoleTextAttribute(h, 0x07);
            }
            else if (j > i)
            {
                SetConsoleTextAttribute(h, 0x07);
                std::cout << " ";
            }
            else
            {
                SetConsoleTextAttribute(h, 0x88);
                std::cout << " ";
            }
        }
        std::cout << "\n";
        SetConsoleTextAttribute(h, 0x07);
        for (int j = 0; j < 20; j++)
        {
            SetConsoleTextAttribute(h, 0xFF);
            std::cout << " ";
            SetConsoleTextAttribute(h, 0x07);
        }
        usleep(2.4 * 100000);
        if (19 - i != 10)
        {
            SetCursorPosition(0, 0);
        }
        else
        {
            system("cls");
        }
    }
    SetConsoleTextAttribute(h, 0x07);
}
bool suitable(int xp, int yp, int xg, int yg)
{
    return (abs(xp - xg) + abs(yp - yg) > 15);
}
void wallSet(std::string a[m][n])
{
    srand(time(0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = ".";
        }
    }
    for (int i = 0; i < m; i += 2)
    {
        for (int j = 0; j < n; j++)
        {
            int p = rand() % 3;
            if (p != 0)
            {
                a[i][j] = "#";
            }
        }
    }
}
void printboard(std::string a[m][n], int score, int life, int scoreHouse, int time[4], int HighScore, int xg[4], int yg[4], char c)
{
    if (c == 'S')
    {
        std::cout << "press any other key to resume\n";
    }
    else
    {
        std::cout << "press S to stop\n";
    }
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "High Score: " << max(HighScore, score + scoreHouse) << "\n";
    std::cout << "life: " << life << "\n";
    std::cout << "score: " << score + scoreHouse << "\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == "@")
            {
                for (int k = 0; k < 4; k++)
                {
                    if (i == xg[k] && j == yg[k])
                    {
                        if (time[k] != 0)
                        {
                            SetConsoleTextAttribute(h, 0x55);
                        }
                        else if (k == 0)
                        {
                            SetConsoleTextAttribute(h, 0x11);
                        }
                        else if (k == 1)
                        {
                            SetConsoleTextAttribute(h, 0x22);
                        }
                        else if (k == 2)
                        {
                            SetConsoleTextAttribute(h, 0x33);
                        }
                        else
                        {
                            SetConsoleTextAttribute(h, 0x44);
                        }
                        break;
                    }
                }
            }
            else if (a[i][j] == "#")
            {
                SetConsoleTextAttribute(h, 0x77);
            }
            else if (a[i][j] == ".")
            {
                SetConsoleTextAttribute(h, 0xF);
            }
            else if (a[i][j] == "o")
            {
                SetConsoleTextAttribute(h, 0xE);
                cout << "o ";
                continue;
            }
            else if (a[i][j] == "☆")
            {
                SetConsoleTextAttribute(h, 0xEE);
            }
            else
            {
                SetConsoleTextAttribute(h, 0x88);
            }
            std::cout << "  ";
        }
        std::cout << "\n";
    }
    SetConsoleTextAttribute(h, 0x07);
}
std::string move(std::string a[m][n], int x, int y, int motion)
{
    switch (motion)
    {
    case 0:
        return a[x][(y + 1) % n];
    case 1:
        return a[(x + m - 1) % m][y];
    case 2:
        return a[x][(y + n - 1) % n];
    default:
        return a[(x + 1) % m][y];
    }
}
void changeCurrent(std::string a[m][n], int score, int x, int y, int xg[4], int yg[4], int r)
{
    if (r == 1)
    {
        int tedad = 0;
        for (int i = 0; i < 4; i++)
        {
            if (x == xg[i] && y == yg[i])
            {
                tedad++;
            }
        }
        if (tedad > 1)
        {
            return;
        }
    }
    if (score == 0)
    {
        a[x][y] = " ";
    }
    else if (score == 10)
    {
        a[x][y] = ".";
    }
    else
    {
        a[x][y] = "o";
    }
}
void randomGhost(std::string a[m][n], int *xghost, int *yghost, int score, int xg[4], int yg[4])
{
    if (a[*xghost][*yghost] == "☆")
    {
        return;
    }
    changeCurrent(a, score, *xghost, *yghost, xg, yg, 1);
    srand(time(0));
    int motion;
    do
    {
        motion = rand() % 4;
    } while (move(a, *xghost, *yghost, motion) == "#");
    switch (motion)
    {
    case 0:
        *yghost = ((*yghost) + 1) % n;
        break;
    case 1:
        *xghost = ((*xghost) + m - 1) % m;
        break;
    case 2:
        *yghost = ((*yghost) + n - 1) % n;
        break;
    default:
        *xghost = ((*xghost) + 1) % m;
    }
    a[*xghost][*yghost] = "@";
}
void pacmanMove(std::string a[m][n], int *x, int *y, char c)
{
    a[*x][*y] = " ";
    switch (c)
    {
    case 'w':
        if (a[(*x + m - 1) % m][*y] != "#")
        {
            *x = (*x + m - 1) % m;
        }
        break;
    case 's':
        if (a[(*x + 1) % m][*y] != "#")
        {
            *x = (*x + 1) % m;
        }
        break;
    case 'd':
        if (a[*x][(*y + 1) % n] != "#")
        {
            *y = (*y + 1) % n;
        }
        break;
    case 'a':
        if (a[*x][(*y + n - 1) % n] != "#")
        {
            *y = (*y + n - 1) % n;
        }
        break;
    }
    a[*x][*y] = "☆";
}
bool interruptingWall(std::string a[m][n], int xp, int yp, int xg, int yg)
{
    if (abs(xg - xp) == 1)
    {
        int direction = (yp - yg) / abs(yp - yg);
        for (int i = yg; i != yp; i += direction)
        {
            if (a[xp][i] == "#")
            {
                return true;
            }
        }
    }
    return false;
}
void rightOrleft(std::string a[m][n], int xp, int yp, int *xg, int *yg)
{
    int counter1 = 1, counter2 = 1, direction = (xp - *xg) / abs(xp - *xg);
    while (a[*xg + direction][(*yg + counter1) % n] == "#")
    {
        counter1++;
    }
    while (a[*xg + direction][(*yg - counter2 + n) % n] == "#")
    {
        counter2++;
    }
    if (abs((*yg + counter1) % n - yp) - abs((*yg - counter2 + n) % n - yp) + counter1 - counter2 >= 0)
    {
        *yg = (*yg - 1 + n) % n;
    }
    else
    {
        *yg = (*yg + 1) % n;
    }
}
void ghostMove(std::string a[m][n], int xp, int yp, int *xg, int *yg, int score, int xG[4], int yG[4])
{
    changeCurrent(a, score, *xg, *yg, xG, yG, 1);
    if (!(interruptingWall(a, xp, yp, *xg, *yg)))
    {
        if (xp == *xg)
        {
            int direction = (yp - *yg) / abs(yp - *yg);
            if (a[xp][*yg + direction] != "#")
            {
                (*yg) += direction;
            }
            else if (xp == 0)
            {
                (*xg)++;
            }
            else
            {
                (*xg)--;
            }
        }
        else
        {
            int direction = (xp - *xg) / abs(xp - *xg);
            if (a[*xg + direction][*yg] != "#")
            {
                (*xg) += direction;
            }
            else
            {
                rightOrleft(a, xp, yp, xg, yg);
            }
        }
    }
    else
    {
        int direction = (yp - *yg) / abs(yp - *yg);
        (*yg) += direction;
    }
    a[*xg][*yg] = "@";
}
void pacmanSet(std::string a[m][n], int *x, int *y)
{
    srand(time(0));
    do
    {
        *x = rand() % m;
        *y = rand() % n;
    } while (a[*x][*y] != ".");
    a[*x][*y] = "☆";
}
void ghostSet(std::string a[m][n], int x[4], int y[4], int xp, int yp)
{
    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        do
        {
            x[i] = rand() % m;
            y[i] = rand() % n;
        } while (a[x[i]][y[i]] != "." || !(suitable(xp, yp, x[i], y[i])));
        a[x[i]][y[i]] = "@";
    }
}
void specialFood(std::string a[m][n], int x[4], int y[4])
{
    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        do
        {
            x[i] = rand() % m;
            y[i] = rand() % n;
        } while (a[x[i]][y[i]] != ".");
        a[x[i]][y[i]] = "o";
    }
}
void scoreSet(std::string a[m][n], int score[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == ".")
            {
                score[i][j] = 10;
            }
            else
            {
                score[i][j] = 50;
            }
        }
    }
}
void play(int *HighScore, std::string level)
{
    int life = 3;
    int x, y, xghost[4], yghost[4], xf[4], yf[4];
    std::string a[m][n];
    int scoreBoard[m][n];
    wallSet(a);
    specialFood(a, xf, yf);
    scoreSet(a, scoreBoard);
    pacmanSet(a, &x, &y);
    ghostSet(a, xghost, yghost, x, y);
    int eat = 0;
    int firstPos[4][2];
    int xpacfirst = x, ypacfirst = y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
            {
                firstPos[i][j] = xghost[i];
            }
            else
            {
                firstPos[i][j] = yghost[i];
            }
        }
    }
    int score = 0;
    char c = 'e';
    int time[4] = {0};
    printboard(a, score, life, scoreBoard[x][y], time, *HighScore, xghost, yghost, c);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != "#")
            {
                eat++;
            }
        }
    }
    while (true)
    {
        if (kbhit())
        {
            c = getch();
            if (c == 'S')
            {
                SetCursorPosition(0, 0);
                printboard(a, score, life, scoreBoard[x][y], time, *HighScore, xghost, yghost, c);
            }
            while (c == 'S')
            {
                c = getch();
            }
            system("cls");
        }
        SetCursorPosition(0, 0);
        if (scoreBoard[x][y] != 0)
        {
            score += scoreBoard[x][y];
            eat--;
            if (scoreBoard[x][y] == 50)
            {
                for (int i = 0; i < 4; i++)
                {
                    time[i] = 20;
                }
            }
            scoreBoard[x][y] = 0;
        }
        if (eat == 0)
        {
            system("cls");
            std::cout << "You won\n";
            if (*HighScore < score)
            {
                *HighScore = score;
            }
            return;
        }
        pacmanMove(a, &x, &y, c);
        for (int i = 0; i < 4; i++)
        {
            if (time[i] != 0)
            {
                randomGhost(a, &xghost[i], &yghost[i], scoreBoard[xghost[i]][yghost[i]], xghost, yghost);
                if (xghost[i] == x && yghost[i] == y)
                {
                    score += 200, a[x][y] = "☆";
                    time[i] = 0, xghost[i] = firstPos[i][0], yghost[i] = firstPos[i][1];
                    a[xghost[i]][yghost[i]] = "@";
                }
            }
            else
            {
                if (level == "Medium")
                {
                    if (i < 2)
                    {
                        ghostMove(a, x, y, &xghost[i], &yghost[i], scoreBoard[xghost[i]][yghost[i]], xghost, yghost);
                    }
                    else
                    {
                        randomGhost(a, &xghost[i], &yghost[i], scoreBoard[xghost[i]][yghost[i]], xghost, yghost);
                    }
                }
                else if (level == "Easy")
                {
                    randomGhost(a, &xghost[i], &yghost[i], scoreBoard[xghost[i]][yghost[i]], xghost, yghost);
                }
                else
                {
                    ghostMove(a, x, y, &xghost[i], &yghost[i], scoreBoard[xghost[i]][yghost[i]], xghost, yghost);
                }
                if (x == xghost[i] && y == yghost[i])
                {
                    life--, c = 'e';
                    for (int j = 0; j < 4; j++)
                    {
                        changeCurrent(a, scoreBoard[xghost[j]][yghost[j]], xghost[j], yghost[j], xghost, yghost, 0);
                    }
                    x = xpacfirst, y = ypacfirst;
                    for (int j = 0; j < 4; j++)
                    {
                        xghost[j] = firstPos[j][0], yghost[j] = firstPos[j][1];
                    }
                    if (life == 0)
                    {
                        if (*HighScore < score)
                        {
                            *HighScore = score;
                        }
                        system("cls");
                        std::cout << " GAME OVER\n your score: " << score << " \n";
                        return;
                    }
                }
            }
        }
        printboard(a, score, life, scoreBoard[x][y], time, *HighScore, xghost, yghost, c);
        for (int i = 0; i < 4; i++)
        {
            if (time[i] != 0)
            {
                time[i]--;
            }
        }
        usleep(100000 * 4.7);
    }
}
int main()
{
    std::string level;
    std::cout << "Enter level\nEasy(1)\nMedium(2)\nHard(3)\n";
    char num;
    map<char, string> correspondingLevel;
    correspondingLevel['1'] = "Easy", correspondingLevel['2'] = "Medium", correspondingLevel['3'] = "Hard";
    num = getch();
    while (num > '3' || num < '1')
    {
        cout << "enter a valid character:\nEasy(1)\nMedium(2)\nHard(3)\n";
        num = getch();
        system("cls");
    }
    level = correspondingLevel[num];
    system("cls");
    // menue();
    system("cls");
    int wannaPlay = 1, HighScore = 0;
    while (wannaPlay == 1)
    {
        play(&HighScore, level);
        std::cout << "Do you wan to play again?";
        std::cout << "\n";
        std::cout << "if yes type 1,if not type 0\n";
        std::cin >> wannaPlay;
        system("cls");
    }
    std::cout << "Your record:  " << HighScore;
}