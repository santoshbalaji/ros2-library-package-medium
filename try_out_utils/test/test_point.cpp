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
#include <try_out_utils/point.hpp>

TEST_CASE("Test for point", "[]")
{
  SECTION("Test for point with object creation")
  {
    Point p(11, 10);
    REQUIRE(p.get_x() == 11);
    REQUIRE(p.get_y() == 10);
  }
}
