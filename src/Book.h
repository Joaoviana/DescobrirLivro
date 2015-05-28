/*
 * Book.h
 *
 *  Created on: May 14, 2015
 *      Author: joaopadraoviana
 */

#ifndef SRC_BOOK_H_
#define SRC_BOOK_H_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Book {
	string title, author, year;

	vector<Book> livros;
	vector<Book> books;
public:

	Book();
	Book(string title, string author, string year);
	virtual ~Book();

	void loadPortugueseTitles();
	void loadEnglishTitles();

	//buscar random element de um vetor
	Book getRandomLivro();
	Book getRandomBook();

	// nr de livros e books
	int getNrOfBooks();
	int getNrOfLivros();



	//gets and sets
	const string& getAuthor() const;
	void setAuthor(const string& author);

	const string& getYear() const;
	void setYear(const string& year);
	const vector<Book>& getBooks() const;
	void setBooks(const vector<Book>& books);
	const vector<Book>& getLivros() const;
	void setLivros(const vector<Book>& livros);
	string getTitle() const;
	void setTitle(const string& title);
};

#endif /* SRC_BOOK_H_ */


//load ficheiros
//ver quais as variaveis
