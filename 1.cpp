// Example program
#include <iostream>
#include <string>



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



class List {    
public:
    List();
    ~List() {}
    
    void push_back(Material*);
    
private:
    class Elem {
        public:
        Elem* code;
        Material* data;
        
        Elem(Material* data, Elem* code = NULL) {
            this->data = data;
            this->code = code;
        }
    };


    int m_size;
    Elem* head;    
};

List::List() {
    m_size = 0;
    head = NULL;
}

void List::push_back(Material* data) {
    if(head == NULL) {
        head = new Elem(data);    
    } else {
        Elem* current = head;
        
        while(current->code) {
            current = current->code;
        }
        
        current->code = new Elem(data);
    }
    
    m_size++;
}


int main()
{
    Material m("Sneg", 1, 1);
    List lst;
    lst.push_back(&m);
}
