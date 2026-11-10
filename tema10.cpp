#include <iostream>
#include <string>
using namespace std;

enum TipCinema {Standard=1,Imax=2};
class Cinema
{
private:
	const int id;
	string denumire;
	int nrfilme;
	float* pretbile;
	TipCinema tip;
public:
	static int nrcinema;

	//c fara param
	Cinema():id(++nrcinema)
	{
		this->denumire="necunoscută";
		this->nrfilme=0;
		this->pretbile=nullptr;
		this->tip=Imax;
	}

	//c cu param
	Cinema(int iddat,string denumiredat,int nrfilmedat,float *pretbiledat,TipCinema tipdat):id(iddat)
	{
		this->denumire=denumiredat;
		this->nrfilme=nrfilmedat;
		this->tip=tipdat;
		this->pretbile=new float[nrfilmedat];
		for(int i=0; i<nrfilmedat; i++)
		{
			this->pretbile[i]=pretbiledat[i];
		}
		nrcinema++;
	}

	//c copiere
	Cinema(const Cinema&c):id(++nrcinema)
	{
		this->denumire=c.denumire;
		this->nrfilme=c.nrfilme;
		this->tip=c.tip;
		if(c.pretbile!=nullptr) {
			this->pretbile=new float[c.nrfilme];
			for(int i=0; i<c.nrfilme; i++)
			{
				this->pretbile[i]=c.pretbile[i];
			}
		}
		else {
			this->pretbile=nullptr;
		}
	}
	//op =
	Cinema&operator=(const Cinema&c)
	{
		if(this!=&c)

		{
			delete[] this->pretbile;
			this->denumire=c.denumire;
			this->nrfilme=c.nrfilme;
			this->tip=c.tip;
			if(c.pretbile!=nullptr) {
				this->pretbile=new float[c.nrfilme];
				for(int i=0; i<c.nrfilme; i++)
				{
					this->pretbile[i]=c.pretbile[i];
				}
			}
			else {
				this->pretbile=nullptr;
			}
		}
		return *this;

	}

	//get
	int getnrfilme()
	{	return this->nrfilme;
	}

	void setnrf(int nrfnou)
	{
		if(nrfnou>=0)
		{
			this->nrfilme=nrfnou;
		}
		else {
			throw "val neg";
		}
	}

	//afisare
	void afisare()
	{
		cout<<"id: "<<this->id<<endl;
		cout<<"denumirea: "<<this->denumire<<endl;
		cout<<"nrfilme= "<<this->nrfilme<<endl;

		cout<<"pret bilet= ";
		for(int i=0; i<nrfilme; i++)
		{
			cout<<this->pretbile[i]<<" ";
		}
		cout<<endl;
		cout<<"tip= ";
		if(this->tip==Standard)
		{
			cout<<"Standard";
		} else cout<<"Imax";
		cout<<endl<<endl;

	}
	//destructor
	~Cinema()
	{
		delete[] this->pretbile;
	}
};


int Cinema::nrcinema=0;
int main()

{
	Cinema c1;
	c1.afisare();
	float vector[]= {22,33,23};
	Cinema c2(2,"Trivale",3,vector,Imax);
	c2.afisare();
	Cinema c3=c2;
	c3.afisare();
	c2=c1;
	c2.afisare();
	try {
		c1.setnrf(2);
	}
	catch(...)
	{
		"nu ex";
	}

	cout<<"nr filme noi= "<<c1.getnrfilme()<<endl;

	cout<<"total cinema= "<<Cinema::nrcinema<<endl;

}
