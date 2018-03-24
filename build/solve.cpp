#include"solve.h"
#include"keyboard.h"
#include"utility.h"
#include"check.h"
#include<queue>

namespace game
{

  static void draw_solve_path(const vector<point>& __rec)
  {
    printf("%lu\n", __rec.size());
    unsigned long __use = 0;
    for(const point& __tmp : __rec)
    {
      printf("%lu %lu ", __tmp.x, __tmp.y);
      ++__use;
      if((__use & 0x7U) == 0)
      { printf("\n");}
    }
    printf("\n\n");
  }

  namespace __detail
  {
    static void __fill_map(
      const matrix<base_type>& __map, matrix<long>& __filled,
      const std::map<point, point>& __mapping,
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
          const unsigned long __tx = static_cast<long>(__now.__x)+x_dic[__i];
          const unsigned long __ty = static_cast<long>(__now.__y)+y_dic[__i];
          if(check_not_out(__tx, __ty, __map) &&
            check_is_passage(__map.at(__tx, __ty)))
          {
            if((__filled.at(__tx, __ty) == -1 ||
             __filled.at(__tx, __ty) > __now.__step+1))
            {
              if(check_is_transport(__map.at(__tx, __ty)))
              {
                __filled.at(__tx, __ty) = __now.__step+1;
                point __tmp = __mapping.find(point{__tx, __ty})->second;
                if(__filled.at(__tmp.x, __tmp.y) == -1 ||
                 __filled.at(__tmp.x, __tmp.y) > __now.__step+1)
                {
                  __filled.at(__tmp.x, __tmp.y) = __now.__step+1;
                  __queue.push(__point{__tmp.x, __tmp.y, __now.__step+1});
                }
              }
              else
              {
                __filled.at(__tx, __ty) = __now.__step+1;
                __queue.push(__point{__tx, __ty, __now.__step+1});
              }
            }
          }
        }

      }
    }

    static void __find_all(
      const matrix<base_type>& __map,
      const std::map<point, point>& __mapping,
      const unsigned long __res, const matrix<long>& __filled,
      vector<point>& __porec,
      unsigned long __r, unsigned long __c
    )
    {
      using std::system;

      if(__map.at(__r, __c) == puzz_dest)
      {
        draw_solve_path(__porec);
        return;
      }

      if(__porec.size() == __res)
      { return;}

      // printf("%lu %lu %ld\n", __r, __c, __filled.at(__r, __c));

      for(unsigned long __i = 0; __i != 4; ++__i)
      {
        const unsigned long __tx = static_cast<long>(__r)+x_dic[__i];
        const unsigned long __ty = static_cast<long>(__c)+y_dic[__i];

        if(check_not_out(__tx, __ty, __map) &&
          __filled.at(__r, __c) + 1 == __filled.at(__tx, __ty)
        )
        {
          __porec.push_back(point{__tx, __ty});
          if(check_is_transport(__map.at(__tx, __ty)))
          {
            const point __tmp =
              __mapping.find(point{__tx, __ty})->second;
            __find_all(
              __map, __mapping, __res, __filled, __porec, __tmp.x, __tmp.y
            );
          }
          else
          {
            __find_all(
              __map, __mapping, __res, __filled, __porec, __tx, __ty
            );
          }
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

  bool find_all_path(
    const matrix<base_type>& __map,
    const std::map<point, point>& __mapping
  )
  {
    vector<point> __rec;
    if(!find_puzzle_start(__map, __rec))
    { return false;}

    bool __sum = false;

    for(const point& __po: __rec)
    {
      unsigned long __res;
      matrix<long> __record(__map.row(), __map.col());
      __record.init(-1);
      __detail::__fill_map(__map, __record, __mapping, __po.x, __po.y);

      __res = __detail::__find_min_dest(__map, __record);
      if(__res == 0)
      { continue;}
      __sum = true;

      vector<point> __porec;
      __porec.push_back(point{__po.x, __po.y});
      __detail::__find_all(
        __map, __mapping, 0xffffffffUL, __record, __porec, __po.x, __po.y
      );
    }

    return __sum;
  }

  bool find_all_shortest_path(
    const matrix<base_type>& __map,
    const std::map<point, point>& __mapping
  )
  {
    vector<point> __rec;
    if(!find_puzzle_start(__map, __rec))
    { return false;}

    bool __sum = false;
    for(const point& __po: __rec)
    {
      unsigned long __res;
      matrix<long> __record(__map.row(), __map.col());
      __record.init(-1);
      __detail::__fill_map(__map, __record, __mapping, __po.x, __po.y);
#ifndef NDEBUG
      for(unsigned long __i = 0; __i != __record.row(); ++__i)
      {
        for(unsigned long __j = 0; __j != __record.col(); ++__j)
        { printf("%3ld ", __record.at(__i, __j));}
        printf("\n");
      }
#endif // ! NDEBUG
      __res = __detail::__find_min_dest(__map, __record);
      if(__res == 0)
      { continue;}
      __sum = true;

      vector<point> __porec;
      __porec.push_back(point{__po.x, __po.y});
      __detail::__find_all(
        __map, __mapping, __res+1, __record, __porec, __po.x, __po.y
      );
    }
    return __sum;
  }
}
