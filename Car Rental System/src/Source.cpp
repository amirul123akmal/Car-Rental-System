#include <iostream> // cout, cin
#include <fstream> // ifstream, ofstream, fstream
#include <string> // std::string, std::to_string, std::getline
#include <sstream> // std::stringstream
#include <time.h> // time
#include <thread> // sleep_for
#include <chrono> // second

#define CONSOLE(x) std::cout << x << std::endl
#define LOG(x) std::cout << x

class application
{
	std::string numPlate;
	float timeDelta = 0;
	int choices = 0, line_counter = 0;

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
	bool checkCredential()
	{
		std::string line{}, plate;
		bool enabled = false;
		std::fstream file("res/database.txt", std::ios::in);
		while (std::getline(file, line))
		{
			std::istringstream collectedPlate(line);
			while (std::getline(collectedPlate, plate, ','))
			{
				if (plate == numPlate)
				{
					enabled = true;
					continue;
				}
				if (enabled)
				{
					timeDelta = (float)(std::stoi(getTime()) - std::stoi(plate));
					file.close();
					return enabled;
				}
			}
		}
		file.close();
		return false;
	}
	float getPrice()
	{
		if ( ( timeDelta / 60 ) < 1.01)
		{
			return 0;
		}
		timeDelta /= 60;
		if (timeDelta > 5)
		{
			timeDelta -= 5;
			return ( timeDelta * (float)6 ) + (float)25;
		}
		return timeDelta * (float)5;

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
		CONSOLE(
			"=====PRICE RATE=====\n"
			"First 1 Hour free\n"
			"1 Hour = RM 5.00\n"
			"\nAfter 5 Hour , 1 hour = RM 6.00 \n"
			"====================\n"
		);
		CONSOLE("1. Register your car");
		CONSOLE("2. Pay your car");
		std::cin >> choices;
		return choices;
	}
	void payBack()
	{
		clear();
		CONSOLE("Your car's Plate Number: ");
		std::cin.ignore();
		std::getline(std::cin, numPlate, '\n');
		if (checkCredential())
		{
			float price = getPrice();
			float pay;
		again:
			printf("Please pay : RM %.2f", price);
			LOG("Money: ");
			std::cin.ignore();
			std::cin >> pay;
			if (pay != price)
			{
				clear();
				CONSOLE("You need to pay the same amount");
				std::this_thread::sleep_for(std::chrono::seconds(3));
				goto again;
			}
		}
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
		app.payBack();
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