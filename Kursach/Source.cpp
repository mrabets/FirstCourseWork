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
			"1. ���� ��� ���������������" << std::endl <<
			"2. ���� ��� �������������" << std::endl <<
			"3. �����" << std::endl;
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

