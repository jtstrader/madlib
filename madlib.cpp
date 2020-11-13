////////////////////
//     MAD LIB    //
////////////////////

#include "madlib.h"

//////////////////////////
//   PUBLIC FUNCTIONS   //
//////////////////////////

MadLib::MadLib() {

    // post: initialize dupe vectors and input data
    //       into "input vectors" 

    init = false;
    fillInputVectors();
    setDupesFalse();
}

MadLib::~MadLib() {

}

string MadLib::getName(int pos) {

    // post: returns string to client file of specific name

    // return name already chosen
    if(getIndexName(pos))
        return pickedNames[pos];
    
    // name has not been selected yet for that position
    else {
        // custom getIndex overloaded with pos value
        // to factor in for non-changing name variables
        // in client file
        int index = getIndex(randNames, namesDupe);
        // if index == -1 overflow error
        if(index==-1)
            return "MAX NAME VALUES USED";

        pickedNames[pos] = randNames[index];
        return pickedNames[pos];
    }
}

string MadLib::getNoun() {

    // post: returns a noun randomly selected from the noun list

    int index = getIndex(nouns, nounsDupe);
    return index!=-1?nouns[index]:"NOUN NOT FOUND";
}

string MadLib::getAdjective() {

    // post: returns a adjective randomly selected from the adjective list

    int index = getIndex(adjectives, adjectivesDupe);
    return index!=-1?adjectives[index]:"ADJECTIVE NOT FOUND";
}

string MadLib::getVerb() {

    // post: returns a verb randomly selected from the verb list

    int index = getIndex(verbs, verbsDupe);
    return index!=-1?verbs[index]:"VERB NOT FOUND";
}

string MadLib::getAdverb() {

    // post: returns an adverb randomly selected from the adverb list

    int index = getIndex(adverbs, adverbsDupe);
    return index!=-1?adverbs[index]:"ADVERB NOT FOUND";
}

///////////////////////////
//   PRIVATE FUNCTIONS   //
///////////////////////////

int MadLib::getIndex(vector<string>& arr, vector<bool>& arrBool) {

    // post: grabs index of an available value in a vector

    bool exit = false;
    int count = 0;
    int inc = 0;

    // note: when count == 10, break from loop and loop increment until
    // valid value is found for returning
    while(!exit) {
        srand(time(NULL));
        int index = rand()%arr.size();
        if(arrBool[index]) // duplicate pulled
            count++;
        else {
            arrBool[index] = true;
            return index;
        }

        // increment (similar to hash table design) till value found
        while(count==10) {
            if(arrBool[(index+inc)%arr.size()])
                inc++;
            else {
                arrBool[(index+inc)%arr.size()] = true;
                return (index+inc)%arr.size();
            }
            // SERIOUS ERROR. ALL VALUES USED
            if(inc==arr.size())
                return -1;
        }
    }
    return -1; // cover for unreachable return statement
}

bool MadLib::getIndexName(int pos) {

    // post: returns index for for call in namesDupe

    for(int i=0; i<randNames.size(); i++)
        if(pickedNames[pos]==randNames[i])
            return true;
    return false;
}

void MadLib::setDupesFalse() {

    // pre: vectors either empty or containing assortment of true/false values
    
    // post: all vector values set to false
    
    // resize all arrays if not initialized
    if(!init) {
        pickedNames.resize(randNames.size());
        namesDupe.resize(randNames.size());
        nounsDupe.resize(nouns.size());
        adjectivesDupe.resize(adjectives.size());
        verbsDupe.resize(verbs.size());
        adverbsDupe.resize(adverbs.size());

        init = true;
    }

    // set picked named
    for(string val:pickedNames)
        val = "";

    // set all values to false

    // randNames
    for(bool val:namesDupe)
        val = false;
    
    // nouns
    for(bool val:nounsDupe)
        val = false;
    
    // adjectives
    for(bool val:adjectivesDupe)
        val = false;

    // verbs
    for(bool val:verbsDupe)
        val = false;

    // adverbs
    for(bool val:adverbsDupe)
        val = false;
}

void MadLib::fillInputVectors() {

    // pre: empty input vectors

    // post: input vectors filled from respective files

    // in file streams
    ifstream inName;  inName.open("names");
    ifstream inNoun;  inNoun.open("nouns");
    ifstream inAdj;   inAdj.open("adjectives");
    ifstream inVerb;  inVerb.open("verbs");
    ifstream inAdv;   inAdv.open("adverbs");

    string input;
    
    // randNames
    while(inName>>input)
        randNames.push_back(input);
    inName.close();

    // nouns
    while(inNoun>>input)
        nouns.push_back(input);
    inNoun.close();

    // adjectives
    while(inAdj>>input)
        adjectives.push_back(input);
    inAdj.close();

    // verbs
    while(inVerb>>input)
        verbs.push_back(input);
    inVerb.close();

    // adverbs
    while(inAdv>>input)
        adverbs.push_back(input);
    inAdv.close();       
}