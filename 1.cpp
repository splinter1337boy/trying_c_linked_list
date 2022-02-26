// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Example program
#include <iostream>
#include <string>
#include "conio.h"


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
    ~List() {}
    static int getSize() { return m_size; }
    void push_back(Material*);
    
    Material* operator[] (const int);
    
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
    Elem* head;
};

int List::m_size = 0;

List::List() {
    head = NULL;
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
		std::cout << current->code << "\n";
    }
    
    m_size++;
}


Material* List::operator[] (const int index) {
    Elem* current = head;
    while(current) {
        
        if(*(current->code) == index) {
            return current->data;
        }
        
        current = current->pNext;
    }

	throw new std::exception("Can't find an element from the list");
    // exception is needed
}


int main()
{
	try {
		Material* m  = new Material("Sneg", 1, 1);
		Material* m2 = new Material("Telephone", 3, 4);
		List lst;
		lst.push_back(m);

		std::cout << lst[0] << "\n";
	} catch(std::exception& e) {
		std::cout << e.what() << "\n";	
	}
    
	getch();
}

