#include<iostream>
#include<string>

using namespace std;

enum Categorie { ELECTRIC = 10, HIBRID = 6, COMBUSTIBIL = 4 };

class Autoturism {
private:
	const int id;
	float pret;
	string marca;
	Categorie categorie;
	int nrRevizii;
	float* costuriRevizii;
	static int nrAutoturisme;

public:
	Autoturism() : id(++nrAutoturisme) {
		this->marca = "BMW";
		this->pret = 0;
		this->nrRevizii = 0;
		this->costuriRevizii = nullptr;
		this->categorie = COMBUSTIBIL;
	}

	Autoturism(string marca, float pret, int nrRevizii, float* costuri, Categorie categorie) : id(++nrAutoturisme) {
		this->marca = marca;
		this->pret = pret;
		this->nrRevizii = nrRevizii;
		this->costuriRevizii = new float[this->nrRevizii];
		for (int i = 0; i < this->nrRevizii; i++) {
			this->costuriRevizii[i] = costuri[i];
		}
		this->categorie = categorie;

		delete[] costuri;
	}

	Autoturism(const Autoturism& copie) : id(++nrAutoturisme) {
		this->pret = copie.pret;
		this->marca = copie.marca;
		this->categorie = copie.categorie;
		this->nrRevizii = copie.nrRevizii;

		if (copie.costuriRevizii != nullptr) {
			this->costuriRevizii = new float[copie.nrRevizii];
			for (int i = 0; i < copie.nrRevizii; i++) {
				this->costuriRevizii[i] = copie.costuriRevizii[i];
			}
		}
		else {
			this->costuriRevizii = nullptr;
		}
	}

	void operator=(const Autoturism& copie) {
		this->marca = copie.marca;
		this->pret = copie.pret;
		this->categorie = copie.categorie;
		this->nrRevizii = copie.nrRevizii;

		if (this->costuriRevizii != nullptr) {
			delete[] this->costuriRevizii;
			this->costuriRevizii = nullptr;
		}

		if (copie.costuriRevizii != nullptr) {
			this->costuriRevizii = new float[copie.nrRevizii];
			for (int i = 0; i < copie.nrRevizii; i++) {
				this->costuriRevizii[i] = copie.costuriRevizii[i];
			}
		}
		else {
			this->costuriRevizii = nullptr;
		}
	}

	void afisareAutoturism() {
		cout << endl << this->id << ". Autoturismul " << this->marca << " costa " << this->pret << " euro, este de categorie ";
		if (this->categorie == COMBUSTIBIL) cout << "COMBUSTIBIL";
		if (this->categorie == ELECTRIC) cout << "ELECTRIC";
		if (this->categorie == HIBRID) cout << "HIBRID";
		cout << " si are " << this->nrRevizii << " revizii cu costurile: ";
		if (this->costuriRevizii != nullptr && this->nrRevizii > 0) {
			for (int i = 0; i < this->nrRevizii - 1; i++) {
				cout << this->costuriRevizii[i] << " euro, ";
			}
			cout << this->costuriRevizii[this->nrRevizii - 1] << " euro.";
		}
	}

	~Autoturism() {
		if (this->costuriRevizii != nullptr) {
			delete[] this->costuriRevizii;
		}
	}

	void operator+=(float valoareDeAdaugat) {
		this->pret += valoareDeAdaugat;
	}

	bool operator>(const Autoturism& a) {
		return this->pret > a.pret;
	}

	bool operator>=(int x) const {
		if (this->nrRevizii >= x)
			return true;
		return false;
	}

	bool operator<=(int x) const {
		if (this->pret <= x)
			return true;
		return false;
	}

	bool operator!() {
		return this->pret > 0;
	}

	float operator()(int nrElemente) {
		float s = 0, ma = 0;
		for (int i = 0; i < this->nrRevizii; i++)
			s += this->costuriRevizii[i];
		if (this->nrRevizii != 0)
			ma = s / this->nrRevizii;

		return ma;
	}

