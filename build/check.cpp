#include"check.h"

namespace game
{
  bool check_block_vaild(base_type __step) noexcept
  {
    return __step == puzz_wall  || __step == puzz_dest ||
           __step == puzz_start || __step == puzz_pass ||
           __step == puzz_now;
  }

  bool check_is_passage(base_type __step) noexcept
  { return __step == puzz_start || __step == puzz_pass || __step == puzz_dest;}

  bool check_not_out(
    unsigned long __row, unsigned long __col,
    const matrix<base_type>& __map
  ) noexcept
  {
    return __row > 0 && __row < __map.row() &&
           __col > 0 && __col < __map.col();
  }

  bool check_is_write_ligatures(base_type __step) noexcept
  { return __step == puzz_start || __step == puzz_dest || __step == puzz_write;}

  bool check_map_base(const matrix<base_type>& __map) noexcept
  {
    const base_type* __map_end = __map.data() + __map.size();
    unsigned long long __check = 0;

    // Maybe we assume more than one dest? Uhh....
    for(const base_type* __i = __map.data(); __i != __map_end; ++__i)
    {
      if(*__i == puzz_dest)
      { ++__check;}
    }
    if(__check == 0)
    { return false;}

    __check = 0;
    for(const base_type* __i = __map.data(); __i != __map_end; ++__i)
    {
      if(*__i == puzz_start)
      { ++__check;}
    }
    return __check == 1;
  }

  bool check_map_wall(const matrix<base_type>& __map) noexcept
  {
    using __map_size_type = typename matrix<base_type>::size_type;
    const __map_size_type __row = __map.row()-1;
    const __map_size_type __col = __map.col()-1;

    for(__map_size_type __i = 0; __i <= __col; ++__i)
    {
      if(__map.at(0, __i) != puzz_wall)
      { return false;}
    }
    for(__map_size_type __i = 0; __i <= __row; ++__i)
    {
      if(__map.at(__i, 0) != puzz_wall || __map.at(__i, __col) != puzz_wall)
      { return false;}
    }
    for(__map_size_type __i = 0; __i <= __col; ++__i)
    {
      if(__map.at(__row, __i) != puzz_wall)
      { return false;}
    }
    return true;
  }

  bool find_puzzle_start(
    const matrix<base_type>& __map,
    unsigned long& __x, unsigned long& __y
  ) noexcept
  {
    const base_type* __map_end = __map.data() + __map.size();

    for(const base_type* __i = __map.data(); __i != __map_end; ++__i)
    {
      if(*__i == puzz_start)
      {
        __x = (__i - __map.data()) / __map.col();
        __y = (__i - __map.data()) % __map.col();
        return true;
      }
    }
    return false;
  }

  namespace __detail
  {

    bool __check_one_step(
      const matrix<base_type>& __map, matrix<bool>& __rec,
      unsigned long __r, unsigned long __c
    )
    {
      if(__map.at(__r, __c) == puzz_dest)
      { return true;}

      for(unsigned long __i = 0; __i != 4; ++__i)
      {
        const long __trow = static_cast<long>(__r)+x_dic[__i];
        const long __tcol = static_cast<long>(__c)+y_dic[__i];
        if(check_not_out(__trow, __tcol, __map) &&
          !__rec.at(__trow, __tcol) &&
          check_is_passage(__map.at(__trow, __tcol))
        )
        {
          __rec.at(__trow, __tcol) = true;
          if(__check_one_step(__map, __rec, __trow, __tcol))
          { return true;}
          __rec.at(__trow, __tcol) = false;
        }
      }

      return false;
    }
  }

  bool check_is_mapped_vaild(const matrix<base_type>& __map) noexcept
  {
    // if(!(check_map_base(__map) && check_map_wall(__map)))
    // { return false;}
    // matrix<bool> __record(__map.row(), __map.col());
    // unsigned long __x, __y;
    // if(find_puzzle_start(__map, __x, __y))
    // { return __detail::__check_one_step(__map, __record, __x, __y);}
    return check_map_base(__map) && check_map_wall(__map);
  }
}
