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

#include <try_out/point_checker.hpp>

#include <vector>

void PointChecker::add_point(double x, double y)
{
  try_out_utils::Point * point = new try_out_utils::Point(x, y);
  this->points_.push_back(point);
}

std::vector<std::vector<double>> PointChecker::find_distance_matrix()
{
  std::vector<std::vector<double>> overall_vect;
  for (unsigned int i = 0; i < this->points_.size(); i++) {
    std::vector<double> inner_vect;
    for (unsigned int j = 0; j < this->points_.size(); j++) {
      double x_compute =
        (this->points_[j]->get_x() - this->points_[i]->get_x()) *
        (this->points_[j]->get_x() - this->points_[i]->get_x());
      double y_compute =
        (this->points_[j]->get_y() - this->points_[i]->get_y()) *
        (this->points_[j]->get_y() - this->points_[i]->get_y());
      double distance = std::sqrt(x_compute + y_compute);
      inner_vect.push_back(distance);
    }
    overall_vect.push_back(inner_vect);
  }
  return overall_vect;
}

int main()
{
  PointChecker point_checker;
  point_checker.add_point(5, 5);
  return 0;
}
