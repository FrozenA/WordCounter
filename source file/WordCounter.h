#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct NUM
{
    int ch;
    int word;
    int line;
    int spaceline;
    int codeline;
    int comment;

    NUM()
    {
        memset(this, 0, sizeof(NUM));
    }
};

struct WC
{
    ifstream inFile;
    string FileName;
    NUM num;

    bool open(const string &File)
    {
        FileName = File;
        inFile.open(File);
        if (inFile.is_open() == 0)
            return false;
        return true;
    }

    int count_char(const string &str)
    {
        return str.size();
    }

    int count_word(const string &str)
    {
        int res = 0;
        for (int j = 0; j < int(str.size());)
        {
            if (isalpha(str[j]) or isdigit(str[j]))
            {
                res++;
                while (j < int(str.size()) and (isalpha(str[j]) or isdigit(str[j])))
                    j++;
            }
            else
                j++;
        }
        return res;
    }

    int count_line(const string &str)
    {
        return 1;
    }

    bool isspace(const string &str)
    {
        int space = 0;
        int num = 0;
        for (const char &ch : str)
        {
            space += (ch == ' ');
            num += (isalpha(ch) or isdigit(ch));
        }
        if (num == 0 and str.size() - space <= 1)
            return 1;
        return 0;
    }

    pair<bool, bool> code_comment(const string &str)
    {
        bool isword = false;
        if (isalpha(str[0]) or isdigit(str[0]))
            isword = true;
        for (int i = 1; i < int(str.size()); ++i)
        {
            if (isalpha(str[i]) or isdigit(str[i]))
                isword = true;
            if (str[i - 1] == '/' and str[i] == '/')
                return make_pair(isword, 1);
        }
        return make_pair(isword, 0);
    }

    void count()
    {
        memset(&this->num, 0, sizeof(this->num));
        string str;
        while (getline(inFile, str))
        {
            num.ch += count_char(str);
            num.word += count_word(str);
            num.line += count_line(str);
            num.codeline += code_comment(str).first;
            num.comment += code_comment(str).second;
            num.spaceline += isspace(str);
        }
    }

    void print(int argc, char *argv[])
    {
        count();
        cout << FileName << endl;
        for (int i = 1; i < argc; ++i)
        {
            if (string(argv[i]) == string("-c"))
                cout << "num_char : " << num.ch << endl;
            if (string(argv[i]) == string("-w"))
                cout << "num_word : " << num.word << endl;
            if (string(argv[i]) == string("-l"))
                cout << "num_line : " << num.line << endl;
            if (string(argv[i]) == string("-a"))
            {
                cout << "num_code line : " << num.codeline << endl;
                cout << "num_blank line : " << num.spaceline << endl;
                cout << "num_comment line: " << num.comment << endl;
            }
        }
        cout << endl;
    }
};

   #endif // WORDCOUNTER_H
