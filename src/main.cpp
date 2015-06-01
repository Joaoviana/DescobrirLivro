/*
 * main.cpp
 *
 *  Created on: May 14, 2015
 *      Author: joaopadraoviana
 */

#include "Book.h"
#include "Menu.h"
#include "LevenshteinDistance.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void ClearScreen() {
	cout << string(100, '\n');
}
vector<string> splitString(string input, string delimiter) {
	vector<string> output;
	size_t start = 0;
	size_t end = 0;

	while (start != string::npos && end != string::npos) {
		start = input.find_first_not_of(delimiter, end);

		if (start != string::npos) {
			end = input.find_first_of(delimiter, start);

			if (end != string::npos) {
				output.push_back(input.substr(start, end - start));
			} else {
				output.push_back(input.substr(start));
			}
		}
	}
	return output;
}

vector<string> filter(vector<string> s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i].size() <= 2) {
			s.erase(s.begin() + i);
			i--;
		}
	}
	return s;
}

vector<int> compare(vector<string> input, vector<string> bookTitle) {
	vector<int> points;
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < bookTitle.size(); j++) {
			if (uiLevenshteinDistance(input[i], bookTitle[j]) == 0) {
				points.push_back(0);
			} else if (uiLevenshteinDistance(input[i], bookTitle[j]) == 1) {
				points.push_back(1);
			} else if (uiLevenshteinDistance(input[i], bookTitle[j]) == 2) {
				points.push_back(2);
			} else if (uiLevenshteinDistance(input[i], bookTitle[j]) == 3) {
				points.push_back(3);
			}
		}
	}
	return points;
}

bool checksIfFinished(vector<int> scoreVector, vector<string> bookTitle) {
	int nrOfCorrect = 0;

	for (int k = 0; k < scoreVector.size(); k++) {
		if (scoreVector[k] == 0) {
			nrOfCorrect++;
		}
	}

	if (nrOfCorrect != bookTitle.size()) {
		return false;
	} else
		return true;
}

void firstMenu() {
	Book b = Book();
	b.loadPortugueseTitles();
	//b.loadEnglishTitles();

	vector<int> points;

	int score = 6;
	bool finished = false;
	string userClue;
	vector<string> splitTitle, splitUserInput;
	string randTitle = b.getRandomLivro().getTitle();
	cout << randTitle << endl << endl;
	cout << "DESCRICAO: " << endl;
	cout << b.getRandomLivro().getClue() << endl << endl;

	splitTitle = splitString(randTitle, " ");
	vector<string> title = filter(splitTitle);
	string lixo;
	getline(cin, lixo);
	while (finished == false) {
		string response;
		cout << "----";
		cout << "PISTA: " << endl;
		getline(cin, response);
		printf("merda merda \n");
		splitUserInput = splitString(response, " ");
		points = compare(splitUserInput, title);

		for (int i = 0; i < points.size(); i++) {
			int x = points[i];

			cout << "ALGORITHM OUTPUT: " << points[i] << endl;

			switch (x) {
			case 0:
				cout << "esta certo" << endl;
				break;
			case 1:
				cout << "perto" << endl;
				break;
			case 2:
				cout << "quase lá" << endl;
				break;
			case 3:
				cout << "frio" << endl;
				break;
			}
		}

		finished = checksIfFinished(points, title);
		score--;

		if (score < 0) {
			cout << "PERDEU";
			break;
		}
	}

	if (score > 0) {
		cout << "***PONTUACAO*** " << score << endl << endl;
		cout << "GANHOU";
	} else {
		cout << "PERDEU";
	}

}

