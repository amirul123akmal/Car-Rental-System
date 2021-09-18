#include <iostream> // cout, cin
#include <fstream> // ifstream, ofstream, fstream
#include <string> // std::string, std::to_string, std::getline
#include <sstream> // std::stringstream
#include <time.h> // time
#include <thread> // sleep_for
#include <vector> // std::vector
#include <chrono> // second

#define CONSOLE(x) std::cout << x << std::endl
#define LOG(x) std::cout << x

class application
{
	std::string numPlate;
	float timeDelta = 0;
	int choices = 0, lineCounter = 0;

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
					lineCounter++; 
					continue;
				}
				if (!enabled)
				{
					lineCounter++;
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
	void clearStore(float& price)
	{
		// Initialization and setup for remove from database.txt and move it to history.txt
		std::ifstream file("res/database.txt", std::ios::in);
		std::ofstream tempFile("res/temp.txt", std::ios::out);
		std::ofstream history("res/history.txt", std::ios::app);

		// storing all the data into array
		std::vector<std::string> dbData{};
		std::string temp, temp2;
		while (!file.eof())
		{
			file >> temp;
			dbData.push_back(temp);
		}
		file.close();
		// last line gets duplicated
		// so we need to remove it
		dbData.pop_back();

		temp = dbData[--lineCounter] + "\n";
		int cap = dbData.capacity();
		dbData.erase(dbData.begin() - (lineCounter));
		// -2 because -1 = remove the 1 we wanted to, -1 = remove the last duplicated line
		int limit = dbData.capacity() - 2;
		int counter = 0;
		while (counter < limit)
		{
			temp2 = dbData[counter++] + "\n";
			tempFile << temp2;
		}
		tempFile.close();
		history << temp;
		history.close();

		system("del res\\database.txt");
		system("rename res\\temp.txt database.txt");
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
			float price = std::ceil(getPrice() * 100) / 100;
			float pay;
		again:
			pay = 0;
			CONSOLE("Enter 123 to exit");
			printf("Please pay : RM %.2f", price);
			LOG("\nMoney: ");
			std::cin >> pay;
			if ( pay == 123)
			{
				goto exit;
			}
			if (pay != price)
			{
				clear();
				CONSOLE("You need to pay the same amount");
				std::this_thread::sleep_for(std::chrono::seconds(3));
				goto again;
			}
			clearStore(price);

		exit:
			CONSOLE("");
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
		goto starting;
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