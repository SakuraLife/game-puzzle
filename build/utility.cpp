#include"utility.h"
#include"keyboard.h"
#include"check.h"
#include<queue>
#include<cstdio>
#include<ctime>
#include<cstdlib>

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
  void reflush_screen() noexcept
  {
    using std::system;
    system("clear");
  }
}

namespace game
{
  countdown::countdown(clock_type __h, clock_type __m, clock_type __s) noexcept:
    __hh{__h}, __mm{__m}, __ss{__s}
  { }

  void draw_time(countdown& __timer)
  {
    std::lock_guard<std::mutex> __guard(__timer.__mutex);
    printf(
      "Left Time:%02u:%02u:%02u\n",
      __timer.__hh, __timer.__mm, __timer.__ss
    );
  }

  static void _forward(countdown& __timer)
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

  static void _decrease_time(countdown& __timer)
  {
    std::lock_guard<std::mutex> __guard(__timer.__mutex);
    if(!(__timer.__hh || __timer.__mm || __timer.__ss))
    { return;}
    if(__timer.__ss == 0)
    {
      if(__timer.__mm == 0)
      {
        --__timer.__hh;
        __timer.__mm = 59U;
      }
      else
      { --__timer.__mm;}
      __timer.__ss = 59U;
    }
    else
    { --__timer.__ss;}
  }

}

namespace game
{
  mutex_puzz::mutex_puzz(const matrix<base_type>& __tdata):
    __data{__tdata}, __mutex{}
  { }

  // static bool check_at_dest(
  //   mutex_puzz& __map,
  //   unsigned long __x, unsigned long __y
  // )
  // {
  //   std::lock_guard<std::mutex> __guard(__map.__mutex);
  //   return __map.__data.at(__x, __y) == puzz_dest;
  // }

  static bool move_one_step(
    mutex_puzz& __map,
    unsigned long __nr, unsigned long __nc,
    long __dr, long __dc
  )
  {
    const long __trow = static_cast<long>(__nr+__dr);
    const long __tcol = static_cast<long>(__nc+__dc);
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    if(check_not_out(__trow, __tcol, __map.__data) &&
       check_is_passage(__map.__data.at(__trow, __tcol)))
    {
      __map.__data.at(__trow, __tcol) = puzz_now;
      __map.__data.at(__nr, __nc) = puzz_pass;
      return true;
    }
    return false;
  }


  void draw_matrix(const matrix<base_type>& __map) noexcept
  {
    using std::printf;
    for(unsigned long __i = 0; __i != __map.row(); ++__i)
    {
      for(unsigned long __j = 0; __j != __map.col(); ++__j)
      {
        switch(__map.at(__i, __j))
        {
          case puzz_wall:
            printf(" #");
            break;
          case puzz_now:
            printf(" \e[1;36m@\e[0m");
            break;
          case puzz_start:
            printf(" \e[1;31m0\e[0m");
            break;
          case puzz_dest:
            printf(" \e[1;31m1\e[0m");
            break;
          case puzz_pass:
            printf(" \e[1;30m-\e[0m");
            break;
          case puzz_write:
            printf(" \e[1;33mx\e[0m");
            break;
        }
      }
      printf("\n");
    }
  }

  static void draw_play_matrix(mutex_puzz& __map)
  {
    std::lock_guard<std::mutex> __guard(__map.__mutex);
    reflush_screen();
    draw_matrix(__map.__data);
  }

  static void draw_solve_path(
    const matrix<base_type>& __map, const vector<point>& __rec
  )
  {
    matrix<base_type> __use(__map);
    for(const auto& __tmp : __rec)
    { __use.at(__tmp.x, __tmp.y) = puzz_write;}
    __use.at(__rec.front().x, __rec.front().y) = puzz_start;
    __use.at(__rec.back().x, __rec.back().y) = puzz_dest;
    draw_matrix(__use);
    printf("\n");
  }

