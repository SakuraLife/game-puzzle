
#ifndef __PUZZLE_MAIN_PROCESS__
#define __PUZZLE_MAIN_PROCESS__

#include"constant.hpp"
#include"matrix.hpp"
#include"structs.hpp"
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
  struct point_mutex
  {
    public:
      point __now;
      std::mutex __mutex;

    public:
      point_mutex() noexcept = default;
      point_mutex(const point& __po) noexcept:
        __now{__po}
      { }
  };

  void init_record() noexcept;

  void draw_play_matrix(
    mutex_puzz& __map, point_mutex& __now, countdown_mutex& __timer
  );

  void _game_playing(
    countdown_mutex* __timer, mutex_puzz* __map,
    const std::map<point, point>* __mapping,
    point_mutex* __now
  );
  void _time_opreator(
    countdown_mutex* __timer, mutex_puzz* __map,
    point_mutex* __now
  );
}

#endif // ! __PUZZLE_MAIN_PROCESS__

