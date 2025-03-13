#include "ladder.h"
#include <cmath>

void error(string word1, string word2, string msg) {
    cout << msg << word1 << " " << word2 << endl; 
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int length_cmp = str1.size() - str2.size();
    int edit_amount = 0;
    int other_index = 0;
    for (int i = 0; i < str1.size() && other_index < str2.size();) {
        if (edit_amount > 1) {return false;}
        if (str1[i] == str2[other_index]) {
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
    return edit_amount <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    vector<string> start;
    start.push_back(begin_word);
    ladder_queue.push(start);
    set<string> visited;
    visited.insert(begin_word);
    vector<string> empty_ladder;
    if (begin_word == end_word) {return empty_ladder;}
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

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}