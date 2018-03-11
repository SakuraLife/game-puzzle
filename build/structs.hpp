
#ifndef __PUZZLE_STRUCTS__
#define __PUZZLE_STRUCTS__

namespace game
{
  struct point
  {
    unsigned long x;
    unsigned long y;
  };

  bool operator<(const point& __x, const point& __y) noexcept
  {
    if(__x.x == __y.x)
    { return __x.y < __y.y;}
    return __x.x < __y.x;
  }

  struct countdown
  {
    typedef unsigned int clock_type;
    clock_type hh;
    clock_type mm;
    clock_type ss;
  };
}

#endif // ! __PUZZLE_STRUCTS__
