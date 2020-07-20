#include "Console.h"
#include <algorithm>

#define INDENT "     "

namespace Console {

	//whether the console is locked
	static bool locked = false;

	//the number of indents to use
	static int indent = 0;

	//the last character previously written to the screen
	static char lastChar = '\n';

	void Lock() {
		locked = true;
	}

	void Unlock() {
		locked = false;
	}

	bool IsLocked() {
		return locked;
	}

	void Pause() {
		
		if (!locked)
			Ignore();
	}

	void IncreaseIndent() {
		if (!locked)
			indent++;
	}

	void DecreaseIndent() {
		if (!locked) {
			indent--;

			//indent cannot be less than 0
			indent = std::max(indent, 0);
		}
	}

	void Write(const std::string& message) {

		//only write the indents if this is a beginning of a new line
		if (!locked) {
			if (lastChar == '\n')
				for (int i = 0; i < indent; i++)
					std::cout << INDENT;

			std::cout << message;

			//store the last character entered
			lastChar = message[message.length() - 1];
		}
		
	}

	void GetLine(std::string& line)
	{
		if ( !locked ) {
			std::getline(std::cin, line);
			lastChar = '\n';
		}
	}

	void Ignore() {

		if (!locked) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			lastChar = '\n';
		}
		
	}

}