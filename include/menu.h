#ifndef MENU_H
#define MENU_H
#include <iostream>

class Menu
{
private:
    /* data */
    static void drawRectangle(float x, float y, float z, float width, float height);
    static void drawString(float x, float y, float z, const char *string);

public:
    Menu(/* args */);
    static void drawMenu(int selected);
    ~Menu();
};

#endif
