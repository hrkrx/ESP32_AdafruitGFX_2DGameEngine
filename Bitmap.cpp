#include "Bitmap.h"

Bitmap::Bitmap(char* data)
{
    
    for(short i = 0; i < 14; i++)
    {
        _bitmapFileHeader[i] = data[i];
    }

    _dataOffset = _GetLittleEndianUint32(_bitmapFileHeader, 10);
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

    _bitCount = _GetLittleEndianUint16(_dipHeader, 14);
    _
     
}

int Bitmap::GetWidth()
{
    return (int)_GetLittleEndianUint32(_dipHeader, 4);
}

int Bitmap::GetHeight()
{
    return (int)_GetLittleEndianUint32(_dipHeader, 8);
}

uint16_t Bitmap::_GetLittleEndianUint16(char* bytes, int start = 0)
{
    uint16_t result = 0;
    for (uint16_t n = sizeof(result) + start; n >= start; n--)
        result = (result << 8) + bytes[n];
    return result;
}

uint32_t Bitmap::_GetLittleEndianUint32(char* bytes, int start = 0)
{
    uint32_t result = 0;
    for (uint32_t n = sizeof(result) + start; n >= start; n--)
        result = (result << 8) + bytes[n];
    return result;
}