  namespace __detail
  {
    static void __find_all(
      const matrix<base_type>& __map, const matrix<long>& __filled,
      vector<point>& __porec,
      unsigned long __r, unsigned long __c
    )
    {
      using std::system;

      if(__map.at(__r, __c) == puzz_dest)
      {
        reflush_screen();
        draw_solve_path(__map, __porec);
        keyboard::read_one_char();
        return;
      }

      for(unsigned long __i = 0; __i != 4; ++__i)
      {
        const unsigned long __trow = static_cast<long>(__r)+x_dic[__i];
        const unsigned long __tcol = static_cast<long>(__c)+y_dic[__i];
        if(check_not_out(__trow, __tcol, __map) )
        {
          __porec.push_back(point{__trow, __tcol});
          __find_all(__map, __filled, __porec, __trow, __tcol);
          __porec.pop_back();
        }
      }
    }


    static void __fill_map(
      const matrix<base_type>& __map, matrix<long>& __filled,
      unsigned long __r, unsigned long __c
    )
    {
      struct __point
      {
        unsigned long __x;
        unsigned long __y;
        long __step;
      };

      std::queue<__point> __queue;
      __filled.at(__r, __c) = 0;
      __queue.push(__point{__r, __c, 0});
      while(!__queue.empty())
      {
        __point __now = __queue.front(); __queue.pop();

        for(unsigned long __i = 0; __i != 4; ++__i)
        {
          const unsigned long __trow = static_cast<long>(__now.__x)+x_dic[__i];
          const unsigned long __tcol = static_cast<long>(__now.__y)+y_dic[__i];
          if(check_not_out(__trow, __tcol, __map) &&
            check_is_passage(__map.at(__trow, __tcol)))
          {
            if((__filled.at(__trow, __tcol) == -1 ||
             __filled.at(__trow, __tcol) > __now.__step+1))
            {
              __queue.push(__point{__trow, __tcol, __now.__step+1});
              __filled.at(__trow, __tcol) = __now.__step+1;
            }
          }
        }

      }
    }

    static void __find_all_shortest(
      const matrix<base_type>& __map,
      const unsigned long __res, const matrix<long>& __filled,
      vector<point>& __porec,
      unsigned long __r, unsigned long __c
    )
    {
      using std::system;

      if(__map.at(__r, __c) == puzz_dest)
      {
        reflush_screen();
        draw_solve_path(__map, __porec);
        keyboard::read_one_char();
        return;
      }
      if(__porec.size() == __res)
      { return;}

      // printf("%lu %lu %ld\n", __r, __c, __filled.at(__r, __c));

      for(unsigned long __i = 0; __i != 4; ++__i)
      {
        const unsigned long __trow = static_cast<long>(__r)+x_dic[__i];
        const unsigned long __tcol = static_cast<long>(__c)+y_dic[__i];

        if(check_not_out(__trow, __tcol, __map) &&
          __filled.at(__r, __c) + 1 == __filled.at(__trow, __tcol)
        )
        {
          __porec.push_back(point{__trow, __tcol});
          __find_all_shortest(__map, __res, __filled, __porec, __trow, __tcol);
          __porec.pop_back();
        }
      }
    }

    static unsigned long __find_min_dest(
      const matrix<base_type>& __map, const matrix<long>& __filled
    )
    {
      unsigned long __res = 0U;
      const base_type* __map_end = __map.data() + __map.size();
      const long* __res_map_start = __filled.data();
      // const long* __res_map_end = __res_map_start + __map.size();
      for(const base_type* __i = __map.data(); __i != __map_end; ++__i, ++__res_map_start)
      {
        if(*__i == puzz_dest && *__res_map_start != -1)
        {
          if(__res == 0U || __res > static_cast<unsigned long>(*__res_map_start))
          { __res = *__res_map_start;}
        }
      }
      return __res;
    }
  }

  void _time_opreator(
    countdown* __timer, mutex_puzz* __map
  )
  {
    using std::exit;

    for(; __timer->__hh || __timer->__mm || __timer->__ss;)
    {
      if(check_record())
      { return;}
      _forward(*__timer);
      if(check_record())
      { return;}
      _decrease_time(*__timer);
      if(check_record())
      { return;}
      draw_play_matrix(*__map);
      if(check_record())
      { return;}
      printf("Please go on\n\n");
      if(check_record())
      { return;}
      draw_time(*__timer);
    }
    if(check_record())
    { return;}
    time_out();
    draw_play_matrix(*__map);
    printf("Time out\n");
    exit(EXIT_SUCCESS);
  }

