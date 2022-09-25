// Copyright 2022 [No Owner].
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TRY_OUT__POINT_CHECKER_HPP_
#define TRY_OUT__POINT_CHECKER_HPP_

#include <try_out_utils/point.hpp>
#include <memory>
#include <cmath>
#include <vector>

class PointChecker
{
private:
  std::vector<Point *> points_;

public:
  void add_point(double x, double y);
  std::vector<std::vector<double>> find_distance_matrix();
};

#endif  // TRY_OUT__POINT_CHECKER_HPP_
