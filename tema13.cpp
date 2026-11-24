#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class ExceptieCustom : public exception
{
private:
	string mesaj;
public:
	ExceptieCustom(const char* mesaj) : mesaj(mesaj) {}

	const char* what() const noexcept override
	{
		return this->mesaj.c_str();
	}
};

class Produs
{
private:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() : id(0), denumire("Laptop"), pret(5000)
	{

	}

	Produs(int idP, string denumireP, float pretP) : id(idP), denumire(denumireP), pret(pretP)
	{
		if (pret < PRET_MINIM)
		{
			throw ExceptieCustom("Pretul este prea mic!");
		}
	}

	virtual ~Produs()
	{

	}

	virtual void afisare()
	{
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;
	}

	virtual float getProcentScumpire() = 0;
};

const float Produs::PRET_MINIM = 1;

class ProdusRedus : public Produs
{
private:
	float procentReducere;

public:
	ProdusRedus() : Produs(), procentReducere(10)
	{
	}

	ProdusRedus(int id, string denumire, float pret, float procentReducere) : Produs(id, denumire, pret), procentReducere(procentReducere)
	{
	}

	void afisare() override
	{
		cout << endl;
		this->Produs::afisare();
		cout << endl << "Procent reducere: " << this->procentReducere;
	}

	float getProcentReducere()
	{
		return this->procentReducere;
	}

	float getProcentScumpire() override
	{
		return 0;
	}
};

class ProdusScumpit : public Produs
{
private:
	float procentScumpire;
public:

	ProdusScumpit() : Produs()
	{
		this->procentScumpire = 0;
	}

	ProdusScumpit(int id, string denumire, float pret, float procentScumpire) : Produs(id, denumire, pret)
	{
		this->procentScumpire = procentScumpire;
	}

	void afisare() override
	{
		cout << endl;
		this->Produs::afisare();
		cout << endl << "Procent Scumpire: " << this->procentScumpire;
	}

	float getProcentScumpire() override
	{
		return this->procentScumpire;
	}
};

class PlataProdusInterface
{
public:
	virtual ~PlataProdusInterface() {}
	virtual string Platit(float sumaCheltuita) = 0;
};

class PlataProdus : public PlataProdusInterface
{
public:
	string Platit(float sumaCheltuita) override
	{
		if (sumaCheltuita == 0)
			return "Din pacate nu s-a efectuat plata";

		if (sumaCheltuita > 0)
			return "Plata a fost efectuata cu succes";

		throw ExceptieCustom("Eroare! Introdu te rog un numar pozitiv");
	}
};

int main()
{
	ProdusScumpit iPhone(4, "Iphone 17", 5700, 15);
	iPhone.afisare();
	Produs* vectorProduse[2];
	vectorProduse[0] = new ProdusScumpit(1, "Motorina", 9, 5);
	vectorProduse[1] = new ProdusScumpit(2, "Benzina", 8.5f, 4);

	for (int i = 0; i < 2; i++)
	{
		vectorProduse[i]->afisare();
		delete vectorProduse[i];
	}

	PlataProdusInterface* operation2 = new PlataProdus();
	try
	{
		cout << endl << operation2->Platit(0);
	}
	catch (ExceptieCustom& e)
	{
		cout << endl << e.what();
	}
	delete operation2;

	return 0;
}