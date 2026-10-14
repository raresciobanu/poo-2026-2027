#include<iostream>

using namespace std;

class Persoana {
	//totul este privat daca nu specifici un modificator de acces
	int varsta;
	string nume;
	string locNastere;
	char* pTelefon;
	double* pVenituri;
	int nrVenituri;

private:
	const int ID;
	static int numarObPersoana;
public:

	//constructor default
	Persoana() :ID(0) {
		//nu e nevoie sa pui this daca nu ai conflicte pe acelasi nume de variabila
		varsta = 0;
		nume = "nume necunoscut";
		locNastere = "loc nastere necunoscut";
		pTelefon = new char[strlen("telefon necunoscut") + 1];//+1 pt acel \0
		strcpy(pTelefon, "telefon necunoscut");

		nrVenituri = 0;
		pVenituri = nullptr;
		numarObPersoana++;
	}

	//constructor cu 2 parametrii
	Persoana(int varsta, string nume) :ID(0) {
		this->varsta = varsta;
		this->nume = nume;
		this->locNastere = "loc nastere necunoscut";

		pTelefon = new char[strlen("telefon necunoscut") + 1];//+1 pt acel \0
		strcpy(pTelefon, "telefon necunoscut");

		nrVenituri = 0;
		pVenituri = nullptr;
		numarObPersoana++;
	}

	//constructor cu toti parametrii
	Persoana(int varsta, string nume, string locNastere,
		const char* pTelefon, double* pVenituri, int nrVenituri, int ID) :ID(ID) {

		this->varsta = varsta;
		this->nume = nume;
		this->locNastere = locNastere;

		this->pTelefon = new char[strlen(pTelefon) + 1];//+1 pt acel \0
		strcpy(this->pTelefon, pTelefon);

		this->nrVenituri = nrVenituri;

		this->pVenituri = new double[nrVenituri];
		for (int i = 0;i < nrVenituri; i++) {
			this->pVenituri[i] = pVenituri[i];
		}
		numarObPersoana++;
	}

	Persoana(const Persoana& p) :ID(p.ID) {
		this->varsta = p.varsta;
		this->nume = p.nume;
		this->locNastere = p.locNastere;

		this->pTelefon = new char[strlen(p.pTelefon) + 1];//+1 pt acel \0
		strcpy(this->pTelefon, p.pTelefon);

		this->nrVenituri = p.nrVenituri;

		this->pVenituri = new double[p.nrVenituri];
		for (int i = 0;i < p.nrVenituri; i++) {
			this->pVenituri[i] = p.pVenituri[i];
		}
		numarObPersoana++;
	}

	Persoana& operator=(const Persoana& p) {
		//todo
	}

	//destructor
	~Persoana() {
		cout << "s-a distrus persoana: " << nume << endl;

		if (pTelefon != nullptr) {
			delete[] pTelefon;
		}

		if (pVenituri != nullptr) {
			delete[] pVenituri;
		}
		numarObPersoana--;
	}

	int getID() {
		return ID;
	}

