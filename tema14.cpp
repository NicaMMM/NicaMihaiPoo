#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class ExceptieMetrou : public exception
{
private:
	string mesaj;
public:
	ExceptieMetrou(const char* mesajeroare) : mesaj(mesajeroare)
	{
	}

	const char* what() const noexcept override
	{
		return this->mesaj.c_str();
	}
};

enum Magistrala { M1 = 1, M2 = 2, M3 = 3, M4 = 4, M5 = 5 };

class MetrouBucuresti
{
	const int id;
	string statie;
	float distantaParcursa;
	Magistrala magistrala;
	char* destinatie;

public:
	static const float DISTANTA_MINIMA;
	MetrouBucuresti() : id(0)
	{
		this->statie = "X";
		this->distantaParcursa = 0;
		this->magistrala = M1;
		this->destinatie = nullptr;
	}

	MetrouBucuresti(int idM, string statie, float distantaParcursa, Magistrala magistrala, const char* destinatie) : id(idM)
	{
		if (distantaParcursa < DISTANTA_MINIMA)
			throw ExceptieMetrou("Eroare! Trenul nu poate parcurge o distanta negativa");

		this->statie = statie;
		this->distantaParcursa = distantaParcursa;
		this->magistrala = magistrala;
		if (destinatie != nullptr)
		{
			this->destinatie = new char[strlen(destinatie) + 1];
			strcpy(this->destinatie, destinatie);
		}
		else
		{
			this->destinatie = nullptr;
		}
	}

	MetrouBucuresti(const MetrouBucuresti& m) : id(m.id)
	{
		this->statie = m.statie;
		this->distantaParcursa = m.distantaParcursa;
		this->magistrala = m.magistrala;
		if (m.destinatie != nullptr)
		{
			this->destinatie = new char[strlen(m.destinatie) + 1];
			strcpy(this->destinatie, m.destinatie);
		}
		else
		{
			this->destinatie = nullptr;
		}
	}

	virtual void afisare()
	{
		cout << endl << endl;
		cout << this->id << ". In acest moment trenul circula pe M" << this->magistrala << ", se afla la statia " << this->statie;
		cout << ", a parcurs o distanta de " << this->distantaParcursa << " km si circula in directia: ";
		if (this->destinatie != nullptr)
			cout << this->destinatie;
	}

	MetrouBucuresti& operator=(const MetrouBucuresti& m)
	{
		if (this != &m)
		{
			if (this->destinatie != nullptr)
			{
				delete[] this->destinatie;
				this->destinatie = nullptr;
			}
			this->statie = m.statie;
			this->distantaParcursa = m.distantaParcursa;
			this->magistrala = m.magistrala;
			if (m.destinatie != nullptr)
			{
				this->destinatie = new char[strlen(m.destinatie) + 1];
				strcpy(this->destinatie, m.destinatie);
			}
		}
		return *this;
	}

	bool operator>(const MetrouBucuresti& m)
	{
		return this->distantaParcursa > m.distantaParcursa;
	}

	Magistrala operator()(string statie)
	{
		if (statie == "Piata Unirii" || statie == "Piata Victoriei")
			return M1;
		return M5;
	}

	char operator[](int index)
	{
		if (this->destinatie != nullptr && index >= 0 && index < (int)strlen(this->destinatie))
			return this->destinatie[index];
		else
			throw ExceptieMetrou("Te rog sa introduci un Index Valid!!");
	}

	virtual ~MetrouBucuresti()
	{
		if (this->destinatie != nullptr)
		{
			delete[] this->destinatie;
			this->destinatie = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const MetrouBucuresti& m);

	explicit operator char*()
	{
		return this->destinatie;
	}
};

ostream& operator<<(ostream& out, const MetrouBucuresti& m)
{
	out << endl << endl;
	out << m.id << ". In acest moment trenul circula pe M" << m.magistrala << ", se afla la statia " << m.statie;
	out << ", a parcurs o distanta de " << m.distantaParcursa << " km si circula in directia: ";
	if (m.destinatie != nullptr)
		out << m.destinatie;
	return out;
}

class MetrouScurtat : public MetrouBucuresti
{
private:
	char* destinatieNoua;
public:
	MetrouScurtat() : MetrouBucuresti()
	{
		this->destinatieNoua = nullptr;
	}

