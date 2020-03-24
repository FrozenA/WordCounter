#include <iostream>
#include <unistd.h>
#include "WordCounter.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFileInfo>
#include <QDebug>
#include <QTextStream>

using namespace std;
char pathFileName[128] = "d:\\WordCounterPath";
int Argc;
char **Argv;
string fileName;
bool isSubdir = false;
bool isWindow = false;

//用system的dir命令获取文件目录
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
        QFileInfo fi(t.c_str());
        if (fi.isDir())
            res.push_back(t);
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

int ShowWindow()
{
    QApplication a(Argc, Argv);
    MainWindow w;
    w.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    QTextStream cout(stdout);
    Argc = argc;
    Argv = argv;

    for (int i = 0; i < argc; ++i)
    {
        if (string(argv[i]) == string("-s"))
            isSubdir = true;
        if (string(argv[i]) == string("-x"))
            isWindow = true;
    }

    if (isWindow)
        ShowWindow();
    else
    {
        fileName = (string("\\") += argv[argc - 1]);

        char nowPath[1024];
        getcwd(nowPath, 1024);
        Count(nowPath);
        string del = "del 2>NUL ";
        del += pathFileName;
        system(del.c_str());
    }

    return 0;
}
