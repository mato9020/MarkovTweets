#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

class markovTweet{
    string fileText; //contents of text file stored here
    map<string, vector<string>> vocabulary;

public:

    void createTweet(int keyLength, int desiredChars) {
        //max amount of words possible in a Tweet
        int words = 280;
        //reading text from input file
        ifstream f("input.txt");
        if(f.good()){
          fileText.assign((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
        }else{
          //returns if input file can't be read or found
          cout << "\n" << "Input cannot be read. Ensure there is a file called input.txt in this directory." << "\n" << endl;
          return;
        }
        //returns if input file is empty
        if(fileText.length() < 1){
          cout << "Input has too few characters to work.";
          return;
        }

        cout << "\n" << "Artificially generated tweet using Markov Chains based off of input.txt: " << "\n" << "\n";

        //needs to be an empty space at end of text or code runs infinitely
        fileText.push_back(' ');
        createVocab(keyLength);
        generateText(words - keyLength, desiredChars, fileText.length());
    }

private:

    void generateText(int w, int dChars, int fileLength) {
        string outputTemp;
        string outputFinal;
        string key;
        string first;
        string second;
        size_t next = 0;
        map<string, vector<string> >::iterator it = vocabulary.begin();
        advance(it, rand() % vocabulary.size()); //to make starting point random
        key = (*it).first;
        outputTemp += (key);
        while(true) {
            vector<string> d = vocabulary[key];
            if(d.size() < 1) break; //adds more words to string to be added if too low
            second = d[rand() % d.size()]; 
            if(second.length() < 1) break;
            outputTemp += " ";
            outputTemp += second;
            if(--w < 0) break;
            next = key.find_first_of(' ', 0);
            first = key.substr(next + 1);
            key = first + " " + second;
        }

        //ensures that output is correct length
        for(int i = 0; i < dChars; i++){
          if(i == fileLength) break;
          outputFinal += outputTemp[i];
        }
        cout << outputFinal;
    }

    void createVocab(unsigned int keylen) {
        string word;
        string key;
        size_t wordCount = 0;
        size_t pos = 0;
        size_t next = 0;
        next = fileText.find_first_not_of(' ', 0); //finds first character that is not a space -> ' '
        if(next == string::npos) return; //if the first character found that isnt a space is at the end of the input string, return
        while(wordCount < keylen) {
            pos = fileText.find_first_of(' ', next);
            word = fileText.substr(next, pos - next);
            key += word + " ";
            next = fileText.find_first_not_of(' ', pos + 1);
            if(next == string::npos) return;
            wordCount++;
        }
        key = key.substr(0, key.size() - 1);
        while(true) {
            next = fileText.find_first_not_of(' ', pos + 1); //finds first character that is not a space after current position
            if(next == string::npos) return;
            pos = fileText.find_first_of(' ', next);
            word = fileText.substr(next, pos - next);
            if(word.size() < 1) break;
            if(find( vocabulary[key].begin(), vocabulary[key].end(), word) == vocabulary[key].end() ) //creating a word set to build generated text from
                vocabulary[key].push_back(word);
            key = key.substr(key.find_first_of(' ') + 1) + " " + word;
        }
    }
};

int main() {  
    srand(time( 0 )); //preps rand() so that output is (hopefully) different every time
    markovTweet t;
    
    //First number is the key length. Lower number means more random sounding text, higher number sounds more like source text
    //Second number is how many characters long the output is. A tweet can not be more than 280 characters
    t.createTweet(2, 280);
    return 0;
}
