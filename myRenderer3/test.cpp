#include "test.h"
#include <stack>
#include <iostream>
#include <deque>
#include <iomanip>


using namespace std;

void showstack(stack <int> s)
{
    while (!s.empty())
    {
        cout << '\t' << s.top();
        s.pop();
    }
    cout << '\n';
}


void test()
{
    std::cout << "\nrunning tests================================ " << endl;

    std::deque<std::string> letters;

    letters.push_back("abc");
    std::string s = "def";
    std::string s1 = "def";
    letters.push_back(std::move(s));
    letters.push_back(std::move(s1));
    letters.push_back(std::move(s));
    letters.push_back(std::move(s));

    std::cout << "deque holds: ";
    for (auto&& i : letters) std::cout << std::quoted(i) << ' ';
    std::cout << "\nMoved-from string holds " << std::quoted(s) << '\n';

}