/*
* For dynamic palettes
*
* > have a u16, curpal (actually, int is faster; only go with u16 if we really need that VRAM)
* > sprite needs palette slot (will store it, in order to know which one to reference; also needed to free)
* > have u16, simpal = curpal++
* > sprite.slot = curpal XOR simpal (would be sqrt but ints are faster so it's futile unless we really need that VRAM)
* > curpal++ (faster than curpal = simpal)
*
* This might become a problem when curpal is full. We can make an exception for this.
*
* > sprite on process to be destroyed
* > curpal = curpal AND NOT sprite.slot
* > sprite now safe to be destroyed
*/