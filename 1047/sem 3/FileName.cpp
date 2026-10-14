#include<iostream>

using namespace std;

class Vehicul {
	//totul este privat in aceasta clasa by default
	double nrKm;
	string marca;
	string culoare;
	char* pSerieSasiu;
	int* pVitezeMedii;
	int nrViteze;
private:
	const int ID;
	static int numarObVehicul;
public:

	//constructor default/fara parametri
	Vehicul() :ID(0) {
		//nu esti obligat sa pui this->
		//el se pune daca EXISTA conflicte cu alte variabile care au acelasi nume
		nrKm = 0.0;
		marca = "marca necunoscuta";
		culoare = "culoare necunoscuta";

		pSerieSasiu = new char[strlen("serie sasiu necunoscuta") + 1];//+1 pt ca avem \0
		strcpy(pSerieSasiu, "serie sasiu necunoscuta");

		nrViteze = 0;
		pVitezeMedii = nullptr;
		numarObVehicul++;
	}

	//constructor cu 2 parametri
	Vehicul(double nrKm, string marca) :ID(0) {
		this->nrKm = nrKm;
		this->marca = marca;
		this->culoare = "culoare necunoscuta";

		pSerieSasiu = new char[strlen("serie sasiu necunoscuta") + 1];//+1 pt ca avem \0
		strcpy(pSerieSasiu, "serie sasiu necunoscuta");

		nrViteze = 0;
		pVitezeMedii = nullptr;
		numarObVehicul++;
	}


	//constructor cu toti parametrii
	Vehicul(double nrKm, string marca, string culoare,
		const char* pSerieSasiu, int nrViteze, int* pVitezeMedii, int ID) :ID(ID) {
		this->nrKm = nrKm;
		this->marca = marca;
		this->culoare = culoare;

		this->pSerieSasiu = new char[strlen(pSerieSasiu) + 1];//+1 pt ca avem \0
		strcpy(this->pSerieSasiu, pSerieSasiu);

		this->nrViteze = nrViteze;
		this->pVitezeMedii = new int[nrViteze];
		for (int i = 0;i < nrViteze;i++) {
			this->pVitezeMedii[i] = pVitezeMedii[i];
		}
		numarObVehicul++;
	}

	Vehicul(const Vehicul& v) :ID(v.ID) {
		this->nrKm = v.nrKm;
		this->marca = v.marca;
		this->culoare = v.culoare;

		this->pSerieSasiu = new char[strlen(v.pSerieSasiu) + 1];//+1 pt ca avem \0
		strcpy(this->pSerieSasiu, v.pSerieSasiu);

		this->nrViteze = v.nrViteze;
		this->pVitezeMedii = new int[v.nrViteze];
		for (int i = 0;i < v.nrViteze;i++) {
			this->pVitezeMedii[i] = v.pVitezeMedii[i];
		}
		numarObVehicul++;
	}

	Vehicul& operator=(const Vehicul& v) {
		//todo
	}

	//destructor
	~Vehicul() {
		cout << "S-a distrus un vehicul cu marca: " << marca << " si culoare: " << culoare << endl;


		if (this->pSerieSasiu != nullptr) {
			delete[] this->pSerieSasiu;
		}

		if (this->pVitezeMedii != nullptr) {
			delete[] this->pVitezeMedii;
		}
		numarObVehicul--;
	}

	double getID() {
		return this->ID;
	}

	double getNrKm() {
		return this->nrKm;
	}

	void setNrKm(double nrKm) {
		this->nrKm = nrKm;
	}

	string getMarca() {
		return this->marca;
	}

	void setMarca(string marca) {
		this->marca = marca;
	}

	string getCuloare() {
		return this->culoare;
	}

	void setCuloare(string culoare) {
		this->culoare = culoare;
	}

	char* getPSerieSasiu() {
		return pSerieSasiu;
	}

	void setPSerieSasiu(const char* pSerieSasiu) {
		//shallow copy - ai mai multi pointeri ce pointeaza catre aceeasi adresa de memorie
		//this->pSerieSasiu = pSerieSasiu;

		//deep copy - adica creezi o noua zona de memorie si copiezi toata informatia acolo
		if (this->pSerieSasiu != nullptr) {
			delete[] this->pSerieSasiu; //evitare memory leaks
		}

		this->pSerieSasiu = new char[strlen(pSerieSasiu) + 1];//+1 pt ca avem \0
		strcpy(this->pSerieSasiu, pSerieSasiu);
	}

	int getNrViteze() {
		return nrViteze;
	}

	void setNrViteze(int nrViteze) {
		this->nrViteze = nrViteze;
	}

	int getNumarObVehicul() {
		return numarObVehicul;
	}

