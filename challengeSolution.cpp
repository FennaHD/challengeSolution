#include <iostream>
#include <map>
#include <vector>
#include <string>

int RomanToNumeral(std::string roman, std::map<char,int> romanLetters);
void PrintMenu();
std::string NumeralToRoman(int numeral);

int main() {
  //assumptions: only give options stated on the menu

  //create roman map
  std::map<char,int> romanLetters;
  romanLetters['I'] = 1;
  romanLetters['V'] = 5;
  romanLetters['X'] = 10;
  romanLetters['L'] = 50;
  romanLetters['C'] = 100;
  romanLetters['D'] = 500;
  romanLetters['M'] = 1000;

  PrintMenu();
  int answer;
  std::cin >> answer;
  while (answer != 3) {
    if (answer == 1) {
      std::string roman;
      std::cout << "Provide Roman Numeral to Translate" << std::endl;
      std::cin >> roman;
      int solution = RomanToNumeral(roman, romanLetters);
      if (solution == -1) {
        std::cout << "Invalid Roman Numeral" << std::endl;
      } else {
       std::cout << "The translation for " << roman << " is " << solution << std::endl;
      }
    } else if (answer == 2) {
      int numeral;
      std::cout << "Provide Modern Number to Translate" << std::endl;
      std::cin >> numeral;
      std::string solution = NumeralToRoman(numeral);
      std::cout << "The translation for " << numeral << " is " << solution << std::endl;
    }
    PrintMenu();
    std::cin >> answer;
  }
  return 0;
}

int RomanToNumeral(std::string roman, std::map<char,int> romanLetters) {
  int count = 0;
  for (unsigned int i = 0; i < roman.size(); i++) {
    //filters last digit, as it won't have a succesor
    if (i < roman.size() - 1) {
      //checks for substractive notation, return correct number and skips succesor
      if (romanLetters[roman.at(i)] < romanLetters[roman.at(i+1)]) {
        if (romanLetters[roman.at(i)]*10 >= romanLetters[roman.at(i+1)]){
          int numberToAdd = romanLetters[roman.at(i+1)] - romanLetters[roman.at(i)];
          count += numberToAdd;
          ++i;
        } else {
          count = -1;
          break;
        }
      } else {
        count += romanLetters[roman.at(i)];
      }
    } else {
      count += romanLetters[roman.at(i)];
    }
  }
  return count;
}

std::string NumeralToRoman(int numeral) {
  std::vector<int> numbers{1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
  std::vector<std::string> romans{"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
  std::string solution = "";
  // find largest number that is less than or equal to "numeral"
  while(numeral != 0) {
    for (unsigned int i = numbers.size()-1; i >= 0; --i) {
      if (numbers.at(i) <= numeral) {
        solution.append(romans.at(i));
        //new "numeral" is old numeral - largest number
        numeral -= numbers.at(i);
        break;
      }
    }
  }
  return solution;
}

void PrintMenu() {
  std::cout << "Pick an option from the menu" << std::endl
            << "1 - Translate from Roman Numerals to Modern Numbers" << std::endl
            << "2 - Translate from Modern Numbers to Roman Numerals" << std::endl
            << "3 - Exit" << std::endl;
}
