#include"build/puzzle.h"
#include"build/defdata.h"
#include<cstdio>
#include<map>

// #include"./build/check.h"
// #include"./build/defdata.h"
// #include"./build/keyboard.h"
// #include"./build/main.h"
// #include"./build/map_operation.h"
// #include"./build/puzzle.h"
// #include"./build/solve.h"
// #include"./build/utility.h"
// #include"./build_in/map_0.h"
// #include"./build_in/map_1.h"

// #include"./build/check.cpp"
// #include"./build/defdata.cpp"
// #include"./build/keyboard.cpp"
// #include"./build/main.cpp"
// #include"./build/map_operation.cpp"
// #include"./build/puzzle.cpp"
// #include"./build/solve.cpp"
// #include"./build/utility.cpp"
// #include"./build_in/map_0.cpp"
// #include"./build_in/map_1.cpp"

// namespace
// {
//   [[unused]] void puzz_help() noexcept
//   {
//     using ::std::printf;

//     printf("Usage:\n");
//     printf("puzzle.main [-p][-s][-e][-h] <PATH>\n\n");

//     printf("  -p [<path>]\tplay the game with map file, deafault with\n  \t\t  build-in maps.\n");
//     printf("  -s [<path>]\tsolve the game with map file, deafault with\n  \t\t  build-in maps.\n");
//     printf("  -e <path>\tedit the map file.\n");
//     printf("  -h\t\tprint this help.\n");
//     printf("  -v\t\tprint the author information.\n");
//   }

//   [[unused]] void author_inf() noexcept
//   {
//     using ::std::printf;

//     printf("Created by Inochi Amaoto.\n");
//   }

// }

int main(int argc, char* argv[])
{
  using std::printf;

  // if(argc == 1 || argc > 3)
  // {
  //   help_error:
  //     puzz_help();
  //     printf("\n");
  //     author_inf();
  //     return 0;
  // }

  // game::puzzle puzz;

  // if(argc == 2)
  // {
  //   if(argv[1][0] != '-')
  //   { goto help_error;}
  //   switch(argv[1][1])
  //   {
  //     case 'h':
  //       puzz_help();
  //       printf("\n");
  //     case 'v':
  //       author_inf();
  //       break;
  //     case 'p':
  //       if(puzz.load_data(game::default_data(0)) && puzz.load_time(0, 1, 0))
  //       { puzz.game_play();}
  //       break;
  //     case 's':
  //       if(puzz.load_data(game::default_data(0)))
  //       { puzz.game_solve();}
  //       break;
  //     case 'e':
  //     default:
  //       printf("Unknown options: -%c\n\n", argv[1][1]);
  //       goto help_error;
  //   }
  //   return 0;
  // }
  // if(argv[1][0] != '-')
  // { goto help_error;}
  // switch(argv[1][1])
  // {
  //   case 'h':
  //     puzz_help();
  //     printf("\n");
  //   case 'v':
  //     author_inf();
  //     break;
  //   case 'p':
  //     if(puzz.load_data(argv[2]))
  //     { puzz.game_play();}
  //     break;
  //   case 's':
  //     if(puzz.load_data(argv[2]))
  //     { puzz.game_solve();}
  //     break;
  //   case 'e':
  //     game::puzzle::game_edit(argv[2]);
  //     break;
  //   default:
  //     printf("Unknown options: -%c\n\n", argv[1][1]);
  //     goto help_error;
  // }

  std::vector<game::point> __po;
  game::matrix<game::base_type> __map;
  std::map<game::point, game::point> __mapping;
  game::build_in_data(__map, 0);
  game::build_in_mapping(__mapping, 0);
  game::countdown __time = game::build_in_time(0);
  game::puzzle puzz;

  if(
    puzz.load_data(std::move(__map)) &&
    puzz.load_time(__time) &&
    puzz.load_mapping(std::move(__mapping)) &&
    puzz.load_select(-1)
  )
  { puzz.game_play();}

  return 0;
}
