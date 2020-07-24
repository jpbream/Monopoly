#include "Console.h"
#include <algorithm>
#include <Windows.h>

#undef max
#define INDENT "     "

#define MAX_ROW 10

namespace Console {

	//whether the console is locked
	static bool locked = false;

	//the number of indents to use
	static int indent = 0;

	//the last character previously written to the screen
	static char lastChar = '\n';

	static HANDLE stdCout = GetStdHandle(STD_OUTPUT_HANDLE);
	int numRows = 0;

	static void Scroll()
	{
		numRows++;

		CONSOLE_SCREEN_BUFFER_INFO sbInfo;
		SMALL_RECT rect;
		GetConsoleScreenBufferInfo(stdCout, &sbInfo);

		int height = sbInfo.srWindow.Bottom - sbInfo.srWindow.Top;
		int rowToScroll = sbInfo.srWindow.Top + (height / 3);

		if ( numRows > rowToScroll ) {
			rect.Top = numRows - rowToScroll;
			rect.Bottom = numRows - rowToScroll;
			rect.Left = 0;
			rect.Right = 0;

			SetConsoleWindowInfo(stdCout, FALSE, &rect);
		}
	}

	void SetFontScale(int scale)
	{
		PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX();
		font->cbSize = sizeof(CONSOLE_FONT_INFOEX);
		GetCurrentConsoleFontEx(stdCout, 0, font);
		font->dwFontSize.X = 10 * scale;
		font->dwFontSize.Y = 18 * scale;
		SetCurrentConsoleFontEx(stdCout, 0, font);
		delete font;
	}

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

			if ( lastChar == '\n' )
				Scroll();
		}
		
	}

	void GetLine(std::string& line)
	{
		if ( !locked ) {
			std::getline(std::cin, line);
			lastChar = '\n';
			Scroll();
		}
	}

	void Ignore() {

		if (!locked) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			lastChar = '\n';
		}
		
	}

}