#include <iostream>
#include "stdio.h"
#include "fstream"
#include "string"
#include "sstream"
#include "vector"

using namespace std;

void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c);

string beginString = "StartComponents\n"
                     "\n"
                     "Component (Name \"example\") (PartCount 1) (DesPrefix \"U?\")\n"
                     "Rectangle (Width 5) (Start 300, -3400) (End 5300, 200) (Part 1)\n";
string endString = "Description (Value \"No Description Available\") (Part 1)\n"
                   "EndComponent\n"
                   "EndComponents\n";

int main(int argc, char *argv[]) {
    printf("your original file is %s\n", argv[1]);
    string filename = argv[1];
    filename = filename.substr(0, filename.find(".csv")) + ".txt";
    cout << "filename = " << filename << endl;
    std::fstream inFile;
    inFile.open(argv[1], std::ios::binary | std::ios::in);
    if (!inFile.is_open()) {
        cout << "Open file error!!\n";
        return -1;
    }
    fstream outFile;
    outFile.open(filename, ios::out);
    outFile << beginString;
    string line;
    getline(inFile, line);
    while (!inFile.eof()) {
        getline(inFile, line);
        cout << line << endl;
        vector<string> column;
        SplitString(line, column, ",");
        if (!column.empty()) {
            outFile << "Pin (Location ";
            outFile << column[3] << ", " << column[4] << ") ";
            outFile << "(Rotation " << column[5] << ")";
            outFile << "(PinType Passive) (Length " << column[2] << ")";
            outFile << "(Width 0) (Designator Visible \"" << column[0] << "\") (Name Visible \"" << column[1];
            outFile << "\") (PinSwap 0) (PartSwap 0) (PinSeq " + column[0] << ") (Part 1)\n";
        }
    }
    outFile << endString;
    inFile.close();
    outFile.close();
    return 0;
}

void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

