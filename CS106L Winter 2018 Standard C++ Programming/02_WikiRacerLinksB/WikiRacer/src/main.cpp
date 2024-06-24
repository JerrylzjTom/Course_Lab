
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"


using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;

unordered_map<string, unordered_set<string>> existpages;

int numCommonLinks(const unordered_set<string>& curr_set, const unordered_set<string>& target_set) {
    auto search_fn = [&target_set] (const string& s) { return target_set.count(s); };
    return std::count_if(curr_set.begin(), curr_set.end(), search_fn);
}

/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */
vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: Fill in the findWikiLinks method in wikiscraper.cpp,
    //       then write this  function as per the handout.
    //
    //                Best of luck!
	WikiScraper scraper;
    
	const auto target_set = scraper.getLinkSet(end_page);

    auto cmpFn = [&](const vector<string>& left, const vector<string>& right) {
        unordered_set<string> left_set, right_set;
        if (existpages.find(left.back()) != existpages.end()) {
            left_set = existpages[left.back()];
        }
        else {
			left_set = scraper.getLinkSet(left.back());
            existpages[left.back()] = left_set;
        }
		if (existpages.find(right.back()) != existpages.end()) {
            right_set = existpages[right.back()];
        }
        else {
			right_set = scraper.getLinkSet(right.back());
			existpages[right.back()] = right_set;
        }
        return numCommonLinks(left_set, target_set) < numCommonLinks(right_set, target_set);
    };

	std::priority_queue<vector<string>, vector<vector<string>>,
        decltype(cmpFn)> ladderQueue(cmpFn);
    
    vector<string> ladder = {start_page};
    unordered_set<std::string> visited;
    visited.insert(start_page);

    ladderQueue.push(ladder);

    while (!ladderQueue.empty()) {
        vector<string> ladder = ladderQueue.top();

        cout << "{";
        for (auto& link : ladder) {
            cout << link << " ";
        }
        cout << "}" << endl;

        ladderQueue.pop();
        const string current_page = ladder.back();
        const auto current_set = scraper.getLinkSet(current_page);

        if (current_set.find(end_page) != current_set.end()) {
            ladder.push_back(end_page);
            return ladder;
        }

		auto start_time = std::chrono::high_resolution_clock::now();
        for (const auto& neighbor : current_set) {
            if (visited.find(neighbor) == visited.end()) {
				vector<string> copyed_ladder = ladder;
                copyed_ladder.push_back(neighbor);

				/*auto start_time = std::chrono::high_resolution_clock::now();*/

                ladderQueue.push(copyed_ladder);

                cout << "Updated: " << neighbor << " "
                    << ladderQueue.size() << " " << ladderQueue.top().back() << " " << endl;
    //            auto end_time = std::chrono::high_resolution_clock::now();
				//std::chrono::duration<double> elapsed = end_time - start_time;
				//std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

                visited.insert(neighbor);
            }
        }
	    auto end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end_time - start_time;
		std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    }

    return {};
}



int main() {
    auto ladder = findWikiLadder("Milkshake", "Gene");
    cout << endl;

    if(ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
        cout << "Ladder found:" << endl;

        for (auto& element : ladder) {
            cout << element << ", ";
        }
    }
    return 0;
}