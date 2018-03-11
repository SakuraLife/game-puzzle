
#ifndef __PUZZLE_SOLVE__
#define __PUZZLE_SOLVE__

#include"constant.hpp"
#include"matrix.hpp"

namespace game
{
  bool find_all_path(const matrix<base_type>& __map);
  bool find_all_shortest_path(const matrix<base_type>& __map);
}

#endif // ! __PUZZLE_SOLVE__
