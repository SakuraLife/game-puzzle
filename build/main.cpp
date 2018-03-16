#include"main.h"
#include"utility.h"
#include"check.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>

namespace game
{
  constexpr static unsigned long __reserve_len = 24UL;
}

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
  void init_position(
    const matrix<base_type>& __map, game_postion& __pos
  ) noexcept
  {
    if(__map.col() > __reserve_len)
    {
      if(static_cast<long long>(__pos.x - __reserve_len/2) >= 0)
      {
        if(__pos.x - __reserve_len/2 + __reserve_len > __map.row())
        {
          __pos.__down = __map.row();
          __pos.__up = __pos.__down - __reserve_len;
        }
        else
        {
          __pos.__up = __pos.x - __reserve_len/2;
          __pos.__down = __pos.__up + __reserve_len;
        }
      }
      else
      {
        __pos.__up = 0;
        __pos.__down = __reserve_len;
      }
    }
    else
    {
      __pos.__up = 0;
      __pos.__down = __map.row();
    }

    if(__map.col() > __reserve_len)
    {
      if(static_cast<long long>(__pos.y - __reserve_len/2)>= 0)
      {
        if(__pos.y - __reserve_len/2 + __reserve_len > __map.col())
        {
          __pos.__right = __map.col();
          __pos.__left = __pos.__right - __reserve_len;
        }
        else
        {
          __pos.__left = __pos.y - __reserve_len/2;
          __pos.__right = __pos.__left + __reserve_len;
        }
      }
      else
      {
        __pos.__left = 0;
        __pos.__right = __reserve_len;
      }
    }
    else
    {
      __pos.__left = 0;
      __pos.__right = __map.col();
    }

    return;
  }

  static void readapt_postion(
    const matrix<base_type>& __map, game_postion& __pos,
    const bool __row, const bool __col
  ) noexcept
  {
    if(__row && __pos.__down-__pos.__up == __reserve_len)
    {
      if(__pos.x-__pos.__up == 1UL && __pos.__up != 0)
      { --__pos.__up; --__pos.__down;}
      if(__pos.__down-__pos.x == 2UL && __pos.__down != __map.row())
      { ++__pos.__up; ++__pos.__down;}
    }
    if(__col && __pos.__right-__pos.__left == __reserve_len)
    {
      if(__pos.y-__pos.__left == 1UL && __pos.__left != 0)
      { --__pos.__left; --__pos.__right;}
      if(__pos.__right-__pos.y == 2UL && __pos.__right != __map.row())
      { ++__pos.__left; ++__pos.__right;}
    }
    return;
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
    char __tmp = __map.__data.at(__now.__pos.x, __now.__pos.y);
    __map.__data.at(__now.__pos.x, __now.__pos.y) = puzz_now;
    draw_matrix(
      __map.__data,
      __now.__pos.__up, __now.__pos.__down,
      __now.__pos.__left, __now.__pos.__right
    );
    __map.__data.at(__now.__pos.x, __now.__pos.y) = __tmp;
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
    char __tmp = __map.__data.at(__now.__pos.x, __now.__pos.y);
    __map.__data.at(__now.__pos.x, __now.__pos.y) = puzz_now;
    draw_matrix(
      __map.__data,
      __now.__pos.__up, __now.__pos.__down,
      __now.__pos.__left, __now.__pos.__right
    );
    __map.__data.at(__now.__pos.x, __now.__pos.y) = __tmp;

    printf("Please go on\n\n");

    draw_time(__timer.__time);

#ifndef NDEBUG

    printf("\nNow position:(%4lu, %4lu)\n", __now.__pos.x, __now.__pos.y);
    printf("\nNow draw position:\n");
    printf("UP:\t%4lu\n", __now.__pos.__up);
    printf("DOWN:\t%4lu\n", __now.__pos.__down);
    printf("LEFT:\t%4lu\n", __now.__pos.__left);
    printf("RIGHT:\t%4lu\n", __now.__pos.__right);

#endif // ! NDEBUG
  }
}

