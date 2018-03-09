
#include"map_operation.h"

void game::map_init(game::matrix<game::base_type>& __map) noexcept
{
  using __map_size_type =
    typename game::matrix<game::base_type>::size_type;
  const __map_size_type __row = __map.row()-1;
  const __map_size_type __col = __map.col()-1;

  for(__map_size_type __i = 0; __i <= __col; ++__i)
  { __map.at(0, __i) = puzz_wall;}
  for(__map_size_type __i = 1; __i < __row; ++__i)
  {
    __map.at(__i, 0) = puzz_wall;
    for(__map_size_type __j = 1; __j < __col; ++__j)
    { __map.at(__i, __j) = puzz_pass;}
    __map.at(__i, __col) = puzz_wall;
  }
  for(__map_size_type __i = 0; __i <= __col; ++__i)
  { __map.at(__row, __i) = puzz_wall;}

  return;
}

void game::map_init_out_wall(matrix<base_type>& __map) noexcept
{
  using __map_size_type =
    typename game::matrix<game::base_type>::size_type;
  const __map_size_type __row = __map.row()-1;
  const __map_size_type __col = __map.col()-1;

  for(__map_size_type __i = 0; __i <= __col; ++__i)
  { __map.at(0, __i) = puzz_wall;}
  for(__map_size_type __i = 1; __i < __row; ++__i)
  {
    __map.at(__i, 0) = puzz_wall;
    __map.at(__i, __col) = puzz_wall;
  }
  for(__map_size_type __i = 0; __i <= __col; ++__i)
  { __map.at(__row, __i) = puzz_wall;}

  return;
}
