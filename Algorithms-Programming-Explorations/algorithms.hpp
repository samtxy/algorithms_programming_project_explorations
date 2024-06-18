///////////////////////////////////////////////////////////////////////////////
// algorithms.hpp
//
// Definitions for four algorithms:
//
// run_length_encode
// longest_frequent_substring
// reformat_date
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

using namespace std;
#include <unordered_map>
#include <string>

namespace algorithms {
  void append_run(string& cString, const char& runChar, int runLength){
    if (runLength > 1){
      cString = cString + to_string(runLength);
    }

    cString = cString + runChar;
  }
  // Run-length-encode the given string.
  //
  // uncompressed must be a string containing only lower-case letters or spaces.
  //
  // A run is defined as a sequence of K>2 contiguous copies of the same
  // character c.
  // For example, "aaa" is a run with K=3 and c='a'.
  // This function returns a string based on uncompressed, where every run is
  // replaced with the string
  //   COUNTc
  // where COUNT is the base-10 representation of K. Non-run characters are
  // left as-is.
  //
  // Example inputs and outputs:
  //   "aaa" -> "3a"
  //   "heloooooooo there" -> "hel8o there"
  //   "footloose and fancy free" -> "f2otl2ose and fancy fr2e"
  //
  // Throws std::invalid_argument if the string contains invalid characters.
  std::string run_length_encode(const std::string& uString) {
    string cString = "";
    if (uString.empty()){
      return cString;
    }
    for (int i = 0; i < uString.size(); ++i){
      if (!islower(uString[i]) and !isspace(uString[i])){
        throw invalid_argument("ERROR: The input string contains invalid characters. Only lowercase characters and spaces are allowed.*");
      }
    }

    char runChar = uString[0];
    int runLength = 1;

    for (int i = 1 ; i < uString.size(); ++i){
      char capturedChar = uString[i];
      if (capturedChar == runChar){
        runLength++;
      }else{
        append_run(cString, runChar, runLength);
        runChar = capturedChar;
        runLength = 1;
      }
    }
    append_run(cString, runChar, runLength);
    return cString;
  }

  // Returns the longest substring of text, such that every character in the
  // substring appears at least k times in text.
  // If there are ties, the substring that appears first is returned.
  std::string longest_frequent_substring(const std::string& text, unsigned k) {
     string cand;
      int n = text.length();
      unordered_map <char, int> freq;
      for (int i = 0; i < n; i++) //keep track of words freq and add it into an unordered map 
      {
 
          if (freq.find(text[i]) == freq.end())
          {
              freq.insert(make_pair(text[i], 1));
          }

          else
          {
              freq[text[i]]++;
          }
      }
      string best = "";
      for (int b = 0; b <= n - 1; b++)  // double for loop to generate all possible substring
      {
          for (int e = b + 1; e <= n; e++)
          {
              int j = 0;
              cand = text.substr(b, e - b);
              while(j < cand.size()) {  // while loop to check if all character in cand meet the requirement and if it does then it become the best
                 if (freq[cand[j]] < k)
                   break;
                  j++;
              }
                    if (j == cand.size() && cand.size() > best.size())
                    best = cand;

          }

      }
      return best;
   
  }

