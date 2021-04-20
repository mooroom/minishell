#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "[argc]: " << argc << endl;
    cout << "[argv1]: " << argv[1] << endl;

    int N;
    cin >> N;

    vector<int> numbers;
    vector<int> sorted;

    for (int i = 0; i < N; i++)
    {
        int num;
        cin >> num;
        numbers.push_back(num);
    }

    cout << "there are elements #: " << numbers.size() << endl;

    return 0;
}