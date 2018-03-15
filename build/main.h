
#ifndef __PUZZLE_MAIN_PROCESS__
#define __PUZZLE_MAIN_PROCESS__

#include"constant.hpp"
#include"matrix.hpp"
#include"structs.hpp"
#include"keyboard.h"
#include<map>
#include<mutex>

namespace game
{
  struct mutex_puzz
  {
    matrix<base_type>   __data;
    std::mutex          __mutex;

    mutex_puzz() noexcept = default;
    mutex_puzz(const matrix<base_type>& __tdata):
      __data{__tdata}, __mutex{}
    { }
  };
  struct countdown_mutex
  {
    public:
      typedef countdown clock_type;

    public:
      clock_type __time;
      std::mutex __mutex;

    public:
      countdown_mutex() noexcept = default;
      countdown_mutex(const clock_type& __t) noexcept:
        __time{__t}
      { }
  };
  struct game_postion
  {
    public:
      unsigned long x;
      unsigned long y;
      unsigned long __up;
      unsigned long __down;
      unsigned long __left;
      unsigned long __right;

  };

  struct point_mutex
  {
    public:
      game_postion __pos;
      std::mutex __mutex;
    public:
      point_mutex() noexcept = default;
      point_mutex(const point& __po) noexcept:
        __pos{__po.x, __po.y, 0, 0, 0, 0}, __mutex{}
      { }
  };

  void init_record() noexcept;
  void init_position(
    const matrix<base_type>& __map,
    point_mutex& __now
  ) noexcept;

  void draw_play_matrix(
    mutex_puzz& __map, point_mutex& __now, countdown_mutex& __timer
  );

  bool move_one_step(
    const matrix<base_type>& __map, game_postion& __pos,
    const bool __row, const bool __col,
    const std::map<point, point>& __mapping,
    keyboard::keyboard_mapping __act
  ) noexcept;

  void _game_playing(
    countdown_mutex* __timer, mutex_puzz* __map,
    const std::map<point, point>* __mapping,
    point_mutex* __now,
    const bool __row, const bool __col
  );
  void _time_opreator(
    countdown_mutex* __timer, mutex_puzz* __map,
    point_mutex* __now
  );

}

#endif // ! __PUZZLE_MAIN_PROCESS__

