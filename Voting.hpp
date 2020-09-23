// ---------
// Voting.h
// ---------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <iterator> // istream_iterator
#include <vector>

using namespace std;

// // ------------
// // redistribute_votes
// // ------------

// /**
//  * Redistribute votes from losers to next eligible candidates
//  * @param ballots_and_all_choices int matrix
//  * @param candidate_num_of_votes int array
//  * @param losers int vector
//  * @param ballots_candidate_has int vector
//  * @param min int
//  */
// void redistribute_votes(int (*)[20], int*, vector<int>, vector<int>*, int);

// // ------------
// // get_winner
// // ------------

// /**
//  * Determine the winner from a set of votes
//  * @param ballots_and_all_choices matrix
//  * @param num_candidates int
//  * @param n int
//  * @param candidate_names string array
//  * @return a string
//  */
// string get_winner(int (*)[20], int, int, string*);

// // ------------
// // fill_ballot_info
// // ------------

// /**
//  * Take input and organize ballots with their rankings
//  * @param sin istream
//  * @param ballots_and_all_choices int matrix
//  * @param num_candidates int
//  * @return an int
//  */
// int fill_ballot_info(istream&, int (*)[20], int);

// // ------------
// // fill_candidate_names
// // ------------

// /**
//  * Take input and retrieve names of candidates
//  * @param sin istream
//  * @param candidate_names string array
//  * @param num_candidates int
//  * @return an int
//  */
// int fill_candidate_names(istream&, string*, int);

// // ------------
// // get_number_of_candidates
// // ------------

// /**
//  * Take input and retrieve number of candidates
//  * @param sin istream
//  * @return an int
//  */
// int get_number_of_candidates(const string&);

// // ------------
// // get_number_of_cases
// // ------------

// /**
//  * Take input and retrieve number of case
//  * @param sin istream
//  * @return an int
//  */
// int get_number_of_cases(const string&);

/**
 * @param an istream
 * @param an ostream
 */
void voting_solve (istream&, ostream&);

#endif // Voting_h
