#include"build/puzzle.h"

namespace
{
  void print_default_inc_st() noexcept
  {
    printf("#include\"constant.hpp\"\n");
    printf("#include\"matrix.hpp\"\n");
    printf("#include\"map_operation.h\"\n");
    printf("#include\"check.h\"\n");
    printf("#include<cassert>\n");
    printf("\n");

    printf("void game::default_data(game::matrix<game::base_type> __map, long __num)\n");
    printf("{\n");
    printf("  __map.resize(40, 40);\n");
    printf("  game::map_init(__map);\n");
    printf("\n");
    printf("  assert(game::check_map_wall(__map) == true);\n");
    printf("\n");

  }
  void print_default_inc_body(const game::matrix<game::base_type>& __map)
  {
    for(unsigned long __i = 1; __i+1 < __map.row(); ++__i)
    {
      for(unsigned long __j = 1; __j+1 < __map.col(); ++__j)
      {
        switch(__map.at(__i, __j))
        {
          case game::puzz_wall:
            printf("  __map.at(%2lu, %2lu) = game::puzz_wall;\n", __i, __j);
            break;
          case game::puzz_start:
            printf("  __map.at(%2lu, %2lu) = game::puzz_start;\n", __i, __j);
            break;
          case game::puzz_dest:
            printf("  __map.at(%2lu, %2lu) = game::puzz_dest;\n", __i, __j);
            break;
          case game::puzz_tran:
            printf("    use.at(%2lu, %2lu) = game::puzz_tran;\n", __i, __j);
            break;
          case game::puzz_now:
          case game::puzz_pass:
          case game::puzz_write:
            break;
        }
      }
    }

    return;
  }

  void print_default_inc_ed() noexcept
  {
    printf("\n");
    printf("  return;\n");
    printf("}\n");
  }
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  { return 0;}

  game::puzzle puzz;
  if(puzz.load_data(argv[1]))
  {
    print_default_inc_st();
    print_default_inc_body(puzz.data());
    print_default_inc_ed();
  }

  return 0;
}
