#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

class Word
{
private:

	std::string word;
	bool syllable;

	bool isVowel(char letter) const
	{

		char vowel[] = { 'a', 'e', 'j', 'i', 'o', 'u', '5', '7', '8', '9' };
		for (int i = 0; i < sizeof(vowel); ++i)
		{
			if (vowel[i] == letter)
			{
				return true;
			}
		}
		return false;
	}

	bool isSonorant(char letter) const
	{
		char sonorant[] = { 'y', 'l', 'm', 'n', 'r' };
		for (int i = 0; i < sizeof(sonorant); ++i)
		{
			if (sonorant[i] == letter)
			{
				return true;
			}
		}
		return false;
	}

	bool isConsonant(char letter) const
	{
		char consonant[] = { 'b', 'v', 'g', 'd', '1', 'z', 'y', 'k', 'l', 'm', 'n', 'p', 'r', 's', 't', 'f', 'h', 'c', '4', 'w', '2' };
		for (int i = 0; i < sizeof(consonant); ++i)
		{
			if (consonant[i] == letter)
			{
				return true;
			}
		}
		return false;
	}

	void myPrint(int b, int e)
	{
		if (syllable)
		{
			std::cout << ", ";
		}
		std::cout << '[';
		for (int i = b; i < e; ++i)
		{
			std::cout << word.at(i);
		}
		std::cout << ']';
		syllable = true;
	}

	void splitOnSyllablesAndPrint(int b, int e)
	{
		int countVowels = 0;
		for (int i = b; i < e; ++i)
		{
			if (isVowel(word.at(i)))
			{
				++countVowels;
			}
		}
		if (countVowels == 0)
		{
			myPrint(b, e);
			return;
		}
		int j = b;
		for (int i = b; i < e; ++i)
		{
			if ((isVowel(word.at(i))) && (countVowels > 1))
			{
				--countVowels;
				if ((i + 1 < e) && (isSonorant(word.at(i + 1)) && (i + 2 < e) && (isConsonant(word.at(i + 2)))))
				{
					myPrint(j, i + 2);
					j = i + 2;
					++i;
				}
				else
				{
					myPrint(j, i + 1);
					j = i + 1;
				}
			}
		}
		if (syllable)
		{
			std::cout << ", ";
		}
		syllable = true;
		std::cout << "[";
		for (int i = j; i < e; ++i)
		{
			std::cout << word.at(i);
		}
		std::cout << "]";
	}

public:

	Word()
	{
		syllable = false;
		std::cin >> word;
	}

	void printSyllables()
	{
		if (word.size() == 1)
		{
			std::cout << word;
			return;
		}
		int j = 0;
		for (unsigned int i = 0; i < word.size(); ++i)
		{
			if ((word.at(i) == '-') && (i != 0))
			{
				splitOnSyllablesAndPrint(j, i);
				j = i + 1;
			}
		}
		splitOnSyllablesAndPrint(j, word.size());
	}

	friend std::istream& operator >> (std::istream& in, Word& w)
	{
        in >> w.word;
	}
};

int main()
{
    freopen("konvert", "r", stdin);
    freopen("syllables", "w", stdout);
	while (!std::cin.eof())
    {
        Word word;
        std::cin >> word;
        word.printSyllables();
    }
	return 0;
}
