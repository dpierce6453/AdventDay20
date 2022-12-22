//
// Created by Dan on 12/22/2022.
//

#ifndef ADVENTDAY20_TESTFILES_H
#define ADVENTDAY20_TESTFILES_H


#include <string>

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)

#ifndef CMAKE_SOURCE_DIR_VAR
#error A CMake definition for CMAKE_SOURCE_DIR_VAR is required
#endif


static const std::string testfilepath = VALUE(CMAKE_SOURCE_DIR_VAR);
static const std::string inputFileName = testfilepath + "/input.txt";


#endif //ADVENTDAY20_TESTFILES_H
