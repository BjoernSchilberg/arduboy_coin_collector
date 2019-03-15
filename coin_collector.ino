/*
    Coin Collector
    By Bjoern Schilberg
    March, 2019

*/

#include <Arduboy2.h>
Arduboy2 arduboy;

uint8_t foxx = 0;
uint8_t foxy = 8;

const unsigned char PROGMEM fox[] = {
        0x00, 0x00, 0x00, 0x00, 0x76, 0xdf, 0x86, 0x04, 0x04, 0x24, 0x06, 0x27, 0x8c, 0xf8, 0x60, 0x00,
        0x00, 0x00, 0x0c, 0x0c, 0xdc, 0xf6, 0x23, 0x43, 0x43, 0x23, 0xf3, 0xdf, 0x0d, 0x0c, 0x00, 0x00};

void setup()
{
    // Clears the screen at sets the framerate to 60 fps
    arduboy.begin();

    arduboy.display();

}

void loop()
{
    //Prevent the Arduboy from running too fast
    if (!arduboy.nextFrame())
    {
        return;
    }

    arduboy.clear();

    if (arduboy.pressed(LEFT_BUTTON) && foxx > 0)
    {
        foxx--;
    }
    if (arduboy.pressed(RIGHT_BUTTON) && foxx + 16 < 128)
    {
        foxx++;
    }
    if (arduboy.pressed(UP_BUTTON) && foxy > 0)
    {
        foxy--;
    }
    if (arduboy.pressed(DOWN_BUTTON) && foxy + 16 < 64)
    {
        foxy++;
    }

    arduboy.println(foxx);
    arduboy.println(foxy);

    arduboy.drawBitmap(foxx, foxy, fox, 16, 16, WHITE);

    arduboy.display();
}
