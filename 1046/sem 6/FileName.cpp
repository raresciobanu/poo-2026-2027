#include<iostream>

using namespace std;

enum LUNA_NASTERE
{
	IANUARIE,
	FEBRUARIE,
	MARTIE,
	APRILIE,
	MAI,
	IUNIE,
	IULIE,
	AUGUST,
	SEPTEMBRIE,
	OCTOMBRIE,
	NOIEMBRIE,
	DECEMBRIE,
	NECUNOSCUT
};

class Persoana {
	//totul este privat daca nu specifici un modificator de acces
	int varsta;
	string nume;
	string locNastere;
	char* pTelefon;
	double* pVenituri;
	int nrVenituri;
	LUNA_NASTERE lunaNastere;
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
		lunaNastere = NECUNOSCUT;
		numarObPersoana++;
	}

	//constructor cu 2 parametrii
	Persoana(int varsta, string nume) :ID(0) {
		this->varsta = varsta;
		this->nume = nume;
		this->locNastere = "loc nastere necunoscut";

		pTelefon = new char[strlen("telefon necunoscut") + 1];//+1 pt acel \0
		strcpy(pTelefon, "telefon necunoscut");

		lunaNastere = NECUNOSCUT;

		nrVenituri = 0;
		pVenituri = nullptr;
		numarObPersoana++;
	}

	//constructor cu toti parametrii
	Persoana(int varsta, string nume, string locNastere,
		const char* pTelefon, double* pVenituri, int nrVenituri,
		int ID, LUNA_NASTERE lunaNastere) :ID(ID) {

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

		this->lunaNastere = lunaNastere;
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
		this->lunaNastere = p.lunaNastere;
		numarObPersoana++;
	}

	//se returneaza Persoana& pt a putea face inlantuire de op =: p1=p2=p3=p4;
	Persoana& operator=(const Persoana& p) {
		if (this != &p) {//ignora cazul p1=p1;
			this->varsta = p.varsta;
			this->nume = p.nume;
			this->locNastere = p.locNastere;

			delete[] this->pTelefon;//evitare memory leaks
			this->pTelefon = new char[strlen(p.pTelefon) + 1];//+1 pt acel \0
			strcpy(this->pTelefon, p.pTelefon);

			this->nrVenituri = p.nrVenituri;

			delete[] this->pVenituri;//evitare memory leaks
			this->pVenituri = new double[p.nrVenituri];
			for (int i = 0;i < p.nrVenituri; i++) {
				this->pVenituri[i] = p.pVenituri[i];
			}

			this->lunaNastere = p.lunaNastere;
		}

		return *this;
	}

	//se testeaza: cout << p1;
	//friend - imprieteneste clasa ta cu acesta functie implementata global
	//=> ai acces la zona privata a clasei prin intermediul lui p...altfel trebuia sa folosesti getteri
	//implementarea functiei se poate face in clasa sau in afara
	friend ostream& operator<<(ostream& out, const Persoana& p);
	friend istream& operator>>(istream& in, Persoana& p);

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

	LUNA_NASTERE getLunaNastere() const {
		return this->lunaNastere;
	}

	//aceasta metoda a devenit constanta pentru a nu permite suprascrierea campurilor clasei
	//in interiorul ei ( e folosita in op << unde Persoana este constanta)
	string getLunaNastereCaText() const {
		switch (this->lunaNastere) {
		case IANUARIE:
			return "ianuarie";
		case FEBRUARIE:
			return "februarie";
		case MARTIE:
			return "martie";
		case APRILIE:
			return "aprilie";
		case MAI:
			return "mai";
		case IUNIE:
			return "iunie";
		case IULIE:
			return "iulie";
		case AUGUST:
			return "august";
		case SEPTEMBRIE:
			return "septembrie";
		case OCTOMBRIE:
			return "octombrie";
		case NOIEMBRIE:
			return "noiembrie";
		case DECEMBRIE:
			return "decembrie";
			//case NECUNOSCUT:
			//	return "luna de nastere necunoscuta";// am comentat ca sa intre pe cazul default - sa stiti si de el
		default:
			return "luna de nastere necunoscuta";
		}
	}

	void setLunaNastere(LUNA_NASTERE lunaNastere) {
		this->lunaNastere = lunaNastere;
	}

	//polimorfism: 
	//overload(supraincarcare) - poti defini mai multe metode cu acelasi nume
	//conditia ar fi ca nr de parametri primit sa fie diferit/acelasi nr de parametri dar in alta ordine
	void setLunaNastere(string lunaNastere) {
		if (lunaNastere == "ianuarie") {
			this->lunaNastere = IANUARIE;
		}
		else if (lunaNastere == "februarie") {
			this->lunaNastere = FEBRUARIE;
		}
		else if (lunaNastere == "martie") {
			this->lunaNastere = MARTIE;
		}
		else if (lunaNastere == "aprilie") {
			this->lunaNastere = APRILIE;
		}
		else if (lunaNastere == "mai") {
			this->lunaNastere = MAI;
		}
		else if (lunaNastere == "iunie") {
			this->lunaNastere = IUNIE;
		}
		else if (lunaNastere == "iulie") {
			this->lunaNastere = IULIE;
		}
		else if (lunaNastere == "august") {
			this->lunaNastere = AUGUST;
		}
		else if (lunaNastere == "septembrie") {
			this->lunaNastere = SEPTEMBRIE;
		}
		else if (lunaNastere == "octombrie") {
			this->lunaNastere = OCTOMBRIE;
		}
		else if (lunaNastere == "noiembrie") {
			this->lunaNastere = NOIEMBRIE;
		}
		else if (lunaNastere == "decembrie") {
			this->lunaNastere = DECEMBRIE;
		}
		else {
			this->lunaNastere = NECUNOSCUT;
		}
	}

	void afisare() {
		cout << "ID = " << ID << "; nume = " << nume << "; varsta = " << varsta
			<< "; loc nastere = " << locNastere << "; telefon = " << pTelefon
			<< "; luna nastere = " << getLunaNastereCaText()
			<< "; luna nastere ca enum = " << lunaNastere << endl;

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

	double aflaMinimDinPVenituri() {
		double min = pVenituri[0];

		for (int i = 0;i < nrVenituri;i++) {
			if (min > pVenituri[i]) {
				min = pVenituri[i];
			}
		}

		return min;
	}


};

