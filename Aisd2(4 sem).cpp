#include <iostream>
#include <windows.h>
#include <string>
#include "List.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string text, codedText, decodedText;
	list* newList = new list;
	double codedMem, decodedMem, compression;
	cout << "Введите строку" << endl;
	getline(cin, text);
	codedText = newList->fanoCoding(text);
	decodedText = newList->fanoDecoding(codedText);
	newList->tableOutput();
	decodedMem = 8 * decodedText.length();
	codedMem = 2 * codedText.length();
	compression = decodedMem / codedMem;
	cout << "Закодированная строка: " << codedText << endl;
	cout << "Декодированная строка: " << decodedText << endl;
	cout << "Памяти до кодирования: " << decodedMem << " || Памяти после кодирования: " << codedMem << " || Коэф. сжатия: " << compression << endl;
	delete newList;
	return 0;
}
