#include <stdio.h>  
#include <iostream> 
#include <locale.h>
#include <windows.h>
#include "Header.h"

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

struct Admins
{
	char login[20];
	char password[20];
};

struct Users
{
	char login[20];
	char password[20];
};

const char* dataFile = "dataBusTimetable.txt";
const char* adminFile = "admins.txt";
const char* userFile = "users.txt";

struct busTimetable* trip = 0;
int tripAmount = 0;

struct Admins* admin = 0;
int adminAmount = 0;

struct Users* user = 0;
int userAmount = 0;

void adminAuthorization()
{
	int choice;
	while (true)
	{
		std::cout <<
			"1. ������� ���� ���������������" << std::endl <<
			"2. �����������" << std::endl <<
			"3. ����" << std::endl <<
			"4. ������� ��������������" << std::endl <<
			"5. ����������� ���� ���������������" << std::endl <<
			"6. �����" << std::endl;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			createFile(adminFile, admin);
			break;
		case 2:
			admin = signUp(admin, adminAmount);
			break;
		case 3:
			if (signIn(admin))
				adminMenu();
			else
				std::cout << "������������ ����� ��� ������" << std::endl;
			break;
		case 4:
			admin = deleteData(admin);
			break;
		case 5:
			loadStruct(adminFile, admin);
			break;
		default:
			return;
		}
	}
}

void userAuthorization()
{
	int choice;
	while (true)
	{
		std::cout <<
			"1. �����������" << std::endl <<
			"2. �����" << std::endl <<
			"3. �����" << std::endl;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			user = signUp(user, userAmount);
			break;
		case 2:
			if (signIn(user))
				userMenu();
			else
				std::cout << "������������ ����� ��� ������" << std::endl;
			break;
		default:
			return;
		}
	}
}

void userManagement()
{
	int choice;
	while (true)
	{
		std::cout <<
			"1. ������� ���� �������������" << std::endl <<
			"2. ����������� ������������" << std::endl <<
			"3. �������� ������ ������������" << std::endl <<
			"4. ����������� ���� �������������" << std::endl <<
			"5. ������� ������������" << std::endl <<
			"6. �����" << std::endl;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			createFile(userFile, user);
			break;
		case 2:
			user = signUp(user, userAmount);
			break;
		case 3:
			user = changeData(user);
			break;
		case 4:
			loadStruct(userFile, user);
			break;
		case 5:
			user = deleteData(user);
			break;
		default:
			return;
		}
	}
}

void userMenu()
{
	while (true)
	{
		std::cout <<
			"1. ����������� ��� ���������� �����" << std::endl <<
			"2. ������ ����� �� ���� ��������" << std::endl <<
			"3. ������� ���������� � ������, �������� ����� ���������������" << std::endl <<
			"   ��� �������� � ����� ���������� ������ ��������� �������" << std::endl <<
			"4. �����" << std::endl;
		int choice;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			loadStruct(dataFile, trip);
			break;

		case 2:
			findBusType();
			break;
		case 3:
			findEarlierTrip();
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
		std::cout <<
			"1. ������� ���� � ����������� �������" << std::endl <<
			"2. �������� ����� ����" << std::endl <<
			"3. �������� ����" << std::endl <<
			"4. ������� ����" << std::endl <<
			"5. ����������� ��� ���������� ����� � ����� " << std::endl <<
			"6. ���������� ��������������" << std::endl <<
			"7. ������ ����� �� ������" << std::endl <<
			"8. �����" << std::endl;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			createFile(dataFile, trip);
			break;
		case 2:
			trip = signUp(trip, tripAmount);
			break;
		case 3:
			trip = changeData(trip);
			break;
		case 4:
			trip = deleteData(trip);
			break;
		case 5:
			loadStruct(dataFile, trip);
			break;
		case 6:
			userManagement();
			break;
		case 7:
			findTripNumber();
			break;
		default:
			return;
		}
	}
}

template <typename T>
void createFile(const char* filename, T* someStruct)
{
	if (FILE* T = fopen(filename, "w+"))
		std::cout << "���� ������� ������" << std::endl;
	else
		std::cout << "������ �������� �����" << std::endl;
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

int saveStruct(const char* filename, struct Admins* admin, int n)
{
	FILE* fileTemp;
	char* c;

	// ����� ������������ ������
	int size = n * sizeof(struct Admins);

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
	c = (char*)admin;
	for (int i = 0; i < size; i++)
	{
		putc(*c, fileTemp);
		c++;
	}
	fclose(fileTemp);
	return 0;
}

int saveStruct(const char* filename, struct Users* user, int n)
{
	FILE* fileTemp;
	char* c;

	// ����� ������������ ������
	int size = n * sizeof(struct Users);

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
	c = (char*)user;
	for (int i = 0; i < size; i++)
	{
		putc(*c, fileTemp);
		c++;
	}
	fclose(fileTemp);
	return 0;
}

int loadStruct(const char* filename, struct busTimetable* trip)
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

int loadStruct(const char* filename, struct Admins* admin)
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
	struct Admins* ptr = (struct Admins*)malloc(n * sizeof(struct Admins));
	c = (char*)ptr;
	// ����� ������ ��������� ����������� �� �����
	while ((i = getc(fileTemp)) != EOF)
	{
		*c = i;
		c++;
	}
	// ������� ����������� ��������� � ����� �� �������
	std::cout << "���������� ���������������: " << n << std::endl;

	for (int k = 0; k < n; k++)
	{
		std::cout << std::endl <<
			k + 1 << " �����: " << (ptr + k)->login << std::endl <<
			k + 1 << " ������: " << (ptr + k)->password << std::endl;
	}

	std::cout << std::endl;
	free(pti);
	free(ptr);
	fclose(fileTemp);
	return 0;
}

