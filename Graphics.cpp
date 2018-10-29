///#####################################################
///# This class is implementing the basic funcionality #
///# for displaying rectangles, triangles, HLines,     #
///# VLines and Text. This class is relying on the     #
///# implementation of drawPixel, setCursor,           #
///# setTextColor, setTextWrap and print of the        #
///# Adafruit_GFX device. Best results are achieved    #
///# when using a displayBuffer.                       #
///# By Sebastian Leifeld                              #
///#####################################################

#include "Graphics.h"

Adafruit_GFX* g;

Graphics::Graphics(Adafruit_GFX* screen)
{
  g = screen;
}

void Graphics::drawBarycentricTriangle(int ax, int ay, int bx, int by, int cx, int cy, uint16_t color)
{
  /* get the bounding box of the triangle */
  int maxX = max(ax, max(bx, cx));
  int minX = min(ax, min(bx, cx));
  int maxY = max(ay, max(by, cy));
  int minY = min(ay, min(by, cy));

  /* spanning vectors of edge (v1,v2) and (v1,v3) */
  int dx = bx - ax;
  int dy = by - ay;
  int ex = cx - ax;
  int ey = cy - ay;
  
  for (int x = minX; x <= maxX; x++)
  {
    for (int y = minY; y <= maxY; y++)
    {
      int qx = x - ax;
      int qy = y - ay;
  
      float s = (float)Extensions::crossProduct(qx, qy, ex, ey) / Extensions::crossProduct(dx, dy, ex, ey);
      float t = (float)Extensions::crossProduct(dx, dy, qx, qy) / Extensions::crossProduct(dx, dy, ex, ey);
  
      if ( (s >= 0) && (t >= 0) && (s + t <= 1))
      {
        g->drawPixel(x, y, color);
      }
    }
  }
}

void Graphics::drawRect(int x, int y, int width, int height, int rotation, uint16_t color)
{
  float rad = rotation * PI / 180;

  //Spitze
  int ax = x;
  int ay = y;

  int bx = x;
  int by = y + height;

  int cx = x + width;
  int cy = y + height;

  int dx = x + width;
  int dy = y;

  //Transformierung des Origin zu (0,0) für die rotation
  int transformedax = ax - x - width / 2;
  int transformeday = ay - y - height / 2;

  int transformedbx = bx - x - width / 2;
  int transformedby = by - y - height / 2;

  int transformedcx = cx - x - width / 2;
  int transformedcy = cy - y - height / 2;

  int transformeddx = dx - x - width / 2;
  int transformeddy = dy - y - height / 2;

  // Transformierung und rotation
  ax = transformedax * cos(rad) - transformeday * sin(rad) + x + width / 2;
  ay = transformeday * cos(rad) + transformedax * sin(rad) + y + height / 2;

  bx = transformedbx * cos(rad) - transformedby * sin(rad) + x + width / 2;
  by = transformedby * cos(rad) + transformedbx * sin(rad) + y + height / 2;

  cx = transformedcx * cos(rad) - transformedcy * sin(rad) + x + width / 2;
  cy = transformedcy * cos(rad) + transformedcx * sin(rad) + y + height / 2;

  dx = transformeddx * cos(rad) - transformeddy * sin(rad) + x + width / 2;
  dy = transformeddy * cos(rad) + transformeddx * sin(rad) + y + height / 2;

  drawBarycentricTriangle( ax,
                           ay,
                           bx,
                           by,
                           cx,
                           cy,
                           color);

  drawBarycentricTriangle( dx,
                           dy,
                           ax,
                           ay,
                           cx,
                           cy,
                           color);

}

void Graphics::drawTriangle(int ax, int ay, int bx, int by, int cx, int cy, int rotation, uint16_t color)
{
  float rad = rotation * PI / 180;

  int sx = (ax + bx + cx) / 3;
  int sy = (ay + by + cy) / 3;

  int minx = min(ax, min(bx, cx));
  int miny = min(ay, min(by, cy));

  //Transformierung des Origin zu (0,0) für die rotation
  int transformedsx = sx - minx;
  int transformedsy = sy - miny;

  int transformedax = ax - minx - transformedsx;
  int transformeday = ay - miny - transformedsy;

  int transformedbx = bx - minx - transformedsx;
  int transformedby = by - miny - transformedsy;

  int transformedcx = cx - minx - transformedsx;
  int transformedcy = cy - miny - transformedsy;

  // Transformierung und rotation
  ax = transformedax * cos(rad) - transformeday * sin(rad) + minx + transformedsx;
  ay = transformeday * cos(rad) + transformedax * sin(rad) + miny + transformedsy;

  bx = transformedbx * cos(rad) - transformedby * sin(rad) + minx + transformedsx;
  by = transformedby * cos(rad) + transformedbx * sin(rad) + miny + transformedsy;

  cx = transformedcx * cos(rad) - transformedcy * sin(rad) + minx + transformedsx;
  cy = transformedcy * cos(rad) + transformedcx * sin(rad) + miny + transformedsy;

  drawBarycentricTriangle( ax,
                           ay,
                           bx,
                           by,
                           cx,
                           cy,
                           color);
}

void Graphics::drawHLine(int ax, int bx, int y, uint16_t color)
{
  if (ax < bx)
  {
    Extensions::swap(ax, bx);
  }

  for(size_t i = 0; i < bx - ax; i++)
  {
    g->drawPixel(ax + i, y, color);
  }
}

void Graphics::drawVLine(int ay, int by, int x, uint16_t color)
{
  if (ay < by)
  {
    Extensions::swap(ay, by);
  }

  for(size_t i = 0; i < by - ay; i++)
  {
    g->drawPixel(x, ay + i, color);
  }
}

void Graphics::drawText(int x, int y, String text, uint16_t color)
{
  char* cMsg = (char*)malloc(sizeof(char)*text.length());
  
  strcpy(cMsg, text.c_str());
  g->setCursor(x,y);
  g->setTextColor(color);
  g->setTextWrap(true);
  g->print(cMsg);
}

void Graphics::drawText(String text, uint16_t color)
{
  drawText(0, 0, text, color);
}