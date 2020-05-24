#pragma once

#include <cstdint>

/* ------------- BonoConnect Compile time parameters here ---------------*/
const uint32_t DEFAULT_X_RESOLUTION   = 640;
const uint32_t DEFAULT_Y_RESOLUTION   = 480;

/* --------------- BonoConnect Runtime parameters here -----------------*/
class Config
{
public:
    static Config& get()
    {
        static Config instance;
        return instance;
    }
    uint32_t windowWidth = DEFAULT_X_RESOLUTION;
    uint32_t windowHeight = DEFAULT_Y_RESOLUTION;

private:
    Config() = default;
    Config(const Config&);
    Config& operator=(const Config&);
};
