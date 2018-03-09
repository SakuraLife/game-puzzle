#include"puzzle.h"
#include"check.h"
#include"utility.h"
#include"map_operation.h"
#include<thread>
#include<cstdlib>
#include<cstdio>

namespace game
{
  bool puzzle::load_data(const char* __str)
  {
    using std::FILE;
    using std::fopen;
    using std::fclose;
    using std::fscanf;
    using std::fprintf;
    FILE* __file = fopen(__str, "r");
    if(__file == nullptr)
    {
      fprintf(stderr, "Error when open the file:%s", __str);
      return false;
    }
    unsigned long __r, __c;
    fscanf(__file, "%lu%lu", &__r, &__c);
    if(__r == 0 || __c == 0)
    {
      fprintf(stderr, "The format is not vaild.\n");
      fclose(__file);
      return false;
    }

    data_type __tmp(__r, __c);
    char __s[4];
    unsigned int __hh, __mm, __ss;

    for(unsigned long __i = 0; __i != __r; ++__i)
    {
      for(unsigned long __j = 0; __j != __c; ++__j)
      {
        fscanf(__file, "%s", __s);
        __tmp.at(__i, __j) = __s[0];
      }
    }
    map_init_out_wall(__tmp);

    fscanf(__file, "%u%u%u", &__hh, &__mm, &__ss);

    fclose(__file);

    return this->load_time(__hh, __mm, __ss) && this->load_data(__tmp);
  }
  bool puzzle::load_data(const data_type& __file_data)
  {
    using std::fprintf;
    if(!check_is_mapped_vaild(__file_data))
    {
      fprintf(stderr, "Error! The data is invaild.\n");
      return false;
    }
    this->__data = __file_data;
    return true;
  }
  bool puzzle::load_time(
    unsigned int __hh, unsigned int __mm, unsigned int __ss
  ) noexcept
  {
    this->__timer.__hh = __hh;
    this->__timer.__mm = __mm;
    this->__timer.__ss = __ss;
    return true;
  }

  void puzzle::game_play()
  {
    using std::printf;

    init_record();
    unsigned long __x, __y;
    mutex_puzz __map(this->__data);
    time_type __clock;
    __clock.__hh = this->__timer.__hh;
    __clock.__mm = this->__timer.__mm;
    __clock.__ss = this->__timer.__ss;

    if(!find_puzzle_start(__map.__data, __x, __y))
    {
      fprintf(stderr, "Error! Can not find start.");
      return;
    }
    __map.__data.at(__x, __y) = puzz_now;

    reflush_screen();
    draw_matrix(__map.__data);
    printf("Please go on\n\n");
    draw_time(__clock);

    std::thread __thread1{_game_playing, &__clock, &__map, __x, __y};
    std::thread __thread2{_time_opreator, &__clock, &__map};

    if(__thread1.joinable())
    { __thread1.join();}
    if(__thread2.joinable())
    { __thread2.join();}

  }
  void puzzle::game_solve()
  {
    using std::printf;

    reflush_screen();
    printf("This is the map:\n");
    draw_matrix(this->__data);
    printf("\n");

    bool __res = find_all_shortest_path(this->__data);
    if(!__res)
    {
      printf("There is no path for the game.\n");
      return;
    }
  }
  void puzzle::game_solve_all()
  {
    using std::printf;

    reflush_screen();
    printf("This is the map:\n");
    draw_matrix(this->__data);
    printf("\n");

    bool __res = find_all_path(this->__data);
    if(!__res)
    {
      printf("There is no path for the game.\n");
      return;
    }
  }

  const puzzle::data_type& puzzle::data() const noexcept
  { return this->__data;}

  void puzzle::game_edit(const char* __path)
  {
    using std::string;
    using std::system;

    string __execs("/bin/nano ");
    __execs.append(__path);

    system(__execs.c_str());

    return;
  }
}
