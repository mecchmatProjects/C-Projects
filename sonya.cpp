#include <iostream>
#include <cstdlib>
#include <cstring>
#include <clocale>
#include <windows.h>
#include <TCHAR.H>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iterator>
typedef std::string TString;
using namespace std;
class Slovo {
	int type, rid, chislo, osoba, vidminok;
};
void SetConsole(const wchar_t* pszTitle = NULL, BOOL bFullScreen = FALSE)
{
	CONSOLE_FONT_INFOEX font;
	HANDLE hStdOut = NULL;

	// кодовая страница
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// шрифт
	font.cbSize = sizeof font;
	font.nFont = 1;
	font.dwFontSize = { 9, 18 };
	font.FontFamily = 0 | FF_DONTCARE & ~TMPF_FIXED_PITCH;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, LF_FACESIZE, L"Lucida Console");

	// установка шрифта
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!SetCurrentConsoleFontEx(hStdOut, FALSE, &font))
		cout << "No";

	// заголовок и полный экран...
	if (pszTitle)
		SetConsoleTitleW(pszTitle);
	if (bFullScreen)
		//      SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
//------------------------------------------------------------------
//Функция, которая проверяет, принадлежит ли буква множеству
//гласных букв
bool IsVowel(char letter) {
	char l = tolower(letter);
	TString a = "аоєиуеіїюя";
	for (size_t i = 0; i < a.length(); i++)
		if (a[i] == l) return true;
	return false;
}
//------------------------------------------------------------------
//Функция, которая проверяет, принадлежит ли буква множеству
//согласных букв
bool IsConsonant(char letter) {
	char l = tolower(letter);
	TString a = "бвгдйжзклмнпрстфхцчшщ";
	for (size_t i = 0; i < a.length(); i++)
		if (a[i] == l) return true;
	return false;
}
//------------------------------------------------------------------
//Функция, которая проверяет, принадлежит ли буква множеству
bool IsLetter(char letter) {
	char l = tolower(letter);
	TString a = "абвгдеєжзиіїйклмнопрстуфхцчшщьюя";
	for (size_t i = 0; i < a.length(); i++)
		if (a[i] == l) return true;
	return false;
}
//------------------------------------------------------------------
//Функция, которая проверяет наличие гласной буквы в строке
bool ContainVowel(TString str) {
	for (size_t k = 0; k < str.length(); k++)
		if (IsVowel(str[k])) return true;
	return false;
}
//------------------------------------------------------------------
//Функция, которая выделяет из текста слово
TString GetWord(TString str) {
	TString word;
	size_t i = 0, n = str.length();

	while (!IsLetter(str[i]) && i < n)
		i++;

	while (IsLetter(str[i]) && i < n) {
		word += str[i];
		i++;
	}

	return word;
}
//------------------------------------------------------------------
//Функция, которая разбивает слово на слоги
TString SplitWord(TString str) {
	TString split, syll;
	size_t len = str.length(), i = 0;
	//Идем вдоль слова
	while (i < len) {
		//Проверка 1-го критерия
		if (IsConsonant(str[i]) && IsVowel(str[i + 1]) && IsVowel(str[i + 2])) {
			if (i + 3 < len) {
				syll = str.substr(i, 2);
				split.append(syll);
				split += '-';
				i += 2;
			}
		}
		else
			//Проверка 1-го критерия не прошла, проверяем 2-ой
			if (IsVowel(str[i]) && IsConsonant(str[i + 1]) && IsConsonant(str[i + 2])) {
				if (i + 3 < len)
					if (ContainVowel(str.substr(i + 3))) {
						syll = str.substr(i, 2);
						split.append(syll);
						split += '-';
						i += 2;
					}
			}
			else
				//Проверка 2-го критерия не прошла, проверяем 3-й
			{
				size_t m = i;

				while (!IsVowel(str[m]) && m < len) m++;
				m++;
				syll = str.substr(i, m - i);
				if (m < len)
					if (ContainVowel(str.substr(m))) {
						split.append(syll);
						split += '-';
						i = m;
					}
			}
		split += str[i];
		i++;
		//Дополнительное условие для некоторых случаев
		if (IsVowel(str[i - 1]) && i < len)
			if (ContainVowel(str.substr(i)))
				split += '-';
	}
	return split;
}
//------------------------------------------------------------------
TString Processing(TString str) {
	size_t start, end = str.length();
	TString text, word;
	//а-на-нас
	for (size_t i = 0; i < end; i++) {
		start = i;
		//Получение очередного слова
		word = GetWord(str.substr(start, end));
		i += word.length();
		//Разбивка на слоги
		text.append(SplitWord(word));
		//Конец разбивки на слоги
		//Вставка знаков препинания
		while (!IsLetter(str[i]) && i < end) {
			text += str[i];
			i++;
		}
		i--;
	}
	return text;
}
TString BackProcess(TString str1) {
	size_t end = str1.length();
	string nullmas = "";
	for (const auto c : str1) {
		if (!ispunct(c)) {

			nullmas.push_back(c);
		}
	}
	str1 = nullmas;
	return str1;
}
int check(TString checking) {
	TString ent = checking;
	TString get;
	for (size_t i = 0; i < ent.length(); i++) {
		if (ent[i] == 'б' && ent[i + 1] == 'е' && ent[i + 2] == 'з') {
			cout << "Префікс: без" << endl;
			if (ent.length() > 5) {
				if (ent[i + 3] == 'р' && ent[i + 4] == 'о' && ent[i + 5] == 'з') cout << "Префікс (2): роз" << endl;
				if (ent[i + 3] == 'в' && ent[i + 4] == 'і' && ent[i + 5] == 'д') cout << "Префікс (2): від" << endl;
				if (ent[i + 3] == 'п' && ent[i + 4] == 'і' && ent[i + 5] == 'д') cout << "Префікс (2): під" << endl;
				if (ent[i + 3] == 'п' && ent[i + 4] == 'р' && ent[i + 5] == 'е') cout << "Префікс (2): пре" << endl;
				if (ent[i + 3] == 'п' && ent[i + 4] == 'р' && ent[i + 5] == 'и') cout << "Префікс (2): при" << endl;
			}
			return false;
		}
		else if (ent[i] == 'р' && ent[i + 1] == 'о' && ent[i + 2] == 'з') return true;
		else if (ent[i] == 'ч' && ent[i + 1] == 'е' && ent[i + 2] == 'р' && ent[i + 3] == 'е' && ent[i + 4] == 'з') return true;
		else if (ent[i] == 'в' && ent[i + 1] == 'і' && ent[i + 2] == 'д') return true;
		else if (ent[i] == 'о' && ent[i + 1] == 'д') return true;
		else if (ent[i] == 'м' && ent[i + 1] == 'і' && ent[i + 2] == 'ж') return true;
		else if (ent[i] == 'н' && ent[i + 1] == 'а' && ent[i + 2] == 'д') return true;
		else if (ent[i] == 'о' && ent[i + 1] == 'б') return true;
		else if (ent[i] == 'п' && ent[i + 1] == 'е' && ent[i + 2] == 'р' && ent[i + 3] == 'е' && ent[i + 4] == 'д') return true;
		else if (ent[i] == 'п' && ent[i + 1] == 'і' && ent[i + 2] == 'д') return true;
		else if (ent[i] == 'п' && ent[i + 1] == 'о' && ent[i + 2] == 'н' && ent[i + 3] == 'а' && ent[i + 4] == 'д') return true;
		else if (ent[i] == 'п' && ent[i + 1] == 'р' && ent[i + 2] == 'е' && ent[i + 3] == 'д') return true;
		else if (ent[i] == 'ч' && ent[i + 1] == 'е' && ent[i + 2] == 'р' && ent[i + 3] == 'е' && ent[i + 4] == 'з') return true;
		else if (ent[i] == 'п' && ent[i + 1] == 'р' && ent[i + 2] == 'е') return true;
		else if (ent[i] == 'п' && ent[i + 1] == 'р' && ent[i + 2] == 'и') return true;
		else if (ent[i] == 'п' && ent[i + 1] == 'р' && ent[i + 2] == 'і') return true;
		else if (ent[i] == 'а' && ent[i + 1] == 'р' && ent[i + 2] == 'х' && ent[i + 3] == 'і') return true;
		else if (ent[i] == 'з' && ent[i + 1] == 'і') return true;
		else if (ent[i] == 'з' && ent[i + 1] == 'о') return true;
		else if (ent[i] == 'і' && ent[i + 1] == 'з') return true;
		else if (ent[i] == 'з') return true;
		else if (ent[i] == 'с') return true;
		else cout << "Префікса немає" << endl;
	}
	return true;
}
void other_check(TString geti) {
	TString get = geti;
	if (get == "без" || get == "роз" || get == "через" || get == "від" || get == "од" || get == "між" || get == "над" || get == "об"
		|| get == "перед" || get == "під" || get == "понад" || get == "пред" || get == "через"
		|| get == "пре" || get == "при" || get == "прі" || get == "архі" || get == "зі" || get == "зо" || get == "із"
		|| get == "з" || get == "с") {
	}
	else {
		cout << "Такого префікса не існує";
		exit(0);
	}
}
void EnterChar() {
	TString pref = "p", corin = "c", suf = "s", ending = "e";
	int number_pref;
	cout << "Скільки префіксів? (0-3): ";
	cin >> number_pref;
	if (number_pref == 1) {
		cout << "Префікс: ";
		cin >> pref;
		other_check(pref);
	}
	else if (number_pref == 2) {
		TString pref1;
		cout << "Префікс (1): ";
		cin >> pref;
		other_check(pref);
		cout << "Префікс (2): ";
		cin >> pref1;
		other_check(pref1);
		pref += pref1;
	}
	else if (number_pref == 3) {
		TString pref1, pref2;
		cout << "Префікс (1): ";
		cin >> pref;
		other_check(pref);
		cout << "Префікс (2): ";
		cin >> pref1;
		other_check(pref1);
		cout << "Префікс (3): ";
		cin >> pref2;
		other_check(pref2);
		pref += pref1 + pref2;
	}
	cout << "Корінь: ";
	cin >> corin;
	if (corin == "p") {
		cout << "У слово має бути хоча б один корінь";
		return EnterChar();
	}
	cout << "Суфікс: ";
	cin >> suf;
	cout << "Закінчення: ";
	cin >> ending;
	if (number_pref == 0) cout << "Слово: " << corin << suf << ending << endl;
	else cout << "Слово: " << pref << corin << suf << ending << endl;
}
void ReloadSlovo(TString slovo) {
	TString word = slovo;
	check(word);
}
//------------------------------------------------------------------
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	SetConsole();
	TString text, text1, t1, slovo;
	cout << "Текст: ";
	getline(cin, text);
	cout << "Розбиття: " << Processing(text) << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Текст: ";
	getline(cin, text1);
	remove_copy(text1.begin(), text1.end(), back_inserter(t1), '-');
	cout << "Злиття: " << t1 << endl;
	cout << "-----------------------------------------" << endl;
	EnterChar();
	cout << "Слово для виведення по частинах: ";
	cin >> slovo;
	ReloadSlovo(slovo);
	system("pause");
	return 0;
}
