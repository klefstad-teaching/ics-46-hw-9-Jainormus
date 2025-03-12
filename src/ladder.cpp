#include "ladder.h"
#include <cmath>

void error(string word1, string word2, string msg) {
    cout << msg << word1 << " " << word2 << endl; 
}

int find_edit_distance(const string& word1, const string& word2) {
        int length_cmp = word1.size() - word2.size();
    int edit_amount = 0;
    int other_index = 0;
    for (int i = 0; i < word1.size() && other_index < word2.size();) {
        if (edit_amount > 1) {return false;}
        if (word1[i] == word2[other_index]) {
            ++i;
            ++other_index;
        } else if (length_cmp < 0) {
            ++edit_amount;
            ++other_index;
            ++length_cmp;
        } else if (length_cmp > 0) {
            ++edit_amount;
            ++i;
            --length_cmp;
        } else {
            ++i;
            ++other_index;
            ++edit_amount;
        }
    }
    edit_amount += (length_cmp > 0) ? length_cmp : length_cmp * -1;
    return edit_amount;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    return find_edit_distance(str1, str2) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return find_edit_distance(word1, word2) == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    vector<string> start;
    start.push_back(begin_word);
    ladder_queue.push(start);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (auto word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (!visited.contains(word)) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
                
            }
        }
    }
    vector<string> empty_ladder;
    return empty_ladder;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; (in >> word);) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (auto i : ladder) {
        cout << i << ' ';
    }
}

// void verify_word_ladder();
