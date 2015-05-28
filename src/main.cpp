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

using namespace std;

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
		if (s[i].size() <= 3) {
			s.erase(s.begin()+ i);
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
			} else {
				i++;
				j++;
			}
		}
	}
	return points;
}

bool checksIfFinished(vector<int> scoreVector, vector<string> bookTitle) {
	bool check = false;
	int nrOfCorrect = 0;

	for (int k = 0; k < scoreVector.size(); k++) {
		if (scoreVector[k] == 0) {
			nrOfCorrect++;
		}
	}

	if (nrOfCorrect == bookTitle.size()) {
		check = true;
	}

	return check;
}

int main() {
	int score = 5;
	vector<string> splitTitle, splitUserInput;
	Book b = Book();
	b.loadPortugueseTitles();
	vector<int> points;
	cout << "livro em portugues:" << endl << endl;
	string randTitle = b.getRandomLivro().getTitle();
	cout << randTitle << endl << endl;
	splitTitle = splitString(randTitle, " ");
	vector<string> splitCenas = filter(splitTitle);
	for (int j = 0; j < splitCenas.size(); j++) {
		cout << splitCenas[j] << endl;
	}

	bool finished = false;
	string userClue;

	while (finished == false) {
		cout << "CLUE: " << endl;
		cin >> userClue;
		splitUserInput = splitString(userClue, " ");
		points = compare(splitUserInput, splitCenas);
		for (int i = 0; i < points.size(); i++) {
			cout << points[i] << endl;
		}
		finished = checksIfFinished(points, splitCenas);
		score--;
	}
	if (score > 0)
		cout << "YOU'VE WON";
	else
		cout << "YOU'VE LOST";
	return 0;
}
//criar interacao com o utilizador
//checkar ordem
//ignorar palavras com menos de 2 caracteres
//2 versoes
//trabalhar com um primeiro, depois ver random titles.
//adicionar pistas, colocando indices nos livros e books e criando pistas.txt e clues.txt
