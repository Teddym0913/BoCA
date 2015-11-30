/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <cmath>

#include "physics/Math.hh"
#include "Debug.hh"

namespace boca
{

int LargeNumber()
{
    return 999999999;
}

float FloorToDigits(float value, int digits)
{
    if (value == 0 || value != value) {
        return 0;
    } else {
        float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
        return std::floor(value * factor) / factor;
    }
}

float CeilToDigits(float value, int digits)
{
    if (value == 0 || value != value) {
        return 0;
    } else {
        float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
        return std::ceil(value * factor) / factor;
    }
}

float RoundError(float value)
{
    return RoundToDigits(value, 2);
}


float RoundToDigits(float value, int digits)
{
    Info0;
    if (value == 0 || value != value) return 0;
    float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
    return std::round(value * factor) / factor;

}

float RoundToError(float value, float error)
{
    Info0;
    if (value == 0 || value != value) return 0;
    float factor = std::pow(10.0, 2 - std::ceil(std::log10(std::abs(error))));
    return std::round(value * factor) / factor;
}


}
