#include<iostream>

using namespace std;


class Persoana {
	//totul este privat daca nu specifici un modificator de acces
	int varsta;
	string nume;
	string locNastere;
public:

	//constructor default
	Persoana() {
		//nu e nevoie sa pui this daca nu ai conflicte pe acelasi nume de variabila
		varsta = 0;
		nume = "nume necunoscut";
		locNastere = "loc nastere necunoscut";
	}

	//constructor cu 2 parametrii
	Persoana(int varsta, string nume) {
		this->varsta = varsta;
		this->nume = nume;
		this->locNastere = "loc nastere necunoscut";
	}

	//constructor cu toti parametrii
	Persoana(int varsta, string nume, string locNastere) {
		this->varsta = varsta;
		this->nume = nume;
		this->locNastere = locNastere;
	}

	//destructor
	~Persoana() {
		cout << "s-a distrus persoana: " << nume << endl;
	}

	int getVarsta() {
		return varsta;
	}

	void setVarsta(int varsta) {
		this->varsta = varsta;
	}

	string getNume() {
		return nume;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	string getLocNastere() {
		return locNastere;
	}

	void setLocNastere(string locNastere) {
		this->locNastere = locNastere;
	}

	void afisare() {
		cout << "nume = " << nume << "; varsta = " << varsta
			<< "; loc nastere = " << locNastere << endl << endl;
	}
};

class Student {
};


class Profesor
{
};


int main() {
	cout << "Hello!\n";

	Persoana p1;//apel constructor default

	cout << "p1 varsta = " << p1.getVarsta() << endl;
	p1.setVarsta(33);
	cout << "p1 varsta = " << p1.getVarsta() << endl << endl;

	cout << "afisare p1\n";
	p1.afisare();


	cout << "afisare p2\n";
	Persoana p2(10, "Popescu Maria");//apel constructor cu 2 param
	p2.afisare();

	cout << "afisare p3\n";
	Persoana p3(10, "Ionescu Mihai", "Bucuresti");//apel constructor cu toti param
	p3.afisare();



	//exemplu pointeri

	int x = 10;
	int* px = &x;

	cout << "x = " << x << endl; //va afisa valoarea variabilei x
	cout << "&x = " << &x << endl; //va afisa adresa variabilei x
	cout << "px = " << px << endl; //va afisa valoarea din pointerul px
	cout << "*px = " << *px << endl; //*px = indirectare -> va afisa variabla catre care pointeaza pointerul px
	cout << "&px = " << &px << endl; //va afisa adresa pointerului px

	return 0;
}