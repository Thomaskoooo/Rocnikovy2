#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <random> 

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

        // Shuffle the questions
        random_device rd;
        mt19937 g(rd());
        shuffle(otazky.begin(), otazky.end(), g);

        int correctAnswers = 0;
        int incorrectAnswers = 0;
        int testSpustenie = 0;
        ifstream spustenieSubor("spustenie.txt");
        if (spustenieSubor.is_open()) {
            spustenieSubor >> testSpustenie;
            spustenieSubor.close();
        } else {
            cout << "Subor spustenie.txt sa nepodarilo otvorit" << endl;
        }
        testSpustenie++;
        ofstream spustenieZapis("spustenie.txt");
        if (spustenieZapis.is_open()) {
            spustenieZapis << testSpustenie;
            spustenieZapis.close();
        } else {
            cout << "Subor spustenie.txt sa nepodarilo zapisat" << endl;
        }

        int numQuestions = min(10, static_cast<int>(otazky.size())); // Limit the number of questions to 10
        for (int i = 0; i < numQuestions; i++) {
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

        cout << "Statistika testu:" << endl;
        cout << "Pocet spravnych odpovedi: " << correctAnswers << endl;
        cout << "Pocet nespravnych odpovedi: " << incorrectAnswers << endl;

        otazkySubor.close();
        odpovedeSubor.close();

        ofstream statistika("statistika.txt", ios::app);
        if (statistika.is_open()) {
            statistika << "Statistika testu:" << endl;
            statistika << "Pocet spravnych odpovedi: " << correctAnswers << endl;
            statistika << "Pocet nespravnych odpovedi: " << incorrectAnswers << endl;
            statistika << "---------------------------" << endl;
            statistika << "Pocet spusteni testu: " << testSpustenie++ << endl;
            statistika << "---------------------------" << endl;
            statistika.close();
        } else {
            cout << "Subor statistika.txt sa nepodarilo vytvorit" << endl;
        }
    }

    return 0;
}
