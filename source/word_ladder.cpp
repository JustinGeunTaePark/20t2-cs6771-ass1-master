#include "comp6771/word_ladder.hpp"
#include <range/v3/algorithm.hpp>
#include <range/v3/functional.hpp>
#include <range/v3/range.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// Written by Justin Geuntae Park (z5060336)
// The following code is a implementation of a word ladder algorthim that
// finds the shortest path from one word to another by changing only one letter at a time.
// It uses a breath first search (BFS) where as letters are changed, if the word is valid
// it is put into a vector of strings as a potential solution then after all combinations are made
// the vector is sorted alphabetically. Then the words are used to extend the ladder,
// if doesn't equal the goal word then it is put back into the queue otherwise it is
// added to the final return vector. It has sets to keep track of whether a word has been
// visited as well as keep track of words that have been found at the same depth. Words of the
// same depth count as valid words for other ladders. If a solution is found then other ladders
// that have a depth greater than the solution are removed.
namespace word_ladder {
	auto generate(std::string const& from,
	              std::string const& to,
	              absl::flat_hash_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		std::queue<std::vector<std::string>> q; // Used to keep track of potential solutions
		std::vector<std::vector<std::string>> ret; // Contains all the solutions of "from" to "to"
		absl::flat_hash_set<std::string> h; // Words that have been visitied before
		absl::flat_hash_set<std::string> depth_words; // Words that exists at the same depth
		std::vector<std::string> word_list; // Words that have been found as potential solutions
		auto min = 0; // Depth of the most optimal solution
		auto depth = 1; // Depth of the current search

		// Inserts the first word into the queue
		h.insert(from);
		std::vector<std::string> v;
		v.push_back(from);
		q.push(v);

		// Until there is no more potential solutions
		while (!q.empty()) {
			std::vector<std::string> v2 = q.front();
			std::string look = v2.back();
			if (ranges::distance(v2) > depth) {
				depth += 1;
				depth_words.clear();
			}
			q.pop();
			// If you reach a new depth then remove
			// words that have been found in the preivous
			// depth
			if (min != 0 && ranges::distance(v2) > min) {
				continue;
			}
			// Checks all positions of a string with all different alphabetical
			// combinations to see if a word exists that hasn't been visited before
			// however if a word has been visited before but is at the same depth
			// then it still counts as a potential solution
			for (auto i = std::string::size_type{0}; i < look.size(); ++i) {
				char back = look[i];
				for (char c = 'a'; c <= 'z'; c++) {
					look[i] = c;
					if (lexicon.contains(look) && (!h.contains(look) || depth_words.contains(look))) {
						h.insert(look);
						depth_words.insert(look);
						word_list.push_back(look);
					}
				}
				look[i] = back;
			}
			// Sorts the potential solutions according to alphabetical order
			ranges::sort(word_list, ranges::less{});
			// From the words that have been found, add that word
			// to the partial solution vector back to the queue or to the return vector
			// depending on whether the word has been found or not
			for (std::string& answer : word_list) {
				std::vector<std::string> ladder = v2;
				ladder.push_back(answer);
				if (answer != to) {
					q.push(ladder);
				}
				else {
					if (min == 0 || ranges::distance(v2) == min) {
						min = depth; // Updates the minimal solution depth
						ret.push_back(ladder);
					}
				}
			}
			word_list.clear();
		}
		return ret;
	}

} // namespace word_ladder