	MetrouScurtat(int idM, string statie, float distantaParcursa, Magistrala magistrala, const char* destinatie, const char* destinatieNoua)
		: MetrouBucuresti(idM, statie, distantaParcursa, magistrala, destinatie)
	{
		if (destinatieNoua != nullptr)
		{
			this->destinatieNoua = new char[strlen(destinatieNoua) + 1];
			strcpy(this->destinatieNoua, destinatieNoua);
		}
		else
		{
			this->destinatieNoua = nullptr;
		}
	}

	MetrouScurtat(const MetrouScurtat& ms) : MetrouBucuresti(ms)
	{
		if (ms.destinatieNoua != nullptr)
		{
			this->destinatieNoua = new char[strlen(ms.destinatieNoua) + 1];
			strcpy(this->destinatieNoua, ms.destinatieNoua);
		}
		else
		{
			this->destinatieNoua = nullptr;
		}
	}

	MetrouScurtat& operator=(const MetrouScurtat& ms)
	{
		if (this != &ms)
		{
			MetrouBucuresti::operator=(ms);
			if (this->destinatieNoua != nullptr)
			{
				delete[] this->destinatieNoua;
				this->destinatieNoua = nullptr;
			}
			if (ms.destinatieNoua != nullptr)
			{
				this->destinatieNoua = new char[strlen(ms.destinatieNoua) + 1];
				strcpy(this->destinatieNoua, ms.destinatieNoua);
			}
		}
		return *this;
	}

	void afisare() override
	{
		cout << endl;
		this->MetrouBucuresti::afisare();
		cout << endl << "Dupa un accident trenul va circula doar pana la statia: ";
		if (this->destinatieNoua != nullptr)
			cout << this->destinatieNoua;
	}

	~MetrouScurtat()
	{
		if (this->destinatieNoua != nullptr)
		{
			delete[] this->destinatieNoua;
			this->destinatieNoua = nullptr;
		}
	}
};

const float MetrouBucuresti::DISTANTA_MINIMA = 0;

class DistantaInterface
{
public:
	virtual ~DistantaInterface() {}
	virtual float DistantaTotala(float LungimeMagistrala, int nrCurse) = 0;
};

class DistantaParcursa : public DistantaInterface
{
public:
	float DistantaTotala(float LungimeMagistrala, int nrCurse) override
	{
		if (LungimeMagistrala > 0 && nrCurse > 0)
			return LungimeMagistrala * nrCurse;
		else
			throw ExceptieMetrou("Nu putem avea lungime sau numar de curse negative sau nule!!");
	}
};

int main()
{
	try
	{
		MetrouBucuresti MB1(1, "Piata Romana", -6.4f, M2, "Pipera");
	}
	catch (ExceptieMetrou& e)
	{
		cout << endl << e.what();
	}

	MetrouBucuresti MB1(1, "Piata Romana", 6.4f, M2, "Pipera");
	MB1.afisare();

	MetrouScurtat MB2(2, "Piata Romana", 6.4f, M2, "Pipera", "Piata Victoriei");
	MB2.afisare();

	DistantaInterface* distanta = new DistantaParcursa();

	try
	{
		cout << endl << "In total metroul a parcurs astazi " << distanta->DistantaTotala(20.38f, 30) << " km.";
	}
	catch (ExceptieMetrou& e)
	{
		cout << endl << e.what();
	}
	delete distanta;

	cout << endl << "Implementare Operator Egal: ";
	MetrouBucuresti MB3;
	MB3 = MB1;
	MB3.afisare();

	MetrouBucuresti MB4(4, "Eroilor", 10, M1, "Gara de Nord-Dristor 2");
	MB4.afisare();
	if (MB4 > MB3)
		cout << endl << "Metroul M1 parcurge o distanta mai lunga decat M2";
	else
		cout << endl << "Metroul M2 parcurge o distanta mai lunga decat M1";

	MetrouBucuresti MB5(5, "Piata Unirii", 5, M2, "Pipera");
	MB5.afisare();
	if (MB5("Piata Unirii") == M1)
		cout << endl << " Aceasta statie are corespondenta cu Magistrala 1";
	else
		cout << endl << " Aceasta statie nu are corespondenta cu Magistrala 1";

	cout << endl << "Apelare Operator INDEX: " << MB5[0];

	cout << endl << "Apelare operator <<: " << MB5;

	cout << endl << "Apelare operator cast: " << (char*)(MB5);

	return 0;
}