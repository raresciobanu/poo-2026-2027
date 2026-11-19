#include<iostream>

using namespace std;

class Hotel {
	int nrCamere;
	double* pTarifeCamere;
	char* pDenumire;
	double datorii;

public:

	// Constructor fara parametri
	Hotel() {
		this->nrCamere = 0;
		this->pTarifeCamere = nullptr;

		this->pDenumire = new char[strlen("unknown") + 1];
		strcpy(this->pDenumire, "unknown");

		this->datorii = 0.0;
	}

	// Constructor cu toti parametrii
	Hotel(int nrCamere, double* pTarifeCamere,
		const char* pDenumire, double datorii) {

		this->nrCamere = nrCamere;

		this->pTarifeCamere = new double[nrCamere];
		for (int i = 0; i < nrCamere; i++) {
			this->pTarifeCamere[i] = pTarifeCamere[i];
		}

		this->pDenumire = new char[strlen(pDenumire) + 1];
		strcpy(this->pDenumire, pDenumire);

		this->datorii = datorii;
	}

	// Constructor de copiere
	Hotel(const Hotel& h) {
		this->nrCamere = h.nrCamere;

		this->pTarifeCamere = new double[h.nrCamere];
		for (int i = 0; i < h.nrCamere; i++) {
			this->pTarifeCamere[i] = h.pTarifeCamere[i];
		}

		this->pDenumire = new char[strlen(h.pDenumire) + 1];
		strcpy(this->pDenumire, h.pDenumire);

		this->datorii = h.datorii;
	}

	// Destructor
	~Hotel() {
		delete[] this->pTarifeCamere;
		delete[] this->pDenumire;
	}

	// OPERATORI

	// operator =
	Hotel& operator=(const Hotel& h) {
		if (this != &h) {
			this->nrCamere = h.nrCamere;

			delete[] this->pTarifeCamere;
			this->pTarifeCamere = new double[h.nrCamere];

			for (int i = 0; i < h.nrCamere; i++) {
				this->pTarifeCamere[i] = h.pTarifeCamere[i];
			}

			delete[] this->pDenumire;
			this->pDenumire = new char[strlen(h.pDenumire) + 1];
			strcpy(this->pDenumire, h.pDenumire);

			this->datorii = h.datorii;
		}

		return *this;
	}

	// operator <<
	friend ostream& operator<<(ostream& out, const Hotel& h) {
		out << "Denumire = " << h.pDenumire
			<< "; datorii = " << h.datorii
			<< "; Nr. Camere = " << h.nrCamere;

		if (h.nrCamere > 0) {
			out << "; Tarife camere: " << endl;
		}

		for (int i = 0; i < h.nrCamere; i++) {
			out << "pTarifeCamere[" << i << "] = "
				<< h.pTarifeCamere[i] << " lei; ";
		}

		out << endl;
		return out;
	}

	// operator >>
	friend istream& operator>>(istream& in, Hotel& h) {
		char aux[100];

		cout << "Denumire = ";
		in.ignore();
		in.getline(aux, 100);

		delete[] h.pDenumire;
		h.pDenumire = new char[strlen(aux) + 1];
		strcpy(h.pDenumire, aux);

		cout << "Datorii = ";
		in >> h.datorii;

		cout << "Nr. Camere = ";
		in >> h.nrCamere;

		delete[] h.pTarifeCamere;
		h.pTarifeCamere = new double[h.nrCamere];

		for (int i = 0; i < h.nrCamere; i++) {
			cout << "Tarif camera [" << i << "] = ";
			in >> h.pTarifeCamere[i];
		}

		return in;
	}

	// OPERATORI UNARI

	// ++ preincrementare
	Hotel& operator++() {
		datorii += 100;
		return *this;
	}

	// ++ postincrementare
	Hotel operator++(int) {
		Hotel aux(*this);
		datorii += 50;
		return aux;
	}

	// OPERATOR +

	// Hotel + double
	double operator+(double datorieNoua) {
		return this->datorii + datorieNoua;
	}

	// Hotel + Hotel
	double operator+(Hotel h) {
		return this->datorii + h.datorii;
	}

	// double + Hotel
	friend double operator+(double datorieNoua, Hotel h) {
		return datorieNoua + h.datorii;
	}

	// OPERATOR []
	double operator[](int index) {
		if (index < 0 || index >= nrCamere) {
			cout << "Index invalid!\n";
			return -1;
		}

		return pTarifeCamere[index];
	}

	//op !
	// returneaza TRUE daca conditia pe care o evaluezi e falsa
	bool operator!() {
		return nrCamere == 0;
	}

	//op cast implicit + explicit - nu merge acum pt ca intra in conflict cu op + => double operator+(Hotel m)
	
	//se testeaza:
	// double x = h4; //cast implicit
	// aceasta implementare merge si pe explicit si implicit
	//operator double() {
	//	return datorii;
	//}

	//op cast explicit
	explicit operator double() {
		return datorii;
	}

	//op ==
	//exemplu simplu
	bool operator==(double datorii) {
		return this->datorii == datorii;
	}

	//exemplu mai complex
	//deep check
	bool operator==(Hotel h) {
		bool esteEgal = this->datorii == h.datorii && this->nrCamere == h.nrCamere;

		if (!esteEgal) return false;

		if (strcmp(this->pDenumire, h.pDenumire) != 0) return false;

		for (int i = 0;i < nrCamere;i++) {
			if (this->pTarifeCamere[i] != h.pTarifeCamere[i]) return false;
		}

		return true;
	}


