#include"main.h"
#include"utility.h"
#include"keyboard.h"
#include"check.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>

namespace game
{

  struct __game_res
  {
    bool __time;
    bool __tasks;
    std::mutex __mutex;
  };
  static __game_res time_record;

  void init_record() noexcept
  { time_record.__tasks = time_record.__time = false;}

  static bool check_record()
  {
    std::lock_guard<std::mutex> __guard(time_record.__mutex);
    bool __res = time_record.__tasks || time_record.__time;
    return __res;
  }

  static void time_out()
  {
    std::lock_guard<std::mutex> __guard(time_record.__mutex);
    time_record.__time = true;
  }

  static void test_out()
  {
    std::lock_guard<std::mutex> __guard(time_record.__mutex);
    time_record.__tasks = true;
  }
}


namespace game
{
  static void _forward(countdown_mutex& __timer)
  {
    using std::time_t;
    using std::time;
    time_t __use = time(nullptr);

    for(; __use == time(nullptr);)
    {
      if(check_record())
      { return;}
    }

    return;
  }

  static void _decrease_time(countdown_mutex& __timer)
  {
    std::lock_guard<std::mutex> __guard(__timer.__mutex);
    if(!(__timer.__time.hh || __timer.__time.mm || __timer.__time.ss))
    { return;}
    if(__timer.__time.ss == 0)
    {
      if(__timer.__time.mm == 0)
      {
        --__timer.__time.hh;
        __timer.__time.mm = 59U;
      }
      else
      { --__timer.__time.mm;}
      __timer.__time.ss = 59U;
    }
    else
    { --__timer.__time.ss;}
  }

}

namespace game
{
  static void draw_play_matrix(
    mutex_puzz& __map, point_mutex& __now
  )
  {
    using std::printf;
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    std::lock_guard<std::mutex> __now_guard(__now.__mutex);

    reflush_screen();
    char __tmp = __map.__data.at(__now.__now.x, __now.__now.y);
    __map.__data.at(__now.__now.x, __now.__now.y) = puzz_now;
    draw_matrix(__map.__data);
    __map.__data.at(__now.__now.x, __now.__now.y) = __tmp;
  }

  void draw_play_matrix(
    mutex_puzz& __map, point_mutex& __now, countdown_mutex& __timer
  )
  {
    using std::printf;
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    std::lock_guard<std::mutex> __now_guard(__now.__mutex);
    std::lock_guard<std::mutex> __time_guard(__timer.__mutex);

    reflush_screen();
    char __tmp = __map.__data.at(__now.__now.x, __now.__now.y);
    __map.__data.at(__now.__now.x, __now.__now.y) = puzz_now;
    draw_matrix(__map.__data);
    __map.__data.at(__now.__now.x, __now.__now.y) = __tmp;

    printf("Please go on\n\n");

    draw_time(__timer.__time);

  }
}

namespace game
{
  static bool move_one_step(
    mutex_puzz& __map, point_mutex& __now,
    const std::map<point, point>& __mapping,
    long __dr, long __dc
  )
  {
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    std::lock_guard<std::mutex> __now_guard(__now.__mutex);
    const unsigned long __tx = static_cast<unsigned long>(__now.__now.x+__dr);
    const unsigned long __ty = static_cast<unsigned long>(__now.__now.y+__dc);
    if(check_not_out(__tx, __ty, __map.__data) &&
       check_is_passage(__map.__data.at(__tx, __ty)))
    {
      if(check_is_transport(__map.__data.at(__tx, __ty)))
      { __now.__now = __mapping.find(point{__tx, __ty})->second;}
      else
      {
        __now.__now.x = __tx;
        __now.__now.y = __ty;
      }
      return true;
    }
    return false;
  }

  static bool check_is_at_dest(
    mutex_puzz& __map, point_mutex& __now
  )
  {
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    std::lock_guard<std::mutex> __now_guard(__now.__mutex);

    return __map.__data.at(__now.__now.x, __now.__now.y) == puzz_dest;
  }

  void _time_opreator(
    countdown_mutex* __timer, mutex_puzz* __map,
    point_mutex* __now
  )
  {
    using std::exit;
    using std::printf;

    for(; __timer->__time.hh || __timer->__time.mm || __timer->__time.ss;)
    {
      if(check_record())
      { return;}
      _forward(*__timer);
      if(check_record())
      { return;}
      _decrease_time(*__timer);
      if(check_record())
      { return;}
      draw_play_matrix(*__map, *__now, *__timer);
      if(check_record())
      { return;}
    }
    if(check_record())
    { return;}
    time_out();
    draw_play_matrix(*__map, *__now);
    printf("Time out\n");
    exit(EXIT_SUCCESS);
  }

  void _game_playing(
    countdown_mutex* __timer, mutex_puzz* __map,
    const std::map<point, point>* __mapping,
    point_mutex* __now
  )
  {
    keyboard::keyboard_mapping __dir;
    while(true)
    {
      if(check_record())
      { return;}
      __dir = keyboard::keyboard_one_step();
      if(check_record())
      { return;}
      switch(__dir)
      {
        case keyboard::keyboard_mapping::right_arrow:
        case keyboard::keyboard_mapping::char_d:
        case keyboard::keyboard_mapping::char_D:
          move_one_step(*__map, *__now, *__mapping, x_dic[0], y_dic[0]);
          break;
        case keyboard::keyboard_mapping::up_arrow:
        case keyboard::keyboard_mapping::char_w:
        case keyboard::keyboard_mapping::char_W:
          move_one_step(*__map, *__now, *__mapping, x_dic[1], y_dic[1]);
          break;
        case keyboard::keyboard_mapping::left_arrow:
        case keyboard::keyboard_mapping::char_a:
        case keyboard::keyboard_mapping::char_A:
          move_one_step(*__map, *__now, *__mapping, x_dic[2], y_dic[2]);
          break;
        case keyboard::keyboard_mapping::down_arrow:
        case keyboard::keyboard_mapping::char_s:
        case keyboard::keyboard_mapping::char_S:
          move_one_step(*__map, *__now, *__mapping, x_dic[3], y_dic[3]);
          break;
        default:
          ;
      }
      if(check_record())
      { return;}
      if(check_is_at_dest(*__map, *__now))
      {
        test_out();
        draw_play_matrix(*__map, *__now);
        printf("You finished the game.\n\n");
        return;
      }
      draw_play_matrix(*__map, *__now, *__timer);
      if(check_record())
      { return;}
    }
  }

}
