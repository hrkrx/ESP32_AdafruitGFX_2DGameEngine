#include "Bitmap.h"

Bitmap::Bitmap(char* data)
{
    
    for(short i = 0; i < 14; i++)
    {
        _bitmapFileHeader[i] = data[i];
    }

    _dataOffset = _bitmapFileHeader[13];
    _dipHeader = new char[data[14]];
    
    for(uint16_t i = 0; i < data[14]; i++)
    {
        _dipHeader[i] = data[i];
    }
    
    _bitmapDataSize = sizeof(data)/sizeof(*data) - _dataOffset;
    _bitmapData = new char[_bitmapDataSize];

    for(uint32_t i = 0; i < _bitmapDataSize; i++)
    {
        _bitmapData[i] = data[i];
    }
     
}

int Bitmap::GetWidth()
{
    return _GetLittleEndianInt(_dipHeader, 18);
}

int Bitmap::GetHeight()
{
    return _GetLittleEndianInt(_dipHeader, 22);
}

uint16_t Bitmap::_GetLittleEndianUint16(char* bytes, int start = 0)
{
    uint16_t result = 0;
    for (uint16_t n = sizeof(result) + start; n >= start; n--)
        result = (result << 8) + bytes[n];
    return result;
}

int Bitmap::_GetLittleEndianInt(char* bytes, int start = 0)
{
    int result = 0;
    for (int n = sizeof(result) + start; n >= start; n--)
        result = (result << 8) + bytes[n];
    return result;
}