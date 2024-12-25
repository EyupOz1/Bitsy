#include "Core/Math/Vector2Int.hpp"
#include "raylib.h"
#include <cmath>

// Vector2Int Class implementation down below
Vector2Int Vector2IntAdd(Vector2Int vec1, Vector2Int vec2)
{
    return {vec1.x + vec2.x, vec1.y + vec2.y};
}
Vector2Int Vector2IntSubstract(Vector2Int vec1, Vector2Int vec2)
{
    return {vec1.x - vec2.x, vec1.y - vec2.y};
}
Vector2Int Vector2IntMultiply(Vector2Int vec1, Vector2Int vec2)
{
    return {vec1.x * vec2.x, vec1.y * vec2.y};
}
Vector2Int Vector2IntScale(Vector2Int vec, int scale)
{
    return {vec.x * scale, vec.y * scale};
}
unsigned char Vector2IntCompare(Vector2Int a, Vector2Int b)
{
    return (a.x == b.x && a.y == b.y);
}
float Vector2IntDistance(Vector2Int v1, Vector2Int v2)
{
    float result = 0.0f;

    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    result = sqrtf(dx * dx + dy * dy);

    return result;
}
float Vector2IntDistanceSqr(Vector2Int v1, Vector2Int v2)
{
    float result = 0.0f;

    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    result = dx * dx + dy * dy;

    return result;
}
int Vector2IntSumOfXYZ(Vector2Int vec)
{
    return vec.x + vec.y;
}
Vector2 Vector2IntToVector2(Vector2Int vec)
{
    return Vector2{
        static_cast<float>(vec.x),
        static_cast<float>(vec.y)};
}

// Vector2
unsigned char Vector2Compare(Vector2 a, Vector2 b)
{
    return (a.x == b.x && a.y == b.y);
}
Vector2Int Vector2ToVector2Int(Vector2 vec)
{
    return Vector2Int{
        static_cast<int>(vec.x),
        static_cast<int>(vec.y)};
}

// Vector2Int Class
Vector2Int Vector2Int::add(const Vector2Int &vec)
{
    return Vector2IntAdd({x, y}, vec);
}
Vector2Int Vector2Int::substract(const Vector2Int &vec)
{
    return Vector2IntSubstract({x, y}, vec);
}
Vector2Int Vector2Int::multiply(const Vector2Int &vec)
{
    return Vector2IntMultiply({x, y}, vec);
}
Vector2Int Vector2Int::scale(int scale)
{
    return Vector2IntScale({x, y}, scale);
}
bool Vector2Int::compare(const Vector2Int &vec)
{
    return Vector2IntCompare({x, y}, vec);
}

float Vector2Int::distance(const Vector2Int &vec)
{
    return Vector2IntDistance({x, y}, vec);
}
float Vector2Int::distanceSqr(const Vector2Int &vec)
{
    return Vector2IntDistanceSqr({x, y}, vec);
}
int Vector2Int::sumOfXYZ()
{
    return Vector2IntSumOfXYZ({x, y});
}
Vector2 Vector2Int::toVector2()
{
    return Vector2IntToVector2({x, y});
}

bool Vector2Int::operator==(const Vector2Int &other) const
{
    return x == other.x && y == other.y;
}
