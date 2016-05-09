#ifndef HANGMANGAME_H
#define HANGMANGAME_H

#include <vector>
#include <string>
#include <set>


class HangManGame
{
public:
    HangManGame();

    int wrongGuesses() const {return _wrongGuesses.size();}
    void makeGuess(char l);
    bool isGuessed(char l);
    bool isWon();
    bool isLost();
    void newPhrase();
    std::string phraseToString() const;
    std::string secretToString() const;

private:
    void init();

private:
    std::vector<std::string> _phrases;

    std::string _secretWord;
    std::set<char> _correctGuesses;
    std::set<char> _wrongGuesses;

};



#endif // HANGMANGAME_H
