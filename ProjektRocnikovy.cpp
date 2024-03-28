#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <vector>



#pragma execution_character_set( "utf-8" ) //na cmd meni foramt endoding


using namespace std;

int main() {

     SetConsoleOutputCP( 65001 ); //diagritika na cmd

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //! For use of SetConsoleTextAttribute()

    SetConsoleTextAttribute(console, 15);

    ifstream otazkySubor("otazky.txt");
    ifstream odpovedeSubor("odpovede.txt");

    if (otazkySubor.is_open() && odpovedeSubor.is_open()) {
        vector<string> otazky;
        vector<string> odpovede;

        string otazka, odpoved;
        int i = 1;

        while (getline(otazkySubor, otazka)) {
            otazky.push_back(otazka);
            odpovede.push_back(odpoved);
            i++;
        }

        random_shuffle(otazky.begin(), otazky.end());

        int correctAnswers = 0;
        int incorrectAnswers = 0;

        for (int i = 0; i < otazky.size(); i++) {
            SetConsoleTextAttribute(console, 15);
            cout << "Otazka " << i + 1 << ": " << otazky[i] << endl;

            string spravnaOdpoved = odpovede[i];

            for (int j = 1; j <= 10; j++) {
                getline(odpovedeSubor, odpoved);
                SetConsoleTextAttribute(console, 15);
                if (j == 10) {
                    spravnaOdpoved = odpoved;
                } else {
                    cout << odpoved << endl;
                }
            }

            string userAnswer;
            cout << "Vasa odpoved: ";
            cin >> userAnswer;

            if (userAnswer == spravnaOdpoved) {
                SetConsoleTextAttribute(console, 2);
                cout << "Spravne!" << endl;
                correctAnswers++;
            } else {
                SetConsoleTextAttribute(console, 4);
                cout << "Nespravne!" << endl;
                incorrectAnswers++;
            }
        }

        otazkySubor.close();
        odpovedeSubor.close();

        ofstream statistika("statistika.txt");
        if (statistika.is_open()) {
            statistika << "Statistika testu:" << endl;
            statistika << "Pocet spravnych odpovedi: " << correctAnswers << endl;
            statistika << "Pocet nespravnych odpovedi: " << incorrectAnswers << endl;
            statistika.close();
        } else {
            cout << "Subor statistika.txt sa nepodarilo vytvorit" << endl;
        }
    } else {
        cout << "Subor sa nepodarilo otvorit" << endl;
    }

    return 0;
}
