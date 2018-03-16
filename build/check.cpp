#include"check.h"

namespace game
{
  bool check_block_vaild(base_type __step) noexcept
  {
    return __step == puzz_wall  || __step == puzz_dest ||
           __step == puzz_start || __step == puzz_pass ||
           __step == puzz_tran  || __step == puzz_trap_wall;
  }

  bool check_is_passage(base_type __step) noexcept
  {
    return __step == puzz_start || __step == puzz_pass ||
           __step == puzz_dest  || __step == puzz_tran ||
           __step == puzz_trap_wall;
  }

  bool check_not_out(
    unsigned long __row, unsigned long __col,
    const matrix<base_type>& __map
  ) noexcept
  {
    return __row > 0 && __row < __map.row() &&
           __col > 0 && __col < __map.col();
  }

  bool check_is_dest(base_type __step) noexcept
  { return __step == puzz_dest;}

  bool check_is_transport(base_type __step) noexcept
  { return __step == puzz_tran;}

  bool check_is_write_ligatures(base_type __step) noexcept
  {
    return __step == puzz_start || __step == puzz_dest ||
           __step == puzz_write || __step == puzz_tran ||
           __step == puzz_trap_wall;
  }

  bool check_map_base(const matrix<base_type>& __map) noexcept
  {
    const base_type* __map_end = __map.data() + __map.size();
    unsigned long long __check = 0;

    // Maybe we assume more than one dest and one start? Uhh....
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
    return __check != 0ULL;
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

  bool check_is_mapped_vaild(const matrix<base_type>& __map) noexcept
  { return check_map_base(__map) && check_map_wall(__map);}

  bool check_mapping_vaild(
    const matrix<base_type>& __map,
    const std::map<point, point>& __mapping
  ) noexcept
  {
    for(const std::pair<const game::point, game::point>& __tmp: __mapping)
    {
      if(__map.at(__tmp.first.x, __tmp.first.y) != puzz_tran ||
         !check_is_passage(__map.at(__tmp.second.x, __tmp.second.y)))
      { return false;}
    }
    return true;
  }

}
