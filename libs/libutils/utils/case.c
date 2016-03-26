#include <string.h>
#include <utils.h>

// TODO: possibly use glibc's implementation
char char_tolower(char c) {
	return (c >= 65 && c <= 90) ? c + 32 : c;
}

char char_toupper(char c) {
	return (c >= 97 && c <= 122) ? c - 32 : c;
}

char shiftify(char c) {
	return (c >= 97 && c <= 122) ? c - 32 : c + 16;
	/*if (c >= 97 && c <= 122)
		return c - 32;
	//TODO: faster
	switch (c) {
		case '`': return '~';
		case '1': return '!';
		case '2': return '@';
		case '3': return '#';
		case '4': return '$';
		case '5': return '%';
		case '6': return '^';
		case '7': return '&';
		case '8': return '*';
		case '9': return '(';
		case '0': return ')';
		case '-': return '_';
		case '=': return '+';
	};*/
}

char isupper(char c) {
	return c >= 65 && c <= 90;
}

char islower(char c) {
	return c >= 97 && c <= 122;
}

char isletter(char c) {
	return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

char isdigit(char c) {
	return c >= 48 && c <= 57;
}

char isalpha(char c) {
	return (c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

/*const char* tolower(const char* string) {
	const char* result = strdup(string);
	for (int i = 0; i < strlen(string); i++)
		result[i] = char_tolower(string[i]);
	return result;
}

const char* toupper(const char* string) {
	const char* result = strdup(string);
	for (int i = 0; i < strlen(string); i++)
		result[i] = char_toupper(string[i]);
	return result;
}*/

//todo: title case - compare strings and stuff, sentence case (full stops)
//if it's not and, etc then string[word_start] = toupper(string[word_start])