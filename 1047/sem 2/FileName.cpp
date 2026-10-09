#include<iostream>

using namespace std;

class Vehicul {
	//totul este privat in aceasta clasa by default
	double nrKm;
	string marca;
	string culoare;
	char* serieSasiu;
	int* vitezeMedii;
	int nrViteze;

public:

	//constructor default/fara parametri
	Vehicul()
	{
		//nu esti obligat sa pui this->
		//el se pune daca EXISTA conflicte cu alte variabile care au acelasi nume
		nrKm = 0.0;
		marca = "marca necunoscuta";
		culoare = "culoare necunoscuta";

		serieSasiu = new char[strlen("serie sasiu necunoscuta") + 1];//+1 pt ca avem \0
		strcpy(serieSasiu, "serie sasiu necunoscuta");

		nrViteze = 0;
		vitezeMedii = nullptr;
	}

	//constructor cu 2 parametri
	Vehicul(double nrKm, string marca) {
		this->nrKm = nrKm;
		this->marca = marca;
		this->culoare = "culoare necunoscuta";

		serieSasiu = new char[strlen("serie sasiu necunoscuta") + 1];//+1 pt ca avem \0
		strcpy(serieSasiu, "serie sasiu necunoscuta");

		nrViteze = 0;
		vitezeMedii = nullptr;
	}


	//constructor cu toti parametrii
	Vehicul(double nrKm, string marca, string culoare,
		const char* serieSasiu, int nrViteze, int* vitezeMedii) {
		this->nrKm = nrKm;
		this->marca = marca;
		this->culoare = culoare;

		this->serieSasiu = new char[strlen(serieSasiu) + 1];//+1 pt ca avem \0
		strcpy(this->serieSasiu, serieSasiu);

		this->nrViteze = nrViteze;
		this->vitezeMedii = new int[nrViteze];
		for (int i = 0;i < nrViteze;i++) {
			this->vitezeMedii[i] = vitezeMedii[i];
		}
	}

	Vehicul(const Vehicul& v) {
		this->nrKm = v.nrKm;
		this->marca = v.marca;
		this->culoare = v.culoare;

		this->serieSasiu = new char[strlen(v.serieSasiu) + 1];//+1 pt ca avem \0
		strcpy(this->serieSasiu, v.serieSasiu);

		this->nrViteze = v.nrViteze;
		this->vitezeMedii = new int[v.nrViteze];
		for (int i = 0;i < v.nrViteze;i++) {
			this->vitezeMedii[i] = v.vitezeMedii[i];
		}
	}

	//destructor
	~Vehicul() {
		cout << "S-a distrus un vehicul cu marca: " << marca << " si culoare: " << culoare << endl;


		if (this->serieSasiu != nullptr) {
			delete[] this->serieSasiu;
		}

		if (this->vitezeMedii != nullptr) {
			delete[] this->vitezeMedii;
		}
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

	char* getSerieSasiu() {
		return serieSasiu;
	}

	void setSerieSasiu(char* serieSasiu) {
		if (this->serieSasiu != nullptr) {
			delete[] this->serieSasiu; //evitare memory leaks
		}

		this->serieSasiu = new char[strlen(serieSasiu) + 1];//+1 pt ca avem \0
		strcpy(this->serieSasiu, serieSasiu);
	}

	int getNrViteze() {
		return nrViteze;
	}

	void setNrViteze(int nrViteze) {
		this->nrViteze = nrViteze;
	}

	int* getVitezeMedii() {
		return this->vitezeMedii;
	}

	void setVitezeMedii(int nrViteze, int* vitezeMedii) {
		if (this->vitezeMedii != nullptr) {
			delete[] this->vitezeMedii; //evitare memory leaks
		}

		this->nrViteze = nrViteze;
		this->vitezeMedii = new int[nrViteze];
		for (int i = 0;i < nrViteze;i++) {
			this->vitezeMedii[i] = vitezeMedii[i];
		}
	}

	void afisare() {
		cout << "marca = " << marca << "; culoare = "
			<< culoare << "; nrKm = " << nrKm << "; serie sasiu = " << serieSasiu << endl;

		if (nrViteze > 0) {
			cout << "Viteze medii:\n";
			for (int i = 0;i < nrViteze;i++) {
				cout << vitezeMedii[i] << " ";
			}
			cout << endl << endl;
		}
		else {
			cout << endl;
		}
	}
};


int main() {
	cout << "Hello!\n";

	Vehicul v1;
	cout << "v1 marca = " << v1.getMarca() << endl;
	v1.setMarca("Audi");
	cout << "v1 marca = " << v1.getMarca() << endl << endl;

	cout << "Afisare v1:\n";
	v1.afisare();

	Vehicul v2(343.44, "BMW");
	cout << "Afisare v2:\n";
	v2.afisare();

	int aux[4] = { 55,60,80,90 };
	Vehicul v3(4343.44, "Dacia", "verde", "54546DDEFGEE43", 4, aux);
	cout << "Afisare v3:\n";
	v3.afisare();


	//exemplu pointeri
	int x = 33;
	int* px = &x;

	cout << "x = " << x << endl; //va afisa valoarea variabilei x
	cout << "&x = " << &x << endl; //va afisa adresa variabilei x
	cout << "px = " << px << endl; //va afisa valoarea din pointerul px
	cout << "*px = " << *px << endl; //*px = indirectare -> va afisa variabla catre care pointeaza pointerul px
	cout << "&px = " << &px << endl; //va afisa adresa pointerului px

	return 0;
}