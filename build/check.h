
#ifndef __PUZZLE_CHECK__
#define __PUZZLE_CHECK__

#include"constant.hpp"
#include"matrix.hpp"

namespace game
{
  bool check_block_vaild(base_type __step) noexcept;

  bool check_is_passage(base_type __step) noexcept;

  bool check_not_out(
    unsigned long __row, unsigned long __col,
    const matrix<base_type>& __map
  ) noexcept;

  bool check_is_write_ligatures(base_type __step) noexcept;

  bool check_map_base(const matrix<base_type>& __map) noexcept;

  bool check_map_wall(const matrix<base_type>& __map) noexcept;

  bool find_puzzle_start(
    const matrix<base_type>& __map,
    unsigned long& __x, unsigned long& __y
  ) noexcept;

  bool check_is_mapped_vaild(const matrix<base_type>& __map) noexcept;

}

#endif // ! __PUZZLE_CHECK__
