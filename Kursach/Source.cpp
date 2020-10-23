#include <iostream> 
#include <locale.h>
#include <windows.h>
#include "Header.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	
	int choice;
	while (true)
	{
		system("CLS");
		std::cout <<
			"1. Вход под администратором" << std::endl <<
			"2. Вход под пользователем" << std::endl <<
			"3. Выход" << std::endl;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{		
			case 1:
				adminAuthorization();
				break;
			case 2:
				userAuthorization();
				break;
			default:
				return 0;		
		}
	}
}

