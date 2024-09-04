# TeensieFont
A tiny font library intended for use on Arduino and other similar platforms

# Capabilities
- A memory footprint of roughly 200-300 bytes if the font is loaded in flash
- Pseudo font antialiasing without changing the font  [Soon]
- No specific display requirements
- Font transparency and colour can be implemented by the user with a custom driver
- Online script to create your own font from a ttf file [Soon]
  
# Examples
### Inter font (105 characters)
24pt [2776 Bytes]\
10pt [1226 Bytes] {Needs slight optimisations}\
5pt  [388 Bytes] {Really too small to read!}\
\
Example at 24pt font without antialiasing [Simulator screenshot]\
![24pt Inter w/ no antialias](img/hello_world_noAA.png?raw=true "24pt font without antialiasing") \
<sup>(24pt is roughly 17x18px)</sup>

# Note
The "libray" isn't a library yet but it shouldn't be too difficult to use it in your own project. Its part of a larger project to make a full graphics library similar to LVGL.\
Likewise it isn't a full Arduino project yet, since i'm testing it on my laptop, I have written it to be C++ compliant and am running my code alongside a Java simulator that emulates the parallel LCD im using. Use attributes like PROGMEM on font definitions for utilising SPI Flash.\
The above "issues" will be fixed when I finish most of my library and migrate over to hardware as in this arrangement im able to develop faster.

# Limitations
- Above around 60pt font, the bit packing algorithm isn't as efficient (due to a fixed "segment" size of 4 bits per colour change)
- The library is not designed to be super fast, I just wanted support for more fonts in less memory
- Fonts files are black and white (no grayscale), colour is implemented by "chromakey"
- No current way [But really simple to do] to free up memory after loading a font
- Missing optimisations regarding font loading and unpacking

# Usage

Import headers
```c++
#include "teeniefont.h"
#include "fonts.h"
```

Configure the font
```c++
setFont(FONT_INTER_24);
setBackground(WHITE);
setForeground(BLACK);
enableAA(false);
configurePixelWriter(myPixelWriter);
```

Implement the simple driver method that takes an XY Co-ordinate and a colour and puts it on the screen.
```c++
void myPixelWriter(int x, int y, int col) {
    writePixel(x,y,col);
}
```

Utilise the draw text function
```c++
drawText("Hello World!",0,0);
```

> # Note:
> Colour is a 32 bit unsigned integer. Its 3 colour channels (8bit) with an 8bit alpha channel. If you don't have a framebuffer or a way of reading the current colour of a pixel at a co-ordinate to properly implement transparency, the alpha (transparancy) channel should be treated as a 0-255 percentage of foreground to background colour to lerp.\
Colour is encoded as: 0xAARRGGBB\
Black is 0xFF000000, White is 0xFFFFFFFF (You can #DEFINE these)