	int getNumarObPersoana() {
		return numarObPersoana;
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

	char* getPTelefon() {
		return this->pTelefon;
	}

	void setPTelefon(const char* pTelefon) {
		//shallow copy - ai mai multi pointeri ce pointeaza catre aceeasi adresa de memorie
		// adica asa: this->pTelefon = pTelefon;

		//deep copy - adica creezi o noua zona de memorie si copiezi toata informatia acolo
		if (this->pTelefon != nullptr) {
			delete[] this->pTelefon; //evitare memory leaks
		}

		this->pTelefon = new char[strlen(pTelefon) + 1];//+1 pt acel \0
		strcpy(this->pTelefon, pTelefon);
	}

	int getNrVenituri() {
		return nrVenituri;
	}

	void setNrVenituri(int nrVenituri) {
		this->nrVenituri = nrVenituri;
	}

	double* getPVenituri() {
		return pVenituri;
	}

	void setPVenituri(int nrVenituri, double* pVenituri) {
		this->nrVenituri = nrVenituri;

		if (this->pVenituri != nullptr) {
			delete[] this->pVenituri; //evitare memory leaks
		}

		this->pVenituri = new double[nrVenituri];
		for (int i = 0;i < nrVenituri; i++) {
			this->pVenituri[i] = pVenituri[i];
		}
	}

	void afisare() {
		cout << "ID = " << ID << "; nume = " << nume << "; varsta = " << varsta
			<< "; loc nastere = " << locNastere << "; telefon = " << pTelefon << endl;

		if (nrVenituri > 0) {
			cout << "Venituri:\n";
			for (int i = 0;i < nrVenituri;i++) {
				cout << pVenituri[i] << " ";
			}
			cout << endl << endl;
		}
		else {
			cout << endl;
		}
	}
};

int Persoana::numarObPersoana = 0;

//mostenire -> conceptul de compunere - has a
class Facultate {
	int nrPersoane;
	Persoana* pPersoane;

	//constructor cu toti parametrii
	Facultate(Persoana* pPersoane, int nrPersoane) {
		this->nrPersoane = nrPersoane;

		this->pPersoane = new Persoana[nrPersoane];
		for (int i = 0;i < nrPersoane; i++) {
			this->pPersoane[i] = pPersoane[i];
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

	//apel constructor cu toti param
	Persoana p3(10, "Ionescu Mihai", "Bucuresti", "0746 434 544", venituri, 5, 33311);
	p3.afisare();

	//constr. de copiere
	Persoana p4(p3);
	cout << "afisare p4\n";
	p4.afisare();
	//constr. de copiere
	Persoana p5 = p4;
	cout << "afisare p5\n";
	p5.afisare();

	//afisare si modificare prin getteri si setteri
	cout << "aplicare setteri si getteri pe p3\n\n";
	p3.setNume("Marin Ciobanu");
	p3.setVarsta(22);
	p3.setPTelefon("0764 343 434");
	p3.setLocNastere("Vaslui");
	p3.setNrVenituri(50);//nu conteaza ce dau aici ca oricum va fi suprascris nrVenituri de metoda setVenituri 
	double venituri2[2] = { 677.78, 111.55 };
	p3.setPVenituri(2, venituri2);

	cout << "ID = " << p3.getID() << "; nume = " << p3.getNume() << "; varsta = " << p3.getVarsta()
		<< "; loc nastere = " << p3.getLocNastere() << "; telefon = " << p3.getPTelefon() << endl;

	if (p3.getNrVenituri() > 0) {
		cout << "Venituri:\n";
		for (int i = 0;i < p3.getNrVenituri();i++) {
			cout << p3.getPVenituri()[i] << " ";
		}
		cout << endl << endl;
	}
	else {
		cout << endl;
	}



	//exemplu pointeri

	int x = 10;
	int* px = &x;

	cout << "x = " << x << endl; //va afisa valoarea variabilei x
	cout << "&x = " << &x << endl; //va afisa adresa variabilei x
	cout << "px = " << px << endl; //va afisa valoarea din pointerul px
	cout << "*px = " << *px << endl; //*px = indirectare -> va afisa variabla catre care pointeaza pointerul px
	cout << "&px = " << &px << endl; //va afisa adresa pointerului px

	//const

	const int ww = 22;//variabila constanta - nu mai poate fi modificata
	const int* pointer1 = &ww; //ai un pointer ce pointeaza catre o zona de memorie CONSTANTA
	//pointer1 = px;

	int* const pointer2 = &x; //ai un pointer CONSTANT care poate pointa catre orice
	//pointer2 = px; - va da eroare

	const int* const pointer3 = &ww;  //ai un pointer CONSTANT care pointeaza catre o zona de memorie CONSTANTA


	cout << "obiecte persoana create pana in acet moment = "
		<< p5.getNumarObPersoana() << " " << p4.getNumarObPersoana() << endl;

	return 0;
}