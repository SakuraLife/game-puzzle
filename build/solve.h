
#ifndef __PUZZLE_SOLVE__
#define __PUZZLE_SOLVE__

#include"constant.hpp"
#include"matrix.hpp"
#include"structs.hpp"
#include"keyboard.h"
#include<map>

namespace game
{
  bool find_all_path(
    const matrix<base_type>& __map,
    const std::map<point, point>& __mapping
  );
  bool find_all_shortest_path(
    const matrix<base_type>& __map,
    const std::map<point, point>& __mapping
  );
}

#endif // ! __PUZZLE_SOLVE__
