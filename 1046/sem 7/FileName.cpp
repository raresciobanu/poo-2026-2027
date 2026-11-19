#include<iostream>

using namespace std;

class Magazin {
	int nrAlimente;
	string* pAlimente;
	char* pDenumire;
	double datorii;

public:

	Magazin() {
		this->nrAlimente = 0;
		this->pAlimente = nullptr;
		this->pDenumire = new char[strlen("unknown") + 1];
		strcpy(this->pDenumire, "unknown");
		this->datorii = 0.0;
	}


	Magazin(int nrAlimente, string* pAlimente, const char* pDenumire, double datorii) {
		this->nrAlimente = nrAlimente;

		this->pAlimente = new string[nrAlimente];
		for (int i = 0;i < nrAlimente;i++) {
			this->pAlimente[i] = pAlimente[i];
		}

		this->pDenumire = new char[strlen(pDenumire) + 1];
		strcpy(this->pDenumire, pDenumire);

		this->datorii = datorii;
	}

	Magazin(const Magazin& m) {
		this->nrAlimente = m.nrAlimente;

		this->pAlimente = new string[m.nrAlimente];
		for (int i = 0;i < m.nrAlimente;i++) {
			this->pAlimente[i] = m.pAlimente[i];
		}

		this->pDenumire = new char[strlen(m.pDenumire) + 1];
		strcpy(this->pDenumire, m.pDenumire);

		this->datorii = m.datorii;
	}

	~Magazin() {
		if (this->pAlimente != nullptr) {
			delete[] this->pAlimente;
		}

		if (this->pDenumire != nullptr) {
			delete[] this->pDenumire;
		}
	}

	//OPERATORI

	//op =
	Magazin& operator=(const Magazin& m) {
		if (this != &m) {
			this->nrAlimente = m.nrAlimente;

			delete[] this->pAlimente;
			this->pAlimente = new string[m.nrAlimente];
			for (int i = 0;i < m.nrAlimente;i++) {
				this->pAlimente[i] = m.pAlimente[i];
			}

			delete[] this->pDenumire;
			this->pDenumire = new char[strlen(m.pDenumire) + 1];
			strcpy(this->pDenumire, m.pDenumire);

			this->datorii = m.datorii;
		}

		return *this;
	}

	//op <<
	friend ostream& operator<<(ostream& out, const Magazin& m) {
		out << "Denumire = " << m.pDenumire << "; datorii = " << m.datorii
			<< "; Nr. Alimente = " << m.nrAlimente;

		if (m.nrAlimente > 0) {
			out << "; Alimente: " << endl;
		}

		for (int i = 0;i < m.nrAlimente;i++) {
			out << "pAlimente[" << i << "] = " << m.pAlimente[i] << "; ";
		}
		out << endl;

		return out;
	}

	friend istream& operator>>(istream& in, Magazin& m) {
		char aux[100];
		cout << "Denumire = "; in.getline(aux, 100);

		delete[] m.pDenumire;
		m.pDenumire = new char[strlen(aux) + 1];
		strcpy(m.pDenumire, aux);

		cout << "Datorii = "; in >> m.datorii;

		cout << "Nr. Alimente = "; in >> m.nrAlimente;

		in.ignore(); //puneti asta cand ramane in buffer un \n de la linia de mai sus

		delete[] m.pAlimente;
		m.pAlimente = new string[m.nrAlimente];
		for (int i = 0;i < m.nrAlimente;i++) {
			cout << "pAlimente[" << i << "] = ";

			in.getline(aux, 100);

			m.pAlimente[i] = aux;
		}

		return in;
	}

	//op unari
	//op ++ preincrementare
	Magazin& operator++() { //va incrementa datoriile cu 100lei
		datorii += 100;

		return *this;
	}

	//op ++ postincrementare
	Magazin operator++(int) { //va incrementa datoriile cu 50lei
		Magazin aux(*this);
		datorii += 50;

		return aux;
	}

	//op +
	double operator+(double datorieNoua) {
		return this->datorii + datorieNoua;
	}

	double operator+(Magazin m) {
		return this->datorii + m.datorii;
	}

	friend double operator+(double datorieNoua, Magazin m) {
		return datorieNoua + m.datorii;
	}

	//op []
	string operator[](int index) {
		if (index<0 || index >= nrAlimente) {
			cout << "indexul dat este < 0 sau > nrAlimnete\n";
			return "nimic";
		}

		return pAlimente[index];
	}
};

int main() {
	Magazin m1;
	Magazin m2(2, new string[2]{ "apa", "pepsi" }, "Magazin ASE", 2222.55);

	cout << m1 << endl << endl << m2 << endl;


	//op ++
	cout << "op ++\n";
	cout << ++m2 << endl;
	cout << m2++ << endl;
	cout << m2 << endl;

	//op +
	double calcul = m2 + 1000;
	cout << "calcul = " << calcul << endl;

	Magazin m3(3, new string[3]{ "bere", "paine", "ciocolata" }, "Magazin LUCA", 1500);
	cout << "datoriile pe 2 magazine = " << m2 + m3 << endl;

	double calcul2 = 3000 + m3;
	cout << "calcul2 = " << calcul2 << endl << endl;

	//op []

	cout << "op[]: " << m3[1] << endl << endl;

	//op >> si <<

	cout << "op >>\n";
	Magazin m4;
	cin >> m4;
	cout << m4 << endl;


}