#include <gba.h>

typedef u16 COLOR;

#define MEM_VRAM    0x06000000

#define vid_mem         ((COLOR*)MEM_VRAM)

#define M3_WIDTH        240
#define M3_HEIGHT       160
#define M3_PITCH        2
#define M3_SIZE         M3_WIDTH * M3_HEIGHT * M3_PITCH

// === PROTOTYPES =====================================================

void m3_plot(int x, int y, COLOR clr);
void m3_line(int x1, int y1, int x2, int y2, COLOR clr);
void m3_rect(int left, int top, int right, int bottom, COLOR clr);
void m3_frame(int left, int top, int right, int bottom, COLOR clr);


// === INLINES ========================================================

//! Plot a single \a clr colored pixel in mode 3 at (\a x, \a y).
void m3_plot(int x, int y, COLOR clr)
{
    vid_mem[y*M3_WIDTH+x]= clr; 
}

//! Draw a \a clr colored line in mode 3.
void m3_line(int x1, int y1, int x2, int y2, COLOR clr)
{
    bmp16_line(x1, y1, x2, y2, clr, vid_mem, M3_WIDTH*2);
}

//! Draw a \a clr colored rectangle in mode 3.
void m3_rect(int left, int top, int right, int bottom, COLOR clr)
{
    bmp16_rect(left, top, right, bottom, clr, vid_mem, M3_WIDTH*2);
}

//! Draw a \a clr colored frame in mode 3.
void m3_frame(int left, int top, int right, int bottom, COLOR clr)
{
    bmp16_frame(left, top, right, bottom, clr, vid_mem, M3_WIDTH*2);
}

void m3_fill(COLOR clr)
{
    int ii;
    u32 *dst= (u32*)vid_mem;
    u32 wd= (clr<<16) | clr;

    for(ii=0; ii<M3_SIZE/4; ii++)
        *dst++= wd;
}