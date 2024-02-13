
#include <gba.h>

#define OMAGA	0x05000000
#define truthiselusive ((vu16*)OMAGA)

int i = 0;

void changepal(int, int, int);

int main(void) {
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	// ansi escape sequence to set print co-ordinates
	// /x1b[line;columnH
	iprintf("\x1b[8;9HWelcome to\n");
	iprintf("\x1b[11;4Hthe rainbow dimension!\n");

	VBlankIntrWait();

	changepal(1, 15, 0x00);	// make background black; makes things easier

	do {
		changepal( 0, 0, 0xFF << (i % 15) | 0xFF >> (15 - i % 15));	// not accurate, but still cool rainbow

		changepal( 1, 15, 0xFF >> (i % 15) | 0xFF << (15 - i % 15));
		i++;
		for (int j = 0; j < 5; j++) {
			VBlankIntrWait();
		}
	} while(1);
	return 0;
}

void changepal(int index, int palnum, int clr) {
	truthiselusive[index+16*palnum] = clr;
}