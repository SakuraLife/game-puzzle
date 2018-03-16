#include<cstdio>
#include"build/structs.hpp"
#include"build/puzzle.h"

namespace
{
  void print_header(unsigned long in) noexcept
  {
    using std::printf;

    printf("#ifndef __PUZZ_DEFAULT_MAP_%lu__\n", in);
    printf("#define __PUZZ_DEFAULT_MAP_%lu__\n", in);
    printf("\n");
    printf("#include\"puzzle_fwd.hpp\"\n");
    printf("\n");

    printf("namespace game\n");
    printf("{\n");
    printf("  namespace build_in\n");
    printf("  {\n");
    printf("    void map_%lu_data(matrix<game::base_type>& __map);\n", in);
    printf("    countdown map_%lu_time() noexcept;\n", in);
    printf("    void map_%lu_mapping(std::map<point, point>& __mapping);\n", in);
    printf("  }\n");
    printf("}\n");
    printf("\n");
    printf("#endif // ! __PUZZ_DEFAULT_MAP_%lu__\n", in);
    printf("\n");
  }

  void print_map_data_header(unsigned long in) noexcept
  {
    using std::printf;

    printf("#include\"map_%lu.h\"\n", in);
    printf("\n\n");

  }
  void print_map_data(
    const game::matrix<game::base_type>& __map, unsigned long in
  ) noexcept
  {
    using std::printf;
    printf(
      "void game::build_in::map_%lu_data(matrix<game::base_type>& __map)\n",
      in
    );
    printf("{\n");
    printf("  __map.resize(%4lu, %4lu);\n", __map.row(), __map.col());
    printf("  game::map_init(__map);\n");
    printf("\n");

    for(unsigned long __i = 1; __i+1 < __map.row(); ++__i)
    {
      for(unsigned long __j = 1; __j+1 < __map.col(); ++__j)
      {
        switch(__map.at(__i, __j))
        {
          case game::puzz_wall:
            printf("  __map[%4lu] = game::puzz_wall;\n", __i*__map.row()+__j);
            break;
          case game::puzz_start:
            printf("  __map[%4lu] = game::puzz_start;\n", __i*__map.row()+__j);
            break;
          case game::puzz_dest:
            printf("  __map[%4lu] = game::puzz_dest;\n", __i*__map.row()+__j);
            break;
          case game::puzz_tran:
            printf("  __map[%4lu] = game::puzz_tran;\n", __i*__map.row()+__j);
            break;
          case game::puzz_trap_wall:
            printf("  __map[%4lu] = game::puzz_trap_wall;\n", __i*__map.row()+__j);
            break;
          case game::puzz_trap_tran:
            printf("  __map[%4lu] = game::puzz_trap_tran;\n", __i*__map.row()+__j);
            break;
          case game::puzz_trap_pass:
            printf("  __map[%4lu] = game::puzz_trap_pass;\n", __i*__map.row()+__j);
            break;
          case game::puzz_now:
          case game::puzz_pass:
          case game::puzz_write:
            break;
        }
      }
    }

    printf("\n");
    printf("  return;\n");
    printf("}\n");
    printf("\n");

    return;
  }

  void print_map_time(
    const game::countdown& __now, unsigned long in
  ) noexcept
  {
    using std::printf;

    printf(
      "game::countdown game::build_in::map_%lu_time() noexcept\n",
      in
    );
    printf(
      "{ return game::countdown{%hu, %hu, %hu};}\n",
      __now.hh, __now.mm, __now.ss
    );
    printf("\n");
  }
  void print_map_mapping(
    const std::map<game::point, game::point>& __mapping,
    unsigned long in
  ) noexcept
  {
    using std::printf;

    printf(
      "void game::build_in::map_%lu_mapping(std::map<point, point>& __mapping)\n",
      in
    );
    printf("{\n");
    for(const std::pair<const game::point, game::point>& __tmp: __mapping)
    {
      printf("  __mapping.insert(std::pair<const point, point>{\n");
      printf(
        "    point{%3lu, %3lu}, point{%3lu, %3lu}\n",
        __tmp.first.x, __tmp.first.y,
        __tmp.second.x, __tmp.second.y
      );
      printf("  });\n");
    }
    printf("}\n");
    printf("\n");
  }
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  { return 0;}

  unsigned long in = 0;
  game::puzzle puzz;
  if(puzz.load_file(argv[1]))
  {
    print_header(in);
    print_map_data_header(in);
    print_map_data(puzz.map_data(), in);
    print_map_time(puzz.time_data(), in);
    print_map_mapping(puzz.mapping_data(), in);
  }

  return 0;
}
