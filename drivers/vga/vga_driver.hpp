#pragma once

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
#define CURSOR_HIGH_BYTE_OFFSET 14
#define CURSOR_LOW_BYTE_OFFSET 15

enum class Color : unsigned char{
    Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, Pink, Yellow, White
};

class ScreenChar
{
private:
    unsigned char m_AsciiCode;
    Color m_BackgroundColor;
    Color m_ForegroundColor;
public:
    ScreenChar(unsigned char asciiCode, const Color& backgroundColor, const Color& foregroundColor);
    unsigned char getAsciiCode() const;
    Color getBackgroundColor() const;
    Color getForegroundColor() const;
    unsigned short getCellData() const;
};

void clearScreen();
void scrollScreen(unsigned char lines);
void printChar(const ScreenChar& screenChar, char row, char col);
void printString(const ScreenChar*& screenChars, char row, char col);
void printk(const char* str);