#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

#include <vector>
#include <pwd.h>

using namespace std;

vector<string> split(string);
bool is_background(string);

int main()
{
    // const char *s1 = "hello1";
    // char s2[] = "hello2";
    // const char *s3[] = {"hello3"};

    // string s4 = "hello4";
    // const char *s5 = s4.c_str();

    vector<string> strvec;
    string input;
    cout << "input: ";
    getline(cin, input);
    strvec = split(input);

    bool isBackground = is_background(strvec.back());
    if (isBackground)
    {
        cout << "background running!" << endl;
        strvec.back().pop_back();
    }

    cout << strvec.back() << endl;
    return 0;
}

bool is_background(string cmd)
{
    if (cmd.back() == '&')
        return true;
    return false;
}

vector<string> split(string line)
{
    vector<string> v;
    istringstream ss(line);
    string buff;
    while (getline(ss, buff, ' '))
    {
        v.push_back(buff);
    }

    return v;
}