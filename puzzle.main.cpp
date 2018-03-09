#include<cstdio>
#include"build/puzzle.h"
#include"build/defdata.h"

namespace
{
  void puzz_help() noexcept
  {
    using ::std::printf;

    printf("Usage:\n");
    printf("puzzle.main [-p][-s][-e][-h] <PATH>\n\n");

    printf("  -p [<path>]\tplay the game with map file, deafault with\n  \t\t  build-in maps.\n");
    printf("  -s [<path>]\tsolve the game with map file, deafault with\n  \t\t  build-in maps.\n");
    printf("  -e <path>\tedit the map file.\n");
    printf("  -h\t\tprint this help.\n");
    printf("  -v\t\tprint the author information.\n");
  }

  void author_inf() noexcept
  {
    using ::std::printf;

    printf("Created by Inochi Amaoto.\n");
  }

}

int main(int argc, char* argv[])
{
  using std::printf;

  if(argc == 1 || argc > 3)
  {
    help_error:
      puzz_help();
      printf("\n");
      author_inf();
      return 0;
  }

  game::puzzle puzz;

  if(argc == 2)
  {
    if(argv[1][0] != '-')
    { goto help_error;}
    switch(argv[1][1])
    {
      case 'h':
        puzz_help();
        printf("\n");
      case 'v':
        author_inf();
        break;
      case 'p':
        if(puzz.load_data(game::default_data(0)) && puzz.load_time(0, 1, 0))
        { puzz.game_play();}
        break;
      case 's':
        if(puzz.load_data(game::default_data(0)))
        { puzz.game_solve();}
        break;
      case 'e':
      default:
        printf("Unknown options: -%c\n\n", argv[1][1]);
        goto help_error;
    }
    return 0;
  }
  if(argv[1][0] != '-')
  { goto help_error;}
  switch(argv[1][1])
  {
    case 'h':
      puzz_help();
      printf("\n");
    case 'v':
      author_inf();
      break;
    case 'p':
      if(puzz.load_data(argv[2]))
      { puzz.game_play();}
      break;
    case 's':
      if(puzz.load_data(argv[2]))
      { puzz.game_solve();}
      break;
    case 'e':
      game::puzzle::game_edit(argv[2]);
      break;
    default:
      printf("Unknown options: -%c\n\n", argv[1][1]);
      goto help_error;
  }

  return 0;
}
