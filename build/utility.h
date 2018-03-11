
#ifndef __PUZZLE_UTILITY__
#define __PUZZLE_UTILITY__

#include"constant.hpp"
#include"matrix.hpp"
#include"structs.hpp"


namespace game
{
  void reflush_screen() noexcept;

  void draw_matrix(const matrix<base_type>& __map) noexcept;
  void draw_time(const countdown& __timer) noexcept;

  bool find_puzzle_start(
    const matrix<base_type>& __map, vector<point>& __rec
  );
  void select_one_start(
    const vector<point>& __rec, long long __at,
    unsigned long& __x, unsigned long& __y
  ) noexcept;
}

#endif // ! __PUZZLE_UTILITY__
