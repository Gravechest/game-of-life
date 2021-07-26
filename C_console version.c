#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include <cstring>
#include <ctime>

const int length = 101;
const int width = 51;
char mapBuffer[width][length];
char map[width][length];
const char gliderGun[9][36] = {
    {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,32,35,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,35,35,32,32,32,32,32,32,35,35,32,32,32,32,32,32,32,32,32,32,32,32,35,35},
    {32,32,32,32,32,32,32,32,32,32,32,35,32,32,32,35,32,32,32,32,35,35,32,32,32,32,32,32,32,32,32,32,32,32,35,35},
    {35,35,32,32,32,32,32,32,32,32,35,32,32,32,32,32,35,32,32,32,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {35,35,32,32,32,32,32,32,32,32,35,32,32,32,35,32,35,35,32,32,32,32,35,32,35,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,35,32,32,32,32,32,35,32,32,32,32,32,32,32,35,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,35,32,32,32,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32}
};
int Ptime;

COORD cursorPosition;

void fillMap() {
    for (int i = 0; i < width; i++) {
        for (int i2 = 0; i2 < length; i2++) {
            if (i2 == length - 1) {
                map[i][i2] = 10;
                break;
            }
            if (rand() % 2 == 0) {
                map[i][i2] = 35;
            }
            else {
                map[i][i2] = 32;
            }
        }
    }
}

void displayMap() {
    printf("%s", map);
    printf("%i", Ptime);
    Ptime++;
}

void updateMap() {
    memcpy(mapBuffer, map, sizeof(map));
    for (int i = 0; i < width; i++) {
        for (int i2 = 0; i2 < length - 1; i2++) {
            int neighbours = -1;
            for (int j = -1; j < 2; j++) {
                for (int j2 = -1; j2 < 2; j2++) {
                    if (i + j < 0 || i2 + j2 < 0 || i + j > width - 1 || i2 + j2 > length - 1) {
                        continue;
                    }
                    if (map[i + j][i2 + j2] == 35) {
                        neighbours++;
                    }
                }
            }
            if (map[i][i2] == 32) {
                if (neighbours == 2) {
                    mapBuffer[i][i2] = 35;
                }
            }
            else {
                if (neighbours > 3 || neighbours < 2) {
                    mapBuffer[i][i2] = 32;
                }
            }
        }
    }
    memcpy(map, mapBuffer, sizeof(map));
}

void loadGliderGun() {
    memset(map, 32, sizeof(map));
    for (int i = 0; i < 9; i++) {
        for (int i2 = 0; i2 < 36; i2++) {
            map[i + 10][i2 + 10] = gliderGun[i][i2];
        }
    }
    for (int i = 0; i < width; i++) {
        map[i][length - 1] = 10;
    }
}

void main() {
    long long second;
    time(&second);
    srand(second);
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    loadGliderGun();
    for (;;) {
        updateMap();
        displayMap();
        Sleep(16);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }
}
