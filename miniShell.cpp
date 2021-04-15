#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#include <string>
#include <ctime>

#include <pwd.h>

using namespace std;

int main()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    struct passwd *pw;
    uid_t uid;

    uid = geteuid();
    pw = getpwuid(uid);

    char pathname[1024];

    while (true)
    {
        getcwd(pathname, 1024);
        string str(pathname);
        cout << "[" << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "]"
             << (pw->pw_name)
             << "@" << pathname << "$" << endl;
    }
    return 0;
}