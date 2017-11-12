/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=3 myImages game_over1.png gameplay.jpg game_over.gif frogger.jpg 
 * Time-stamp: Thursday 11/09/2017, 22:52:25
 * 
 * Image Information
 * -----------------
 * game_over1.png 950@534
 * gameplay.jpg 480@360
 * game_over.gif (frame 0) 600@400
 * game_over.gif (frame 1) 600@400
 * game_over.gif (frame 2) 600@400
 * game_over.gif (frame 3) 600@400
 * frogger.jpg 992@660
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef MYIMAGES_H
#define MYIMAGES_H

extern const unsigned short game_over1[507300];
#define GAME_OVER1_SIZE 1014600
#define GAME_OVER1_LENGTH 507300
#define GAME_OVER1_WIDTH 950
#define GAME_OVER1_HEIGHT 534

extern const unsigned short gameplay[172800];
#define GAMEPLAY_SIZE 345600
#define GAMEPLAY_LENGTH 172800
#define GAMEPLAY_WIDTH 480
#define GAMEPLAY_HEIGHT 360

extern const unsigned short game_over0[240000];

extern const unsigned short game_over1[240000];

extern const unsigned short game_over2[240000];

extern const unsigned short game_over3[240000];

extern const unsigned short frogger[654720];
#define FROGGER_SIZE 1309440
#define FROGGER_LENGTH 654720
#define FROGGER_WIDTH 992
#define FROGGER_HEIGHT 660

extern const unsigned short* game_over_frames[4];
#define GAME_OVER_FRAMES 4

#define GAME_OVER_SIZE 480000
#define GAME_OVER_LENGTH 240000
#define GAME_OVER_WIDTH 600
#define GAME_OVER_HEIGHT 400

#endif

