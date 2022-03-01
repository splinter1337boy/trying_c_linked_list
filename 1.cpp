// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// rename variable m_size to m_counter


// Example program
#include <iostream>
#include <string>
#include "conio.h"


class ArrayException : public std::exception {
private:
	std::string m_error;

public:
	ArrayException(std::string error) : m_error(error) {
	}

	const char* what() throw() { return m_error.c_str(); }
};


class Material {
private:
	std::string nazv;
	float rash;
	float ost;

public:
	Material() {
		nazv = "Noname";
		rash = 0;
		ost = 0;
	}

	Material(std::string p1, float p2, float p3) {
		nazv = p1;
		if(p2 > 0) rash = p2; else p2 = 0;
		if(p3 > 0) ost = p3; else p3 = 0;
	}

	Material(Material& o) {
		nazv = o.nazv;
		rash = o.rash;
		ost = o.ost;
	}

	Material* operator = (Material* m) {
		if(this == m) return this;

		nazv = m->nazv;
		ost = m->ost;
		rash = m->rash;

		return this;
	}

	~Material() {}

	void setNazv(std::string p) { nazv = p; }
	void setR(float p) { rash = p; }
	void setO(float p) { ost = p; }

	std::string getNazv() { return nazv; }
	float getR() { return rash; }
	float getO() { return ost; }

	void print() { std::cout << nazv << "  " << ost << "  " << rash << "\n"; }
};

std::ostream& operator << (std::ostream& out, Material* m) {
    out << "Name: " << m->getNazv() << "; Rashod: " << m->getR() << "; Ostatok: " << m->getO() << "\n";
    
    return out;
}




class List {    
public:
    List();
    ~List();
    static int getSize() { return m_size; }
	int getLength() { return m_length; }
    void push_back(Material*);
	void pop_front();
	void clear();
    
    Material* operator[] (const int);
	Material* operator = (const Material*);
    
private:
    class Elem {
        public:
        int* code;
        Elem* pNext;
        Material* data;

		Elem() {
			data = NULL;
			pNext = NULL;
			code = NULL;
		}
        
        Elem(Material* data, Elem* pNext = NULL) {
            this->data = data;
            this->pNext = pNext;
            this->code = new int(m_size);
        }

    };


    static int m_size;
	int m_length;
    Elem* head;
};

int List::m_size = 0;

List::List() {
    head = NULL;
	m_length = 0;
}

List::~List() {
	clear();
}

void List::push_back(Material* data) {
    if(head == NULL) {
        head = new Elem(data);   
    } else {
        Elem* current = head;
        
        while(current->pNext) {
            current = current->pNext;
        }
        
        current->pNext = new Elem(data);
    }
    
    m_size++;
	m_length++;
}

void List::pop_front() {
	Elem* next = head;

	head = head->pNext;

	delete next;

	m_length--;
}

void List::clear() {
	while(m_length) {
		pop_front();
	}
}


Material* List::operator[] (const int index) {
    Elem* current = head;
	int counter = 0;
    while(current) {
        if(counter == index) {
            return current->data;
        }
        
        current = current->pNext;
		counter++;
    }

	throw ArrayException(std::to_string((_ULonglong)index));
    // exception is needed
}

std::ostream& operator << (std::ostream& out, List& lst) {
	for(int i = 0; i < lst.getLength(); i++) {
		out << lst[i];
	}
	out << "\n";
	return out;
}


int main()
{
	try {
		Material* m  = new Material("Sneg", 1, 1);
		Material* m2 = new Material("Telephone", 3, 4);
		Material* m3 = new Material("Stol", 2, 2);
		List lst;
		lst.push_back(m);
		lst.push_back(m2);
		lst.push_back(m3);

		std::cout << lst.getLength() << "\n";
		
		std::cout << lst << "\n";

		lst.pop_front();
		std::cout << lst.getLength() << "\n";

		std::cout << lst << "\n";

		
		lst.pop_front();
		std::cout << lst.getLength() << "\n";

		std::cout << lst << "\n";

		lst[0]->operator=(m);

		std::cout << lst.getLength() << "\n";

		std::cout << lst << "\n";
	} catch(ArrayException& e) {
		std::cerr << "Out of range, index (" << e.what() << ")\n";	
	} catch(std::exception& e) {
		std::cerr << "Some other std::exception occured (" << e.what() << ")\n";
	}
    
	getch();
}

