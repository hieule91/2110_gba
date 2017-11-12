#include "myLib.h"
#include "welcomeScreen.h"
#include "gameOver.h"
#include "gamePlay.h"
#include <stdlib.h>


unsigned short *videoBuffer = (unsigned short *)0x6000000;

Vehicle lane[5][1];

void initLane() {  //initialises the lane array to zero
    int i,j;
    n = sizeof(lane) / sizeof(lane[0]);
    m = sizeof(lane[0]) / sizeof(lane[0][0]);
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            lane[i][j].pos = 0;
            lane[i][j].speed = 0;
        }
    }
}

void shiftLane() {
    int i,j;
    n = sizeof(lane) / sizeof(lane[0]);
    m = sizeof(lane[0]) / sizeof(lane[0][0]);
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            Vehicle vehicle = lane[i][j];
            vehicle.pos = (vehicle.pos + vehicle.speed) % SCREEN_WIDTH;
        }
    }

}

Vehicle createCars(int x, int y, int pos, int speed) {
    Vehicle vehicle = {x, y, pos, speed};
    return vehicle;
}



// void initBricks(Rect* bricks) {
//     u16 colors[4] = {RED, GREEN, BLUE, YELLOW};
//     for (int row = 0; row < BRICKROWS; row++) {
//         for (int col = 0; col < BRICKCOLS; col++) {
//             *(bricks + OFFSET(row, col, BRICKCOLS)) =
//                 createRect(col * BRICK_WIDTH,
//                            15 + row * BRICK_HEIGHT,
//                            BRICK_WIDTH, BRICK_HEIGHT,
//                            colors[(col * row) % 4]);
//         }
//     }
// }

// void resetGame(Rect* bricks, Rect* paddle, Rect* box) {
//     for (int i = 0; i < BRICKSNUM; i++) {
//         (bricks + i)->isRemoved = 0;
//     }

//     paddle->x = 120;
//     paddle->y = 140;
//     box->x = 120;
//     box->y = 100;
// }


// void drawRectArr(Rect* rectArr, int length) {
//     for (int i = 0; i < length; i++) {
//         if (rectArr->isRemoved == 0) {
//             drawRect(*(rectArr + i));
//         }
//     }
// }

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
        DMA[3].cnt = width | DMA_ON;
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

