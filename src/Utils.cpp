#include "Utils.h"

#include <sstream>
#include <algorithm>

namespace Multipass{


  void Parse(int result[4], const std::string& input)
  {
    std::istringstream parser(input);
    parser >> result[0];
    for (int idx = 1; idx < 4; idx++)
    {
      parser.get(); //Skip period
      parser >> result[idx];
    }
  }

  bool IsVersionLess(std::string& one, std::string& two)
  {
    int parsedA[4], parsedB[4];
    Parse(parsedA, one);
    Parse(parsedB, two);
    return std::lexicographical_compare(parsedA, parsedA + 4, parsedB, parsedB + 4);
  }

}