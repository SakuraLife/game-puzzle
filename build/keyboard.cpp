
#include"keyboard.h"

#include<cstdio>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>

char keyboard::read_one_char() noexcept
{
  using std::getchar;

  static termios __old, __new;

  tcgetattr(STDIN_FILENO, &__old);
  __new = __old;

  __new.c_lflag &= ~(ICANON);

  tcsetattr(STDIN_FILENO, TCSANOW, &__new);

  char __res = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &__old);

  return __res;
}

int keyboard::kbhit() noexcept
{
  using std::ungetc;
  using std::getchar;

  struct termios __old, __new;
  int __res;
  int __old_fcntl;

  tcgetattr(STDIN_FILENO, &__old);
  __new = __old;
  __new.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &__new);
  __old_fcntl = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, __old_fcntl | O_NONBLOCK);

  __res = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &__old);
  fcntl(STDIN_FILENO, F_SETFL, __old_fcntl);

  if(__res != EOF)
  {
    ungetc(__res, stdin);
    return 1;
  }

  return 0;
}

keyboard::keyboard_mapping keyboard::keyboard_one_step() noexcept
{
  char __char = read_one_char();
  if(__char == char{0x1B})
  {
    if(!keyboard::kbhit())
    { return keyboard_mapping::esc;}
    if(keyboard::read_one_char() == '[')
    {
      if(!keyboard::kbhit())
      { return keyboard_mapping::unknown;}
      __char = keyboard::read_one_char();
      switch(__char)
      {
        case 'A':
          return keyboard_mapping::up_arrow;
        case 'B':
          return keyboard_mapping::down_arrow;
        case 'C':
          return keyboard_mapping::right_arrow;
        case 'D':
          return keyboard_mapping::left_arrow;
        case 'F':
          return keyboard_mapping::end;
        case 'H':
          return keyboard_mapping::home;
        case '2':
          if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
          { return keyboard_mapping::unknown;}
          return keyboard_mapping::insert;
        case '3':
          if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
          { return keyboard_mapping::unknown;}
          return keyboard_mapping::del;
        case '5':
          if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
          { return keyboard_mapping::unknown;}
          return keyboard_mapping::page_up;
        case '6':
          if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
          { return keyboard_mapping::unknown;}
          return keyboard_mapping::page_down;
        default:
          return keyboard_mapping::unknown;
      }
    }
  }

  return static_cast<keyboard_mapping>(__char);
}
