#include "myLib.h"
#include "welcomeScreen.h"
#include "gameOver.h"
#include "gamePlay.h"
#include "rightCar.h"
#include "leftCar.h"
#include <stdlib.h>


unsigned short *videoBuffer = (unsigned short *)0x6000000;

Vehicle lane[6][6];

void setPosition(int row, int col, int y) {
    //lane[row][col].y = yPosition;
    // if (lane[row][col].x > SCREEN_HEIGHT || lane[row][col].x < 0) {
    //     lane[row][col].x = 0;
    // }
    lane[row][col].y = y;
}

// void setFrogPosition(Frog* frog, int x, int y) {
//     if (x < 0) {
//         frog->x = 0;
//     } else if (x > SCREEN_HEIGHT - 15 - frog->width) {
//         frog->x = SCREEN_HEIGHT - 15 - frog->width;
//     } else {
//         frog->x = x;
//     }

//     if (y < 0) {
//         frog->y = 0;
//     } else if (y > SCREEN_WIDTH - frog->height) {
//         frog->y = SCREEN_WIDTH - frog->height;
//     } else {
//         frog->y = y;
//     }
// }


void setSpeed(int row, int col, int speed) {
    lane[row][col].speed = speed;
}

void setDirection(int row, int left) {
    int j, m;
    m = sizeof(lane[row]) / sizeof(lane[row][0]);
    for (j = 0; j < m; j++) {
        if (left) {
            lane[row][j].left = 1;
        } else {
            lane[row][j].right = 1;
        }
    }
}

void initLane() {  //initialises the lane array
    int numLanes, numCarsPerLane;
    numLanes = sizeof(lane) / sizeof(lane[0]);
    numCarsPerLane = sizeof(lane[0]) / sizeof(lane[0][0]);
    // int offset = 20;
    // int allLanesHeight = SCREEN_HEIGHT - 2 * BAR_HEIGHT - offset;
    // int oneLaneHeight = allLanesHeight / numLanes;
    // int carSpace = SCREEN_WIDTH / numCarsPerLane;
    for (int i = 0; i < numLanes; i++) {
        int speed = rand() % 2;
        for (int j = 0; j < numCarsPerLane; j++) {
            setPosition(i, j, j * 20);
            setSpeed(i, j, speed);
            setDirection(i, i % 2);
        }
    }
}

void drawCars() {
    int m, n;
    n = sizeof(lane) / sizeof(lane[0]);
    m = sizeof(lane[0]) / sizeof(lane[0][0]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lane[i][j].left) {
                // lane[i][j].oldX = lane[i][j].x;
                lane[i][j].oldY += (lane[i][j].y - lane[i][j].speed - 5);
            } else {
                // lane[i][j].oldX = lane[i][j].x;
                lane[i][j].oldY += (lane[i][j].y + lane[i][j].speed + 5);
            }
        }
    }
}

void updateCarPos() {
    int m, n;
    n = sizeof(lane) / sizeof(lane[0]);
    m = sizeof(lane[0]) / sizeof(lane[0][0]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lane[i][j].left) {
                drawImage3(lane[i][j].x, lane[i][j].oldY, LEFTCARS_WIDTH, LEFTCARS_WIDTH, leftCars);
            } else {
                drawImage3(lane[i][j].x, lane[i][j].oldY, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);
            }
        }
    }
}
// drawImage3(100, 2, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);
// drawImage3(100, 100, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);
// drawImage3(100, 220, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);

// drawImage3(115, 12, LEFTCARS_WIDTH, LEFTCARS_WIDTH, leftCars);
// drawImage3(115, 125, LEFTCARS_WIDTH, LEFTCARS_WIDTH, leftCars);
// drawImage3(115, 215, LEFTCARS_WIDTH, LEFTCARS_WIDTH, leftCars);

// drawImage3(90, 2, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);
// drawImage3(90, 100, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);
// drawImage3(90, 220, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);

Frog createFrog(int x, int y, int width, int height, u16 color) {
    Frog frog = {x, y, color, width, height};
    return frog;
}

