/*
 * Mad Lib Generator
 * @Jacob Strader
 * 
 * Creates madlibs based on information generated from input files
 * nouns, verbs, adverbs, and adjectives are pulled from their respective files,
 * while the actual madlib is pulled from the file "template".
 * 
 * THe program looks for the key '[' (which begins an input tag) and then read in
 * the following input description. If non is found, for whatever reason (typo),
 * insert "typo" into that text in order to notify the user of an input error. Otherwise,
 * fill in the correct data value for that slot e.g.:
 * 
 * [name1] is ready for [noun] -> Jacob is ready for school!
 * 
 * Note: names should be predefined and set to variables, either in a string vector in the
 * client file or in a single string var depending on the input file. If the value after name
 * in the tag exceeds the size of the name vector in the MadLib class, print "NAME LIMIT EXCEEDED"
 * to the output string to notify the user of input error.
 * 
 * Boolean arrays are defined to keep track of data pulled (at random) from the list.
 * In the case that data grabbed has already been selected, the program will redo the random
 * selection. If this process occurs 10 times in a row, the program will instead treat the data
 * similar to a hash table, incrementing the index and modding by the size of the array (to prevent
 * out of bounds exceptions) until a suitable value is found to be input into the string.
 * 
 * This client file reads input from the template file and then parses the data into the output string,
 * checking for the '[' tag. If said tag is found, tag is then sent to the MadLib class which searches for
 * a valid option to output to the string (based on the constraints described above)
*/


#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "madlib.h"

using namespace std;

string readFile(); // reads in data from the template file
string createMadLib(MadLib& ml, string input); // creates mad lib from 
string flagCheck(MadLib& ml, string input, int& pos); // checks for a flag based on input string and starting pos

int main() {
    MadLib ml;
    string madlib = createMadLib(ml, readFile());

    cout<<madlib;

    return 0;
}

// reads in data from the template file
string readFile() {
    ifstream inTemp;
    inTemp.open("template");

    string in; string output;
    while(getline(inTemp, in))
        output+=(output==""?in:"\n"+in);
    return output;
}

// create mad lib 
string createMadLib(MadLib& ml, string input) {
    string output;

    // go through every index of input
    // look for flag characters '['
    for(int i=0; i<input.length(); i++) {
        if(input[i]=='[')
            output+=flagCheck(ml, input, ++i);
        else
            output+=input[i];   
    }
    return output;
}

// check flag type and convert flag to text
string flagCheck(MadLib& ml, string input, int& pos) {
    int origin = pos;
    string flag;
    string output;

    // missing ']' or incorrect flag usage
    while(pos-origin!=10) {
        if(input[pos]==']')
            break;
        flag+=input[pos++]; // grab input at pos then increment. cannot exceed 10 increments
    }

    // name check
    if(flag.length()>4 && flag.substr(0, 4)=="name") {
        int nameID = stoi(flag.substr(4, flag.length()-4));
        return ml.getName(nameID-1);
    }

    // noun
    else if(flag=="noun")
        return ml.getNoun();
    // adjective
    else if(flag=="adjective")
        return ml.getAdjective();
    // verb
    else if(flag=="verb")
        return ml.getVerb();
    // adverb
    else if(flag=="adverb")
        return ml.getAdverb();

    // flag not found
    else
        return "FLAG NOT FOUND";
}