  void _game_playing(
    countdown* __timer, mutex_puzz* __map,
    unsigned long __x, unsigned long __y
  )
  {
    keyboard::keyboard_mapping __dir;
    base_type __tmp = puzz_write;
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
          {
            std::lock_guard<std::mutex> __guard(__map->__mutex);
            __tmp = __map->__data.at(static_cast<long>(__x) + x_dic[0], static_cast<long>(__y) + y_dic[0]);
          }
          if(move_one_step(*__map, __x, __y, x_dic[0], y_dic[0]))
          {
            __x = static_cast<long>(__x) + x_dic[0];
            __y = static_cast<long>(__y) + y_dic[0];
          }
          break;
        case keyboard::keyboard_mapping::up_arrow:
        case keyboard::keyboard_mapping::char_w:
        case keyboard::keyboard_mapping::char_W:
          {
            std::lock_guard<std::mutex> __guard(__map->__mutex);
            __tmp = __map->__data.at(static_cast<long>(__x) + x_dic[1], static_cast<long>(__y) + y_dic[1]);
          }
          if(move_one_step(*__map, __x, __y, x_dic[1], y_dic[1]))
          {
            __x = static_cast<long>(__x) + x_dic[1];
            __y = static_cast<long>(__y) + y_dic[1];
          }
          break;
        case keyboard::keyboard_mapping::left_arrow:
        case keyboard::keyboard_mapping::char_a:
        case keyboard::keyboard_mapping::char_A:
          {
            std::lock_guard<std::mutex> __guard(__map->__mutex);
            __tmp = __map->__data.at(static_cast<long>(__x) + x_dic[2], static_cast<long>(__y) + y_dic[2]);
          }
          if(move_one_step(*__map, __x, __y, x_dic[2], y_dic[2]))
          {
            __x = static_cast<long>(__x) + x_dic[2];
            __y = static_cast<long>(__y) + y_dic[2];
          }
          break;
        case keyboard::keyboard_mapping::down_arrow:
        case keyboard::keyboard_mapping::char_s:
        case keyboard::keyboard_mapping::char_S:
          {
            std::lock_guard<std::mutex> __guard(__map->__mutex);
            __tmp = __map->__data.at(static_cast<long>(__x) + x_dic[3], static_cast<long>(__y) + y_dic[3]);
          }
          if(move_one_step(*__map, __x, __y, x_dic[3], y_dic[3]))
          {
            __x = static_cast<long>(__x) + x_dic[3];
            __y = static_cast<long>(__y) + y_dic[3];
          }
          break;
        default:
          ;
      }
      if(check_record())
      { return;}
      if(__tmp == puzz_dest)
      {
        test_out();
        draw_play_matrix(*__map);
        printf("You finished the game.\n\n");
        return;
      }
      draw_play_matrix(*__map);
      if(check_record())
      { return;}
      printf("Please go on\n\n");
      if(check_record())
      { return;}
      draw_time(*__timer);
      if(check_record())
      { return;}
    }
  }

  bool find_all_path(const matrix<base_type>& __map)
  {
    unsigned long __x, __y;
    unsigned long __res;
    if(!find_puzzle_start(__map, __x, __y))
    { return false;}

    matrix<long> __record(__map.row(), __map.col());
    __record.init(-1);
    __detail::__fill_map(__map, __record, __x, __y);

    __res = __detail::__find_min_dest(__map, __record);
    if(__res == 0)
    { return false;}

    vector<point> __porec;
    __porec.push_back(point{__x, __y});
    __detail::__find_all(__map, __record, __porec, __x, __y);

    return true;
  }

  bool find_all_shortest_path(const matrix<base_type>& __map)
  {
    unsigned long __x, __y;
    unsigned long __res;

    if(!find_puzzle_start(__map, __x, __y))
    { return false;}

    matrix<long> __record(__map.row(), __map.col());
    __record.init(-1);
    __detail::__fill_map(__map, __record, __x, __y);

    __res = __detail::__find_min_dest(__map, __record);
    if(__res == 0)
    { return false;}

    vector<point> __porec;
    __porec.push_back(point{__x, __y});
    __detail::__find_all_shortest(__map, __res+1, __record, __porec, __x, __y);

    return true;
  }

}
