#include <iostream>
#include <stack>
#include <map>

using namespace std;

enum level {EASY = 1, MEDIUM = 2, HARD = 3};

class Card {
    private:
        string question;
        string answer;
    public:
        //constructors
        Card(const string q = "", const string a = ""): question(q), answer(a) {}
        
        //set-get functions
        string getQ() const {return question;}
        string getA() const {return answer;}
        void setQ(const string q) {question = q;}
        void setA(const string a) {answer = a;}
        
        void print() {
            cout << "Q: " << question << "\n" << "A: " << answer << "\n" << endl;
        }
};

class FlashCardSet {
    private:
        //key will be the Card's ID
        map<int, Card> setEasy;
        map<int, Card> setMedium;
        map<int, Card> setHard;
        
        map<int, Card>* getPtr(level d) {
            map<int, Card>* setptr;
            switch(d) {
                case EASY: setptr = &setEasy; break;
                case MEDIUM: setptr = &setMedium; break;
                case HARD: setptr = &setHard; break;
            }
            return setptr;
        }
        
        bool idExists(int id, level d) {
            map<int, Card>* setptr = getPtr(d);
            map<int, Card>::iterator iter;
            iter = setptr->find(id);
            return (iter != setptr->end());
        }
        
    public:
        FlashCardSet() {
            setEasy[-1] = Card("null question", "null answer");
            setMedium[-1] = Card("null question", "null answer");
            setHard[-1] = Card("null question", "null answer");
        }
        
        void add(const Card cardtoAdd, level d) {
            map<int, Card>* setptr = getPtr(d);
    
            int idx = 0;
            while(true) {
                if (!idExists(idx, d)) {
                    (*setptr)[idx] = cardtoAdd;
                    return;
                }
                idx++;
            }
        }
        
        void rmv(const int id, level d) {
            map<int, Card>* setptr = getPtr(d);
            setptr->erase(id);
        }
        
        void set(const int id, const level d, const string q, const string a) {
            map<int, Card>* setptr = getPtr(d);
            (*setptr)[id] = Card(q, a);
        }
        
        void set(const int id, const level d, const Card card) {
            map<int, Card>* setptr = getPtr(d);
            (*setptr)[id] = card;
        }
        
        //prints all flashcard
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
    cards.set(1, "haha", "lolol");
    cards.print();
    cards.review();
    return 0;   
}
