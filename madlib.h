#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>

using namespace std;

class MadLib {
    public:
        MadLib(); // constructor
        ~MadLib(); // destructor

        string getName(int); // get name from list at specific pos 
        string getNoun(); // get noun from list
        string getAdjective(); // get adjective from list
        string getVerb(); // get verb from list
        string getAdverb(); // get adverb from list 

    private:
        void setDupesFalse(); // sets all dupe check arrays to false
        void fillInputVectors(); // reads data from input files
        int getIndex(vector<string>& arr, vector<bool>& arrBool); // get index to be used in public getters
        bool getIndexName(int); // overloaded getIndex checks ONLY randNames for dupes

        // input vectors
        vector<string> randNames;
        vector<string> nouns;
        vector<string> adjectives;
        vector<string> verbs;
        vector<string> adverbs;

        vector<string> pickedNames;

        // bool vectors
        // catch duplications
        bool init;
        vector<bool> namesDupe;
        vector<bool> nounsDupe;
        vector<bool> adjectivesDupe;
        vector<bool> verbsDupe;
        vector<bool> adverbsDupe;
};