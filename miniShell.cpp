#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <pwd.h>
#include <sstream>
#include <fcntl.h>

using namespace std;

bool is_background;

void cmdline_handler(string cmdline);

int main()
{
    struct passwd *pw;
    uid_t uid;

    uid = geteuid();
    pw = getpwuid(uid);

    char pathname[1024];

    while (true)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char timebuff[80];

        strftime(timebuff, 80, "[%H:%M:%S]", ltm);

        getcwd(pathname, 1024);
        string str(pathname);
        string input;

        cout << timebuff
             << (pw->pw_name)
             << "@" << pathname << "$";

        getline(cin, input);
        cmdline_handler(input);
    }
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

void err_handler(string message)
{
    perror(message.c_str());
    exit(1);
}

void builtin_cmd_handler(vector<string> cmds)
{
    if (cmds[0] == "cd")
        chdir(cmds[1].c_str());
    else
        exit(0);
}

bool background_cmd_handler(string &s)
{
    if (s[s.length() - 1] == '&')
    {
        s.pop_back();
        return true;
    }
    return false;
}

string redirection_handler(string cmdline)
{
    const char *target;
    int fd;
    string cmdline_tmp = cmdline;

    for (int i = 0; i < cmdline.length(); i++)
    {
        if (cmdline[i] == '<')
        {
            string cmdstriped = strip(cmdline.substr(i + 1));
            target = cmdstriped.c_str();
            fd = open(target, O_RDONLY | O_CREAT);
            if (fd == -1)
                err_handler("Error[open]]");
            dup2(fd, 0);
            close(fd);
            cmdline_tmp = cmdline.substr(0, i);
            break;
        }
        else if (cmdline[i] == '>')
        {
            string cmdstriped = strip(cmdline.substr(i + 1));
            target = cmdstriped.c_str();
            fd = open(target, O_WRONLY | O_CREAT | O_TRUNC);
            if (fd == -1)
                err_handler("Error[open]]");
            dup2(fd, 1);
            close(fd);
            cmdline_tmp = cmdline.substr(0, i);
            break;
        }
    }

    return cmdline_tmp;
}

void cmd_handler(string cmdline)
{
    string final_cmdline = redirection_handler(cmdline);
    vector<string> cmds = split(final_cmdline);
    char *cmdargs[10];

    for (int i = 0; i < cmds.size() + 1; i++)
    {
        if (i == cmds.size())
        {
            cmdargs[i] = NULL;
            break;
        }
        cmdargs[i] = strdup(cmds[i].c_str());
    }

    execvp(cmdargs[0], cmdargs);
    err_handler("Error[exec]");
}

void cmdline_handler(string cmdline)
{
    pid_t pid;
    vector<string> cmds = split(cmdline);

    if (cmds[0] == "cd" || cmds[0] == "exit")
    {
        builtin_cmd_handler(cmds);
        return;
    }

    is_background = background_cmd_handler(cmdline);

    pid = fork();
    switch (pid)
    {
    case -1:
        err_handler("Error[fork]");
    case 0:
        cmd_handler(cmdline);
    default:
        if (is_background)
            break;
        waitpid(pid, NULL, 0);
    }
}