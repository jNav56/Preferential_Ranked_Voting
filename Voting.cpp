// -----------
// Voting.c++
// -----------

// --------
// includes
// --------

#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

#include "Voting.hpp"

using namespace std;

#define MAX_NUMBER_OF_CASES 100
#define MAX_NUMBER_OF_CANDIDATES 20
#define MAX_NUMBER_OF_BALLOTS 1000

int candidate_num_of_votes[MAX_NUMBER_OF_CANDIDATES];
int ballots_and_all_choices[MAX_NUMBER_OF_BALLOTS][MAX_NUMBER_OF_CANDIDATES];
string candidate_names[MAX_NUMBER_OF_CANDIDATES];

void redistribute_votes(vector<int> losers, vector<int> ballots_candidate_has[], int min) {
    // Let's redistribute the loser votes
    for(int i = 0; i < (int)losers.size(); i++) {
                
        vector<int> ballots = ballots_candidate_has[losers.at(i)];
                
        for(int j = 0; j < min; j++) {
                    
            int ballot_ID = ballots.at(j);
            int index_on_ballot = 0;
                    
            int next_candidate = ballots_and_all_choices[ballot_ID][index_on_ballot];
            next_candidate--;
                    
            while(candidate_num_of_votes[next_candidate] == -1) {
                index_on_ballot++;
                next_candidate = ballots_and_all_choices[ballot_ID][index_on_ballot];
                next_candidate--;
            }
                         
            candidate_num_of_votes[next_candidate]++;
            ballots_candidate_has[next_candidate].push_back(ballot_ID);
        }
    }
}

string get_winner(int num_candidates, int n) {
    
    string result = "";
    int ballots_to_win = (n >> 1) + 1;
        
    // Array to hold the number of votes each candidate has
    for(int i = 0; i < num_candidates; i++) {
        candidate_num_of_votes[i] = 0;
    }
        
    // Keep track of the highest number of votes and least number of votes
    int max = 0;
    int min = 1001;
        
    // Array holds the specific ballots each candidate has
    vector<int> *ballots_candidate_has = new vector<int>[num_candidates];
        
    // Fill in number of votes and ballot IDs each candidate has at first
    for (int i = 0; i < n; i++) {
        int candidate_at_index = ballots_and_all_choices[i][0];
            
        // Increase number of votes to candidate and add ballot id
        candidate_num_of_votes[candidate_at_index - 1]++;
        ballots_candidate_has[candidate_at_index - 1].push_back(i);
    } 
        
    // Vector that contains the losers of each round
    vector<int> losers;
        
    while(true) {
        
        // Go through eligible candidates and get their number of votes
        for(int i = 0; i < num_candidates; i++) {
            int total_votes = candidate_num_of_votes[i];
                
            if(total_votes != -1) {
                    
                if(total_votes > max)
                    max = total_votes;
                    
                if(total_votes < min)
                    min = total_votes;
            }
        }
            
        // If there is a winner(s) we get them and save them to result 
        if(max >= ballots_to_win || min == max) {
            for(int i = 0; i < num_candidates; i++) {
                if(candidate_num_of_votes[i] == max) {
                    result += candidate_names[i] + "\n";
                }
            }
            return result;
        }
            
        // There are no winners so lets get and eliminate the losers
        for (int i = 0; i < num_candidates; i++) {   
            if (candidate_num_of_votes[i] == min) {
                losers.push_back(i);
                candidate_num_of_votes[i] = -1;
            }
        }
        
        redistribute_votes(losers, ballots_candidate_has, min);
            
        losers.clear();
            
        max = 0;
        min = 1001;
    }
    return result;
}

int fill_ballot_info(istream& sin, int num_candidates) {
    string s;
    int n = 0;
    // We will fill the ballot vector of each candidate
    while (getline(sin, s)) { // I'M ASSUMING THIS STOPS AT A EMPTY NEWLINE
            
        if(s.empty()) {
            break;
        }
            
        istringstream sin(s);
        for (int i = 0; i < num_candidates; i++) {
            int j;
            sin >> j;
            ballots_and_all_choices[n][i] = j;
        }
        n++;
    }
    
    return n;
}

void fill_candidate_names(istream& sin, int num_candidates) {
    string s;
    
    // Fill the candidate array with the number of candidates
    for(int i = 0; i < num_candidates; i++) {
        getline(sin, s);

        candidate_names[i] = s;
    }
}

int get_number_of_candidates (const string& s) {
    istringstream sin(s);
    int i;
    sin >> i;
    return i;
}

int get_number_of_cases(const string& s) {
    istringstream sin(s);
    int i;
    sin >> i;
    return i;
}

// -------------
// voting_solve
// -------------

void voting_solve(istream& sin, ostream& sout) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string s;
    
    getline(sin, s);
    int cases = get_number_of_cases(s);
    
    getline(sin, s);
    for(int i = 0; i < cases; i++) {
        
        getline(sin, s);
        int num_candidates = get_number_of_candidates(s);
        
        fill_candidate_names(sin, num_candidates);

        int num_of_ballots = fill_ballot_info(sin, num_candidates);
        
        string result = get_winner(num_candidates, num_of_ballots);
        sout << result;
        
        if(i + 1 != cases) {
            sout << endl;
        }
        
    }
}