	//op -=

	//op +=
	//caz mai simplu
	//returnam o referinta la obiect pentru a rezolva si cazul: ((h4 += 100) += 200) += 300;
	//merge si cu void daca vreti sa nu acoperiti cazul de mai sus adica doar: h4+=100;
	Hotel& operator+=(float crestereDatorie) { //am pus float ca sa pot supraincarca de 2 ori op +=
		this->datorii += crestereDatorie;
		return *this;
	}


	//caz complex
	Hotel& operator+=(double tarifCamera) {
		double* temp = new double[nrCamere + 1];

		for (int i = 0;i < nrCamere;i++) {
			temp[i] = pTarifeCamere[i];
		}

		temp[nrCamere] = tarifCamera;

		delete[] pTarifeCamere;

		pTarifeCamere = temp;
		nrCamere++;

		return *this;
	}


	Hotel& operator-=(double tarifDeEliminat) {
		int countDetectii = 0;
		for (int i = 0;i < nrCamere;i++) {
			if (pTarifeCamere[i] == tarifDeEliminat) countDetectii++;
		}

		double* pAux = new double[nrCamere - countDetectii];

		int k = 0;
		for (int i = 0;i < nrCamere;i++) {
			if (pTarifeCamere[i] != tarifDeEliminat) pAux[k++] = pTarifeCamere[i];
		}

		delete[] pTarifeCamere;

		pTarifeCamere = pAux;
		nrCamere -= countDetectii;

		return *this;
	}

	//op functie/op ()
	Hotel& operator()(int pozitieEliminat) {
		if (pozitieEliminat < 0 || pozitieEliminat >= nrCamere) {
			cout << "pozitieEliminat este < 0 sau >= nrCamere\n";
			return *this;
		}

		double* pAux = new double[nrCamere - 1];

		int k = 0;
		for (int i = 0;i < nrCamere;i++) {
			if (i != pozitieEliminat) pAux[k++] = pTarifeCamere[i];
		}

		delete[] pTarifeCamere;

		pTarifeCamere = pAux;
		nrCamere--;


		return *this;
	}

	Hotel& operator()(int pozitie, double tarifDeAdaugat) {
		if (pozitie < 0 || pozitie >= nrCamere) {
			cout << "pozitie este < 0 sau >= nrCamere\n";
			return *this;
		}

		double* pAux = new double[nrCamere + 1];

		int k = 0;
		for (int i = 0;i < nrCamere;i++) {
			if (i == pozitie) {
				pAux[k++] = tarifDeAdaugat;
			}
			pAux[k++] = pTarifeCamere[i];
		}

		delete[] pTarifeCamere;

		pTarifeCamere = pAux;
		nrCamere++;


		return *this;
	}
};

int main() {

	Hotel h1;

	Hotel h2(3,
		new double[3] { 250, 350, 500 },
		"Hotel International", 2200.50);

	cout << h1 << endl;
	cout << h2 << endl;

	// OPERATOR ++
	cout << "OPERATOR ++\n";

	cout << ++h2 << endl;
	cout << h2++ << endl;
	cout << h2 << endl;

	// OPERATOR +
	cout << "OPERATOR +\n";

	double calcul = h2 + 1000.2;
	cout << "Calcul = " << calcul << endl;

	Hotel h3(2,
		new double[2] { 400, 600 },
		"Hotel Central", 1500);

	cout << "Datorii doua hoteluri = "<< h2 + h3 << endl;
	h2.operator+(h3);

	double calcul2 = 3000.2 + h3;
	cout << "Calcul2 = " << calcul2 << endl;

	// OPERATOR []
	cout << "\nOPERATOR []\n";

	cout << "Tariful primei camere = "
		<< h3[0] << " lei\n";

	cout << "Tariful celei de-a doua camere = "
		<< h3[1] << " lei\n\n\n";

	// OPERATOR !/negatie
	if (!h3) {
		cout << "Hotelul NU are camere disponibile\n";
	}
	else {
		cout << "Hotelul are camere disponibile\n";
	}

	//OPERATOR ==
	if (h3 == 1500.3) {
		cout << "Da! Hotelul are datorii de 1500lei\n";
	}
	else {
		cout << "Nu! Hotelul are alte datorii\n";
	}

	Hotel h4 = h3;
	if (h4 == h3) {
		cout << "Hotel h4==h3\n";
	}
	else {
		cout << "Hotel h4!=h3\n";
	}

	// OPERATOR +=
	cout << "operator += :\n" << (((h4 += 200.2) += 200.2) += 300.6) << endl;

	cout << "operator += tarif camera nou: \n" << (h4 += 66.88) << endl;

	cout << "operator -= tarif camera de eliminat: \n" << (h4 -= 200.2) << endl;


	// OPERATOR ()

	cout << "operator () : \n" << h4(1) << endl;
	cout << "operator () adauga la pozitie data : \n" << h4(1, 979) << endl;

	//op cast explicit
	cout << "cast explicit => datorii h4: " << (double)h4 << endl;

	// OPERATOR >> si <<
	cout << "\nOPERATOR >>\n";

	Hotel h9;
	cin >> h9;

	cout << h9 << endl;

	// OPERATOR =
	Hotel h11;
	h11 = h3;

	cout << "Hotel copiat prin operatorul =\n";
	cout << h11;

}