
#include <stdio.h>
#include <tonc.h>
#include <string.h>

#include "ice_fairy.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

void obj_test() {
	int x = SCREEN_WIDTH / 2, y = SCREEN_HEIGHT / 2;

	u32 tileid = 0, palette = 0;

	OBJ_ATTR *cirno = &obj_buffer[0];

	obj_set_attr(cirno,
		ATTR0_SQUARE,
		ATTR1_SIZE_16,
		ATTR2_PALBANK(palette) | tileid);

	obj_set_pos(cirno, x, y);

	while(1) {
		vid_vsync();
		key_poll();

		// move left/right
		x += 2*key_tri_horz();

		// move up/down
		y += 2*key_tri_vert();

		palette = key_hit(KEY_SELECT) ? palette+1 : palette;

		// Hey look, it's one of them build macros!
		cirno->attr2= ATTR2_BUILD(tileid, palette, 0);
		obj_set_pos(cirno, x, y);

		oam_copy(oam_mem, obj_buffer, 1);	// only need to update one
	}
}

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	// Places the glyphs of a 4bpp boxed cirno sprite
	//   into LOW obj memory (cbb == 4)
	memcpy(&tile_mem[4][0], ice_fairyTiles, ice_fairyTilesLen);
	memcpy(pal_obj_mem, ice_fairyPal, ice_fairyPalLen);

	oam_init(obj_buffer, 128);
	REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D;

	obj_test();

	while(1)
	{
		VBlankIntrWait();
	}

	return 0;
}
