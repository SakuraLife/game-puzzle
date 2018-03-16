#include"analyze.h"
#include"check.h"

namespace game
{
  static void analyze_point_pos(
    const point& __pre, const point& __now,
    vector<keyboard::keyboard_mapping>& __trace
  )
  {
    const long __d_x = static_cast<long>(__now.x-__pre.x);
    const long __d_y = static_cast<long>(__now.y-__pre.y);
    if(__d_x == 0)
    {
      if(__d_y == 1)
      { __trace.push_back(keyboard::keyboard_mapping::right_arrow);}
      if(__d_y == -1)
      { __trace.push_back(keyboard::keyboard_mapping::left_arrow);}
    }
    if(__d_y == 0)
    {
      if(__d_x == 1)
      { __trace.push_back(keyboard::keyboard_mapping::down_arrow);}
      if(__d_x == -1)
      { __trace.push_back(keyboard::keyboard_mapping::up_arrow);}
    }
  }

  void analyze_point_trace(
    const matrix<base_type>& __map,
    const std::map<point, point>& __mapping,
    const vector<point>& __po,
    vector<keyboard::keyboard_mapping>& __trace
  )
  {
    typedef vector<point>::const_iterator __iterator;
    __iterator __i = __po.begin();
    __iterator __j = __i;
    ++__i;
    for(; __i != __po.end(); ++__i, ++__j)
    {
      if(check_is_transport(__map.at(__j->x, __j->y)))
      { analyze_point_pos(__mapping.find(*__j)->second, *__i, __trace);}
      else
      { analyze_point_pos(*__j, *__i, __trace);}
    }
    return;
  }

}
