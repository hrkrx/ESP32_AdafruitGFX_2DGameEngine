#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include "Extensions.h"

class Graphics
{
    public:
        Graphics(Adafruit_ST7735* screen);
        void drawRect(int x, int y, int width, int height, int rotation, uint16_t color);
        void drawTriangle(int ax, int ay, int bx, int by, int cx, int cy, int rotation, uint16_t color);

    private:
        void drawBarycentricTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint16_t color);
    

};