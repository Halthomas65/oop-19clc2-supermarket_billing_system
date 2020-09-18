#include "Tokenizer.h"

vector<string> Tokenizer::split(string haystack, string needle) {
    vector<string> tokens;
    int startPosition = 0;
    while (true) {
        size_t position = haystack.find(needle, startPosition);
        if (position != string::npos) {
            string token = haystack.substr(startPosition, position - startPosition);
            startPosition = position + needle.length();
            tokens.push_back(token);
        }
        else {
            string token = haystack.substr(startPosition, haystack.length());
            tokens.push_back(token);
            break;
        }
    }
    return tokens;
}
