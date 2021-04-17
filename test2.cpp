#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test(const char *s)
{
    cout << "string is: " << s << endl;
}

void popback(string &s)
{
    s.pop_back();
}

// void parse(char cmd[])
// {
//     for (int i = 0; i < strlen(cmd); i++)
//     {
//         if (cmd[i] == '<')
//         {

//         }
//             cmd[i] = '\0';
//     }
// }

int main()
{
    string my_string = "hello";
    // test(my_string.c_str());
    // popback(my_string);
    char my_s[] = "hello < tello";
    // parse(my_s);
    my_string[3] = '\0';
    cout << my_string << endl;
}