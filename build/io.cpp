
#include"io.h"

#include<cstdio>
#include<termios.h>
#include<unistd.h>

char io::read_one_char() noexcept
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
