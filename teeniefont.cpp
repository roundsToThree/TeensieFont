#include "teeniefont.h"

void (*pixelMethod)(int, int, int);
int backgroundCol = 0xFFFFFFFF;
int foregroundCol = 0xFF000000;
bool AAenabled = false;
Font font = nullptr;

int fontHeight;
Font *fontMap;

void loadCharSet(int &index, char first, char last);

void loadFont()
{
    if (font == nullptr)
        return;

    // Allocate font map (128 ascii char limit currently)
    if (fontMap == nullptr)
        fontMap = new Font[128];

    fontHeight = font[0];
    unsigned char set = font[1];

    int ind = 2;
    // If uppercase selected
    if (set & 1 == 1)
        loadCharSet(ind, 'A', 'Z');
    // Lowercase selected
    if ((set >> 1) & 1 == 1)
        loadCharSet(ind, 'a', 'z');
    // Numbers selected
    if ((set >> 2) & 1 == 1)
        loadCharSet(ind, '0', '9');
    // Symbols selected
    if ((set >> 3) & 1 == 1){
        loadCharSet(ind, ' ', '@');
        loadCharSet(ind, '[', '`');
        loadCharSet(ind, '{', '~');
    }
    
    
}

// Looking from position index, load the range of characters specified (inclusive)
void loadCharSet(int &index, char first, char last)
{

    for (int i = 0; i <= last - first; ++i)
    {
        // Write positon to map
        fontMap[first + i] = font + index;

        // Read font information
        // Byte 2 contains the length
        index += font[++index] + 1;
    }
}

void configurePixelWriter(void (*func)(int, int, int))
{
    pixelMethod = func;
}

void setBackground(int colour)
{
    backgroundCol = colour;
}

void setForeground(int colour)
{
    foregroundCol = colour;
}

void setFont(Font _font)
{
    font = _font;
}
// Pseudo antialiasing
void enableAA(bool enable)
{
    AAenabled = enable;
}

unsigned int drawCharacter(const char c, int x, int y)
{
    // Get the bitmap of the character
    Font charData = fontMap[c];

    int fontWidth = charData[0];
    int bitmapSize = charData[1];

    Font bitmap = charData + 2;

    // First bit of bitmap size determines whether foreground or background is being written
    bool writingBackground = ((fontWidth >> 7) != 1);
    if(!writingBackground) fontWidth -= 0b10000000;

    // Unpack the bitmap
    const int mapSize = bitmapSize << 1;
    unsigned char *map = new unsigned char[mapSize];

    for (int i = 0; i < bitmapSize; ++i)
    {
        map[(i << 1) + 1] = ((bitmap[i] & 0xF0) >> 4);
        map[i << 1] = bitmap[i] & 0x0F;
    }

    // map[bitmapSize<<1] = 0;
    // unsigned char map[] = {0x0F,0x08,0x03,0x0D,0x04,0x0D,0x02,0x01,0x02,0x0C,0x02,0x01,0x02,0x0B,0x02,0x02,0x02,0x0B,0x02,0x03,0x02,0x09,0x03,0x03,0x02,0x09,0x02,0x04,0x02,0x09,0x02,0x05,0x02,0x07,0x03,0x05,0x02,0x07,0x0B,0x06,0x0B,0x05,0x03,0x07,0x02,0x05,0x02,0x08,0x03,0x04,0x02,0x09,0x02,0x03,0x02,0x0A,0x02,0x03,0x02,0x0A,0x03,0x01};

    int ind = 0;
    for (int j = 0; j < mapSize; ++j)
    {
        int t = ind + map[j];
        int col = writingBackground ? backgroundCol : foregroundCol;
        for (; ind < t; ++ind)
            pixelMethod(x + (ind % fontWidth), y + (ind / fontWidth), col);
        // n.pixels[ind] = currentCol;

        if (map[j] != 0xF)
            writingBackground = !writingBackground;
    }
    delete map;

    return fontWidth;
}

void drawText(const char *text, int x, int y)
{
    loadFont();
    unsigned int ind = 0;
    while (text[ind] != '\0')
        x += drawCharacter(text[ind++], x, y);
}