int Persoana::numarObPersoana = 0;

ostream& operator<<(ostream& out, const Persoana& p) {
	out << "ID = " << p.ID << "; nume = " << p.nume << "; varsta = " << p.varsta
		<< "; loc nastere = " << p.locNastere << "; telefon = " << p.pTelefon
		<< "; luna nastere = " << p.getLunaNastereCaText()
		<< "; luna nastere ca enum = " << p.lunaNastere << endl;


	if (p.nrVenituri > 0) {
		out << "Venituri:\n";
		for (int i = 0;i < p.nrVenituri;i++) {
			out << p.pVenituri[i] << " ";
		}
		out << endl << endl;
	}
	else {
		out << endl;
	}

	return out;
}

istream& operator>>(istream& in, Persoana& p) {
	cout << "nume = "; in >> p.nume;
	cout << "varsta = "; in >> p.varsta;
	cout << "locNastere = "; in >> p.locNastere;

	char aux[100];
	cout << "telefon = "; in >> aux;

	delete[] p.pTelefon;//evitare memory leaks
	p.pTelefon = new char[strlen(aux) + 1];//+1 pt acel \0
	strcpy(p.pTelefon, aux);

	cout << "luna nastere enum ca sir de caractere= "; in >> aux;
	p.setLunaNastere(aux);

	cout << "nrVenituri = "; in >> p.nrVenituri;

	cout << "Venituri:\n";
	delete[] p.pVenituri;//evitare memory leaks
	p.pVenituri = new double[p.nrVenituri];
	for (int i = 0;i < p.nrVenituri; i++) {
		cout << "pVenituri[" << i << "] = ";
		in >> p.pVenituri[i];
	}

	return in;
}

//mostenire -> conceptul de compunere - has a
class Facultate {
	int nrPersoane;
	Persoana* pPersoane;
public:
	Facultate() {
		this->nrPersoane = 0;

		this->pPersoane = nullptr;
	}

	//constructor cu toti parametrii
	Facultate(int nrPersoane, Persoana* pPersoane) {
		this->nrPersoane = nrPersoane;

		this->pPersoane = new Persoana[nrPersoane];
		for (int i = 0;i < nrPersoane; i++) {
			this->pPersoane[i] = pPersoane[i];
		}
	}

	Facultate(const Facultate& f) {
		this->nrPersoane = f.nrPersoane;

		this->pPersoane = new Persoana[f.nrPersoane];
		for (int i = 0;i < f.nrPersoane; i++) {
			this->pPersoane[i] = f.pPersoane[i];
		}
	}

	~Facultate() {
		if (this->pPersoane != nullptr) {
			delete[] this->pPersoane;
		}
	}

	Facultate& operator=(const Facultate& f) {
		if (this != &f) {
			this->nrPersoane = f.nrPersoane;

			delete[] this->pPersoane;
			this->pPersoane = new Persoana[f.nrPersoane];
			for (int i = 0;i < f.nrPersoane; i++) {
				this->pPersoane[i] = f.pPersoane[i];
			}
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Facultate& f) {
		out << "Facultate:\n";
		out << "Nr. persoane = " << f.nrPersoane << "; Persoane:\n";
		for (int i = 0;i < f.nrPersoane; i++) {
			out << f.pPersoane[i];
		}

		return out;
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
	Persoana p3(10, "Ionescu Mihai", "Bucuresti", "0746 434 544", venituri, 5, 33311, IULIE);
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
	cout << "afisare dupa setteri p3\n" << p3 << endl;
	cout << "p3 minim = " << p3.aflaMinimDinPVenituri() << endl;

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


	cout << "obiecte persoana create pana in acest moment = "
		<< p5.getNumarObPersoana() << " " << p4.getNumarObPersoana() << endl << endl;


	//op = si <<
	Persoana p6;
	p6 = p3;


	//testare enum
	p6.setLunaNastere("ianuarie");
	cout << p6 << endl;
	p6.setLunaNastere(MAI);
	cout << p6 << endl;

	//op >>
	Persoana p7;
	cin >> p7;
	cout << p7;

	Persoana persoane[2];
	persoane[0] = p1;
	persoane[1] = p3;

	cout << "\n\nafisare facultate\n\n";
	Facultate f1(2, persoane);
	cout << f1 << endl << endl;



	return 0;
}