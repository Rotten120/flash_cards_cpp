#include <iostream>
#include <stack>
#include <map>

using namespace std;

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
        map<int, Card> set;
        
        bool idExists(int id) {
            map<int, Card>::iterator iter;
            iter = set.find(id);
            return (iter != set.end());
        }
        
    public:
        FlashCardSet() {
            set[-1] = Card("null question", "null answer");
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
        void rmv(int id) {
            set.erase(id);
        }
        
        void print() {
            for(auto&pair : set) {
                if (pair.first == -1) continue;
                cout << "id" << pair.first << endl;
                pair.second.print();
            }
        }
};

int main(void) {
    FlashCardSet cards;
    Card a("a", "b");
    Card b("c", "d");
    Card c("e", "f");
    cards.add(a);
    cards.add(b);
    cards.rmv(1);
    cards.add(c);
    cards.add(b);
    cards.print();
    return 0;   
}
