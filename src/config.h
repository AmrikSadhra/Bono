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

    // Explicitly disable copy constructor and assignment operator
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    uint32_t windowWidth = DEFAULT_X_RESOLUTION;
    uint32_t windowHeight = DEFAULT_Y_RESOLUTION;

private:
    Config() = default;
};
