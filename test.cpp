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

int main()
{
    // const char *s1 = "hello1";
    // char s2[] = "hello2";
    // const char *s3[] = {"hello3"};

    // string s4 = "hello4";
    // const char *s5 = s4.c_str();

    // int x1[] = {1, 2, 3, 4};

    // cout << s1 << endl;
    // cout << s2 << endl;
    // cout << s3[0] << endl;
    // cout << s4 << endl;
    // cout << s5 << endl;
    vector<string> strvec;
    string input;
    cout << "input: ";
    getline(cin, input);
    strvec = split(input);

    // for (int i = 0; i < strvec.size(); i++)
    // {
    //     cout << strvec[i] << endl;
    // }
    string last_cmd = strvec.back();
    if (last_cmd == "&")
        cout << "is background" << endl;

    return 0;
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