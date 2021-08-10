#include <string>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_PHONE_BOOK_LEN = 1000000;
const int MAX_PHONE_NUMBER_LEN = 20;

class Trie;
Trie* newTrie();

class Trie {
public:
    Trie* nodes[10];
    bool isBranchNode;
    bool isTerminalNode;

    bool checkValidationAndAdd(const char* s, int len) {
        if (len == 0) isTerminalNode = true;
        else isBranchNode = true;

        if (isTerminalNode) return !isBranchNode;

        char i = *s - '0';

        if (!nodes[i])
            nodes[i] = newTrie();

        return nodes[i]->checkValidationAndAdd(s + 1, len - 1);
    }
};

Trie nodes[MAX_PHONE_BOOK_LEN * MAX_PHONE_NUMBER_LEN + 1];
int nNodes = 0;

Trie* newTrie() {
    return &(nodes[nNodes++]);
}

bool solution(vector<string> phone_book) {
    Trie* trie = newTrie();

    for (auto phoneNumber : phone_book) {
        if (!trie->checkValidationAndAdd(phoneNumber.c_str(), phoneNumber.size())) {
            return false;
        }
    }
    return true;
}
