#ifndef __PUZZ_DEFAULT_MAP_1__
#define __PUZZ_DEFAULT_MAP_1__

#include"puzzle_fwd.hpp"

namespace game
{
  namespace build_in
  {
    void map_1_data(matrix<game::base_type>& __map);
    countdown map_1_time() noexcept;
    void map_1_mapping(std::map<point, point>& __mapping);
  }
}

#endif // ! __PUZZ_DEFAULT_MAP_1__
