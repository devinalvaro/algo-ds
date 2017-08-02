/* Trie for lowercase letters (a - z) */

#include <string>
#include <vector>

using namespace std;

class Trie
{
private:
    vector<vector<int>> trie;
    vector<int> occurence;
    int last_index;

public:
    Trie()
    {
        trie.assign(300300, vector<int>(26, -1));
        occurence.assign(300300, 0);

        last_index = 25; // trie[0...25] are the roots (a - z)
    }

    void insert(string word)
    {
        size_t index = word[0] - 'a';

        for (size_t i = 1; i < word.size(); i++) {
            int ascii = word[i] - 'a';

            if (trie[index][ascii] == -1) {
                trie[index][ascii] = ++last_index;
            }
            index = trie[index][ascii];
        }

        occurence[index]++;
    }

    int search(string word)
    {
        int index = word[0] - 'a';

        for (size_t i = 1; i < word.size(); i++) {
            int ascii = word[i] - 'a';

            if (trie[index][ascii] == -1) {
                return 0;
            }
            index = trie[index][ascii];
        }

        return occurence[index];
    }
};
