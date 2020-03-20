#include <bits/stdc++.h>
using namespace std;

struct WC
{
    ifstream inFile;
    string FileName;
    struct
    {
        int ch;
        int word;
        int line;
        int spaceline;
        int codeline;
    } num;

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
        for (int j = 0; j < str.size();)
        {
            if (isalpha(str[j]) or isdigit(str[j]))
            {
                res++;
                while (j < str.size() and (isalpha(str[j]) or isdigit(str[j])))
                    j++;
            }
            else
                j++;
        }
        return res;
    }

    int count_line(const string &str)
    {
        if (str.size() > 0)
            return 1;
        else
            return 0;
    }

    void print(int argc, char *argv[])
    {
        memset(&this->num, 0, sizeof(this->num));
        cout << FileName << endl;
        string str;
        while (getline(inFile, str))
            for (int i = 1; i < argc; ++i)
            {
                if (string(argv[i]) == string("-c"))
                    num.ch += count_char(str);
                if (string(argv[i]) == string("-w"))
                    num.word += count_word(str);
                if (string(argv[i]) == string("-l"))
                    num.line += count_line(str);
            }
        for (int i = 1; i < argc; ++i)
        {
            if (string(argv[i]) == string("-c"))
                cout << "num_char : " << num.ch << endl;
            if (string(argv[i]) == string("-w"))
                cout << "num_word : " << num.word << endl;
            if (string(argv[i]) == string("-l"))
                cout << "num_line : " << num.line << endl;
        }
        cout << endl;
    }
};