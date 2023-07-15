#ifndef LIST
#define LIST

#include <string>
#include <fstream>

struct words{
  std::string word = "";
  int qnt = 0;

  words(std::string w, int q){
    word = w;
    qnt = q;
  }
};

class Word{
  public:
    Word();
    Word(std::string &word, int qnt, int iD, Word* next, Word* previous);

    words* _word;
    Word* next;
    Word* previous;

    int iD;
};

class ListWords{
  public:
    ListWords();
    ~ListWords();
    void AddNewWord(std::string word);
    void swap(Word* &W1,
              Word* &W2);
    void ListAccess();
    void Print(std::ofstream &FileOut);


    int _words;
    int total;

    Word* First;
    Word* Last;
};
 
#endif