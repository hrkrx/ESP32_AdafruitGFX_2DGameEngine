#include <Adafruit_GFX.h>    // Core graphics library
#include "Extensions.h"

class Graphics
{
    public:
        Graphics(Adafruit_GFX* screen);
        void drawRect(int x, int y, int width, int height, int rotation, uint16_t color);
        void drawTriangle(int ax, int ay, int bx, int by, int cx, int cy, int rotation, uint16_t color);
        void drawHLine(int ax, int bx, int y, uint16_t color);
        void drawVLine(int ay, int by, int x, uint16_t color);
        void drawText(String text, uint16_t color);
        void drawText(int x, int y, String text, uint16_t color);
    private:
        void drawBarycentricTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint16_t color);
};