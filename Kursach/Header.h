#pragma once

void adminAuthorization();
void userAuthorization();

void adminMenu();
void userManagement();
void userMenu();

int saveStruct(const char*, struct busTimetable*, int);
int saveStruct(const char*, struct Admins*, int);
int saveStruct(const char*, struct Users*, int);

int loadStruct(const char*, struct busTimetable*);
int loadStruct(const char*, struct Admins*);
int loadStruct(const char*, struct Users*);

busTimetable* addStruct(busTimetable*, const int);
Admins* addStruct(Admins*, const int);
Users* addStruct(Users*, const int);

template <typename T>
void createFile(const char*, T*);

busTimetable* changeData(busTimetable*);
Users* changeData(Users*);

busTimetable* deleteData(busTimetable*);
Admins* deleteData(Admins*);
Users* deleteData(Users*);

busTimetable* signUp(busTimetable*, int&);
Admins* signUp(Admins*, int&);
Users* signUp(Users*, int&);
bool signIn(Admins*);
bool signIn(Users*);

void findTripNumber();
void findBusType();
void findEarlierTrip();
void printSomeTrip(int);
