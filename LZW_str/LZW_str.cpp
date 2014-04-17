#include <string>
#include <map>

// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.
template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result) {
	// Build the dictionary.
	int dictSize = 256;
	std::map<std::string, int> dictionary;
	for (int i = 0; i < 256; i++)
		dictionary[std::string(1, i)] = i;

	std::string w;
	for (std::string::const_iterator it = uncompressed.begin();
		it != uncompressed.end(); ++it) {
		char c = *it;
		std::string wc = w + c;
		if (dictionary.count(wc))
			w = wc;
		else {
			*result++ = dictionary[w];
			// Add wc to the dictionary.
			dictionary[wc] = dictSize++;
			w = std::string(1, c);
		}
	}

	// Output the code for w.
	if (!w.empty())
		*result++ = dictionary[w];
	return result;
}

// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end) {
	// Build the dictionary.
	int dictSize = 256;
	std::map<int, std::string> dictionary;
	for (int i = 0; i < 256; i++)
		dictionary[i] = std::string(1, i);

	std::string w(1, *begin++);
	std::string result = w;
	std::string entry;
	for (; begin != end; begin++) {
		int k = *begin;
		if (dictionary.count(k))
			entry = dictionary[k];
		else if (k == dictSize)
			entry = w + w[0];
		else
			throw "Bad compressed k";

		result += entry;

		// Add w+entry[0] to the dictionary.
		dictionary[dictSize++] = w + entry[0];

		w = entry;
	}
	return result;
}

#include <iostream>
#include <iterator>
#include <vector>
#include <conio.h>
#include <stdio.h>

int main() {


	std::vector<int> compressed;
	std::cout << "\n\nThe string to be compressed is 'LOVE EACH AND EVERY PEOPLE OF THE WORLD'\n\n\n";
	compress("LOVE EACH AND EVERY PEOPLE OF THE WORLD", std::back_inserter(compressed));
	std::cout << "The compressed string to a list of output symbols -->  \n\n ";
	copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
	std::string decompressed = decompress(compressed.begin(), compressed.end());
	std::cout << "\n\nThe decompressed string is -->  \n\n " << decompressed << std::endl;
	printf("\n\nPress any key to continue...\n");
	_getch();
	return 0;
}