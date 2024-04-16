#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;



// Add prototypes of helper functions here
void wordleRecursion(const string& in, string floating, const set<string>& dict, size_t emp, string curr, set<string>& ans);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  std::set<std::string> ans;

  size_t empty = 0;
  for (auto c : in)
  {
    if (c == '-')
        empty++;
  }
  wordleRecursion(in, floating, dict, empty, "", ans);
  return ans;
}

void wordleRecursion(const string& in, string floating, const set<string>& dict, size_t emp, string curr, set<string>& ans)
{
    if (emp < floating.size())
        return;
    else if (curr.size() == in.size())
    {
        if (dict.find(curr) != dict.end() && floating.empty())
        {
            ans.insert(curr);
        }
    }
    else if (in[curr.size()] != '-')
    {
        wordleRecursion(in, floating, dict, emp, curr + in[curr.size()], ans);
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            char c = char(97 + i);
            size_t loc = floating.find(c);
            if (loc != string::npos)
            {
                floating.erase(loc, 1);
                wordleRecursion(in, floating, dict, emp - 1, curr + c, ans);
                floating += c;
            }
            else
            {
                wordleRecursion(in, floating, dict, emp - 1, curr + c, ans);
            }
        }
    }


}

// Define any helper functions here
