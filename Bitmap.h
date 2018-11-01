// implementation of the Windows Bitmap filetype
#include <stdint.h>

class Bitmap
{
    public:
    Bitmap(char* data);
    int GetWidth();
    int GetHeight();
    uint16_t GetPixel(int x, int y);

    private:
    char* _bitmapFileHeader = new char[14];
    char* _dipHeader;
    char* _bitmapData;
    int _dataOffset;
    short _compression;
    int _colorTable;
    int _colorCount;
    uint32_t _bitmapDataSize;
    uint16_t _colorDepth;
    int _GetLittleEndianInt(char* bytes, int start = 0);
    uint16_t _GetLittleEndianUint16(char* bytes, int start = 0);
};