	float& operator[](int index) {
		if (index >= 0 && index < this->nrRevizii) {
			return this->costuriRevizii[index];
		}
		else
			throw exception();
	}

	friend void operator<<(ostream& out, Autoturism autoObj) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << autoObj.id;
		out << endl << "Marca: " << autoObj.marca;
		out << endl << "Pret: " << autoObj.pret;
		out << endl << "Categorie: ";
		if (autoObj.categorie == COMBUSTIBIL) out << "COMBUSTIBIL";
		if (autoObj.categorie == ELECTRIC) out << "ELECTRIC";
		if (autoObj.categorie == HIBRID) out << "HIBRID";
		out << endl << "Nr revizii: " << autoObj.nrRevizii;

		if (autoObj.costuriRevizii != nullptr && autoObj.nrRevizii > 0) {
			out << endl << "Costuri revizii: ";
			for (int i = 0; i < autoObj.nrRevizii - 1; i++) {
				out << autoObj.costuriRevizii[i] << " euro, ";
			}
			out << autoObj.costuriRevizii[autoObj.nrRevizii - 1] << " euro.";
		}
	}

	friend void operator>>(istream& in, Autoturism& autoObj) {
		cout << endl << "Pret: ";
		in >> autoObj.pret;

		cout << endl << "Marca: ";
		in >> autoObj.marca;

		cout << endl << "Categorie (4-COMBUSTIBIL, 6-HIBRID, 10-ELECTRIC): ";
		int cat;
		in >> cat;
		if (cat == 4) autoObj.categorie = COMBUSTIBIL;
		if (cat == 10) autoObj.categorie = ELECTRIC;
		if (cat == 6) autoObj.categorie = HIBRID;

		cout << endl << "Nr revizii: ";
		in >> autoObj.nrRevizii;

		cout << endl << "Costuri revizii: ";
		if (autoObj.costuriRevizii != nullptr) {
			delete[] autoObj.costuriRevizii;
			autoObj.costuriRevizii = nullptr;
		}

		autoObj.costuriRevizii = new float[autoObj.nrRevizii];
		for (int i = 0; i < autoObj.nrRevizii; i++) {
			cout << endl << "Costul[" << i << "]: ";
			in >> autoObj.costuriRevizii[i];
		}
	}

	Autoturism operator++(int) {
		Autoturism copie = *this;
		this->pret++;

		return copie;
	}

	Autoturism operator++() {
		this->pret++;
		return *this;
	}

	explicit operator int() {
		return this->nrRevizii;
	}

	explicit operator string() {
		return this->marca;
	}
};

int Autoturism::nrAutoturisme = 0;

int main() {
	Autoturism dacia;
	dacia.afisareAutoturism();

	float* costuri = new float[3] { 150.5, 220.0, 310.8 };
	Autoturism* tesla = new Autoturism("Tesla", 35000, 3, costuri, ELECTRIC);
	tesla->afisareAutoturism();

	if (!dacia) {
		cout << endl << "Pretul este mai mare decat 0!";
	}
	else {
		cout << endl << "Pretul este mai mic sau egal cu 0!";
	}

	cout << endl << endl;
	if ((*tesla) >= 3) {
		cout << "Autoturismul are minim 3 revizii";
	}
	else {
		cout << "Autoturismul are sub 3 revizii";
	}

	cout << endl << endl << "Media costurilor de revizie este de " << (*tesla)(3);
	cout << endl << endl;

	if (dacia <= 10000) {
		cout << "Acest autoturism costa pana in 10000 de euro";
	}
	else {
		cout << "Acest autoturism este mai scump de 10000 de euro!";
	}

	for (int i = 0; i < 3; i++) {
		cout << endl << "Costurile dublate sunt: " << (*tesla)[i] * 2 << " ";
	}

	Autoturism a1 = dacia++;
	Autoturism a2 = ++dacia;

	cout << a1;
	cout << a2;

	cout << endl << (int)a2;
	cout << endl << (int)(dacia);
	cout << endl << endl << string(dacia);

	delete tesla;

	return 0;
}