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

#include <catch2/catch.hpp>
#include <try_out/point_checker.hpp>

#include <vector>
#include <cmath>

TEST_CASE("Test for point checker", "[]")
{
  SECTION("Test for distance matrix computation")
  {
    PointChecker point_checker;
    point_checker.add_point(1, 1);
    point_checker.add_point(2, 2);
    point_checker.add_point(3, 3);
    std::vector<std::vector<double>> result = point_checker.find_distance_matrix();
    REQUIRE(result.size() == 3);
    REQUIRE(result[0].size() == 3);
    REQUIRE(result[1].size() == 3);
    REQUIRE(result[2].size() == 3);
    REQUIRE(result[0][0] == 0);
    REQUIRE(std::round(result[0][1] - 1.4142135624) == 0);
    REQUIRE(std::round(result[0][2] - 2.8284271247) == 0);
    REQUIRE(std::round(result[1][2] - 1.4142135624) == 0);
    REQUIRE(result[1][1] == 0);
    REQUIRE(std::round(result[1][2] - 1.4142135624) == 0);
    REQUIRE(std::round(result[2][0] - 2.8284271247) == 0);
    REQUIRE(std::round(result[2][1] - 1.4142135624) == 0);
    REQUIRE(result[2][2] == 0);
  }
}
