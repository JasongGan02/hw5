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
void worldeRecursion(const std::string& in, const std::string& floatingRef, int* floating, std::set<std::string>& ans, const std::set<std::string>& dict, std::string& current, int n)
{
    if (n == in.size())
    {
        if (dict.find(current) != dict.end())
        {
            for (auto c: floatingRef)
            {
                if (floating[c - 'a'] > 0)
                    return;
            }
            ans.insert(current);
        }
        return;
    }

    if (in[n] != '-')
    {
        worldeRecursion(in, floatingRef, floating, ans, dict, current, n+1);
    }
    else
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            if (floatingRef.find(c) != std::string::npos)
            {
                floating[c - 'a']--;
                current[n] = c;
                worldeRecursion(in, floatingRef, floating, ans, dict, current, n + 1);
                floating[c - 'a']++;
            }
            else if (floatingRef.find(c) == std::string::npos)
            {
                current[n] = c;
                worldeRecursion(in, floatingRef, floating, ans, dict, current, n + 1);
            }
        }
    }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  std::set<std::string> ans;
  std::string current = in;
  int free[26] = {};
  for (auto ch : floating)
  {
    free[ch - 'a']++; 
  }
  
  worldeRecursion(in, floating, free, ans, dict, current, 0);
  return ans;
}

// Define any helper functions here
