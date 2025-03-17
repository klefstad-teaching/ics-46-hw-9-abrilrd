#include "ladder.h"

void error(string word1, string word2, string msg){cout << word1 << " " << word2 << ": " << msg << endl;}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int counter = 0;
    int strlen1 = str1.size();
    int strlen2 = str2.size();
    
    /*
    3 cases
    1st is that size1 - size2 == 0 (same size)
    2nd is that size1 is + or - 1 of size 2 or vice versa (1 insert or delete)
    3rd is the 2nd case BUT the insertion is at the end (so you made it to the end with no flags)
    */
    int diff = abs(strlen1 - strlen2);
    if (diff > d) return false;

    if (diff == 0){
        for (int i = 0; i < strlen1; ++i) {
            if (str1[i] != str2[i]){
                counter++;
                if (counter > d) return false;
            }
        }
    }
    else{
        //int size = min(strlen1, strlen2);
        for (int i = 0, j = 0; i < strlen1 && j < strlen2;) {
            if (str1[i] != str2[j]){
                counter++;
                if (counter > d) return false;
                if(strlen1 > strlen2) i++;
                else j++;
            }
            else {
                i++;
                j++;
            }
        }
        //counter += diff;
    }
    //diff_count += std::abs(static_cast<int>(str1.size()) - static_cast<int>(str2.size()));
    
    return counter <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for(const string& word: word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if(word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    //error(begin_word, end_word, "No word ladder found.");
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
    if(!ladder.empty()){
        cout << "Word ladder found: ";
        for(string word: ladder)
            cout << word << " ";
        cout << endl;
    }
    cout << "No word ladder found." << endl;
    
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    //ladder = generate_word_ladder("", "dog", word_list);
    print_word_ladder(generate_word_ladder("marty", "curls", word_list));
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    
}