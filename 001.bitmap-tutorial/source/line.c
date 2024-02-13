#include <gba.h>

void bmp16_line (int x1, int x2, int y1, int y2, u32 clr, void *dstBase, u32 dstPitch) {
    int ii, dx, dy, xstep, ystep, dd;
    u16 *dst = (u16*)(dstBase + y1*dstPitch + x1*2); // pointer dst points to address in memory where (x1, y1) is
    dstPitch /= 2;

    // NORMALIZATION
    if (x1>x2)
    { xstep = -1;   dx = x1-x2; }
    else
    { xstep = +1;   dx = x2-x1;}

    if (y1>y2)
    { ystep = -dstPitch;   dy = y1-y2; }
    else
    { ystep = +dstPitch;   dy = y1-y2; }


    // DRAWING
    if(dy == 0) {       // Horizontal
        for(ii=0; ii<=dx; ii++)
            dst[ii*xstep]= clr;
    }
    else if(dx == 0) {  // Vertical
        for(ii=0; ii<=dy; ii++)
            dst[ii*ystep]= clr;
    }

    else if(dx>=dy) {   // Diagonal, slope <= 1
        dd= 2*dy - dx;

        for(ii=0; ii<=dx; ii++) {
            *dst= clr;
            if(dd >= 0)
            {   dd -= 2*dx; dst += ystep;  }

            dd += 2*dy;
            dst += xstep;
        }
    }
    else {              // Diagonal, slope > 1
        dd= 2*dx - dy;

        for(ii=0; ii<=dy; ii++) {
            *dst= clr;
            if(dd >= 0)
            {   dd -= 2*dy; dst += xstep;  }

            dd += 2*dx;
            dst += ystep;
        }
    }
}

void bmp16_rect(int left, int top, int right, int bottom, u32 clr,
    void *dstBase, u32 dstPitch)
{
    int ix, iy;

    u32 width= right-left, height= bottom-top;
    u16 *dst= (u16*)(dstBase+top*dstPitch + left*2);
    dstPitch /= 2;

    // --- Draw ---
    for(iy=0; iy<height; iy++)
        for(ix=0; ix<width; ix++)
            dst[iy*dstPitch + ix]= clr;
}

void bmp16_frame(int left, int top, int right, int bottom, u32 clr,
    void *dstBase, u32 dstPitch)
{
    // Frame is RB exclusive
    right--;
    bottom--;

    bmp16_line(left,  top,   right,  top,    clr, dstBase, dstPitch);
    bmp16_line(left,  bottom, right, bottom, clr, dstBase, dstPitch);

    bmp16_line(left,  top,   left,   bottom, clr, dstBase, dstPitch);
    bmp16_line(right, top,   right,  bottom, clr, dstBase, dstPitch);
}