namespace game
{
  static bool do_one_step(
    const matrix<base_type>& __map, game_postion& __pos,
    const bool __row, const bool __col,
    const std::map<point, point>& __mapping,
    long __dr, long __dc
  ) noexcept
  {
    const unsigned long __tx =
      static_cast<unsigned long>(__pos.x+__dr);
    const unsigned long __ty =
      static_cast<unsigned long>(__pos.y+__dc);
    if(check_not_out(__tx, __ty, __map) &&
       check_is_passage(__map.at(__tx, __ty)))
    {
      if(check_is_transport(__map.at(__tx, __ty)))
      {
        // transport do
        point __tmp = __mapping.find(point{__tx, __ty})->second;
        __pos.x = __tmp.x;
        __pos.y = __tmp.y;
        init_position(__map, __pos);
      }
      else
      {
        __pos.x = __tx;
        __pos.y = __ty;
        readapt_postion(__map, __pos, __row, __col);
      }
      return true;
    }
    return false;
  }
  bool move_one_step(
    const matrix<base_type>& __map, game_postion& __pos,
    const bool __row, const bool __col,
    const std::map<point, point>& __mapping,
    keyboard::keyboard_mapping __act
  ) noexcept
  {
    switch(__act)
    {
      case keyboard::keyboard_mapping::right_arrow:
      case keyboard::keyboard_mapping::char_d:
      case keyboard::keyboard_mapping::char_D:
        return do_one_step(__map, __pos, __row, __col, __mapping, x_dic[0], y_dic[0]);
        break;
      case keyboard::keyboard_mapping::up_arrow:
      case keyboard::keyboard_mapping::char_w:
      case keyboard::keyboard_mapping::char_W:
        return do_one_step(__map, __pos, __row, __col, __mapping, x_dic[1], y_dic[1]);
        break;
      case keyboard::keyboard_mapping::left_arrow:
      case keyboard::keyboard_mapping::char_a:
      case keyboard::keyboard_mapping::char_A:
        return do_one_step(__map, __pos, __row, __col, __mapping, x_dic[2], y_dic[2]);
        break;
      case keyboard::keyboard_mapping::down_arrow:
      case keyboard::keyboard_mapping::char_s:
      case keyboard::keyboard_mapping::char_S:
        return do_one_step(__map, __pos, __row, __col, __mapping, x_dic[3], y_dic[3]);
        break;
      default:
        ;
    }
    return false;
  }
  static bool move_one_step(
    mutex_puzz& __map, point_mutex& __now,
    const bool __row, const bool __col,
    const std::map<point, point>& __mapping,
    keyboard::keyboard_mapping __act
  )
  {
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    std::lock_guard<std::mutex> __now_guard(__now.__mutex);

    return move_one_step(
      __map.__data, __now.__pos, __row, __col, __mapping, __act
    );
  }

  static bool check_is_at_dest(
    mutex_puzz& __map, point_mutex& __now
  )
  {
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    std::lock_guard<std::mutex> __now_guard(__now.__mutex);

    return check_is_dest(__map.__data.at(__now.__pos.x, __now.__pos.y));
  }

  void _game_playing(
    countdown_mutex* __timer, mutex_puzz* __map,
    const std::map<point, point>* __mapping,
    point_mutex* __now,
    const bool __row, const bool __col
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
      move_one_step(*__map, *__now, __row, __col, *__mapping, __dir);
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

namespace game
{

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

}

namespace game
{
  static void delay(std::clock_t times) noexcept
  {
    using std::clock_t;
    using std::clock;
    for(clock_t __now = clock(); clock() - __now < times;)
    { }
  }
  void show_puzzle_trace(
    matrix<base_type>& __map, game_postion& __pos,
    const std::map<point, point>& __mapping,
    const vector<keyboard::keyboard_mapping>& __po
  ) noexcept
  {
    using std::time_t;
    using std::time;

    init_position(__map, __pos);

    auto __use = [&__map, &__pos]()->void{
      reflush_screen();
      char __tmp = __map.at(__pos.x, __pos.y);
      __map.at(__pos.x, __pos.y) = puzz_now;
      draw_matrix(
        __map, __pos.__up, __pos.__down, __pos.__left, __pos.__right
      );
      __map.at(__pos.x, __pos.y) = __tmp;

#ifndef NDEBUG
      printf("\nNow position:(%4lu, %4lu)\n", __pos.x, __pos.y);
      printf("\nNow draw position:\n");
      printf("UP:\t%4lu\n", __pos.__up);
      printf("DOWN:\t%4lu\n", __pos.__down);
      printf("LEFT:\t%4lu\n", __pos.__left);
      printf("RIGHT:\t%4lu\n", __pos.__right);
#endif // ! NDEBUG

      delay(CLOCKS_PER_SEC / 10 * 3);
      return;
    };

    __use();
    const bool __row = __pos.__up != 0 || __pos.__down != __map.row();
    const bool __col =  __pos.__left != 0 || __pos.__right != __map.col();
    for(const keyboard::keyboard_mapping& __dir: __po)
    {
      move_one_step(__map, __pos, __row, __col, __mapping, __dir);
      __use();
    }
  }
}