	int* getPVitezeMedii() {
		return this->pVitezeMedii;
	}

	void setPVitezeMedii(int nrViteze, int* pVitezeMedii) {
		if (this->pVitezeMedii != nullptr) {
			delete[] this->pVitezeMedii; //evitare memory leaks
		}

		this->nrViteze = nrViteze;
		this->pVitezeMedii = new int[nrViteze];
		for (int i = 0;i < nrViteze;i++) {
			this->pVitezeMedii[i] = pVitezeMedii[i];
		}
	}

	void afisare() {
		cout << "ID = " << ID << "; marca = " << marca << "; culoare = "
			<< culoare << "; nrKm = " << nrKm << "; serie sasiu = " << pSerieSasiu << endl;

		if (nrViteze > 0) {
			cout << "Viteze medii:\n";
			for (int i = 0;i < nrViteze;i++) {
				cout << pVitezeMedii[i] << " ";
			}
			cout << endl << endl;
		}
		else {
			cout << endl;
		}
	}
};

int Vehicul::numarObVehicul = 0;//initializare var statica

// mostenire - has A - conceptul de compunere
class Dealer {
	int nrMasini;
	Vehicul* pVehicule;
public:
	Dealer(int nrMasini, Vehicul* pVehicule) {
		this->nrMasini = nrMasini;

		this->pVehicule = new Vehicul[nrMasini];
		for (int i = 0;i < nrMasini;i++) {
			this->pVehicule[i] = pVehicule[i];
		}
	}
};

// mostenire - is A - mostenire directa
class Masina :public Vehicul {

};

int main() {
	cout << "Hello!\n";

	//constr default
	Vehicul v1;
	cout << "v1 marca = " << v1.getMarca() << endl;
	v1.setMarca("Audi");
	cout << "v1 marca = " << v1.getMarca() << endl << endl;

	cout << "Afisare v1:\n";
	v1.afisare();

	//const 2 param
	Vehicul v2(343.44, "BMW");
	cout << "Afisare v2:\n";
	v2.afisare();

	//constr toti param
	int aux[4] = { 55,60,80,90 };
	Vehicul v3(4343.44, "Dacia", "verde", "54546DDEFGEE43", 4, aux, 12445);
	cout << "Afisare v3:\n";
	v3.afisare();

	//constr copiere
	Vehicul v4(v3);
	cout << "Afisare v4:\n";
	v4.afisare();

	Vehicul v5 = v4;
	cout << "Afisare v5:\n";
	v5.afisare();

	//testare setteri si getteri
	cout << "==setter si getteri==\n\n";
	v3.setMarca("BMW");
	v3.setCuloare("rosie");
	v3.setNrKm(255000.96);
	v3.setPSerieSasiu("CU4MV4MVJ54MV434");
	v3.setNrViteze(100);//va fi suprascris de catre setVitezeMedii ca altfel oricum nu are sens

	int aux2[6] = { 95,55,66,99,120,180 };
	v3.setPVitezeMedii(6, aux2);

	cout << "ID = " << v3.getID() << "; marca = " << v3.getMarca() << "; culoare = "
		<< v3.getCuloare() << "; nrKm = " << v3.getNrKm() << "; serie sasiu = " << v3.getPSerieSasiu() << endl;

	if (v3.getNrViteze() > 0) {
		cout << "Viteze medii:\n";
		for (int i = 0;i < v3.getNrViteze();i++) {
			cout << v3.getPVitezeMedii()[i] << " ";
		}
		cout << endl << endl;
	}
	else {
		cout << endl;
	}

	//exemplu pointeri
	int x = 33;
	int* px = &x;

	cout << "x = " << x << endl; //va afisa valoarea variabilei x
	cout << "&x = " << &x << endl; //va afisa adresa variabilei x
	cout << "px = " << px << endl; //va afisa valoarea din pointerul px
	cout << "*px = " << *px << endl; //*px = indirectare -> va afisa variabla catre care pointeaza pointerul px
	cout << "&px = " << &px << endl; //va afisa adresa pointerului px

	//const
	const int ww = 77;
	const int* pointer1 = &ww;//pointer ce pointeaza catre o zona de memorie CONSTANTA
	//*pointer1 = 44; -> nu merge

	int* const pointer2 = &x;//pointer CONSTANT ce pointeaza catre o zona de memorie oarecare
	//pointer2 = pointer1; -> nu merge

	const int* const pointer3 = &ww; //pointer CONSTANT ce pointeaza catre o zona de memorie CONSTANTA


	//var statica
	cout << "\n\nstatic: \nobiecte vehicul create pana in acest moment = "
		<< v3.getNumarObVehicul() << " " << v2.getNumarObVehicul() << endl;

	return 0;
}