


// #define BRICKROWS 5
// #define BRICKCOLS 12
// #define BRICKSNUM (BRICKCOLS)*(BRICKCOLS) 
// #define BRICK_WIDTH 20
// #define BRICK_HEIGHT 5

// #define PADDLE_WIDTH 30
// #define PADDLE_HEIGHT 5
// #define PADDLE_COLOR PURPLE

// #define BOX_WIDTH 5
// #define BOX_HEIGHT 5



// unsigned short *videoBuffer;

// typedef struct DMA_CONTROLLER
// {
//     const void* src;
//     void* dst;
//     u32 cnt;
// } DMA_CONTROLLER;


// /* functions for drawing the screen */
// void setPixel(int x, int y, u16 color);
// void drawChar(int x, int y, char ch, u16 color);
// void drawString(int x, int y, char* str, u16 color);
// void drawImage3(int x, int y, int width, int height, const u16* image);
// void fillScreen(int x, int y, int width, int height, const u16 color);
// void clearScreen();
// void waitForVBlank();
// void drawGameOverScreen();
// void drawWelcomeScreen();
// void resetGame(Rect* bricks, Rect* paddle, Rect* box);
// void drawRect(Rect rect);
// void drawRectArr(Rect* rect, int length);



// *** General =======================================================

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef char s8;
typedef short s16;
typedef int s32;

#define TRUE 1
#define FALSE 0

/* DMA */

#define REG_DMA0SAD         *(volatile u32*)0x40000B0 		// source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(volatile u32*)0x40000BC 		// source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(volatile u32*)0x40000C8 		// source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(volatile u32*)0x40000D4 		// source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

// *** Video =======================================================

/* Mode 3 */
extern u16* videoBuffer;               // 0x6000000
extern const unsigned char fontdata_6x8[12288];

#define REG_DISPCNT  *(u16*) 0x4000000
#define SCANLINECOUNTER *(unsigned short *)0x4000006
#define OFFSET(r, c, rowlen) ((r) * (rowlen) + (c))


//Background Enables
#define BG0_ENABLE  (1 << 8)
#define BG1_ENABLE  (1 << 9)
#define BG2_ENABLE  (1 << 10)
#define BG3_ENABLE  (1 << 11)

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

#define FROGGERS_WIDTH 10
#define FROGGERS_HEIGHT 10

#define CAR_WIDTH 10
#define CAR_HEIGHT 10

#define BAR_HEIGHT 10

#define COLOR(r, g, b) (r | (g << 5) | (b << 10))

#define BLACK   COLOR(0, 0, 0)
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0, 0)
#define GREEN   COLOR(0, 31, 0)
#define BLUE    COLOR(0, 0, 31)
#define YELLOW  COLOR(31, 31, 0)
#define CYAN    COLOR(0, 31, 31)
#define MAGENTA COLOR(31, 0, 31)
#define GRAY    COLOR(25, 25, 25)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)

#define MODE_0 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define MODE_4 4
#define MODE_5 5
#define MODE_6 6

/* DMA */

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

typedef struct Frog
{
	int x;
	int y;
	u16 color;
	int width;
	int height;
} Frog;

typedef struct Vehicle
{	
	int x;
	int y;
	int oldX;
	int oldY;
	int speed;
	int left;
	int right;
} Vehicle;

// typedef struct Rect
// {
// 	int x;
// 	int y;
// 	u16 color;
// 	int width;
// 	int height;
// 	int isRemoved;
// } Rect;


// Defines
// DMA channels
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

// Mostly just used for sound.
#define DMA_REPEAT (1 << 25)

// DMA copies 16 bits at a time normally (1 pixel), 
// but can be set to copy 32 bits at a time to be 
// even faster for mutliples of 32 bits.
#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)


// *** Input =========================================================

// Buttons

#define BUTTON_A		(1 << 0)
#define BUTTON_B		(1 << 1)
#define BUTTON_SELECT	(1 << 2)
#define BUTTON_START	(1 << 3)
#define BUTTON_RIGHT	(1 << 4)
#define BUTTON_LEFT		(1 << 5)
#define BUTTON_UP		(1 << 6)
#define BUTTON_DOWN		(1 << 7)
#define BUTTON_R		(1 << 8)
#define BUTTON_L		(1 << 9)

#define BUTTONS (*(unsigned int *)0x4000130)

#define KEY_DOWN_NOW(key) (~(BUTTONS) & key)

// Prototypes
void waitForVBlank();
void drawRectangle(int row, int col, int width, int height, u16 color);
void drawImage3(int row, int col, int width, int height, const u16* image);
void fillScreen(volatile u16 color);
void welcomeScreen();
void gamePlayScreen();
void gameOverScreen();
void setPixel(int x, int y, u16 color);
void drawChar(int x, int y, char ch, u16 color);
void drawString(int x, int y, char* str, u16 color);
Frog createFrog(int x, int y, int width, int height, u16 color);
void setFrogPosition(Frog* frog, int x, int y);
void drawFrog(Frog frog);
void initLane();
void drawCars();
void updateCarPos();
int isCollided(Frog frog);


