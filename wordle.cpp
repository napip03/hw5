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
bool contains(std::string&guess, const std::string in);
std::string wordleHelp(int n, std::string& guess, const std::string& in, 
const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& returnSet);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		int n = in.length();
		std::set<std::string> returnSet;
		//std::string hi = "nd";
		//std::string g = "dint";
		//bool jim =  contains( g, hi );
		//cout << "----------" <<jim << endl;
		std::string guess = in;
		wordleHelp(n, guess, in, floating, dict, returnSet);
		returnSet.erase("");
		return returnSet;
}

// Define any helper functions here
// returns if the string contains the letters in guess
bool contains(std::string&guess, const std::string in)
{
	//cout << guess <<" " << in;
	for (int i = 0; i < in.length(); i++)
	{
		//cout << i << in[i] << endl;
		if (guess.find(in[i])==std::string::npos) //check if char is in word at atleast one instance
		{
			//cout << endl;
			return false;
		}
	}
	//cout << ":)" << endl;
	return true;
}
// returns a string that can be found in dict (using recursion)
std::string wordleHelp(int n, std::string& guess, const std::string& in, 
const std::string& floating, const std::set<std::string>& dict,  std::set<std::string>& returnSet)
// a = 97 z = 122
{
	//cout << "called function" << endl;
	string alph = "abcdefghijklmnopqrstuvwxyz";
	if (n <= 0)
	{
		if (dict.find(guess) != dict.end() && contains(guess, floating) == true)
		{
			//cout << guess << endl;
			returnSet.insert(guess);
			return guess;
		}
		return "";
	}
	else
	{
		if (in[n-1] == '-') //if the space is blank
		{
			 //use floating 
			 if (floating != "")
			 {
					for (int i = 0; i < floating.length(); i++) //itterates through the floating
					{
						guess[n-1] = floating[i];
						
						wordleHelp(n-1, guess, in, floating, dict, returnSet);  //floating unchanged (case: double letters)
						wordleHelp(n-1,guess, in, floating, dict, returnSet); //floating remove c 
					}
			 }
			 //skip floating used in other position case
			 for (char c: alph)
			 {
					guess[n-1] = c;
					wordleHelp(n-1,guess, in, floating, dict, returnSet);
					
			 }
		}
		else //space is filled
		{
			//cout << in[n-1] << guess[n-1] << endl;
			n = n-1;
			wordleHelp(n, guess, in, floating, dict, returnSet);
			//update n and try again
		}
	}
	return "";
}