
#ifndef __PUZZLE_MAIN__
#define __PUZZLE_MAIN__

#include"constant.hpp"
#include"matrix.hpp"
#include"structs.hpp"
#include<map>

namespace game
{
  class puzzle
  {
    public:
      using data_type       = matrix<base_type>;
      using time_type       = countdown;

    public:
      using value_type      = typename data_type::value_type;
      using reference       = typename data_type::reference;
      using const_reference = typename data_type::const_reference;
      using size_type       = typename data_type::size_type;

    private:
      data_type __data;
      time_type __timer;
      std::map<point, point> __mapping;
      long long __select;

    public:
      puzzle();
      ~puzzle();

    public:
      bool load_file(const char* __str);
      bool load_data(const data_type& __file_data);
      bool load_data(data_type&& __file_data);
      bool load_mapping(const std::map<point, point>& __file_data);
      bool load_mapping(std::map<point, point>&& __file_data);
      bool load_time(
        unsigned int __hh, unsigned int __mm, unsigned int __ss
      ) noexcept;
      bool load_time(const countdown& __t) noexcept;
      bool load_select(long long __at) noexcept;

    public:
      void game_play() const;
      void game_solve() const;
      void game_solve_all() const;
      void game_show(const char* __fname);

    public:
      const data_type& map_data() const noexcept;
      const time_type& time_data() const noexcept;
      const std::map<point, point>& mapping_data() const noexcept;
      long long select_type_data() const noexcept;

    public:
      static void game_edit(const char* __path);

  };
}

#endif // ! __PUZZLE_MAIN__
