#include "hangmangame.h"
#include <fstream>
#include <qDebug>
#include <random>
#include <algorithm>
#include <iostream>
#include <sstream>

const int ALLOWED_GUESSES=6;

HangManGame::HangManGame()
{
    init();
}

void HangManGame::makeGuess(char l)
{

    // has c already been guessed
    if (_wrongGuesses.find(l) != _wrongGuesses.end() || _correctGuesses.find(l) != _correctGuesses.end())
        return;

    // c hasn't been guessed put it in one of the guess sets
    std::string::size_type idx = _secretWord.find(l);
    if (idx == std::string::npos) // not found, wrong guess
        _wrongGuesses.insert(l);
    else
        _correctGuesses.insert(l);  // found, good guess

}

bool HangManGame::isGuessed(char l)
{
    // has it been guesed ?
    if (_wrongGuesses.find(l) != _wrongGuesses.end() || _correctGuesses.find(l) != _correctGuesses.end())
        return true;
    else
        return false;
}

bool HangManGame::isWon()
{
    //
    //  If any of the letters in the secret phrase have not
    //  been guesed, you havent won yet
    //
    for (auto c : _secretWord) {
        if (_correctGuesses.find(c) == _correctGuesses.end())
            return false;
    }

    return true; // all letters correctly guesed you won
}

bool HangManGame::isLost()
{
    // you loose when you use up your allowed guesses
    if (_wrongGuesses.size() >= ALLOWED_GUESSES)
        return true;
    else
        return false;
}

void HangManGame::newPhrase()
{
    //
    // get the next secret word/phrase
    //
    _secretWord = _phrases.back();
    _phrases.pop_back();

    //
    // reset the guesses sets
    //
    _correctGuesses.clear();
    _wrongGuesses.clear();

    //
    // set the spaces in a phrase as already guessed
    //
    _correctGuesses.insert(' ');

}

std::string HangManGame::phraseToString() const
{
    std::ostringstream os;

    for (auto c : _secretWord)
    {
        if (_correctGuesses.find(c) == _correctGuesses.end()) // letter not guessed yet
            os << "_";
        else
            os <<  c; // letter has been guesed

        os << " ";
    }
    return os.str();
}

std::string HangManGame::secretToString() const
{
    std::ostringstream os;

    for (auto c : _secretWord)
        os <<  c << " ";
    return os.str();
}

void HangManGame::init()
{
    //
    // read words/phrases from file into vector
    // random shuffle vector so game is different
    // every time
    //
    std::ifstream iFile("/tmp/words");
    if (iFile.fail())
    {
        qWarning() << "Error opening words file\n";
        exit(EXIT_FAILURE);
    }

    std::string word;
    while (!iFile.fail())
    {
        getline(iFile, word);
        std::transform(word.begin(), word.end(), word.begin(), tolower);
        if (!iFile.eof() && word.size() > 0)  // dont add blank lines
            _phrases.push_back(word);
    }
    //
    srand(time(0));
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(_phrases.begin(), _phrases.end(), urng);

    for (int i=1;i<20;++i)
    {
        qWarning() << QString::fromStdString(_phrases[_phrases.size() - i]);
    }

}
