#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;

unordered_set<string> findWikiLinks(const string& page_html);
bool valid(string link);

int main() {
    /* TODO: Write code here! */
    string filename = "";
    std::cout << "Please input filename:";
    std::cin >> filename;

    string filepath = "D:\\Major\\Course_Lab\\CS106L Winter 2018 Standard C++ Programming\\02_WikiRacerLinksA\\WikiRacerLinks\\res\\" + filename;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << endl;
        return 1;
    }
    string page_html = "";
    string line = "";
    while (std::getline(file, line)) {
        page_html += line;
    }
	unordered_set<string> links =  findWikiLinks(page_html);

    for (const auto& name : links) {
        std::cout << name << endl;
    }
}

bool valid(string link) {
    if (std::all_of(link.begin(), link.end(), [](const char ch) {return ch != '#' && ch != ':'; })) {
        return true;
    }
    else {
        return false;
    }
}

unordered_set<string> findWikiLinks(const string& page_html)
{
    unordered_set<string> links;

    std::string start_string = "<a href=\"/wiki/";
    std::string end_string = "\"";
    
    auto start = page_html.begin();

    while (start != page_html.end()) {
		start = std::search(start, page_html.end(), start_string.begin(), start_string.end());

        if (start == page_html.end()) {
            return links;
        }

	    start += start_string.length();

	    auto end = std::search(start, page_html.end(), end_string.begin(), end_string.end());


        if (end == page_html.end()) {
            return links;
        }

        std::string result(start, end);

        start = end;

        if (valid(result)) {
            links.insert(result);
        }
    }
    return links;
}
