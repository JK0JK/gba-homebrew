/*
*   Black, after a few seconds "urgh", "ouch", "argh" with flashing lights
*   "HEY, WATCH IT!"
*   Suddenly, Miles can be seen
*   "Damn it! Not again!"
*
*   Miles' lab fades in
*   
*   "I hate it when this happens..."
*
*   Miles suddenly notices the player
*   "Oh, hi! Welcome to my lab!"
*
*   "Sorry, everhything's gone down the drain over here..."
*   "You just came from that portal, right?"
*
*   "I didn't think it would work, but hey, you're here!"
*
*   "So uh.... Welcome to my lab!"
*
*   "This is where you'll be testing new features and whatnot!"
*   "...well, next time, that is..."
*
*   "Uh... feel free to explore, but there's not much else to this demo"
*/

/* When talking to him:
*   "Oh hey! What's up?"
*   Present multiple choices
*
*   > Who are you?
*       "Name's Miles! This is my lab!"
*       "You could say I'm one of the developers of Minigame Investigator, but the truth is that I'm really not..."
*       "This is a one man team, actually; I'm just along for the ride"
*       "Anyway, we're using my lab for experimenting and testing new stuff!"
*
*   > What's new?
*       "New? We've just started!"
*       "This build is all about making the bare minimum - a benchmark, of sorts!"
*       "Tiles, maps, saving, textboxes, sprites... everything is brand new!"
*       "Where you came from.... You're from the ROM Hack, aren't you?"
*       "Well, in this universe we decided to do stuff from scratch!"
*       "Can't get sued if we don't use the Pokemon engine, right?"
*       "...well, there's that and there's also not having to worry about merge conflicts with the main branch..."
*       "Anyway, I hope you have fun testing!"
*
*   > Remember me?
*       If same or inferior version:
*                           "...no, this is the first time we've met!"
*                           "Maybe me from the ROM Hack universe might, but... I wouldn't hold my breath."
*       If superior version AND flag TALKED_TO_MILES set:
*                           "...no, this is the first time we've met!"
*                           "Well, it's the first time I've met you, but I know it's not the first time you've met me."
*                           "Don't tell me about the future, though, I don't want time paradoxes going on in MY lab!"
*
*   > You suck
*       "...feeling blunt today, are we?"
*
*   > Bye!
*       "Laters!"
*/