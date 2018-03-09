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

    printf("namespace\n");
    printf("{\n");
    printf("  game::matrix<game::base_type> default_data() noexcept\n");
    printf("  {\n");
    printf("    game::matrix<game::base_type> use(40, 40);\n");
    printf("    game::map_init(use);\n");
    printf("\n");
    printf("    assert(game::check_map_wall(use) == true);\n");
    printf("\n");

  }
  void print_default_inc_body(const game::matrix<game::base_type>& __map)
  {
    for(unsigned long __i = 1; __i+1 < __map.row(); ++__i)
    {
      for(unsigned long __j = 1; __j+1 < __map.col(); ++__j)
      {
        // printf("%2c", __map.at(__i, __j));
        switch(__map.at(__i, __j))
        {
          case game::puzz_wall:
            printf("    use.at(%2lu, %2lu) = game::puzz_wall;\n", __i, __j);
            break;
          case game::puzz_start:
            printf("    use.at(%2lu, %2lu) = game::puzz_start;\n", __i, __j);
            break;
          case game::puzz_dest:
            printf("    use.at(%2lu, %2lu) = game::puzz_dest;\n", __i, __j);
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
    printf("    return use;\n");
    printf("  }\n");
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
