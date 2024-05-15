#pragma once

#include <string>

#define HASHTABLE_SIZE 21089 /* Next prime number */

/* Hash functions */
int hashUserID(long long int);
int doubleHashUserID(long long int);
int hashUsername(std::string);
int doubleHashUsername(std::string);