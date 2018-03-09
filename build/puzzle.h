
#ifndef __PUZZLE_MAIN__
#define __PUZZLE_MAIN__

#include"constant.hpp"
#include"matrix.hpp"
#include"utility.h"
#include"map_operation.h"

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

    public:
      puzzle(): __data(), __timer()
      { }

    public:
      bool load_data(const char* __str);
      bool load_data(const data_type& __file_data);
      bool load_time(
        unsigned int __hh, unsigned int __mm, unsigned int __ss
      ) noexcept;

    public:
      void game_play();
      void game_solve();
      void game_solve_all();

    public:
      const data_type& data() const noexcept;

    public:
      static void game_edit(const char* __path);

  };
}

#endif // ! __PUZZLE_MAIN__
