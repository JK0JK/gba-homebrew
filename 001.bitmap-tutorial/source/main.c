
#include <gba.h>

#define DCNT_MODE0     0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005
// layers
#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000

typedef u16 COLOR;
COLOR RGB15(u32 red, u32 green, u32 blue)
{   return red | (green<<5) | (blue<<10);   }

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

    int ii, jj;

    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;

    // Fill screen with grey color
    m3_fill(RGB15(12, 12, 14));

    // Rectangles:
    m3_rect( 12,  8, 108,  72, RGB15(31, 0, 0));
    m3_rect(108, 72, 132,  88, RGB15(0, 31, 0));
    m3_rect(132, 88, 228, 152, RGB15(0, 0, 31));

    // Rectangle frames
    m3_frame(132,  8, 228,  72, RGB15(0, 31, 31));
    m3_frame(109, 73, 131,  87, RGB15(0, 0, 0));
    m3_frame( 12, 88, 108, 152, RGB15(31, 31, 0));

    // Lines in top right frame
    for(ii=0; ii<=8; ii++)
    {
        jj= 3*ii+7;
        m3_line(132+11*ii, 9, 226, 12+7*ii, RGB15(jj, 0, jj));
        m3_line(226-11*ii,70, 133, 69-7*ii, RGB15(jj, 0, jj));
    }

    // Lines in bottom left frame
    for(ii=0; ii<=8; ii++)
    {
        jj= 3*ii+7;
        m3_line(15+11*ii, 88, 104-11*ii, 150, RGB15(0, jj, jj));
    }

    while(1);

    return 0;


}




