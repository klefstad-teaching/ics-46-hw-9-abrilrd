#include "ladder.h"

void error(string word1, string word2, string msg){cout << word1 << " " << word2 << ": " << msg;}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (str1.size() - str2.size()>0)
        return str1.size() - str2.size() < d;
    return str2.size() - str1.size() < d;
}

bool is_adjacent(const string& word1, const string& word2){
    if (word1.size() != word2.size()) return false;
    int diff_count = 0;
    
    for (int i = 0; i < word1.size(); ++i) {
        if (word1[i] != word2[i])
            diff_count++;
            //if (diff_count > 1) return false;
    }
    
    return diff_count == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited = word_list;
    visited.insert(begin_word);
    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(const string& word: word_list) {
            if (is_adjacent(last_word, word)){
                    if (visited.find(word) == visited.end() && is_adjacent(last_word, word)){
                        visited.insert(word);
                        vector<string> new_ladder = ladder;
                        if(word == end_word)
                            return new_ladder;
                        ladder_queue.push(new_ladder);
                    }

            }
        }
    }
    error(begin_word, end_word, "no ladder found");
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file) {
        error("","","Error opening file!");
        return;
    }
    string word;
    while (file >> word)
        word_list.insert(word);
}

void print_word_ladder(const vector<string>& ladder){
    for(string word: ladder)
        cout << word << " ";
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    /*
    ladder = generate_word_ladder("cat", "dog", word_list);
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    */
}