#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#define CONSOLE(x) std::cout << x << std::endl
#define LOG(x) std::cout << x

class application
{
	std::string numPlate;
	int choices = 0;

	std::string getTime()
	{
		time_t seconds;
		time(&seconds);
		return std::to_string(seconds);
	}
	void regInsertion()
	{
		std::string text{};
		std::ofstream file("res/database.txt", std::ios::app);
		text = numPlate + "," + getTime() + "\n";
		file << text;
		file.close();
	}
public:
	int get()
	{
		return choices;
	}
	void clear()
	{
		system("cls");
	}
	int parkReg()
	{
		clear();
		CONSOLE("No Spaces");
		CONSOLE("Number Plate: ");
		std::cin.ignore();
		std::getline(std::cin, numPlate);
		if (numPlate == "abcdefgh")
		{
			return 0;
		}
		regInsertion();
		return 1;
	}
	int mainMenu()
	{
		clear();
		choices = 0;
		CONSOLE("1. Register your car");
		CONSOLE("2. Pay your car");
		std::cin >> choices;
		return choices;
	}
	int payBack()
	{

	}
};

int main()
{
	application app;
starting:
	app.clear();
	switch (app.mainMenu())
	{
	case 1:
		if (app.parkReg())
		{
			goto starting;
		}
		break;
	case 2:
		break;
	default:
		if (app.get() == 123456)
		{
			break;
		}
		goto starting;
		break;
	}
}