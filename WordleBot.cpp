#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void updateWordLists(vector<string> &guessList, vector<string> &answerList, string info, string guessedWord){
    for(int i = 0; i < 5; i++){
        if(guessedWord.rfind(guessedWord.at(i)) != i){
            if(info.at(i) == '_'){
                info.at(i) = 'I';
            }
            if(info.at(guessedWord.rfind(guessedWord.at(i))) == '_'){
                info.at(guessedWord.rfind(guessedWord.at(i))) = 'I';
            }
        }
    }
    
    for(int i = 0; i < guessList.size(); i++){
        for(int j = 0; j < 5; j++){
            if(info.at(j) == 'G'){
                if(guessedWord.at(j) != guessList.at(i).at(j)){
                    guessList.erase(guessList.begin() + i);
                    i--;
                    break;
                }
            }else if(info.at(j) == 'Y'){
                if(guessList.at(i).find(guessedWord.at(j)) == string::npos){
                    guessList.erase(guessList.begin() + i);
                    i--;
                    break;
                }
                if(guessedWord.at(j) == guessList.at(i).at(j)){
                    guessList.erase(guessList.begin() + i);
                    i--;
                    break;
                }
            }else if(info.at(j) == '_'){
                if(guessList.at(i).find(guessedWord.at(j)) != string::npos){
                    guessList.erase(guessList.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < answerList.size(); i++){
        for(int j = 0; j < 5; j++){
            if(info.at(j) == 'G'){
                if(guessedWord.at(j) != answerList.at(i).at(j)){
                    answerList.erase(answerList.begin() + i);
                    i--;
                    break;
                }
            }else if(info.at(j) == 'Y'){
                if(answerList.at(i).find(guessedWord.at(j)) == string::npos){
                    answerList.erase(answerList.begin() + i);
                    i--;
                    break;
                }
            }else{
                if(answerList.at(i).find(guessedWord.at(j)) != string::npos){
                    answerList.erase(answerList.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }
}

void getGuessValues(vector<string> &guessList, vector<string> &answerList, vector<int> &guessValues){
    string curGuess;
    string curAnswer;
    for(int i = 0; i < guessList.size(); i++){
        curGuess = guessList.at(i);
        int val = 0;
        for(int j = 0; j < answerList.size(); j++){
            curAnswer = answerList.at(j);
            vector<char> lettersInAns;
            for(int k = 0; k < 5; k++){
                lettersInAns.push_back(curAnswer.at(k));
            }

            int lettersRemoved = 0;
            for(int k = 0; k < lettersInAns.size(); k++){
                if(curGuess.at(k + lettersRemoved) == lettersInAns.at(k)){
                    val += 3;
                    lettersInAns.erase(lettersInAns.begin() + k);
                    k--;
                    lettersRemoved++;
                }
            }

            for(int k = 0; k < lettersInAns.size(); k++){
                if(curGuess.find(lettersInAns.at(k)) != string::npos){
                    val += 1;
                    lettersInAns.erase(lettersInAns.begin() + k);
                    k--;
                    lettersRemoved++;
                }
            }
        }
        guessValues.push_back(val);
        // cout << "Guess: " << curGuess << ", Value: " << val << endl;
        if(i != guessList.size() - 1 && guessList.at(i).at(0) != guessList.at(i+1).at(0)){
            cout << "Onto " << guessList.at(i+1).at(0) << endl;
        }
    }
}

int main(){
    ifstream guesses("GuessList.txt");
    ifstream answers("AnswerList.txt");

    vector<string> guessList;
    vector<string> answerList;

    string curGuess;
    while(guesses >> curGuess){
        guessList.push_back(curGuess);
    }

    string curAnswer;
    while(answers >> curAnswer){
        answerList.push_back(curAnswer);
    }

    vector<int> guessValues;

    cout << "Possible Guesses: " << guessList.size() << ", Possible Answers: " << answerList.size() << endl;
    string userInput = "not";
    cout << curGuess.size(); 
    int maxValInd = 0;
    string bestGuess = "soare";
    while(userInput.find("exit") == string::npos){
        cout << "The Best Guess is " << bestGuess << endl;

        cout << "Enter exit if done, if not enter the response as: _ for miss, Y for Yellow, G for Green" << endl;
        cin >> userInput;

        if(userInput.find("exit") == string::npos){
            guessValues.resize(0);

            updateWordLists(guessList, answerList, userInput, bestGuess);
            cout << "Possible Guesses: " << guessList.size() << ", Possible Answers: " << answerList.size() << endl;

            getGuessValues(guessList, answerList, guessValues);
            maxValInd = 0;
            for(int i = 0; i < guessValues.size(); i++){
                if(guessValues.at(i) > guessValues.at(maxValInd)){
                    maxValInd = i;
                } 
            }
            bestGuess = guessList.at(maxValInd);
            guessList.erase(guessList.begin() + maxValInd);
        }
    }

    return 0;
}