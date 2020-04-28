#pragma once
#include <iostream>
using namespace std;

struct listElement
{
	char symbol; 
 	int frequency;
	string code; 
	listElement* next, * prev; 
};

class list
{
private:
	listElement* head, * tail;

public:
	list() // constructor
	{
		head = nullptr;
		tail = nullptr;
	}

	~list() // destructor
	{
		if (head) // if list is not empty
		{
			listElement* buf;
			while (head != tail) // until there is one element
			{
				buf = head;
				head = head->next;
				delete buf;
			}
			delete head;
			head = nullptr;
			tail = nullptr;
		}
	}

	void check(char symbolInput) // filling the symbols list and counting frequency
	{
		bool found = false; // if symbol is already in list -> true
		if (head) 
		{
			listElement* cur = head; // current element
			if (cur->symbol == symbolInput) // if it is first symbol
			{
				found = true;
				cur->frequency++;
			}
			while ((cur != tail) && (!found)) // until no more elements left or symbol found 
			{
				cur = cur->next;
				if (cur->symbol == symbolInput) // if symbol found
				{
					found = true;
					cur->frequency++;
				}
			}
			if (!found) this->pushBack(symbolInput); // if there is no this symbol in the list - add it 
		}
		else this->pushBack(symbolInput); // if list is empty - add symbol
	}

	void input(string text) // input of data
	{
		int length = text.length();
		for (int i = 0; i < length; i++)
		{
			check(text[i]);
		}
	}

	void sortingFrequences()
	{
		if (head != tail) // if more than 2 elements in list
		{
			bool swap; // if there were swaps on this step
			listElement* buf, * cur; // temporary element and current element
			do
			{
				swap = false;
				cur = head; 
				while (cur != tail) 
				{
					if (cur->frequency > cur->next->frequency) // condition of swapping
					{
						buf = cur->next; // the next element after current
						if (cur == head) head = buf; // if current is first element, change head
						if (buf == tail) tail = cur; // if next element is last, change tail
						if ((buf->next)&&(cur->prev)) // if there are elements on two sides by those two elements
						{
							cur->next = buf->next;
							buf->prev = cur->prev;
							cur->prev->next = buf;
							buf->next->prev = cur;
						}
						else if (buf->next) // if only on right side
						{
							cur->next = buf->next;
							buf->prev = nullptr;
							buf->next->prev = cur;
						}
						else if (cur->prev) // if only on left side
						{
							buf->prev = cur->prev;
							cur->next = nullptr;
							cur->prev->next = buf;
						}
						else // if not
						{
							buf->prev = nullptr;
							cur->next = nullptr;
						}
						buf->next = cur; 
						cur->prev = buf;
						cur = buf;
						swap = true; // we swapped elements
					}
					cur = cur->next;
				}
			} while (swap);
		}
	}

	void fano() // activator of recursive function
	{
		if (head)
		{
			string empty = "";
			fanoRec(empty, empty, head, tail);
		}
		else throw logic_error("Empty list");
	}
	
	void fanoRec(string& branch, string& fullBranch, listElement* start, listElement* end) // counting codes for symbols (branch - last turn to this element(1/0), fullBranch- all turns to last element)
	{
		listElement* cur, * leftEnd, * rightStart; // current element, last element in left part, first element in right part
		double fullSum = 0; // sum of all elements frequences
		int sum = 0; // sum which we count to take a half
		string curBranch = ""; // path to this element

		curBranch = fullBranch + branch;
		if (start == end) // if element is leaf
		{
			start->code = curBranch;
			return;
		}
		cur = start;
		fullSum += start->frequency;
		while (cur != end) // counting sum of all elements
		{
			cur = cur->next;
			fullSum += cur->frequency;
		}
		fullSum /= 2.; // counting a half of sum
		cur = start;
		while (fabs(fullSum - (sum + cur->frequency)) < fabs(fullSum - sum) && (cur!=end)) // until we get half or one element element
		{
			sum += cur->frequency;
			cur = cur->next;
		}
		rightStart = cur;
		leftEnd = cur->prev;
		string zero = "0";
		string one = "1";
		fanoRec(zero, curBranch, start, leftEnd); // the same for left part
		fanoRec(one, curBranch, rightStart, end); // the same for right part
	}

	string codeSearch(char symbol) // searching the code of symbol
	{
		if (head)
		{
			listElement* cur = head;
			if (cur->symbol == symbol) return cur->code;
			while (cur != tail)
			{
				cur = cur->next;
				if (cur->symbol == symbol) return cur->code;
			}
		}
		else return "";
	}

	int frequencySearch(char symbol) // searching the frequency of symbol
	{
		if (head)
		{
			listElement* cur = head;
			if (cur->symbol == symbol) return cur->frequency;
			while (cur != tail)
			{
				cur = cur->next;
				if (cur->symbol == symbol) return cur->frequency;
			}
		}
		else return 0;
	}

	string fanoCoding(string decodedText) // coding the text by codes
	{
		string codedText = "";
		input(decodedText);
		sortingFrequences();
		fano();
		int length = decodedText.length();
		for (int i = 0; i < length; i++)
		{
			codedText += this->codeSearch(decodedText[i]);
		}
		return codedText;
	}

	string fanoDecoding(string codedText)
	{
		int length = codedText.length();
		int iterator = 0, level = 0; // iterator for string, level of code (amount of digits in it)
		string decodedText = "";
		listElement* start, * end, * cur; // first and last elements in search area, current element
		while (iterator < length)
		{
			start = head;
			end = tail;
			level = 0;
			while (start != end) // until element found
			{
				if (codedText[iterator + level] == '0') // checking each symbol of code by level determination
				{
					cur = start; // if zero - we must search from start
					while (cur->code[level] != '1') // searching the first element of right side
					{
						cur = cur->next;
					}
					end = cur->prev; // determining the last element of left side
					level++; // change the level to next symbol
				}
				else // the same, but from end to start
				{
					cur = end;
					while (cur->code[level] != '0')
					{
						cur = cur->prev;
					}
					start = cur->next;
					level++;
				}
			}
			decodedText += start->symbol;
			iterator += level; // moving to next code
		}
		return decodedText;
	}

	void tableOutput() // output the table of frequences and codes
	{
		if (head)
		{
			listElement* cur = head;
			cout << cur->symbol << " || Частота: " << cur->frequency << " || Код: " << cur->code << endl;
			while (cur != tail)
			{
				cur = cur->next;
				cout << cur->symbol << " || Частота: " << cur->frequency << " || Код: " << cur->code << endl;
			}
			cout << endl;
		}
	}

	void pushBack(char symbolInput) // adding an element to the end of the list
	{
		listElement* newElement = new listElement;
		if (head) // if list is not empty
		{
			tail->next = newElement;
			newElement->next = nullptr;
			newElement->prev = tail;
			tail = newElement;
			newElement->symbol = symbolInput;
			newElement->frequency = 1;
			newElement->code = "";
		}
		else
		{
			head = newElement;
			tail = head;
			newElement->next = nullptr;
			newElement->prev = nullptr;
			newElement->symbol = symbolInput;
			newElement->frequency = 1;
			newElement->code = "";
		}
	}

};