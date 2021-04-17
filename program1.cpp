#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> merged;
    int lpointer = 0;
    int rpointer = 0;

    while (left.size() > lpointer && right.size() > rpointer)
    {
        if (left[lpointer] > right[rpointer])
        {
            merged.push_back(right[rpointer]);
            rpointer++;
        }
        else
        {
            merged.push_back(left[lpointer]);
            lpointer++;
        }
    }

    while (left.size() > lpointer)
    {
        merged.push_back(left[lpointer]);
        lpointer++;
    }

    while (right.size() > rpointer)
    {
        merged.push_back(right[rpointer]);
        rpointer++;
    }

    return merged;
}

vector<int> mergeSplit(vector<int> nums)
{
    if (nums.size() <= 1)
        return nums;

    vector<int> left, right;
    int midium = nums.size() / 2;

    for (int i = 0; i < midium; i++)
        left.push_back(nums[i]);

    for (int i = midium; i < nums.size(); i++)
        right.push_back(nums[i]);

    left = mergeSplit(left);
    right = mergeSplit(right);

    return merge(left, right);
}

int main()
{
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

    sorted = mergeSplit(numbers);

    cout << "[sorted]: ";
    for (int i = 0; i < sorted.size(); i++)
    {
        cout << sorted[i] << " ";
    }
    cout << endl;

    return 0;
}