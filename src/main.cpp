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
			} else {
				i++;
				j++;
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
	}
	else
		return true;
}

int main() {
	int score = 6;
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
		cout << "CLUE: ";
		string response;
		getline(cin, response);
		//cin >> userClue;
		//cout << "CIN   " << response << endl;
		splitUserInput = splitString(response, " ");
		points = compare(splitUserInput, splitCenas);
		for (int i = 0; i < points.size(); i++) {
			cout << "ALGORITHM OUTPUT: " <<points[i] << endl << endl;
			int x = points[i];
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
		finished = checksIfFinished(points, splitCenas);

		score--;
		if (score < 0) {
			cout << "YOU'VE LOST";
			break;
		}
	}
	if (score > 0) {
		cout << score << endl << endl;
		cout << "YOU'VE WON";
	} else {
		//cout << score << endl << endl;
		cout << "YOU'VE LOST";
	}
	return 0;
}
//checkar ordem
//2 versoes
//adicionar pistas, colocando indices nos livros e books e criando pistas.txt e clues.txt
