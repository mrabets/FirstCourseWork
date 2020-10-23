#pragma once

void adminAuthorization();
void userAuthorization();

void adminMenu();
void userMenu();
void userManagement();

int saveStruct(struct Trips*, int);
int saveStruct(struct Admins*, int);
int saveStruct(struct Users*, int);

int loadStruct(struct Trips*);
int loadStruct(struct Admins*);
int loadStruct(struct Users*);

Trips* addStruct(Trips*, const int);
Admins* addStruct(Admins*, const int);
Users* addStruct(Users*, const int);

template <typename T>
void createFile(const char*, T*);

Trips* changeData(Trips*);
Users* changeData(Users*);

Trips* deleteData(Trips*);
Admins* deleteData(Admins*);
Users* deleteData(Users*);

Trips* signUp(Trips*, int&);
Admins* signUp(Admins*, int&);
Users* signUp(Users*, int&);

bool signIn(Admins*);
bool signIn(Users*);

void findTripNumber();
void findBusType();
void findEarlierTrip();
void printSomeTrip(int);