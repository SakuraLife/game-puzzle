
#ifndef __PUZZLE_DEFAULT_DATA__
#define __PUZZLE_DEFAULT_DATA__

#include"constant.hpp"
#include"matrix.hpp"
#include"structs.hpp"
#include<map>

namespace game
{
  void build_in_data(matrix<base_type>& __map, long __num);
  countdown build_in_time(long num) noexcept;
  void build_in_mapping(std::map<point, point>& __mapping, long __num);
}

#endif // ! __PUZZLE_DEFAULT_DATA__
