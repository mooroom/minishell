#include <iostream>
#include <string>

using namespace std;

string strip(string s);

int main()
{
    string cmd = "ls < make file   ";

    const char *arg;
    for (int i = 0; i < cmd.length(); i++)
    {
        if (cmd[i] == '<')
        {
            string cmdstriped = strip(cmd.substr(i + 1));
            arg = cmdstriped.c_str();
        }
    }

    cout << arg << endl;

    return 0;
}

string strip(string s)
{
    string res;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ')
        {
            res = s.substr(i);
            break;
        }
    }
    for (int i = res.length() - 1; i > 0; i--)
    {
        if (res[i] != ' ')
        {
            res = res.substr(0, i + 1);
            break;
        }
    }
    return res;
}