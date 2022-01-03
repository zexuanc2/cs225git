/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    string line;
    ifstream infile(word_list_fname);
    //specify the working condition of the code 
    if (infile.is_open()) {
        while(getline(infile,line)) {
            if (line.size() == 5) {
                string a = line.substr(1, line.size() - 1);
                string b = line[0] + line.substr(2, line.size() - 1);
                if (d.homophones(line, a) && (d.homophones(line, b))) {
                    ret.push_back(tuple<string, string, string>(line, a, b));
                }
            }
        }
    }
    infile.close();
    return ret;
}
