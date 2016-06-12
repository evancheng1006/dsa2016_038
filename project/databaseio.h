#ifndef DATABASEIO_H
#define DATABASEIO_H

#include "database.h"
#include <iostream>
#include <fstream>
#include <cstring>

std::istream & operator >> (std::istream & input, DATABASE & db);
std::ostream & operator << (std::ostream & output, const DATABASE & db);

#endif