void secondMenu() {
	Book b = Book();
	b.loadEnglishTitles();

	vector<int> points;
	int score = 6;
	bool finished = false;
	string userClue;
	vector<string> splitTitleEng, splitUserInputEng;
	string randTitleEng = b.getRandomBook().getTitle();
	//cout << randTitleEng << endl << endl;
	cout << "DESCRIPTION: " << endl;
	cout << b.getRandomBook().getClue() << endl << endl;

	splitTitleEng = splitString(randTitleEng, " ");
	vector<string> titleEng = filter(splitTitleEng);

	string lixo;
	getline(cin, lixo);
	while (finished == false) {
		string response;

		cout << "CLUE: ";
		getline(cin, response);

		splitUserInputEng = splitString(response, " ");
		points = compare(splitUserInputEng, titleEng);

		for (int i = 0; i < points.size(); i++) {
			int x = points[i];

			//cout << "ALGORITHM OUTPUT: " << points[i] << endl;

			switch (x) {
			case 0:
				cout << "you guessed right!" << endl;
				break;
			case 1:
				cout << "close" << endl;
				break;
			case 2:
				cout << "almost there" << endl;
				break;
			case 3:
				cout << "cold..." << endl;
				break;
			}
		}

		finished = checksIfFinished(points, titleEng);
		score--;

		if (score < 0) {
			cout << "YOU'VE LOST";
			break;
		}
	}

	if (score > 0) {
		cout << "***SCORE*** " << score << endl << endl;
		cout << "YOU'VE WON";
	} else {
		cout << "YOU'VE LOST";
	}

}

void testMenu() {
	Book b = Book();
	b.loadPortugueseTitles();

	vector<int> points;

	int score = 6;
	bool finished = false;
	string userClue;
	vector<string> splitTitle, splitUserInput;
	string randTitle = b.getRandomLivro().getTitle();
	cout <<  "Titulo do livro: " << randTitle << endl << endl;
	cout << "DESCRICAO: " << endl;
	cout << b.getRandomLivro().getClue() << endl << endl;

	splitTitle = splitString(randTitle, " ");
	vector<string> title = filter(splitTitle);

	cout << "vetor de strings ja filtrado:  " << endl;
	for (int j = 0; j < title.size(); j++) {
		cout << title[j] << endl;
	}
	cout << endl;

	string lixo;
	getline(cin, lixo);
	while (finished == false) {
		string response;

		cout << "PISTA: ";
		getline(cin, response);

		splitUserInput = splitString(response, " ");
		points = compare(splitUserInput, title);

		for (int i = 0; i < points.size(); i++) {
			int x = points[i];

			cout << "ALGORITHM OUTPUT: " << points[i] << endl;

			switch (x) {
			case 0:
				cout << "esta certo" << endl;
				break;
			case 1:
				cout << "perto" << endl;
				break;
			case 2:
				cout << "quase lá" << endl;
				break;
			case 3:
				cout << "frio" << endl;
				break;
			}
		}

		finished = checksIfFinished(points, title);
		score--;

		if (score < 0) {
			cout << "PERDEU";
			break;
		}
	}

	if (score > 0) {
		cout << score << endl << endl;
		cout << "GANHOU";
	} else {
		cout << "PERDEU";
	}

}

int main() {
	int option;

	cout << " D E S C O B R I R  O  L I V R O" << endl << endl;
	cout
			<< "Este jogo pretende que o utilizador descubra um titulo de um livro em que o seu input nao tenha palavras com menos de 3 letras"
			<< endl;
	cout << "1. Versao Portuguesa." << endl << endl;
	cout << "2. English Version." << endl << endl;
	cout << "3. Versao teste (para melhor compreensao do jogo)" << endl;
	cout << "Option: ";
	cin >> option;

	switch (option) {

	case 1:
		cout << endl << endl << endl << endl;
		cout << "-------------------------------------------------" << endl
				<< endl;
		ClearScreen();
		firstMenu();
		break;
	case 2:
		cout << endl << endl << endl << endl;
		cout << "-------------------------------------------------" << endl
				<< endl;
		ClearScreen();
		secondMenu();
		break;
	case 3:
		cout << endl << endl << endl << endl;
		cout << "-------------------------------------------------" << endl
				<< endl;
		ClearScreen();
		testMenu();
		break;
	default:
		break;

	}
	return 0;
}

