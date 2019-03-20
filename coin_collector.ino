/*
    Coin Collector
    By Bjoern Schilberg
    March, 2019

*/

#include <Arduboy2.h>
Arduboy2 arduboy;

const unsigned char PROGMEM fox_image[] = {
    0x00, 0x00, 0x00, 0x00, 0x76, 0xdf, 0x86, 0x04, 0x04, 0x24, 0x06, 0x27, 0x8c, 0xf8, 0x60, 0x00,
    0x00, 0x00, 0x0c, 0x0c, 0xdc, 0xf6, 0x23, 0x43, 0x43, 0x23, 0xf3, 0xdf, 0x0d, 0x0c, 0x00, 0x00};

const unsigned char PROGMEM coin_image[] = {
    0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18};

struct Fox
{
    uint8_t x;
    uint8_t y;
    const unsigned char *image;
};

Fox fox = {0, 8, fox_image};

struct Coin
{
    uint8_t x;
    uint8_t y;
    const unsigned char *image;
};

Coin coin = {};

uint8_t score = 0;

bool collision()
{

    Rect foxRect = Rect{fox.x, fox.y, 16, 16};
    Rect coinRect = Rect{coin.x, coin.y, 8, 8};

    if (arduboy.collide(foxRect, coinRect))
    {
        return true;
    }

    return false;
}

void setup()
{
    // Clears the screen at sets the framerate to 60 fps
    arduboy.begin();

    // Special technique to make sure that the seed is random to get a different sequence each time.
    arduboy.initRandomSeed();

    coin = {(uint8_t)random(0,128), (uint8_t)random(0,64), coin_image};

    arduboy.display();
    Serial.begin(9600);
}

void loop()
{
    //Prevent the Arduboy from running too fast
    if (!arduboy.nextFrame())
    {
        return;
    }

    arduboy.clear();

    if (arduboy.pressed(LEFT_BUTTON) && fox.x > 0)
    {
        fox.x--;
    }
    if (arduboy.pressed(RIGHT_BUTTON) && fox.x + 16 < 128)
    {
        fox.x++;
    }
    if (arduboy.pressed(UP_BUTTON) && fox.y > 0)
    {
        fox.y--;
    }
    if (arduboy.pressed(DOWN_BUTTON) && fox.y + 16 < 64)
    {
        fox.y++;
    }

    //arduboy.println(fox.x);
    //arduboy.println(fox.y);
    //arduboy.println(score);
    arduboy.print("Score:");
    arduboy.print(score);
    arduboy.setCursor(98, 45);
    arduboy.print("X:");
    arduboy.print(fox.x);
    arduboy.setCursor(98, 55);
    arduboy.print("Y:");
    arduboy.print(fox.y);

    if (collision())
    {
        score += 1;
        coin.x = (uint8_t)random(0, 128-8);
        coin.y = (uint8_t)random(0, 64-8);
    };
    arduboy.drawBitmap(fox.x, fox.y, fox.image, 16, 16, WHITE);
    arduboy.drawBitmap(coin.x, coin.y, coin.image, 8, 8, WHITE);

    //Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
    Serial.println(score);

    arduboy.display();
}
