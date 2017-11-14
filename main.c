// Name: HIEU LE

#include "frogs.h"
#include "myLib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum GAMESTATE {
    START,
    WAITING,
    PLAYING,
    GAMEOVER,
    NEWSTATE 
};

int main() {

    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // initialize game state
    enum GAMESTATE state = START;
    // enum GAMESTATE nextState = WAITING;
    int startPressed = 0;

    // // initialize game setting
    // int velocity = 1;
    // int dx = velocity;
    // int dy = -velocity;
    //char scoreBuffer[10];
    //int score = 0;

    // // initial game objects
    // Rect bricks[BRICKSNUM];
    // initBricks(bricks);
    Frog frogger = createFrog(135, 120, FROGGERS_WIDTH, FROGGERS_HEIGHT, GREEN);
    Frog oldFrogger = frogger;

    //int time = 60;
    // Rect box = createRect(120, 100, BOX_WIDTH, BOX_HEIGHT, GREEN);
    // Rect oldBox = box;

    while(1) {

        startPressed = 0;

        switch(state) {
            case(START):
                welcomeScreen();
                drawString(60, 100, "Press 'Enter' to Start", WHITE);
                drawString(60, 115, "Press 'ESC' to Exit", WHITE);
                state = WAITING;
                // nextState = PLAYING;
                break;
            case(WAITING):
                //gamePlayScreen();
                while(KEY_DOWN_NOW(BUTTON_START)) {
                    if (!startPressed) {
                        startPressed = 1;
                        state = PLAYING;
                    }
                }
                break;
            case(GAMEOVER):
                gameOverScreen();
                while(KEY_DOWN_NOW(BUTTON_START)) {
                    if (!startPressed) {
                        startPressed = 1;
                        //welcomeScreen();
                        state = START;
                    }
                }
                break;
                //drawGameOverScreen();
                // reset the game settings
                // resetGame(bricks, &paddle, &box);
                // score = 0;
                // velocity = 1;
                // dx = velocity;
                // dy = -velocity;
            case(PLAYING):
                fillScreen(BLACK);
                state = NEWSTATE;
                break;
            case(NEWSTATE):
                // drawRectangle(50, 50, 100, 100, BLUE);
                
                // drawRectangle(138, 120, 7, 7, GREEN);
                drawImage3(135, 120, FROGGERS_WIDTH, FROGGERS_HEIGHT, froggers);

                memcpy(&oldFrogger, &frogger, sizeof(Frog));
                oldFrogger.color = WHITE;

                // move the paddle as left or right button is pressed
                if (KEY_DOWN_NOW(BUTTON_LEFT)) {
                    setFrogPosition(&frogger, frogger.x, frogger.y - 2);
                }
                if (KEY_DOWN_NOW(BUTTON_RIGHT)) {   
                    setFrogPosition(&frogger, frogger.x, frogger.y + 2);
                }
                if (KEY_DOWN_NOW(BUTTON_UP)) {
                    setFrogPosition(&frogger, frogger.x - 2, frogger.y);
                } 
                if (KEY_DOWN_NOW(BUTTON_DOWN)) {
                    setFrogPosition(&frogger, frogger.x + 2, frogger.y);
                }

                initLane();
                fillScreen(0);
                drawRectangle(0, 0, SCREEN_WIDTH, BAR_HEIGHT, BLUE);
                drawRectangle(135, 0, SCREEN_WIDTH, BAR_HEIGHT, BLUE);
                drawImage3(oldFrogger.x, oldFrogger.y, FROGGERS_WIDTH, FROGGERS_HEIGHT, froggers);
                drawCars();
                updateCarPos();

                // drawImage3(100, 2, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);
                // drawImage3(100, 100, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);
                // drawImage3(100, 220, RIGHTCARS_WIDTH, RIGHTCARS_HEIGHT, rightCars);

                // score++;
                // sprintf(scoreBuffer, "%d", score);
                drawString(1, 150, "LIVES: ", PINK);
                drawString(180, 150, "TIME: ", PINK);
                //drawString(50, 2, scoreBuffer, PINK);
                drawString(1, 2, "SCORE: ", PINK);
                waitForVBlank();            
                
                // drawRectangle(135, 120, 5, 5, RED);

                // drawRectangle(135, 120, 5, 5, RED);

                // if ((box.y + box.height >= SCREEN_HEIGHT)
                //     || (score >= BRICKSNUM)) {
                //     state = GAMEOVER;
                // }
                // // go to welcome screen when select button is pressed
                // while(KEY_DOWN_NOW(BUTTON_SELECT)) {
                //     if (!startPressed) {
                //         startPressed = 1;
                //         // reset the game settings
                //         resetGame(bricks, &paddle, &box);
                //         score = 0;
                //         dx = velocity;
                //         dy = -velocity;
                //         state = START;
                //     }
                // }

                // press A to increase the speed
                while(KEY_DOWN_NOW(BUTTON_START)) {
                    if (!startPressed) {
                        startPressed = 1;
                        // velocity++;
                        // box.color = RED;
                        state = GAMEOVER;
                    }
                }
                break;
        }

        // if (state != PLAYING) {
        //     continue;
        // }

        // save old state of moving objects (e.g box and paddle)
        // memcpy(&oldBox, &box, sizeof(Rect));
        // oldBox.color = WHITE;
        
        // // check for wall collision
        // if (box.x <= 0) {
        //     dx = velocity;
        // } else if (box.x >= SCREEN_WIDTH - box.width) {
        //     dx = -velocity;
        // }
        // if (box.y <= 0) {
        //     dy = velocity;
        // } else if (box.y + box.height >= SCREEN_HEIGHT) {
        //     dy = -velocity;
        // }
        // // move the box
        // setRectPosition(&box, box.x + dx, box.y + dy);

        // int collideollidedBrickIndex = boxCollideBricks(&box, bricks);
        // // collide a brick
        // if (collidedBrickIndex != -1) {
        //     Rect* collidedBrick = bricks + collidedBrickIndex;
        //     collidedBrick->isRemoved = 1;
        //     drawImage3(collidedBrick->x, collidedBrick->y, collidedBrick->width, collidedBrick->height, background);
        //     dy = -dy;
        //     score++;
        // }

        // // collide the paddle
        // if (boxCollidePaddle(&box, &paddle)) {
        //     dy = -velocity;
        // }

        // // move the paddle as left or right button is pressed
        // if (KEY_DOWN_NOW(BUTTON_LEFT)) {
        //     setRectPosition(&paddle, paddle.x - 10, paddle.y);
        // }
        // if (KEY_DOWN_NOW(BUTTON_RIGHT)) {

        //     setRectPosition(&paddle, paddle.x + 10, paddle.y);
        // }

        // // redraw moving objects
        // drawImage3(oldBox.x, oldBox.y, BOX_WIDTH, BOX_HEIGHT, background);
        // drawRect(box);
        // drawImage3(oldPaddle.x, oldPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT, background);
        // drawRect(paddle);
        // sprintf(scoreBuffer,"%d",score);
        // drawImage3(41, 2, 18, 8, background);
        // drawString(41, 2, scoreBuffer, PINK);
        // drawString(5, 2, "SCORE:", PINK);
        // drawString(70, 2, "Press A for more fun", PINK);
    }
    return 0;
}