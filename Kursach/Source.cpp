#include <locale.h>
#include <windows.h>
#include <stdio.h> 
#include <io.h> 
#include <cstring> 
#include <iostream> 
#include <conio.h> 
#include <time.h> 
#include <string> 

void adminAuthorization();
void adminMenu();
void userMenu();
int saveStruct(const char*, struct busTimetable*, int n);
int loadStruct(const char*);
busTimetable* AddStruct(busTimetable*, const int);
void setData(busTimetable*, const int);
void changeData(busTimetable*, const int);

struct busTimetable
{
	int numberBusTrip;
	struct typeBus
	{
		char colour[20];
		char size[20];
	} type;
	char destination[20];
	char departureTime[20];
	char arrivalTime[20];
};
//struct busTimetable trip[] = { 77, "green", "big", "Minsk", "22:10", "12:44", 312, "brown", "little", "Moscow", "23:28", "07:33" };


//void printBestTrip();

const char* dataFile = "dataBusTimetable.txt";
struct busTimetable* trip = 0;
int tripAmount = 0;

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
				adminMenu();
				break;
			case 2:
				userMenu();
				break;
			default:
				return 0;
				
		}
	}

	return 0;
}

void adminAuthorization()
{
	FILE* file_authorization;
	file_authorization = fopen("authorization.txt", "r");
	char login[255], password[255], file_str[255];
	std::cout << "������� ����� ��������������" << std::endl;
	std::cin >> login;
	//std::cout << "������� ������ ��������������" << std::endl;
	//std::cin >> password;
	fgets(file_str, 255, file_authorization);
	if (!strcmp(login, file_str))
	{
		std::cout << "����������� ������ �������" << std::endl;
	}
	else
	{
		std::cout << "�� �� ������ �����������" << std::endl;
	}
}

void userMenu()
{
	while (true)
	{
		std::cout <<
			"1. ����������� ��� ���������� �����" << std::endl <<
			"2. ������ ����� �� ����� ����������" << std::endl <<
			"3. ������ ����� �� ������� �����������" << std::endl <<
			"4. ����� � �������� ����" << std::endl;

		int choice;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			loadStruct(dataFile);
			break;

		case 2:
			char city[20];
			std::cout << "������� �����: " << std::endl;
			std::cin >> city;
			for (int i = 0; i < tripAmount; i++)
			{
				if (!strcmp(city, trip[i].destination))
				{
					std::cout << "������ ���� � �������: " << i + 1 << std::endl;
				}
			}
			break;

		case 3:
			char time[20];
			std::cout << "������� ����� �����������: " << std::endl;
			std::cin >> time;
			for (int i = 0; i < tripAmount; i++)
			{
				if (!strcmp(time, trip[i].departureTime))
				{
					std::cout << "������ ���� � �������: " << i + 1 << std::endl;
				}
			}
			break;

		default:
			return;
		}
	}
}

void adminMenu()
{
	int choice;
	while (true)
	{
		int n;
		std::cout <<
			"1. ������� ���� � ����������� �������" << std::endl <<
			"2. �������� ����� ����" << std::endl <<
			"3. �������� ����" << std::endl <<
			"4. ������� ����" << std::endl <<
			"5. ����������� ��� ���������� ����� � ����� " << std::endl <<
			"6. ������������ ������ � ����" << std::endl <<
			"7. ���������� ��������������" << std::endl <<
			"8. ����� � ���� 1 - �� ������" << std::endl;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			if (FILE* dataBusTimetable = fopen(dataFile, "w"))
				std::cout << "���� ������� ������" << std::endl;
			else
				std::cout << "������ �������� �����" << std::endl;
			break;

		case 2:
			trip = AddStruct(trip, tripAmount);
			setData(trip, tripAmount);
			tripAmount++;
			break;

		case 3:
			int i;	
			std::cout << "�������� ����� �����. ����� ������: " << tripAmount << std::endl;
			std::cin >> i;
			if (i < 1 || i > tripAmount)
			{
				std::cout << "����� ������ �� ����������" << std::endl;
				break;
			}
			changeData(trip, i - 1);
			break;

			case 4:
				int number;
				std::cout << "�������� ����� ����� ��� ��������. ����� ������: " << tripAmount << std::endl;
				std::cin >> i;
				if (i < 1 || i > tripAmount)
				{
					std::cout << "����� ������ �� ����������" << std::endl;
					break;
				}
				//...
				break;
			case 5:
				loadStruct(dataFile);
				break;
			case 6:
				saveStruct(dataFile, trip, tripAmount);
				break;
			case 7:
				break;

			default:
				return;
		}
	}
}