int loadStruct(const char* filename, struct Users* user)
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
	struct Users* ptr = (struct Users*)malloc(n * sizeof(struct Users));
	c = (char*)ptr;
	// ����� ������ ��������� ����������� �� �����
	while ((i = getc(fileTemp)) != EOF)
	{
		*c = i;
		c++;
	}
	// ������� ����������� ��������� � ����� �� �������
	std::cout << "���������� �������������: " << n << std::endl;

	for (int k = 0; k < n; k++)
	{
		std::cout << std::endl <<
			k + 1 << " �����: " << (ptr + k)->login << std::endl <<
			k + 1 << " ������: " << (ptr + k)->password << std::endl;
	}

	std::cout << std::endl;
	free(pti);
	free(ptr);
	fclose(fileTemp);
	return 0;
}

busTimetable* addStruct(busTimetable* trip, const int amount)
{
	if (amount == 0)
	{
		trip = new busTimetable[amount + 1];
	}
	else
	{
		busTimetable* temp = new busTimetable[amount + 1];

		for (int i = 0; i < amount; i++)
		{
			temp[i] = trip[i];
		}
		delete[] trip;

		trip = temp;
	}
	return trip;
}

Admins* addStruct(Admins* admin, const int index)
{
	if (index == 0)
	{
		admin = new Admins[index + 1];
	}
	else
	{
		Admins* temp = new Admins[index + 1];

		for (int i = 0; i < index; i++)
		{
			temp[i] = admin[i];
		}
		delete[] admin;

		admin = temp;
	}
	return admin;
}

Users* addStruct(Users* user, const int index)
{
	if (index == 0)
	{
		user = new Users[index + 1];
	}
	else
	{
		Users* temp = new Users[index + 1];

		for (int i = 0; i < index; i++)
		{
			temp[i] = user[i];
		}
		delete[] user;

		user = temp;
	}
	return user;
}

Admins* signUp(Admins* admin, int& adminAmount)
{
	admin = addStruct(admin, adminAmount);
	std::cout << "����� �����: " << std::endl;
	std::cin >> admin[adminAmount].login;
	std::cout << "����� ������: " << std::endl;
	std::cin >> admin[adminAmount].password;
	adminAmount++;
	saveStruct(adminFile, admin, adminAmount);
	return admin;
}

Users* signUp(Users* user, int& userAmount)
{
	user = addStruct(user, userAmount);
	std::cout << "����� �����: " << std::endl;
	std::cin >> user[userAmount].login;
	std::cout << "����� ������: " << std::endl;
	std::cin >> user[userAmount].password;
	userAmount++;
	saveStruct(userFile, user, userAmount);
	return user;
}

busTimetable* signUp(busTimetable* trip, int& tripAmount)
{
	trip = addStruct(trip, tripAmount);
	std::cout << "������� ����� �����" << std::endl;
	std::cin >> trip[tripAmount].numberBusTrip;
	std::cout << "������� ��� �������� (����)" << std::endl;
	std::cin >> trip[tripAmount].type.colour;
	std::cout << "������� ��� �������� (������)" << std::endl;
	std::cin >> trip[tripAmount].type.size;
	std::cout << "������� ����� ����������" << std::endl;
	std::cin >> trip[tripAmount].destination;
	std::cout << "������� ����� �����������" << std::endl;
	std::cin >> trip[tripAmount].departureTime;
	std::cout << "������� ����� ��������" << std::endl;
	std::cin >> trip[tripAmount].arrivalTime;
	tripAmount++;
	saveStruct(dataFile, trip, tripAmount);
	return trip;
}

bool signIn(Admins* admin)
{
	char login[20];
	char password[20];
	std::cout << "�����: " << std::endl;
	std::cin >> login;
	std::cout << "������: " << std::endl;
	std::cin >> password;
	for (int i = 0; i < adminAmount; i++)
	{
		if (!strcmp(login, admin[i].login) && !strcmp(password, admin[i].password))
		{
			std::cout << "�� ������� ����� ��� ��������������" << std::endl;
			return true;
		}
	}
	return false;
}

bool signIn(Users* user)
{
	char login[20];
	char password[20];
	std::cout << "�����: " << std::endl;
	std::cin >> login;
	std::cout << "������: " << std::endl;
	std::cin >> password;
	for (int i = 0; i < userAmount; i++)
	{
		if (!strcmp(login, user[i].login) && !strcmp(password, user[i].password))
		{
			std::cout << "�� ������� ����� ��� ������������" << std::endl;
			return true;
		}
	}
	return false;
}

