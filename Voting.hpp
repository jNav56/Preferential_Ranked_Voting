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

// -------------
// get_candidate_names - Helper Method for Unit Testing
// -------------

/**
 * Returns a string of the candidate names
 * @param num_candidates int
 * @return a string
 */
string get_candidate_names(int);

// -------------
// get_ballot_info - Helper Method for Unit Testing
// -------------

/**
 * Returns a string of the all ballots
 * @param num_ballots int
 * @param num_candidates int
 * @return a string
 */
string get_ballot_info(int, int);

// -------------
// get_candidate_num_votes - Helper Method for Unit Testing
// -------------

/**
 * Returns a string of the candidates and their votes
 * @param num_candidates int
 * @return a string
 */
string get_candidate_num_votes(int);

// -------------
// call_redistribute - Helper Method for Unit Testing
// -------------

/**
 * Calls redistribute_votes method and passes in given parameters
 * @param an istream
 * @param num_candidates int
 * @param losers int vector
 * @param ballots_candidate_has int vector array
 * @param min int
 * @return a string
 */
string call_redistribute(int, vector<int>, vector<int>[], int);

// -------------
// call_assign_candidates - Helper Method for Unit Testing
// -------------

/**
 * Calls assign_candidates_as_losers method and passes in given parameters
 * @param losers int vector
 * @param num_candidates int
 * @param min int
 * @return a string
 */
string call_assign_candidates(vector<int>, int, int);

// ------------
// is_there_a_winner
// ------------

/**
 * Verify if there is a winner
 * @param result string
 * @param max int
 * @param ballots_to_win int
 * @param min int
 * @param num_candidates int
 * @return a bool
 */
bool is_there_a_winner(string&, int, int, int, int);

// ------------
// assign_candidates_as_losers
// ------------

/**
 * Redistribute votes from losers to next eligible candidates
 * @param losers int vector
 * @param num_candidates int
 * @param min int
 */
void assign_candidates_as_losers(vector<int>&, int, int);

// ------------
// redistribute_votes
// ------------

/**
 * Redistribute votes from losers to next eligible candidates
 * @param losers int vector
 * @param ballots_candidate_has array of int vector
 * @param min int
 */
void redistribute_votes(vector<int>&, vector<int>[], int);

// ------------
// get_winner
// ------------

/**
 * Determine the winner from a set of votes
 * @param num_candidates int
 * @param n int=
 * @return a string
 */
string get_winner(int, int);

// ------------
// fill_ballot_info
// ------------

/**
 * Take input and organize ballots with their rankings
 * @param sin istream
 * @param num_candidates int
 * @return an int
 */
int fill_ballot_info(istream&, int);

// ------------
// fill_candidate_names
// ------------

/**
 * Take input and retrieve names of candidates
 * @param sin istream
 * @param num_candidates int
 */
void fill_candidate_names(istream&, int);

// ------------
// get_number_of_candidates
// ------------

/**
 * Take input and retrieve number of candidates
 * @param sin istream
 * @return an int
 */
int get_number_of_candidates(const string&);

// ------------
// get_number_of_cases
// ------------

/**
 * Take input and retrieve number of case
 * @param sin istream
 * @return an int
 */
int get_number_of_cases(const string&);

// ------------
// voting_solve
// ------------

/**
 * @param an istream
 * @param an ostream
 */
void voting_solve(istream&, ostream&);

#endif // Voting_h
