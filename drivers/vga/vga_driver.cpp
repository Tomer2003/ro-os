#include "vga_driver.hpp"
#include "../port_io/port_io.hpp"
#include "../../libc/include/strings.h"

#define BYTES_FOR_CHARACTER 2
ScreenChar::ScreenChar(unsigned char asciiCode, const Color& backgroundColor, const Color& foregroundColor) : m_AsciiCode(asciiCode), m_BackgroundColor(backgroundColor), m_ForegroundColor(foregroundColor){}

unsigned char ScreenChar::getAsciiCode() const
{
    return m_AsciiCode;
}

Color ScreenChar::getBackgroundColor() const
{
    return m_BackgroundColor;
}

Color ScreenChar::getForegroundColor() const
{
    return m_ForegroundColor;
}

unsigned short ScreenChar::getCellData() const
{
    unsigned short data;
    
    *((unsigned char*)&data) = m_AsciiCode;
    *((unsigned char*)&data + 1) = ((unsigned char)m_BackgroundColor << 4) + (unsigned char)m_ForegroundColor;

    return data;
}

static unsigned short getScreenOffset(unsigned char row, unsigned char col)
{
    return BYTES_FOR_CHARACTER * (row * MAX_COLS + col);
} 

static unsigned short getCursorOffset()
{
    unsigned short cursorOffset = 0;
    portWriteByte(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE_OFFSET);
    cursorOffset += portReadByte(REG_SCREEN_DATA) << 8;
    portWriteByte(REG_SCREEN_CTRL, CURSOR_LOW_BYTE_OFFSET);
    cursorOffset += portReadByte(REG_SCREEN_DATA);

    return cursorOffset * 2;
}

static void setCursorOffset(unsigned short offset)
{
    offset /= 2;
    portWriteByte(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE_OFFSET);
    portWriteByte(REG_SCREEN_DATA, *((unsigned char*)&offset + 1));
    portWriteByte(REG_SCREEN_CTRL, CURSOR_LOW_BYTE_OFFSET);
    portWriteByte(REG_SCREEN_DATA, *((unsigned char*)&offset));
}


static void printCharAt(const ScreenChar& screenChar, char row, char col)
{
    unsigned char* videoMemoryPtr = (unsigned char*)VIDEO_ADDRESS;
    unsigned short offset = getScreenOffset(row, col); 

    if(screenChar.getAsciiCode() == '\n')
    {
        setCursorOffset(getScreenOffset(row + 1, 0));
    }
    else
    {
        *((unsigned short*)(videoMemoryPtr + offset)) = screenChar.getCellData();
    }
}

void printChar(const ScreenChar& screenChar, char row, char col)
{
    unsigned char* videoMemoryPtr = (unsigned char*)VIDEO_ADDRESS;
    unsigned short offset;

    if(row >= 0 && col >= 0)
    {
        offset = getScreenOffset(row, col);    
    }
    else
    {
        offset = getCursorOffset();
    }

    if(screenChar.getAsciiCode() == '\n')
    {
        offset = getScreenOffset(offset / (2 * MAX_COLS), MAX_COLS - 1);
    }
    else
    {
        *((unsigned short*)(videoMemoryPtr + offset)) = screenChar.getCellData();
    }

    offset += 2;
    if(offset > getScreenOffset(MAX_ROWS - 1, MAX_COLS - 1))
    {
        scrollScreen(1);
    }
    else
    {
        setCursorOffset(offset);
    }
}

void clearScreen()
{
    for(char row = 0; row < MAX_ROWS; ++row)
    {
        for(char col = 0; col < MAX_COLS; ++col)
        {
            printChar(ScreenChar(' ', Color::Black, Color::White), row, col);
        }
    }
    setCursorOffset(getScreenOffset(0, 0));
}

void printString(const ScreenChar*& screenChars, char row, char col)
{
    while((*screenChars).getAsciiCode())
    {
        printChar(*screenChars, row, col);
        if(col >= 0 && row >= 0)
        {
            col++;
            if(col == MAX_COLS - 1)
            {
                row++;
                col = 0;
            }
        }
    }
}

void scrollScreen(unsigned char lines)
{
    if(lines <= MAX_ROWS)
    {
        memcpy((void*)(getScreenOffset(0, 0) + VIDEO_ADDRESS), (void*)(getScreenOffset(lines, 0) + VIDEO_ADDRESS), MAX_COLS * 2 * (MAX_ROWS - lines));

        for(unsigned char row = MAX_ROWS - lines; row < MAX_ROWS; ++row)
        {
            for(unsigned char col = 0; col < MAX_COLS; ++col)
            {
                printCharAt(ScreenChar(' ', Color::Black, Color::White), row, col);
            }
        }

        setCursorOffset(getScreenOffset(MAX_ROWS - lines, 0));
    }
}

void printk(const char* str)
{
   while(*str)
    {
        printChar(ScreenChar(*str, Color::Black, Color::White), -1, -1);
        str++;
    }
}