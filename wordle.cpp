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
void dfs(size_t index, std::string in, std::string floating, std::set<std::string>&results, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    dfs(0, in, floating, results, dict);
    return results;

}

// Define any helper functions here


void dfs(size_t index, std::string in, std::string floating, std::set<std::string>&results, const std::set<std::string>& dict){
  if(index == in.size()){
    if(dict.count(in) == 1 && floating.size() == 0){
      results.insert(in);

    }
    return;
  }

  size_t slots = 0;
  for(size_t i = index; i < in.size(); i++){
    if(in[i] == '-'){
      slots++;
    }

  }

  if(slots < floating.size()){
    return;

  }

  if(in[index] != '-'){
    dfs(index+1, in, floating, results, dict);

  }
  else{
    for(char c = 'a'; c<= 'z'; c++){
      in[index] = c;
      std::string floating_ = floating;
      size_t pos = floating_.find(c);
      if(pos != std::string::npos){
        floating_.erase(pos,1);
      }
      dfs(index+1, in, floating_,results, dict);

      in[index] = '-';
    }
  }

}