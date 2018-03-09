
#ifndef __PUZZLE_UTILITY__
#define __PUZZLE_UTILITY__

#include"constant.hpp"
#include"matrix.hpp"
#include<mutex>

namespace game
{
  struct point
  {
    unsigned long x;
    unsigned long y;
  };

  struct mutex_puzz
  {
    matrix<base_type>   __data;
    std::mutex          __mutex;

    mutex_puzz() = default;
    mutex_puzz(const matrix<base_type>& __tdata);
  };
  struct countdown
  {
    public:
      typedef unsigned int clock_type;

    public:
      clock_type __hh, __mm, __ss;
      std::mutex __mutex;

    public:
      countdown() = default;
      countdown(clock_type __h, clock_type __m, clock_type __s) noexcept;
  };


  void init_record() noexcept;
  void draw_time(countdown& __timer);
  void draw_matrix(const matrix<base_type>& __map) noexcept;

  void _game_playing(
    countdown* __timer, mutex_puzz* __map,
    unsigned long __x, unsigned long __y
  );
  void _time_opreator(
    countdown* __timer, mutex_puzz* __map
  );

  void reflush_screen() noexcept;
  bool find_all_path(const matrix<base_type>& __map);
  bool find_all_shortest_path(const matrix<base_type>& __map);

}

#endif // ! __PUZZLE_UTILITY__
