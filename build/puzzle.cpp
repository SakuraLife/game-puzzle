#include"puzzle.h"
#include"check.h"
#include"utility.h"
#include"map_operation.h"
#include"solve.h"
#include"main.h"
#include<thread>
#include<utility>
#include<cstdlib>
#include<cstdio>

namespace game
{
  puzzle::puzzle(): __data{}, __timer{}, __mapping{}, __select{-1}
  { }

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
    long long __sel;
    fscanf(__file, "%lu%lu%lld", &__r, &__c, &__sel);
    if(__r == 0 || __c == 0)
    {
      fprintf(stderr, "The format is not vaild.\n");
      fclose(__file);
      return false;
    }

    data_type __tmp(__r, __c);
    char __s[4];
    unsigned int __hh, __mm, __ss;
    unsigned long long __check = 0;
    point __st, __dest;

    for(unsigned long __i = 0; __i != __r; ++__i)
    {
      for(unsigned long __j = 0; __j != __c; ++__j)
      {
        fscanf(__file, "%s", __s);
        __tmp.at(__i, __j) = __s[0];
        if(__s[0] == puzz_tran)
        { ++__check;}
      }
    }
    map_init_out_wall(__tmp);
    fscanf(__file, "%u%u%u", &__hh, &__mm, &__ss);

    std::map<point, point> __tmap;

    for(unsigned long long __i = 0; __i < __check; ++__i)
    {
      fscanf(
        __file, "%lu%lu%lu%lu",
        &__st.x, &__st.y, &__dest.x, &__dest.y
      );
      __tmap.emplace(__st, __dest);
    }

    fclose(__file);

    return this->load_time(__hh, __mm, __ss) &&
           this->load_data(std::move(__tmp)) &&
           this->load_mapping(std::move(__tmap)) &&
           this->load_select(__sel);
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
  bool puzzle::load_data(data_type&& __file_data)
  {
    using std::fprintf;
    if(!check_is_mapped_vaild(__file_data))
    {
      fprintf(stderr, "Error! The data is invaild.\n");
      return false;
    }
    this->__data = std::move(__file_data);
    return true;
  }

  bool puzzle::load_mapping(const std::map<point, point>& __file_data)
  {
    using std::fprintf;
    if(!check_mapping_vaild(this->__data, __file_data))
    {
      fprintf(stderr, "Error! The data is invaild.\n");
      return false;
    }
    this->__mapping = __file_data;
    return true;
  }
  bool puzzle::load_mapping(std::map<point, point>&& __file_data)
  {
    using std::fprintf;
    if(!check_mapping_vaild(this->__data, __file_data))
    {
      fprintf(stderr, "Error! The data is invaild.\n");
      return false;
    }
    this->__mapping = std::move(__file_data);
    return true;
  }


  bool puzzle::load_time(
    unsigned int __hh, unsigned int __mm, unsigned int __ss
  ) noexcept
  {
    this->__timer.hh = __hh;
    this->__timer.mm = __mm;
    this->__timer.ss = __ss;
    return true;
  }
  bool puzzle::load_time(const countdown& __t) noexcept
  {
    this->__timer = __t;
    return true;
  }
  bool puzzle::load_select(long long __at) noexcept
  {
    this->__select = __at;
    return true;
  }
}

namespace game
{
  void puzzle::game_play()
  {
    using std::printf;

    init_record();
    mutex_puzz __map(this->__data);
    countdown_mutex __clock{this->__timer};
    vector<point> __st_po;

    if(!find_puzzle_start(__map.__data, __st_po))
    {
      fprintf(stderr, "Error! Can not find start.");
      return;
    }
    point_mutex __now;
    select_one_start(
      __st_po, this->__select, __now.__now.x, __now.__now.y
    );

    reflush_screen();
    draw_play_matrix(__map, __now, __clock);

    // _game_playing(&__clock, &__map, &(this->__mapping), &__now);

    std::thread __thread1{
      _game_playing, &__clock, &__map, &(this->__mapping), &__now
    };
    std::thread __thread2{_time_opreator, &__clock, &__map, &__now};

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
