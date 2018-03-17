#ifndef FUTURAMA_FUT_INFRA_POINT_H_INCLUDED
#define FUTURAMA_FUT_INFRA_POINT_H_INCLUDED

namespace fut::infra
{
struct Point
{
    int x = 0;
    int y = 0;
}; // struct Point
} // namespace fut::infra

inline bool operator==(const fut::infra::Point& left, const fut::infra::Point& right)
{
    return left.x == right.x && left.y == right.y;
}

inline bool operator!=(const fut::infra::Point& left, const fut::infra::Point& right)
{
    return left.x != right.x || left.y != right.y;
}

#endif // #ifndef FUTURAMA_FUT_INFRA_POINT_H_INCLUDED
