// ---------------
// TestVoting.c++
// ---------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iterator> // istream_iterator
#include <sstream>  // istringtstream, ostringstream
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "Voting.hpp"

using namespace std;

// ----
// voting_solve
// ----

TEST(VotingFixture, solve0) {
    string names("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan");
    string ballots("\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    
    stringstream ss;
    ss << names << ballots;
    string whole = ss.str();

    istringstream iss(whole);
    ostringstream oss;
    voting_solve(iss, oss);
    ASSERT_EQ("John Doe\n", oss.str());}


TEST(VotingFixture, solve1) {

    string names_0("1\n\n15\nAsui\nKatsuki\nTenya\nKirishima\nOchako");
    string names_1("\nIzuku\nDenki\nShoto\nFumikage\nMina\nKouji");
    string names_2("\nMashirao\nMomo\nTooru\nKyouka");

    string ballot_0("\n11 5 1 8 13 15 14 12 2 7 10 4 6 9 3");
    string ballot_1("\n3 5 14 1 4 9 11 10 15 7 12 8 13 2 6");
    string ballot_2("\n3 6 9 2 14 1 13 12 5 11 7 10 8 4 15");
    string ballot_3("\n11 5 4 6 12 1 9 14 7 8 13 15 3 2 10");
    string ballot_4("\n5 14 8 4 9 7 6 2 12 10 13 1 15 3 11");
    string ballot_5("\n6 12 3 10 4 2 7 9 8 5 1 15 11 13 14");
    string ballot_6("\n4 5 11 15 1 7 12 6 14 8 3 13 10 9 2");
    string ballot_7("\n2 8 6 9 5 15 7 12 11 10 1 3 13 14 4");
    string ballot_8("\n6 13 2 15 11 4 10 5 12 9 1 8 3 14 7");
    string ballot_9("\n9 12 15 11 1 7 8 14 5 6 4 10 2 13 3");
    string ballot_10("\n4 2 5 14 6 3 11 12 15 1 9 10 13 8 7");
    string ballot_11("\n11 5 13 4 7 9 3 12 10 8 6 2 15 14 1");
    string ballot_12("\n1 4 12 10 3 6 7 11 13 8 5 2 9 15 14");
    string ballot_13("\n11 15 7 5 13 4 9 14 2 1 6 12 3 10 8");
    string ballot_14("\n11 10 5 3 14 4 13 6 15 8 2 12 9 7 1");
    string ballot_15("\n13 5 6 7 15 1 14 8 10 11 12 2 3 9 4");
    string ballot_16("\n14 5 7 8 9 6 15 2 10 13 4 11 12 3 1\n");

    stringstream ss;
    ss << names_0 << names_1 << names_2;
    ss << ballot_0 << ballot_1 << ballot_2 << ballot_3 << ballot_4 << ballot_5;
    ss << ballot_6 << ballot_7 << ballot_8 << ballot_9 << ballot_10;
    ss << ballot_11 << ballot_12 << ballot_13 << ballot_14 << ballot_15;
    ss << ballot_16;
    string whole = ss.str();

    istringstream iss(whole);
    ostringstream oss;
    voting_solve(iss, oss);
    ASSERT_EQ("Izuku\n", oss.str());}

// -------------
// get_number_of_cases
// -------------

TEST(VotingFixture, cases0) {
    ASSERT_EQ(get_number_of_cases("31"), 31);
}


TEST(VotingFixture, cases1) {
    istringstream iss("42\n\n3\n");
    string t;
    getline(iss, t);
    ASSERT_EQ(get_number_of_cases(t), 42);
}