busTimetable* changeData(busTimetable* trip)
{
	int i;
	std::cout << "�������� ����� �����. ����� ������: " << tripAmount << std::endl;
	std::cin >> i;
	if (i < 1 || i > tripAmount)
	{
		std::cout << "����� ������ �� ����������" << std::endl;
		return trip;
	}
	i--;
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
	saveStruct(dataFile, trip, tripAmount);
	return trip;
}

Users* changeData(Users* user)
{
	int i;
	std::cout << "�������� ����� ������������. ����� �������������: " << userAmount << std::endl;
	std::cin >> i;
	if (i < 1 || i > userAmount)
	{
		std::cout << "����� ������������� �� ����������" << std::endl;
		return user;
	}
	i--;
	int whatChange;
	std::cout <<
		"��������, ��� ������ �������� � ������������: " << std::endl <<
		"1. �����" << std::endl <<
		"2. ������" << std::endl <<
		"3. �����" << std::endl;
	std::cin >> whatChange;
	system("CLS");
	switch (whatChange)
	{
	case 1:
		std::cout << "������� ����� �����: " << std::endl;
		std::cin >> user[i].login;
		break;
	case 2:
		std::cout << "������� ����� ������: " << std::endl;
		std::cin >> user[i].password;
		break;
	default:
		break;
	}
	saveStruct(userFile, user, userAmount);
	return user;
}

busTimetable* deleteData(struct busTimetable* trip)
{
	int number;
	std::cout << "�������� ����� ����� ��� ��������. ����� ������: " << tripAmount << std::endl;
	std::cin >> number;
	if (number < 1 || number > tripAmount)
	{
		std::cout << "����� ������ �� ����������" << std::endl;
		return trip;
	}
	for (int i = number - 1; i < tripAmount - 1; i++)
	{
		trip[i] = trip[i + 1];
	}
	tripAmount--;
	saveStruct(dataFile, trip, tripAmount);
	return trip;
}

Users* deleteData(struct Users* user)
{
	int number;
	std::cout << "�������� ����� ������������ ��� ��������. ����� �������������: " << userAmount << std::endl;
	std::cin >> number;
	if (number < 1 || number > userAmount)
	{
		std::cout << "����� ������������� �� ����������" << std::endl;
		return user;
	}
	for (int i = number - 1; i < userAmount - 1; i++)
	{
		user[i] = user[i + 1];
	}
	userAmount--;
	saveStruct(userFile, user, userAmount);
	return user;
}

Admins* deleteData(struct Admins* admin)
{
	int number;
	std::cout << "�������� ����� �������������� ��� ��������. ����� ���������������: " << adminAmount << std::endl;
	std::cin >> number;
	if (number < 1 || number > adminAmount)
	{
		std::cout << "����� ��������������� �� ����������" << std::endl;
		return admin;
	}
	for (int i = number - 1; i < adminAmount - 1; i++)
	{
		admin[i] = admin[i + 1];
	}
	adminAmount--;
	saveStruct(adminFile, admin, adminAmount);
	return admin;
}

void findTripNumber()
{
	int number;
	std::cout << "������� ����� �����: " << std::endl;
	std::cin >> number;
	for (int i = 0; i < tripAmount; i++)
	{
		if (number == trip[i].numberBusTrip)
		{
			printSomeTrip(i);
		}
	}
}

void findBusType()
{
	char colour[20], size[20];
	std::cout << "������� ��� �������� (����): " << std::endl;
	std::cin >> colour;
	std::cout << "������� ��� �������� (������): " << std::endl;
	std::cin >> size;
	for (int i = 0; i < tripAmount; i++)
	{
		if (!strcmp(colour, trip[i].type.colour) && !strcmp(size, trip[i].type.size))
		{
			printSomeTrip(i);
		}
	}
}

void findEarlierTrip()
{
	char city[20], time[20];
	std::cout << "������� ����� ����������: " << std::endl;
	std::cin >> city;
	std::cout << "������� ����� ����������� (� ������� 00:00): " << std::endl;
	std::cin >> time;
	for (int i = 0; i < tripAmount; i++)
	{
		if (!strcmp(city, trip[i].destination) && strcmp(time, trip[i].departureTime) > 0)
		{
			printSomeTrip(i);
		}
	}
}

void printSomeTrip(int i)
{
	if (i < 0 || i > tripAmount) return;
	std::cout <<
		i + 1 << " ����� �����: " << trip[i].numberBusTrip << std::endl <<
		i + 1 << " ��� �������� (����): " << trip[i].type.colour << std::endl <<
		i + 1 << " ��� �������� (������): " << trip[i].type.size << std::endl <<
		i + 1 << " ���� ����������: " << trip[i].destination << std::endl <<
		i + 1 << " ����� �����������: " << trip[i].departureTime << std::endl <<
		i + 1 << " ����� ��������: " << trip[i].arrivalTime << std::endl;
}