int saveStruct(const char* filename, struct busTimetable* trip, int n)
{
	FILE* fileTemp;
	char* c;

	// ����� ������������ ������
	int size = n * sizeof(struct busTimetable);

	if ((fileTemp = fopen(filename, "wb")) == NULL)
	{
		perror("Error occured while opening file");
		return 1;
	}
	// ���������� ���������� ��������
	c = (char*)&n;
	for (int i = 0; i < sizeof(int); i++)
	{
		putc(*c++, fileTemp);
	}

	// ����������� ���������� � ���� ��� ���������
	c = (char*)trip;
	for (int i = 0; i < size; i++)
	{
		putc(*c, fileTemp);
		c++;
	}
	fclose(fileTemp);
	return 0;
}

int loadStruct(const char* filename)
{
	FILE* fileTemp;
	char* c;
	int m = sizeof(int);
	int n, i;

	// �������� ������ ��� ���������� ������
	int* pti = (int*)malloc(m);

	if ((fileTemp = fopen(filename, "r")) == NULL)
	{
		perror("Error occured while opening file");
		return 1;
	}
	// ��������� ���������� ��������
	c = (char*)pti;
	while (m > 0)
	{
		i = getc(fileTemp);
		if (i == EOF) break;
		*c = i;
		c++;
		m--;
	}
	//�������� ����� ���������
	n = *pti;

	// �������� ������ ��� ���������� ������� ��������
	struct busTimetable* ptr = (struct busTimetable*)malloc(n * sizeof(struct busTimetable));
	c = (char*)ptr;
	// ����� ������ ��������� ����������� �� �����
	while ((i = getc(fileTemp)) != EOF)
	{
		*c = i;
		c++;
	}
	// ������� ����������� ��������� � ����� �� �������
	std::cout << "���������� ���������� ������: " << n << std::endl;

	for (int k = 0; k < n; k++)
	{
		std::cout << std::endl <<
			k + 1 << " ����� �����: " << (ptr + k)->numberBusTrip << std::endl <<
			k + 1 << " ��� �������� (����): " << (ptr + k)->type.colour << std::endl <<
			k + 1 << " ��� �������� (������): " << (ptr + k)->type.size << std::endl <<
			k + 1 << " ���� ����������: " << (ptr + k)->destination << std::endl <<
			k + 1 << " ����� �����������: " << (ptr + k)->departureTime << std::endl <<
			k + 1 << " ����� ��������: " << (ptr + k)->arrivalTime << std::endl;
	}
	
	std::cout << std::endl;
	free(pti);
	free(ptr);
	fclose(fileTemp);
	return 0;
}

busTimetable* AddStruct(busTimetable* Obj, const int amount)
{
	if (amount == 0)
	{
		Obj = new busTimetable[amount + 1]; // ��������� ������ ��� ������ ���������
	}
	else
	{
		busTimetable* tempObj = new busTimetable[amount + 1];

		for (int i = 0; i < amount; i++)
		{
			tempObj[i] = Obj[i]; // �������� �� ��������� ������
		}
		delete[] Obj;

		Obj = tempObj;
	}
	return Obj;
}

void setData(busTimetable* trip, const int amount)
{
	std::cout << "������� ����� �����" << std::endl;
	std::cin >> trip[amount].numberBusTrip;
	std::cout << "������� ��� �������� (����)" << std::endl;
	std::cin >> trip[amount].type.colour;
	std::cout << "������� ��� �������� (������)" << std::endl;
	std::cin >> trip[amount].type.size;
	std::cout << "������� ����� ����������" << std::endl;
	std::cin >> trip[amount].destination;
	std::cout << "������� ����� �����������" << std::endl;
	std::cin >> trip[amount].departureTime;
	std::cout << "������� ����� ��������" << std::endl;
	std::cin >> trip[amount].arrivalTime;
}

void changeData(busTimetable* trip, const int i)
{
	int whatChange;
	std::cout <<
		"��������, ��� ������ �������� � �����: " << std::endl <<
		"1. ����� �����" << std::endl <<
		"2. ��� ��������" << std::endl <<
		"3. ����� ����������" << std::endl <<
		"4. ����� �����������" << std::endl <<
		"5. ����� ��������" << std::endl <<
		"6. ����� � ���� ��������������" << std::endl;
	std::cin >> whatChange;
	system("CLS");
	switch (whatChange)
	{
		case 1:
			std::cout << "������� ����� �����" << std::endl;
			std::cin >> trip[i].numberBusTrip;
			break;

		case 2:
			std::cout << "������� ��� �������� (����)" << std::endl;
			std::cin >> trip[i].type.colour;
			std::cout << "������� ��� �������� (������)" << std::endl;
			std::cin >> trip[i].type.size;
			break;

		case 3:
			std::cout << "������� ����� ����������" << std::endl;
			std::cin >> trip[i].destination;
			break;

		case 4:
			std::cout << "������� ����� �����������" << std::endl;
			std::cin >> trip[i].departureTime;
			break;

		case 5:
			std::cout << "������� ����� ��������" << std::endl;
			std::cin >> trip[i].arrivalTime;
			break;

		default:
			break;
	}
}