#ifndef TEENIEFONT_H
#define TEENIEFONT_H
const unsigned char typedef *Font;

// provide method to write pixel (x, y, 32bit colour (alpha channel MSB 8bit))
void configurePixelWriter(void (*func)(int, int, int));

void setBackground(int colour);
void setForeground(int colour);
void setFont(Font font);
// Pseudo antialiasing
void enableAA(bool enable);

void drawText(const char* text, int x, int y);

#endif