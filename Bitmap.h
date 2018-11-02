// implementation of the Windows Bitmap filetype
#include <stdint.h>

class Bitmap
{
    public:
    Bitmap(char* data);
    uint32_t GetWidth();
    uint32_t GetHeight();
    uint16_t GetPixel(int x, int y);

    private:
    char* _bitmapFileHeader = new char[14];
    char* _dipHeader;
    char* _bitmapData;
    uint32_t _dataOffset;
    uint32_t _compression;
    uint32_t _colorTable;
    uint32_t _colorCount;
    uint32_t _bitmapDataSize;
    uint16_t _colorDepth;
    uint16_t _bitCount;
    uint32_t _GetLittleEndianUint32(char* bytes, int start = 0);
    uint16_t _GetLittleEndianUint16(char* bytes, int start = 0);
};