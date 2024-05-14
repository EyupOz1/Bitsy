#pragma once


typedef struct Config
{
    unsigned char mouseActive;
    float flyingSpeed;
    float mouseSensitivity;
    float fieldOfView;
} Config;

extern Config GLOBAL;