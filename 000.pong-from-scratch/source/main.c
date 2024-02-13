
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>

#define MEM_VRAM		0x06000000	//constant - is a pointer to VRAM
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

typedef u16 			M3LINE[SCREEN_WIDTH];	// defines type M3LINE as an array with 240 values
#define m3_mem			((M3LINE*)MEM_VRAM)		// M3LINE is a pointer inside VRAM?

void initialSetup();
void drawRect();
void clearRect();
void drawPixel();
void solidScreen();

//---------------------------------------------------------------------------------

int playercolour = 0x07E0;
int backcolour = 0x00;
int markercolour = 0x4444;

/*Players and ball*/
struct rectangle {
	int x;
	int y;
	int prevX;
	int prevY;
	int height;
	int width;
	int velocityX;
	int velocityY;
};

void drawRect(struct rectangle* cRect, int colour) {
	for (int i= cRect -> x; i < cRect->x+cRect->width; i++) {
		for (int j= cRect -> y; j < cRect->y+cRect->height; j++) {
			drawPixel(i, j, colour);
		}
	}
}

void clearRect(struct rectangle* cRect) {
	for (int i= cRect -> prevX; i < cRect-> prevX + cRect->width; i++) {
		for (int j= cRect -> prevY; j < cRect-> prevY + cRect->height; j++) {
			drawPixel(i, j, backcolour);
		}
	}
}

void drawPixel(int x, int y, int colour) {
	m3_mem[y][x] = colour;
}

void solidScreen(int colour) {
	for (int i=0; i < SCREEN_WIDTH; i++) {
		for (int j=0; j < SCREEN_HEIGHT; j++) {
			drawPixel(i, j, colour);
		}
	}
}

//---------------------------------------------------------------------------------
int main(void) {

	initialSetup();

	struct rectangle player;
	player.height = 24;
	player.width = 8;
	player.x = 1;
	player.y = (SCREEN_HEIGHT - player.height) / 2;
	player.prevX = player.x;
	player.prevY = player.y;
	player.velocityX = 0;
	player.velocityY = 0;

	struct rectangle compooter;
	compooter.height = 24;
	compooter.width = 8;
	compooter.x = SCREEN_WIDTH - compooter.width - 1;
	compooter.y = (SCREEN_HEIGHT - compooter.height) / 2;
	compooter.prevX = compooter.x;
	compooter.prevY = compooter.y;
	compooter.velocityX = 0;
	compooter.velocityY = 0;

	struct rectangle ball;
	ball.height = 12;
	ball.width = 12;
	ball.x = (SCREEN_WIDTH - ball.width)/2;
	ball.y = (SCREEN_HEIGHT - ball.height) / 2;
	ball.prevX = ball.x;
	ball.prevY = ball.y;
	ball.velocityX = 0;
	ball.velocityY = 0;

	do {
		VBlankIntrWait();

		player.prevX = player.x;
		player.prevY = player.y;
		compooter.prevX = compooter.x;
		compooter.prevY = compooter.y;
		ball.prevX = ball.x;
		ball.prevY = ball.y;

		scanKeys();
		int key_pressed = keysDown();
		int key_released = keysUp();

		if((key_pressed & KEY_UP) || player.y > (SCREEN_HEIGHT - player.height)) {
			player.velocityY = -2;
		}

		if((key_pressed & KEY_DOWN) || player.y < 0) {
			player.velocityY = 2;
		}

		if(key_released) {
			player.velocityY = 0;
			player.velocityX = 0;
		}
		
		/*Clear*/
		clearRect(&player);
		clearRect(&compooter);
		clearRect(&ball);

		player.y += player.velocityY;
		player.x += player.velocityX;

		/*Draw*/
		drawRect(&player, playercolour);
		drawRect(&compooter, playercolour);
		drawRect(&ball, playercolour);

		if (key_pressed & KEY_DOWN) {
			break;
		}

	} while (1);

	REG_DISPCNT = (1 << 7); //this one is more readable than the other
	//REG_DISPCNT = 0b10000000;

	return 0;
}
//---------------------------------------------------------------------------------


void initialSetup() {
	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);
	consoleDemoInit();

	/* Set the BG2 to Mode 3 - bitmap; lacking in colour diversity, but allows control over each pixel */
	SetMode( MODE_3 | BG2_ON);

	solidScreen(backcolour);	//clean VRAM

	/* Draw center line*/
	for (int i=0; i < SCREEN_HEIGHT; i++) {
		drawPixel (SCREEN_WIDTH/2, i, markercolour); //16 bit colour: RGB 565
	}

	/* Draw center line*/
	for (int i=0; i < SCREEN_WIDTH; i++) {
		drawPixel (i, SCREEN_HEIGHT/2, markercolour); //16 bit colour: RGB 565
	}

}
