#pragma once
#include <iostream>
#include <string>
#include <cstdarg>

//macro to convert an integer to a string
#define itos(A) std::to_string(A)

//used to print game text to the console. std::cout should not be used 
// except for debugging purposes.
namespace Console {

	void SetFontScale(int scale);

	//locks the console. calls to Write will do nothing
	void Lock();

	//unlocks the console. calls to Write will now work
	void Unlock();

	//returns whether the console is locked
	bool IsLocked();

	//pauses the console, user must press enter to unpause
	void Pause();

	//ignores all characters in the console up until the next newline
	void Ignore();

	//increases the indent level of future calls to Write
	void IncreaseIndent();

	//decreases the indent level of new text.
	void DecreaseIndent();

	//writes a message to the console
	void Write(const std::string& message);

	// returns the entire line of input text
	void GetLine(std::string& line);

	//gets input from the console. specify the data type of the input, 
	// the number of inputs requested, and pointers to store the recieved data
	// if an invalid input is entered, the function waits until the user types something valid
	template <class T>
	void Get(int num, ...) {

		if (IsLocked()) {
			return;
		}

		va_list list;
		va_start(list, num);

		for (int i = 0; i < num; ++i) {
			T* arg = va_arg(list, T*);

			std::cin >> *arg;
			while (true) {

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> *arg;
				}

				if (!std::cin.fail())
					break;

			}
		
		}

		va_end(list);
		Ignore();
	}

}
