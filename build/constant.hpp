
#ifndef __PUZZ_CONSTANT__
#define __PUZZ_CONSTANT__

namespace game
{
  typedef char base_type;

  constexpr base_type puzz_wall   = '#';
  constexpr base_type puzz_dest   = '1';
  constexpr base_type puzz_start  = '0';
  constexpr base_type puzz_pass   = '-';
  constexpr base_type puzz_now    = '@';
  constexpr base_type puzz_write  = 'x';
  constexpr base_type puzz_tran   = '*';
  constexpr base_type puzz_cost   = '$';

  constexpr long x_dic[4] = {0, -1, 0, 1};
  constexpr long y_dic[4] = {1, 0, -1, 0};

  enum class puzz_mode : unsigned char
  {
    play = 0,
    modify = 1,
    exit = 2
  };
}

#endif // ! __PUZZ_CONSTANT__
