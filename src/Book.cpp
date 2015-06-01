/*
 * Book.cpp
 *
 *  Created on: May 14, 2015
 *      Author: joaopadraoviana
 */

#include "Book.h"

Book::Book() {
	// TODO Auto-generated constructor stub

}

Book::Book(string title, string author, string year, string clue) {
	this->title = title;
	this->author = author;
	this->year = year;
	this->clue = clue;
}

void Book::loadPortugueseTitles() {
	ifstream file("livros.txt");
	string title, author, year, line, clue;
	while (getline(file, line)) {
		stringstream iss(line);
		getline(iss, title, ',');
		getline(iss, author, ',');
		getline(iss, year, ',');
		getline(iss, clue, '/');

		Book l = Book(title, author, year, clue);
		livros.push_back(l);
	}
}

void Book::loadEnglishTitles() {
	ifstream file("books.txt");
	string title, author, year, line, clue;
	while (getline(file, line)) {
		stringstream iss(line);
		getline(iss, title, ',');
		getline(iss, author, ',');
		getline(iss, year, ',');
		getline(iss,clue, '/');
		// ADICIONAR INDEXES
		Book b = Book(title, author, year, clue);
		books.push_back(b);
	}
}

const string& Book::getAuthor() const {
	return author;
}

void Book::setAuthor(const string& author) {
	this->author = author;
}

const string& Book::getYear() const {
	return year;
}

int Book::getNrOfBooks() {
	string line;
	int nrOfBooks = 0;
	ifstream infile;
	infile.open("books.txt");
	while (!infile.eof()) {
		getline(infile, line);
		nrOfBooks++;
	}
	return nrOfBooks;
}

int Book::getNrOfLivros() {
	string line;
	int nrOfLivros = 0;
	ifstream infile;
	infile.open("livros.txt");
	while (!infile.eof()) {
		getline(infile, line);
		nrOfLivros++;
	}
	return nrOfLivros;
}

const vector<Book>& Book::getBooks() const {
	return books;
}

void Book::setBooks(const vector<Book>& books) {
	this->books = books;
}

const vector<Book>& Book::getLivros() const {
	return livros;
}

string Book::getTitle() const {
	return title;
}

void Book::setTitle(const string& title) {
	this->title = title;
}

void Book::setLivros(const vector<Book>& livros) {
	this->livros = livros;
}

void Book::setYear(const string& year) {
	this->year = year;
}

Book::~Book() {
// TODO Auto-generated destructor stub
}

Book Book::getRandomLivro() {
	int index;
	srand(time(NULL));
	index = rand() % livros.size();

	return getLivros()[index];
}

Book Book::getRandomBook() {
	int index;
	srand(time(NULL));
	index = rand() % books.size();

	return getBooks()[index];
}
