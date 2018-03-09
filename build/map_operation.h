
#ifndef __PUZZLE_OPERATION__
#define __PUZZLE_OPERATION__

#include"constant.hpp"
#include"matrix.hpp"

namespace game
{
  void map_init(matrix<base_type>& __map) noexcept;
  void map_init_out_wall(matrix<base_type>& __map) noexcept;
}

#endif // ! __PUZZLE_OPERATION__
