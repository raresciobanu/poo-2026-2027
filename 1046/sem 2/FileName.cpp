#include<iostream>

using namespace std;

class Persoana {
	//totul este privat daca nu specifici un modificator de acces
	int varsta;
	string nume;
	string locNastere;
	char* telefon;
	double* venituri;
	int nrVenituri;

public:

	//constructor default
	Persoana() {
		//nu e nevoie sa pui this daca nu ai conflicte pe acelasi nume de variabila
		varsta = 0;
		nume = "nume necunoscut";
		locNastere = "loc nastere necunoscut";

		telefon = new char[strlen("telefon necunoscut") + 1];//+1 pt acel \0
		strcpy(telefon, "telefon necunoscut");

		nrVenituri = 0;
		venituri = nullptr;
	}

	//constructor cu 2 parametrii
	Persoana(int varsta, string nume) {
		this->varsta = varsta;
		this->nume = nume;
		this->locNastere = "loc nastere necunoscut";

		telefon = new char[strlen("telefon necunoscut") + 1];//+1 pt acel \0
		strcpy(telefon, "telefon necunoscut");

		nrVenituri = 0;
		venituri = nullptr;
	}

	//constructor cu toti parametrii
	Persoana(int varsta, string nume, string locNastere,
		const char* telefon, double* venituri, int nrVenituri) {

		this->varsta = varsta;
		this->nume = nume;
		this->locNastere = locNastere;

		this->telefon = new char[strlen(telefon) + 1];//+1 pt acel \0
		strcpy(this->telefon, telefon);

		this->nrVenituri = nrVenituri;

		this->venituri = new double[nrVenituri];
		for (int i = 0;i < nrVenituri; i++) {
			this->venituri[i] = venituri[i];
		}
	}

	Persoana(const Persoana& p) {
		this->varsta = p.varsta;
		this->nume = p.nume;
		this->locNastere = p.locNastere;

		this->telefon = new char[strlen(p.telefon) + 1];//+1 pt acel \0
		strcpy(this->telefon, p.telefon);

		this->nrVenituri = p.nrVenituri;

		this->venituri = new double[p.nrVenituri];
		for (int i = 0;i < p.nrVenituri; i++) {
			this->venituri[i] = p.venituri[i];
		}
	}

	//destructor
	~Persoana() {
		cout << "s-a distrus persoana: " << nume << endl;

		if (telefon != nullptr) {
			delete[] telefon;
		}

		if (venituri != nullptr) {
			delete[] venituri;
		}
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

	char* getTelefon() {
		return this->telefon;
	}

	void setTelefon(char* telefon) {
		if (this->telefon != nullptr) {
			delete[] this->telefon;
		}

		this->telefon = new char[strlen(telefon) + 1];//+1 pt acel \0
		strcpy(this->telefon, telefon);
	}

	int getNrVenituri() {
		return nrVenituri;
	}

	void setNrVenituri(int nrVenituri) {
		nrVenituri = nrVenituri;
	}

	double* getVenituri() {
		return venituri;
	}

	void setVenituri(int nrVenituri, double* venituri) {
		this->nrVenituri = nrVenituri;

		delete[] venituri; //evitare memory leaks

		this->venituri = new double[nrVenituri];
		for (int i = 0;i < nrVenituri; i++) {
			this->venituri[i] = venituri[i];
		}
	}

	void afisare() {
		cout << "nume = " << nume << "; varsta = " << varsta
			<< "; loc nastere = " << locNastere << "; telefon = " << telefon << endl;

		if (nrVenituri > 0) {
			cout << "Venituri:\n";
			for (int i = 0;i < nrVenituri;i++) {
				cout << venituri[i] << " ";
			}
			cout << endl << endl;
		}
		else {
			cout << endl;
		}
	}
};

//mostenire -> conceptul de compunere - has a
class Facultate {
	int nrPersoane;
	Persoana* persoane;

	//constructor cu toti parametrii
	Facultate(Persoana* persoane, int nrPersoane) {
		this->nrPersoane = nrPersoane;

		this->persoane = new Persoana[nrPersoane];
		for (int i = 0;i < nrPersoane; i++) {
			this->persoane[i] = persoane[i];
		}
	}
};

//mostenire -> is a
class Student :public Persoana {
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
	double venituri[5] = { 1199.9, 2500.55, 5553.54, 9999.99, 544.44 };

	Persoana p3(10, "Ionescu Mihai", "Bucuresti", "0746 434 544", venituri, 5);//apel constructor cu toti param
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