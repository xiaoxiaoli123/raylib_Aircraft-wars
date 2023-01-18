#pragma once

class Enemy
{
public:
    float x;
    float y;
    bool live;
    int width;
    int height;
    int hp;
    int type;//types of enemy (big/ small)
};