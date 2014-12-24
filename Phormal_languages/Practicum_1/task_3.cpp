#include <iostream>
#include <stack>
#include <climits>
#include <cstdlib>
#define ERROR 1

int main()
{
    std::string alpha;
    char x;
    int k;
    std::stack< std::pair < int, int > > myStack;
    std::cin >> alpha >> x >> k;
    for (int i = 0; i < alpha.length(); ++i)
    {
        switch (alpha[i])
        {
            case '1':
            {
                myStack.push(std::make_pair(0, 0));
                break;
            }
            case '+':
            {
                if (myStack.size() < 2)
                {
                    std::cout << alpha << ": not a regular expression\n";
                    exit(ERROR);
                }
                std::pair < int, int > secondWord = myStack.top();
                myStack.pop();
                std::pair < int, int > firstWord = myStack.top();
                myStack.pop();
                myStack.push(std::make_pair(std::max(firstWord.first, secondWord.first), std::max(firstWord.second, secondWord.second)));
                break;
            }
            case '.':
            {
                if (myStack.size() < 2)
                {
                    std::cout << alpha << ": not a regular expression\n";
                    exit(ERROR);
                }
                std::pair < int, int > secondWord = myStack.top();
                myStack.pop();
                std::pair < int, int > firstWord = myStack.top();
                myStack.pop();
                myStack.push(std::make_pair( ((firstWord.first >= 0) && (secondWord.first >= 0))
                                             ? ((firstWord.first == INT_MAX) || (secondWord.first == INT_MAX))
                                               ? INT_MAX
                                               : firstWord.first + secondWord.first
                                             : INT_MIN,
                                             (firstWord.first >= 0)
                                             ? (firstWord.first == INT_MAX)
                                               ? INT_MAX
                                               : (secondWord.second == INT_MAX)
                                                 ? INT_MAX
                                                 : (firstWord.first + secondWord.second > firstWord.second)
                                                   ? firstWord.first + secondWord.second
                                                   : firstWord.second
                                             : firstWord.second));
                break;
            }
            case '*':
            {
                if (myStack.size() < 1)
                {
                	std::cout << alpha << ": not a regular expression\n";
                    exit(ERROR);
                }
                std::pair < int, int > word = myStack.top();
                myStack.pop();
                myStack.push(std::make_pair((word.first > 0) ? INT_MAX : 0, (word.first > 0) ? INT_MAX : word.second));
                break;
            }
            default:
            {
                if ((alpha[i] != 'a') && (alpha[i] != 'b') && (alpha[i] != 'c'))
                {
                    std::cout << alpha << ": not a regular expression\n";
                    exit(ERROR);
                }
                myStack.push((alpha[i] == x) ? std::make_pair(1, 1) : std::make_pair(INT_MIN, 0));
            }
        }
    }
    if (myStack.size() != 1)
    {
        std::cout << alpha << ": not a regular expression\n";
        exit(ERROR);
    }
    std::pair < int, int > word = myStack.top();
    myStack.pop();
    std::cout << ((std::max(word.first, word.second) >= k) ? "YES\n" : "NO\n");
    return 0;
}
