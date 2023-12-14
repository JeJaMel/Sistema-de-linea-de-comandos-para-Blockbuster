#pragma once

#include "Struct.h"

bool deleteClient(const string &filename, int targetId);
void WriteClientData(const string &filename, const client &c);
bool searchClientById(const string &filename, int targetId, client &foundClient);
bool searchClientByEmail(const string &filename, const string &targetEmail, client &foundClient);
bool searchClientByPhoneNumber(const string &filename, int targetPhoneNumber, client &foundClient);
bool searchClientByAccountName(const string &filename, const string &targetAccountName, client &foundClient);
void deleteClientCase(movie catalog[], int catalogSize);
void displayClientAndHistory(const client &foundClient, movie catalog[], int catalogSize);
void searchClientCase(movie catalog[], int catalogSize);
