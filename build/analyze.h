
#ifndef __PUZZ_ANALYZE__
#define __PUZZ_ANALYZE__

#include"constant.hpp"
#include"matrix.hpp"
#include"structs.hpp"
#include"keyboard.h"
#include<map>

namespace game
{
  void analyze_point_trace(
    const matrix<base_type>& __map,
    const std::map<point, point>& __mapping,
    const vector<point>& __po,
    vector<keyboard::keyboard_mapping>& __trace
  );
}

#endif // ! __PUZZ_ANALYZE__
