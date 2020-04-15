#include <iostream>
#include <vector>

using std::vector;
using std::string;

struct Node {
    Node(): pred(nullptr), terminal(false), name(""){
        next.assign(26, nullptr);
    };

    vector<Node*> next;
    Node* pred;
    bool terminal;
    string name;
};

class Bor {
public:
    Node names, numbers;
    Bor() {
        names = Node();
        numbers = Node ();
    };
    ~Bor(){}

    void add_word(string& word, int type, int dict_pos, string& info) {
        Node* cur_vert;
        if (type == 0){
            cur_vert = &names;
        }
        else {
            cur_vert = &numbers;
        }
        for (int i = 0; i < word.length(); ++i) {
            char current_symbol = word[i];
            int index = (int)current_symbol - dict_pos ;
            //std::cout << index << std::endl;
            //std::cout << current_symbol << std::endl;
            if (cur_vert->next[index] == nullptr) {
                (cur_vert->next[index]) = new Node();
                cur_vert->next[index]->pred = cur_vert;
                if (i == word.length() - 1) {
                    cur_vert->next[index]->terminal = true;
                    cur_vert->name = info;
                    //std::cout << cur_vert->name <<"-name" << std::endl;
                }
            }
            
            cur_vert = cur_vert->next[index];
        }
    };
    
    void add_contact(string& name, string& number) {
        add_word(name, 0, 'a', number);
        add_word(number, 1, '0', name);
    
    };
    
    void find_by_name(const string& s) {
        Node *cur_vert = &names;
        for (int i = 0; i < s.length(); i++) {
            cur_vert = cur_vert->next[s[i] - 'a'];
            if (cur_vert == nullptr) {
                std::cout << "имя не найдено";
                return;
            }
        }
        
        std::cout << cur_vert->pred->name ;
    }
    
    void find_by_number(const string& s) {
        Node *cur_vert = &numbers;
        for (int i = 0; i < s.length(); i++) {
            cur_vert = cur_vert->next[s[i] - '0'];
            if (cur_vert == nullptr) {
                std::cout << "телефон не найден";
                return;
            }
        }
        
        std::cout << cur_vert->pred->name ;
    }
    
    void find_by_notcompl_number(const string& s) {
        Node *cur_vert = &numbers;
        for (int i = 0; i < s.length(); i++) {
            cur_vert = cur_vert->next[s[i] - '0'];
            if (cur_vert == nullptr) {
                std::cout << "телефонов не найдено";
                return;
            }
        }
        string cur_str = s;
        write(cur_vert, cur_str);
    }
    
    void write(Node *v, string& cur_str) {
        if (v->terminal){
            std::cout << cur_str << v->pred->name << std::endl;
        }
        
        for (int i = 0; i < 26; i++) {
            if (v->next[i] != nullptr) {
                cur_str.push_back('0' + i);
                write(v->next[i], cur_str);
                cur_str.pop_back();
            }
        }
    }
    
    void find_number_with_stars(const string& s) {
        Node *cur_vert = &numbers;
        string cur_str = "";
        for (int i = 0; i < s.length(); i++) {
            if(s[i] == '*'){
                for (int j = 0; j < 10; j++) {
                    if (cur_vert->next[j] != nullptr) {
                        cur_str.push_back('0' + j);
                        recurs_find(cur_vert, s, i, cur_str);
                        cur_str.push_back('0' + j);
                    }
                }
            }
            cur_str.push_back(s[i]);
        }
        
    }
    
    void recurs_find (Node *cur_vert, const string& s, int i, string& cur_str){
        if (cur_vert->terminal){
            std::cout << cur_str << cur_vert->pred->name << std::endl;
        }
        
        for (i = i+1; i < s.length(); i++) {
            if(s[i] == '*'){
                for (int j = 0; j < 10; j++) {
                    if (cur_vert->next[j] != nullptr) {
                        cur_str.push_back('0' + j);
                        recurs_find(cur_vert, s, i, cur_str);
                        cur_str.push_back('0' + j);
                    }
                }
            }
            cur_str.push_back(s[i] );
            cur_vert = cur_vert->next[s[i] - '0'];
            if (cur_vert == nullptr) {
                std::cout << "телефонов не найдено" << cur_str;
                return;
            }
        }
        
        std::cout << cur_vert->pred->name ;
    }
    
};

int main() {
    Bor contact_book;
    string name = "me";
    string number = "79655724542";
    
    contact_book.add_contact(name, number);
    contact_book.find_by_notcompl_number("7");
    //contact_book.find_number_with_stars("796557245*2");
    
}
