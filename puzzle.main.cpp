#include"build/puzzle.h"
#include"build/defdata.h"
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>

// #include"./build/check.h"
// #include"./build/defdata.h"
// #include"./build/keyboard.h"
// #include"./build/main.h"
// #include"./build/map_operation.h"
// #include"./build/puzzle.h"
// #include"./build/solve.h"
// #include"./build/analyze.h"
// #include"./build/utility.h"
// #include"./buildin/map_0.h"
// #include"./buildin/map_1.h"

// #include"./build/check.cpp"
// #include"./build/defdata.cpp"
// #include"./build/keyboard.cpp"
// #include"./build/main.cpp"
// #include"./build/map_operation.cpp"
// #include"./build/puzzle.cpp"
// #include"./build/solve.cpp"
// #include"./build/analyze.cpp"
// #include"./build/utility.cpp"
// #include"./buildin/map_0.cpp"
// #include"./buildin/map_1.cpp"

namespace
{
  struct puzz_args
  {
    bool play;
    bool solve;
    bool solve_all;
    bool build_in;
    bool edit;
    bool help;
    bool show;
    unsigned long which;
    const char* file;
    const char* solve_file;
  };

  void puzz_help() noexcept
  {
    using ::std::printf;

    printf("Usage:\n");
    printf("puzzle.main [-b][-p][-s][-e][-h] <PATH>\n\n");

    printf("  -b [num]\tuse build in data.\n");
    printf("  -p [<path>]\tplay the game\n");
    printf("  -s [<path>]\tsolve the game\n");
    printf("  -e <path>\tedit the map file.\n");
    printf("  -d <path> [<path>]\tplay the game use trace files\n");
    printf("  -h\t\tprint this help.\n");
    printf("\nPlease type -b first if you what use build in data.\n");
    // printf("  -v\t\tprint the author information.\n");
  }

  void author_inf() noexcept
  {
    using std::printf;
    printf("Created by Inochi Amaoto.\n");
  }

  void puzz_information() noexcept
  {
    using std::printf;

    printf("This is the symbol information.\n");

    printf("  0\t\tthe start postion.\n  \t\tThe game starts from one of them.\n\n");
    printf("  1\t\tthe destination postion.\n  \t\tThe game ends if you reach one of them.\n\n");
    printf("  #\t\tthe wall.\n  \t\tYou can't pass it at the most time, \n  \t\tbut there are some special walls that you can pass\n\n");
    printf("  -\t\tthe pass.\n  \t\tYou can pass it at the most time,\n  \t\tbut if it's a trap, you can't pass it.\n\n");
    printf("  +\t\tthe transport postion.\n  \t\tYou will be transported to a new postion when you reach.\n");
  }

  void analyze_args(int argc, char* argv[], puzz_args& args)
  {
    using std::fprintf;
    using std::strtoul;
    using std::exit;

    for(int __i = 1; __i < argc; ++__i)
    {
      if(argv[__i][0] == '-')
      {
        switch(argv[__i][1])
        {
          case 'h':
            args.help = true;
            break;
          case 'b':
            args.build_in = true;
            ++__i;
            args.which = strtoul(argv[__i], nullptr, 10);
            break;
          case 'p':
            args.play = true;
            if(!args.build_in)
            {
              ++__i;
              args.file = argv[__i];
            }
            break;
          case 's':
            args.solve = true;
            if(!args.build_in)
            {
              ++__i;
              args.file = argv[__i];
            }
            break;
          case 'd':
            args.show = true;
            ++__i;
            args.solve_file = argv[__i];
            if(!args.build_in)
            {
              ++__i;
              args.file = argv[__i];
            }
            break;
          case 'e':
            args.edit = true;
            ++__i;
            args.file = argv[__i];
            break;
          default:
            fprintf(stderr, "Unknown args - %c\n", argv[__i][1]);
            puzz_help();
            printf("\n");
            puzz_information();
            printf("\n");
            author_inf();
            exit(EXIT_FAILURE);
        }
      }
    }
  }
}

int main(int argc, char* argv[])
{
  using std::printf;
  using std::memset;

  puzz_args args;
  memset(&args, 0x00, sizeof(args));
  if(argc == 1)
  { goto laber_help;}
  analyze_args(argc, argv, args);

  if(args.help)
  {
    laber_help:
      puzz_help();
      printf("\n");
      puzz_information();
      printf("\n");
      author_inf();
      return 0;
  }

  if(args.edit)
  {
    if(args.file == nullptr)
    { args.file = "default.map";}
    game::puzzle::game_edit(args.file);
    return 0;
  }

  game::puzzle puzz;
  bool __load = false;
  if(args.build_in)
  {
    std::vector<game::point> __po;
    game::matrix<game::base_type> __map;
    std::map<game::point, game::point> __mapping;
    game::build_in_data(__map, args.which);
    game::build_in_mapping(__mapping, args.which);
    __load = puzz.load_data(std::move(__map)) &&
             puzz.load_time(game::build_in_time(args.which)) &&
             puzz.load_mapping(std::move(__mapping)) &&
             puzz.load_select(-1);
  }
  else
  {
    if(args.file == nullptr)
    { goto file_error;}
    __load = puzz.load_file(args.file);
  }
  if(!__load)
  {
    file_error:
      fprintf(stderr, "Error when load data.\n");
      return EXIT_FAILURE;
  }

  if(args.play)
  {
    puzz.game_play();
    return 0;
  }
  if(args.solve)
  {
    puzz.game_solve();
    return 0;
  }
  if(args.show)
  {
    puzz.game_show(args.solve_file);
    return 0;
  }

  return 0;
}
