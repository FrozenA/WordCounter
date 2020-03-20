#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
#include "WordCounter.h"
#define pb push_back
using namespace std;
char pathFileName[1024] = "d:\\WordCounterPath";
int Argc;
char **Argv;
string fileName;
bool isSubdir = false;

void GetAllDir(const string &dir)
{
    freopen(pathFileName, "w", stdout);
    system((string("dir /b 2>NUL ") += dir).c_str());
    fclose(stdout);
    freopen("CON", "w", stdout);
}

vector<string> GetSubDir(string dir)
{
    GetAllDir(dir);
    vector<string> res;
    string str;
    ifstream ifs(pathFileName);
    if (!ifs.is_open())
    {
        cout << "Fail";
        exit(0);
    }
    while (ifs >> str)
    {
        string t = dir;
        (t += "\\") += str;
        DWORD dwattr = GetFileAttributes(t.c_str());
        if (dwattr & FILE_ATTRIBUTE_DIRECTORY)
            res.pb(t);
    }
    ifs.close();
    return res;
}

void Count(const string &path)
{
    //递归子文件夹
    if (isSubdir)
    {
        vector<string> subdir = GetSubDir(path);
        for (string t : subdir)
            Count(t);
    }
    //利用system的dir实现通配符匹配
    string filepath = path;
    filepath += fileName;
    GetAllDir(filepath);

    ifstream ifs(pathFileName);
    if (!ifs.is_open())
    {
        cout << "Fail";
        exit(0);
    }
    string file;
    while (ifs >> file)
    {
        filepath = path;
        (filepath += "\\") += file;
        WC wc;
        if (wc.open(filepath))
            wc.print(Argc, Argv);
    }
    ifs.close();
}

int main(int argc, char *argv[])
{
    Argc = argc;
    Argv = argv;
    fileName = (string("\\") += argv[argc - 1]);
    char nowPath[1024];
    getcwd(nowPath, 1024);

    for (int i = 0; i < argc; ++i)
        if (string(argv[i]) == string("-s"))
            isSubdir = true;

    Count(nowPath);

    string del = "del 2>NUL ";
    del += pathFileName;
    system(del.c_str());
    return 0;
}