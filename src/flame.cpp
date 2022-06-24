#include "flame.h"

Flame::Flame(uint16_t width, uint16_t height) {
    this->width = width;
    this->height = height;
    parts = new uint8_t * [width];
    for (uint16_t i = 0; i < width; ++i) {
        parts[i] = new uint8_t [height];
    }
}

Flame::~Flame() {
    for (uint16_t i = 0; i < width; ++i) {
        delete parts[i];
    }
    delete parts;
}

void Flame::tick() {
    movePartsUp();
    movePartsRandomly();
    addParts();
    removeParts();
}

void Flame::draw() {
    move(0, 0);
    for (uint16_t y = 0; y < height; ++y) {
        for (uint16_t x = 0; x < width; ++x) {
            uint8_t p = parts[x][y];
            if (p >= 128) {
                attron(COLOR_PAIR(1));
                addwstr(L"█");
                attroff(COLOR_PAIR(1));
            } else if (p >= 64) {
                attron(COLOR_PAIR(2));
                addwstr(L"▓");
                attroff(COLOR_PAIR(2));
            } else if (p >= 32) {
                attron(COLOR_PAIR(3));
                addwstr(L"▒");
                attroff(COLOR_PAIR(3));
            } else if (p >= 16) {
                attron(COLOR_PAIR(3));
                addwstr(L"░");
                attroff(COLOR_PAIR(3));
            } else if (p >= 8) {
                attron(COLOR_PAIR(3));
                addwstr(L"*");
                attroff(COLOR_PAIR(3));
            } else if (p > 0) {
                attron(COLOR_PAIR(3));
                addwstr(L".");
                attroff(COLOR_PAIR(3));
            } else {
                addwstr(L" ");
            }
        }
    }
}

void Flame::addParts() {
    for (uint16_t i = 0; i < width; ++i) {
        parts[i][height-1] = rand() % UINT8_MAX;
    }
}

void Flame::movePartsUp() {
    for (uint16_t x = 0; x < width; ++x) {
        for (uint16_t y = 1; y < height; ++y) {
            uint8_t partsToMove = parts[x][y] / 2;
            parts[x][y] -= partsToMove;
            parts[x][y-1] += partsToMove;
        }
    }
}

void Flame::movePartsRandomly() {
    for (uint16_t x = 0; x < width; ++x) {
        for (uint16_t y = 0; y < height; ++y) {
            uint8_t part = parts[x][y];
            if (part > 2) {
                uint8_t moveLeft = rand() % (part / 2);
                uint8_t moveRight = rand() % (part / 2);
                if (x > 0) {
                    parts[x-1][y] += moveLeft;
                }
                if (x < width-1) {
                    parts[x+1][y] += moveRight;
                }
                parts[x][y] -= moveLeft + moveRight;
            }
        }
    }
}

void Flame::removeParts() {
    uint8_t removeSize = (UINT8_MAX / height) / 2;
    for (uint16_t x = 0; x < width; ++x) {
        for (uint16_t y = 0; y < height; ++y) {
            if (parts[x][y] <= removeSize) {
                parts[x][y] = 0;
            } else {
                parts[x][y] -= removeSize;
            }
        }
    }
}
