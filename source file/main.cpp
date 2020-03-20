#include <bits/stdc++.h>
using namespace std;

struct WC
{
    ifstream inFile;
    int num_char;
    int num_word;
    int num_line;

    WC() { num_char = 0, num_word = 0, num_line = 0; }

    void open(char *File)
    {
        inFile.open(File);
        if (inFile.is_open() == 0)
        {
            cout << "Fail : File Not Found" << endl;
            exit(0);
        }
    }

    void Count(int argc, char *argv[])
    {
        string str;
        while (getline(inFile, str))
            for (int i = 1; i < argc; ++i)
            {
                if (string(argv[i]) == string("-c"))
                {
                    num_char += str.size();
                }
                if (string(argv[i]) == string("-w"))
                {
                    for (int j = 0; j < str.size();)
                    {
                        if (isalpha(str[j]))
                        {
                            num_word++;
                            while (j < str.size() and isalpha(str[j]))
                                j++;
                        }
                        else
                            j++;
                    }
                }
                if (string(argv[i]) == string("-l"))
                    num_line++;
            }
    }

    void print(int argc, char *argv[])
    {

        for (int i = 1; i < argc; ++i)
        {
            if (string(argv[i]) == string("-c"))
                cout << "num_char : " << num_char << endl;
            if (string(argv[i]) == string("-w"))
                cout << "num_word : " << num_word << endl;
            if (string(argv[i]) == string("-l"))
                cout << "num_line : " << num_line << endl;
        }
    }
};

int main(int argc, char *argv[])
{
    WC wc;
    wc.open(argv[argc - 1]);
    wc.Count(argc, argv);
    wc.print(argc, argv);
    return 0;
}