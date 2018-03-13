
#ifndef __PUZZ_CONSTANT__
#define __PUZZ_CONSTANT__

namespace game
{
  typedef char base_type;

  constexpr base_type puzz_wall       = '#';
  constexpr base_type puzz_dest       = '1';
  constexpr base_type puzz_start      = '0';
  constexpr base_type puzz_pass       = '-';
  constexpr base_type puzz_now        = '@';
  constexpr base_type puzz_write      = 'x';
  constexpr base_type puzz_tran       = '*';
  constexpr base_type puzz_cost       = '$';
  constexpr base_type puzz_trap_wall  = '|';
  constexpr base_type puzz_trap_tran  = '*';
  constexpr base_type puzz_trap_pass  = '^';

  constexpr long x_dic[4] = {0, -1, 0, 1};
  constexpr long y_dic[4] = {1, 0, -1, 0};

}

#endif // ! __PUZZ_CONSTANT__