  // Reformats a string containing a date into YYYY-MM-DD format.
  //
  // input may be formatted in one of four patterns:
  // 1. Y-M-D
  //    where Y, M, and D are positive integers
  // 2. M/D/Y
  //    where Y, M, and D are positive integers
  // 3. MONTH DAY, YEAR
  //    where
  //    - MONTH is a case-insensitive name of a month, ex.
  //      "january", "FEBRUARY", "March", etc.
  //    - DAY is a positive integer representing a day, e.x. "15"
  //    - YEAR is a positive integer representing a year, e.x. "2022"
  // 4. MON DAY, YEAR
  //    where
  //    - MON is a case-insensitive three-letter abbreviation of a month, ex.
  //      "jan", "FEB", "Mar", etc.
  //    - DAY is the same as above
  //    - YEAR is the same as above
  //
  // Any leading spaces or trailing spaces are ignored.
  //
  // Returns a string in strict YYYY-MM-DD format.
  //
  // Throws std::invalid argument if:
  // - input does not fit any of the four patterns
  // - MONTH is not a valid month name
  // - MON is not a valid month abbreviation
  // - DAY is not in the range [1, 31]
  // - YEAR is not in the range [1900, 2099]
  bool pYear(string& input){
     int comp;
     stringstream ss(input);
     ss>>comp;

  if(comp>=1900 && comp <=2099){
    return true;
  }else{throw invalid_argument("invalid inputs"); return false;}
}

bool p1Month(string& input){

  int comp;
  stringstream ss(input);
  ss>>comp;
  if(comp>=1 && comp <=12){
    return true;
  }else{throw invalid_argument("invalid inputs"); return false;}
}

bool pDay(string& input){
  int comp;
  stringstream ss(input);
  ss >> comp;
  if(comp>=1 && comp <=31){
    return true;
  }else{throw invalid_argument("Invalid inputs"); return false;}
}

string monthConversion(string& input, string arr[]){
  string word = input;
  for(int i =0; i < word.length(); i++){
    word[i] = toupper(word[i]);
  }
  if(word =="JANUARY" || word == "JAN"){ return "01";}
  else if(word =="FEBRUARY" || word == "FEB"){return "02";}
  else if(word =="MARCH" || word == "MAR"){return "03";}
  else if(word =="APRIL" || word == "APR"){return "04";}
  else if(word =="MAY"){return "05";}
  else if(word =="JUNE" || word == "JUN"){return "06";}
  else if(word =="JULY" || word == "JUL"){return "07";}
  else if(word =="AUGUST" || word == "AUG"){return "08";}
  else if(word =="SEPTEMBER" || word == "SEP"){return "09";}
  else if(word =="OCTOBER" || word == "OCT"){return "10";}
  else if(word =="NOVEMBER" || word == "NOV"){return "11";}
  else if(word =="DECEMBER" || word == "DEC"){return "12";}
  else{throw invalid_argument("invalid argument."); return word;}
    }



void append_date(string y, string m, string d, string D){
  D = y + "-" + m +"-" + d;
}
std::string reformat_date(const std::string& input) {

    string months[] = { "JANUARY","JAN","FEBRUARY","FEB","MARCH","MAR","APRIL","APR","MAY",
    					"JUNE","JUN","JULY","JUL","AUGUST","AUG","SEPTEMBER","SEP",
    					"OCTOBER","OCT","NOVEMBER","NOV","DECEMBER","DEC"};

  string cInput = input;
  int size = cInput.length();
	string month = "";
	string day = "";
	string year = "";
	string D = "";
	size_t pos = 0;


	for (int j = 1; j < input.size(); j++) {
	   //while (pos !=isspace(input[j])) {
			if (input.find("-")) { //YYYY-MM-DD
				pos = cInput.find("-");
				year = cInput.substr(0, pos);
				//p1Year(year);
				cInput.erase(0, pos);
				pos = cInput.find("-");
				month = cInput.substr(0, pos);
				//p1Month(month);
				cInput.erase(0, pos);
				day = cInput.substr(0,pos);
				//p1Day(day);
      }
      else if(input.find("/")){ //MM/DD/YYYY
        pos = cInput.find("/");
        month = cInput.substr(0,pos);
        cInput.erase(0,pos);
        pos = cInput.find("/");
        day = cInput.substr(0,pos);
        cInput.erase(0,pos);
        year = cInput;
      }
      else if(input.find(" ")){
        pos = cInput.find(" ");
        month = cInput.substr(0,pos);
        month = monthConversion(month, months);
        cInput.erase(0,pos);
        pos = cInput.find(" ");
        day = cInput.substr(0,pos);
        cInput.erase(0,pos);
        pos = cInput.find(" ");
        year = cInput;
      }

    //  }
    }
				if (pDay(day) && p1Month(month) && pYear(year)) {
					append_date(year, month, day, D);
					return D;
				}
        else {throw invalid_argument("invalid argument."); return input;}
			}


}
