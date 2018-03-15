#include"utility.h"
#include<cstdio>
#include<cstdlib>

namespace game
{
  void reflush_screen() noexcept
  {
    using std::system;
    system("clear");
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
          case puzz_trap_wall:
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
          case puzz_trap_pass:
          case puzz_pass:
            printf(" \e[1;30m-\e[0m");
            break;
          case puzz_write:
            printf(" \e[1;33mx\e[0m");
            break;
          case puzz_tran:
            printf(" \e[1;35m+\e[0m");
            break;
        }
      }
      printf("\n");
    }
  }

  void draw_matrix(
    const matrix<base_type>& __map,
    const unsigned long __up, const unsigned long __down,
    const unsigned long __left, const unsigned long __right
  ) noexcept
  {
    using std::printf;
    for(unsigned long __i = __up; __i != __down; ++__i)
    {
      for(unsigned long __j = __left; __j != __right; ++__j)
      {
        switch(__map.at(__i, __j))
        {
          case puzz_trap_wall:
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
          case puzz_trap_pass:
          case puzz_pass:
            printf(" \e[1;30m-\e[0m");
            break;
          case puzz_write:
            printf(" \e[1;33mx\e[0m");
            break;
          case puzz_tran:
            printf(" \e[1;35m+\e[0m");
            break;
        }
      }
      printf("\n");
    }
  }

  void draw_time(const countdown& __timer) noexcept
  {
    printf(
      "Left Time:%02u:%02u:%02u\n",
      __timer.hh, __timer.mm, __timer.ss
    );
  }


  bool find_puzzle_start(
    const matrix<base_type>& __map, vector<point>& __rec
  )
  {
    bool __has = false;
    const base_type* __map_end = __map.data() + __map.size();

    for(const base_type* __i = __map.data(); __i != __map_end; ++__i)
    {
      if(*__i == puzz_start)
      {
        __rec.push_back(point{
          (__i - __map.data()) / __map.col(),
          (__i - __map.data()) % __map.col()
        });
        __has =  true;
      }
    }
    return __has;
  }

  void select_one_start(
    const vector<point>& __rec, long long __at,
    unsigned long& __x, unsigned long& __y
  ) noexcept
  {
    unsigned long long __where = 0;
    if(__at < 0)
    { __where = rand();}
    else
    { __where = static_cast<unsigned long long>(__at);}
    __where %= __rec.size();
    __x = __rec[__where].x;
    __y = __rec[__where].y;
    return;
  }

}

/*
#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"
*/