void setFrogPosition(Frog* frog, int x, int y) {
    if (x < 0) {
        frog->x = 0;
    } else if (x > SCREEN_HEIGHT - 15 - frog->width) {
        frog->x = SCREEN_HEIGHT - 15 - frog->width;
    } else {
        frog->x = x;
    }

    if (y < 0) {
        frog->y = 0;
    } else if (y > SCREEN_WIDTH - frog->height) {
        frog->y = SCREEN_WIDTH - frog->height;
    } else {
        frog->y = y;
    }
}

void drawFrog(Frog frog) {
    fillScreen(frog.color);
}

void setPixel(int x, int y, u16 color)
{
    videoBuffer[OFFSET(y, x, SCREEN_WIDTH)] = color;
}

void drawChar(int x, int y, char ch, u16 color) {
    for (int row = 0; row < CHAR_HEIGHT; row++) {
        for (int col = 0; col < CHAR_WIDTH; col++) {
            if (fontdata_6x8[ch * 48 + OFFSET(row, col, 6)]) {
                setPixel(col + x, row + y, color);
            }
        }
    }
}

void drawString(int x, int y, char* str, u16 color) {
    while (*str) {
        drawChar(x, y, *str++, color);
        x += 6;
    }
}

void drawRectangle(int row, int col, int width, int height, u16 color) {
    for (int r = 0; r < height; r++) {
        // for (int c = 0; c < width; c++) {
            // setPixel(row + r, c + col, RED);//
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(row + r, col, 240)];
        DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
    }
}

void drawImage3(int x, int y, int width, int height, const u16* image) {
    for (int row = 0; row < height; row++) {
        DMA[3].src = image + row * width;
        DMA[3].dst = videoBuffer + OFFSET(row + x, y, SCREEN_WIDTH);
        DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_INCREMENT;
    }
}

// // void fillBackGround(int x, int y, int width, int height)

// void fillScreen(int x, int y, int width, int height, const u16 color) {
//     for (int row = 0; row < height; row++) {
//         DMA[3].cnt = 0;
//         DMA[3].src = &color;
//         DMA[3].dst = videoBuffer + OFFSET(row + y, x, SCREEN_WIDTH);
//         DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
//     }
// }

void fillScreen(volatile u16 color)
{
    // Fill screen with bgcolor using GBA
    REG_DMA3SAD = (u32)&color;
    REG_DMA3DAD = (u32)videoBuffer; 
    REG_DMA3CNT = (240 * 160) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
}

void drawBackGround() {
    drawImage3(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
}

void gamePlayScreen() {
    drawImage3(0, 0, GAMEPLAY_WIDTH, GAMEPLAY_HEIGHT, gameplay);
}

void welcomeScreen() {
    drawImage3(0, 0, FROGGER_WIDTH, FROGGER_HEIGHT, frogger);
}

void gameOverScreen() {
    drawImage3(0, 0, GAME_OVER_WIDTH, GAME_OVER_HEIGHT, game_over3);
}

void waitForVBlank() {
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

void delay(int n)
{
    volatile int x = 0;
    for (int i = 0; i < n * 5000; i++)
    {
        x = x + 1;
    }
}


// int boxCollidePaddle(Rect* box, Rect* paddle) {
//     if (box->y >= (paddle->y - BOX_HEIGHT)
//         && box->y <= (paddle->y + PADDLE_HEIGHT)
//         && box->x >= (paddle->x - BOX_WIDTH)
//         && box->x <= (paddle->x + PADDLE_WIDTH)) {
//         return 1;
//     }
//     return 0;
// }

// int boxCollideBricks(Rect* box, Rect* bricks) {
//     for (int i = 0; i < BRICKSNUM; i++) {
//         Rect* brick = bricks + i;
//         if (brick->isRemoved == 0
//             && boxCollideBrick(box, brick)) {
//             return i;
//         }
//     }
//     return -1;
// }

// int boxCollideBrick(Rect* rect, Rect* box) {
//     if (rect->x < box->x + box->width && box->x < rect->x + rect->width 
//         && rect->y < box->y + box->height && box->y < rect->y + rect->height) {
//         return 1;
//     }
//     return 0;
// }

