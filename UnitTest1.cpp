#include "pch.h"
#include "CppUnitTest.h"
#include "c:/Users/vlad-/source/repos/Aisd2(4 sem)/Aisd2(4 sem)/List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
Assert assert;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(fanoEmptyList)
		{
			bool error = false;			
			list* newList = new list;
			try { newList->fano(); }
			catch (logic_error) { error = true; }
			assert.IsTrue(error);
			delete newList;
		}

		TEST_METHOD(fanoCodingDecoding)
		{
			string text = "wwwcom", codedText, decodedText;
			list* newList = new list;
			codedText = newList->fanoCoding(text);
			decodedText = newList->fanoDecoding(codedText);
			assert.AreEqual(text, decodedText);
			delete newList;
		}

		TEST_METHOD(check)
		{
			char letter = 'w';
			list* newList = new list;
			newList->check(letter);
			assert.AreEqual(1, newList->frequencySearch(letter));
			delete newList;
		}

		TEST_METHOD(input)
		{
			string text = "wwwcom";
			list* newList = new list;
			newList->input(text);
			assert.AreEqual(3, newList->frequencySearch('w'));
			delete newList;
		}
	};
}
