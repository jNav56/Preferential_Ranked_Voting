// ---------------
// TestVoting.c++
// ---------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iterator> // istream_iterator
#include <sstream>  // istringtstream, ostringstream
#include <vector>

#include "gtest/gtest.h"

#include "Voting.hpp"

using namespace std;

// ----
// voting_solve
// ----

TEST(VotingFixture, solve) {
    istringstream iss("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    ostringstream oss;
    voting_solve(iss, oss);
    ASSERT_EQ("John Doe\n", oss.str());}

