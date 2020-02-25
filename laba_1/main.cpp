#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

const string ALPHABET_RUS_UPPER = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const string ALPHABET_RUS_LOWER = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const string ALPHABET_ENG_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ALPHABET_ENG_LOWER = "abcdefghijklmnopqrstuvwxyz";
const string ALPHABET_NUMBERS = "1234567890";

//Class generates passwords
class PassGen {
private:
    string alphabetFull;
    int alphabetFullLength;
    int passLength;
    string password;

public:
    PassGen(string alphabet, int leng) {
        alphabetFull = alphabet;
        passLength = leng;
        alphabetFullLength = alphabet.length();
    }

    pair<string, string> generate() {
        char *filename = new char;
        filename = "password.txt";

        // Generating password
        generatePassword(passLength);

        // Writing to file
        std::ofstream outFile(filename);
        outFile << password;
        outFile << endl;
        outFile.close();

        cout << "Пароль успешно сгенерирован и записан в файл " << filename << "" << endl;
        return make_pair(password, alphabetFull);
    }

private:
    void generatePassword(int passLength) {
        alphabetFullLength = alphabetFull.length();
        for (int i = 0; i < passLength; ++i) {
            password = password + char(alphabetFull[rand() % alphabetFullLength]);
        }
    }

    void swapLetter(string alphabet) {
        password[rand()] = char(alphabet[rand() % alphabet.length()]);
    }
};

class PassCrack {
private:
    string alphabetFull;
    int alphabetFullLength;
    string correctPassword = "";

public:
    explicit PassCrack(pair<string, string> pair1) {
        correctPassword = pair1.first;
        alphabetFull = pair1.second;
        alphabetFullLength = alphabetFull.length();
    }

    void bruteforce(int length) {
        if (length == 0)
            return;

        vector<int> symbolsRegister(length);
        while (true) {
            if (isMatch(formString(symbolsRegister))) {
                cout << "Password cracked: " << formString(symbolsRegister) << endl;
                break;
            }
            shift(symbolsRegister);
        }
    }

private:
    void shift(vector<int> &symbolsRegister) {
        symbolsRegister[0]++;

        for (int i = 1; i < symbolsRegister.size(); ++i) {
            if (symbolsRegister[i - 1] >= alphabetFullLength) {
                symbolsRegister[i]++;
                symbolsRegister[i - 1] = 0;
            }
        }
    }

    string formString(vector<int> symbolsRegister) {
        string guess;
        for (int i = 0; i < symbolsRegister.size(); ++i) {
            guess += char(alphabetFull[symbolsRegister[i]]);
        }
        return guess;
    }

    bool isMatch(string guess) {
        return guess == correctPassword;
    }
};

int main() {
    srand(time(0));
    string alphabetFull;
    int passLength = 6, option;

    cout << "================[Генерация паролей]================";
    cout << endl;
    cout << "Введите длину пароля: ";
    cin >> passLength;
    cout << endl;
    cout << "1) цифры\n"
            "2) строчные латинские буквы\n"
            "3) латинские строчные и заглавные буквы\n"
            "4) кириллица строчные\n"
            "5) кириллица строчные, заглавные\n"
            "6) цифры , латиница строчные";
    cout << endl;
    cin >> option;

    alphabetFull = "";
    switch (option) {
        case 1:
            alphabetFull = ALPHABET_NUMBERS;
            break;
        case 2:
            alphabetFull = ALPHABET_ENG_LOWER;
            break;
        case 3:
            alphabetFull = ALPHABET_ENG_UPPER + ALPHABET_ENG_LOWER;
            break;
        case 4:
            alphabetFull = ALPHABET_RUS_LOWER;
            break;
        case 5:
            alphabetFull = ALPHABET_RUS_UPPER + ALPHABET_ENG_LOWER;
            break;
        case 6:
            alphabetFull = ALPHABET_NUMBERS + ALPHABET_ENG_LOWER;
            break;
    }

    srand(time(NULL));
    PassGen *passGenerator = new PassGen(alphabetFull, passLength);
    pair<string, string> password;
    password = passGenerator->generate();

    cout << "================[Оценка пароля]================";
    cout << endl;
    cout << "При скорости подбора 2 000 000 паролей в секунду уйдет до ";
    cout << pow(alphabetFull.length(), passLength) / 2000000.0;
    cout << " секунд";
    cout << endl;

    cout << "================[Подбор пароля]================";
    cout << endl;


    cout << "Password generated: " << password.first << endl;
    PassCrack *passCracker = new PassCrack(password);

    unsigned int start_time = clock();
    passCracker->bruteforce(password.first.length());
    unsigned int end_time = clock();
    double time = (end_time - start_time) / 1000000.0;

    cout << "Time: " << time << "  sec";
    cout << endl;

    cout << "Количество возможных комбинаций ";
    cout << pow(alphabetFull.length(), passLength);
    cout << endl;
    return 0;
}