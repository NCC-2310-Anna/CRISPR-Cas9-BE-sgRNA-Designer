#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <regex>

#define EXIT 0x1B

using namespace std;


string filename;
string line[3];
regex cbe1(R"(c.{13,19}[agct]gg)");
regex cbe2(R"(cc[agct].{13,19}g)");
regex abe1(R"(a.{13,15}[agct]gg)");
regex abe2(R"(cc[agct].{13,15}t)");

void searchFunction(string subject, regex r){
    smatch match;
    int i = 1;
    while (regex_search(subject, match, r)) {
        cout << "\nMatched string is " << match.str(0) << endl
            << "and it is found at position "
            << match.position(0)<<endl;
        i++;

        // suffix to find the rest of the string.
        subject = match.suffix().str();
    }
}
int main(){
    cout << "Please enter the name of the fasta-file:";
    cin >> filename;
    //std::cout << "You have entered: " << filename << std::endl;
    ifstream inputFile;
    inputFile.open(filename.c_str(), ios::in);
    string buffer;
    if(inputFile.is_open()){
        int counter = 0;
        while(inputFile){
            getline(inputFile, buffer);
            cout << counter << ": " << buffer << endl;
            line[counter]= buffer;
            counter ++;
        }
    }
    searchFunction(line[1], cbe1);

/**********This is the end loop of the program**********/
    cout << "finished, press EXIT to end the program"<< endl;
    while(GetKeyState(EXIT) > -127){
    }
    inputFile.close();
    return 1;
}
