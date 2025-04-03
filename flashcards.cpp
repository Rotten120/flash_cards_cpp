#include <iostream>
#include <stack>
#include <map>

using namespace std;

enum diffi {EASY = 1, MEDIUM = 2, HARD = 3};

class Card {
    private:
        diffi difficulty;
        string question;
        string answer;
    public:
        //constructors
        Card(const string q = "", const string a = "", const diffi d): question(q), answer(a), difficulty(d) {}
        
        //set-get functions
        string getQ() const {return question;}
        string getA() const {return answer;}
        diffi getD() const {return difficulty;}
        void setQ(const string q) {question = q;}
        void setA(const string a) {answer = a;}
        void setD(const diffi d) {difficulty = d;}
        
        void print() {
            cout << "Q: " << question << "\n" << "A: " << answer << "\n"  << "D: " << int(difficulty) << "\n" << endl;
        }
};

class FlashCardSet {
    private:
        //key will be the Card's ID
        map<int, Card> set;
        
        bool idExists(int id) {
            map<int, Card>::iterator iter;
            iter = set.find(id);
            return (iter != set.end());
        }
        
    public:
        FlashCardSet() {
            set[-1] = Card("null question", "null answer", EASY);
        }
        
        void add(const Card cardtoAdd) {
            int idx = 0;
            while(true) {
                if (!idExists(idx)) {
                    set[idx] = cardtoAdd;
                    return;
                }
                idx++;
            }
        }
        
        void rmv(const int id) {
            set.erase(id);
        }
        
        void edit(const int id, const string q, const string a, const diffi d) {
            set[id] = Card(q, a);
        }
        
        void edit(const int id, const Card card) {
            set[id] = card;
        }
        
        void print() {
            for(auto&pair : set) {
                if (pair.first == -1) continue;
                cout << "id" << pair.first << endl;
                pair.second.print();
            }
        }
        
        
        void review() {
            stack<Card> unread;
            stack<Card> read;
            
            for(auto& pair : set) {
                if (pair.first == - 1) continue;
                unread.push(pair.second);
            }
            
            while(true) {
                char cmd;
                unread.top().print();
                cin >> cmd;
                
                if (cmd == 'g' && !unread.empty()) {
                    Card val = unread.top();
                    unread.pop();
                    read.push(val);
                } else if (cmd == 'b' && !read.empty()) {
                    Card val = read.top();
                    read.pop();
                    unread.push(val);
                }
            }
        }
};

int main(void) {
    FlashCardSet cards;
    Card a("a", "b", EASY);
    Card b("c", "d", EASY);
    Card c("e", "f", EASY);
    cards.add(a);
    cards.add(b);
    cards.rmv(1);
    cards.add(c);
    cards.add(b);
    cards.edit(1, "haha", "lolol", HARD);
    cards.print();
    cards.review();
    return 0;   
}
