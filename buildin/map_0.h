#ifndef __PUZZ_DEFAULT_MAP_0__
#define __PUZZ_DEFAULT_MAP_0__

#include"puzzle_fwd.hpp"

namespace game
{
  namespace build_in
  {
    void map_0_data(matrix<game::base_type>& __map);
    countdown map_0_time() noexcept;
    void map_0_mapping(std::map<point, point>& __mapping);
  }
}

#endif // ! __PUZZ_DEFAULT_MAP_0__
