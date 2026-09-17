#pragma once

#include <cmath>
#include <limits>

namespace active_safety{

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef signed int sint32;
typedef unsigned int uint32;
typedef signed long long sint64;
typedef unsigned long long uint64;
typedef float float32;
typedef double float64;

#define m_eps std::numeric_limits<float>::epsilon()
#define m_inf std::numeric_limits<float>::infinity()

#define m_pi 3.1415927
#define deg_2_rad 0.0175
#define rad_2_deg 57.3
#define EQUALS_TOLERANCE 0.000001f
}