#pragma once
#include <cmath>

namespace Math
{
    double DistanceToMeters(float distance)
    {
        const float INCHES_TO_METER_RATE = 39.3701;
        return distance / INCHES_TO_METER_RATE;
    }
    double CalculateDistance(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        float dx = (x1 - x2);
        float dy = (y1 - y2);
        float dz = (z1 - z2);
        float distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2) + std::pow(dz, 2));
        return distance;
    }

    double CalculateDistanceInMeters(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        return DistanceToMeters(CalculateDistance(x1, y1, z1, x2, y2, z2));
    }

    double CalculateDistance2D(float x1, float y1, float x2, float y2)
    {
        float dx = (x1 - x2);
        float dy = (y1 - y2);
        float distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
        return distance;
    }
}
