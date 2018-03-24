
#ifndef __PUZZLE_STRUCTS__
#define __PUZZLE_STRUCTS__

namespace game
{
  struct point
  {
    unsigned long x;
    unsigned long y;

    bool operator<(const point& other) const noexcept
    {
      if(this->x == other.x)
      { return this->y < other.y;}
      return this->x < other.y;
    }
  };

  struct countdown
  {
    typedef unsigned int clock_type;
    clock_type hh;
    clock_type mm;
    clock_type ss;
  };
}

#endif // ! __PUZZLE_STRUCTS__
