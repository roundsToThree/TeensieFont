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
5pt  [388 Bytes]\
\
Example at 24pt font without antialiasing [Simulator screenshot]\
![24pt Inter w/ no antialias](hello_world_noAA.png?raw=true "24pt font without antialiasing") \
<sup>(24pt is roughly 17x18px)</sup>

# Limitations
- Above around 60pt font, the bit packing algorithm isn't as efficient (due to a fixed "segment" size of 4 bits per colour change)
- The library is not designed to be super fast, I just wanted support for more fonts in less memory
