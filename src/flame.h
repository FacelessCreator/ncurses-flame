#pragma once

#include <stdint.h>
#include <string>
#include <iostream>
#include <curses.h>

class Flame {
    private:

    uint16_t width;
    uint16_t height;
    uint8_t ** parts;

    void addParts();
    void movePartsUp();
    void movePartsRandomly();
    void removeParts();

    public:

    Flame(uint16_t width, uint16_t height);
    ~Flame();

    void tick();

    void draw();

};
