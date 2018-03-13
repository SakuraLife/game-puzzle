#include"defdata.h"
#include"../buildin/build_in.hpp"

void game::build_in_data(matrix<base_type>& __map, long __num)
{
  switch(__num)
  {
    case 0:
      game::build_in::map_0_data(__map);
      break;
    case 1:
      game::build_in::map_1_data(__map);
      break;
    default:
      game::build_in::map_0_data(__map);
  }
  return;
}
game::countdown game::build_in_time(long __num) noexcept
{
  switch(__num)
  {
    case 0:
      return game::build_in::map_0_time();
    case 1:
      return game::build_in::map_1_time();
    default:
      return game::build_in::map_0_time();
  }
}
void game::build_in_mapping(std::map<point, point>& __mapping, long __num)
{
  switch(__num)
  {
    case 0:
      game::build_in::map_0_mapping(__mapping);
      break;
    case 1:
      game::build_in::map_1_mapping(__mapping);
      break;
    default:
      game::build_in::map_0_mapping(__mapping);
  }
  return;
}

