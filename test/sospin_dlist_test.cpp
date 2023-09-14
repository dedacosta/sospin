// SOSpin Library
// Copyright (C) 2015,2023 SOSpin Project
//
//   Authors:
//     David da Costa (david.dacosta@dlr.de)
//
// ----------------------------------------------------------------------------
// This file is part of SOSpin Library.
//
// SOSpin Library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or any
// later version.
//
// SOSpin Library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SOSpin Library.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

//       sospin_dlist_test.cpp created on 11/09/2023

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <sstream>

#include <sospin/dlist.h>
#include <sospin/index.h>

using namespace sospin;
using namespace std;
using ::testing::ContainsRegex;

TEST(SospinDListTest, CreationOperators) {
	DList b1 = DList(0, newIdx(1));
	DList b2 = DList(0, newIdx(2));
	DList list = b1*b2*b2*b1;
	ostringstream os;
	os << list;
	string oss = os.str();
	EXPECT_EQ(4, list.numBs());
	EXPECT_THAT(os.str(), ContainsRegex("\\+ b\\([0-9]\\) (\\* b\\([0-9]\\))* \\* b\\([0-9]\\)")) << "Not The expected expression: " + oss;
}
