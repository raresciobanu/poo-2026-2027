#include<iostream>

using namespace std;

class Vehicul {
	//totul este privat in aceasta clasa by default
	double nrKm;
	double pretCarburant;
	double consumMediu;
	string marca;
	string culoare;

public:

	//constructor default/fara parametri
	Vehicul()
	{
		//nu esti obligat sa pui this->
		//el se pune daca EXISTA conflicte cu alte variabile care au acelasi nume
		nrKm = 0.0;
		marca = "marca necunoscuta";
		culoare = "culoare necunoscuta";
	}

	//constructor cu 2 parametri
	Vehicul(double nrKm, string marca) {
		this->nrKm = nrKm;
		this->marca = marca;
		this->culoare = "culoare necunoscuta";
	}

	//constructor cu toti parametrii
	Vehicul(double nrKm, string marca, string culoare) {
		this->nrKm = nrKm;
		this->marca = marca;
		this->culoare = culoare;
	}

	//destructor
	~Vehicul() {
		cout << "S-a distrus un vehicul cu marca: " << marca << " si culoare: " << culoare << endl;
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

	void afisare() {
		cout << "marca = " << marca << "; culoare = "
			<< culoare << "; nrKm = " << nrKm << endl << endl;
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

	Vehicul v3(4343.44, "Dacia", "verde");
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