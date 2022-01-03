/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    string line;
    ifstream infile(filename);
    if (infile.is_open()) {
        while (getline(infile,line)) {
            string temp = line;
            std::sort(temp.begin(), temp.end());
            dict[temp].push_back(line);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto str: words) {
    	string word = str;
    	std::sort(word.begin(), word.end());
    	dict[word].push_back(str);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string str = word;
    std::sort(str.begin(), str.end());
    if (dict.find(str) == dict.end() || dict.at(str).size() == 1) {
    	return vector<string>();
    }
    return dict.at(str);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for (auto vect: dict)
    	if (vect.second.size() > 1) ret.push_back(vect.second);
    return ret;
}
