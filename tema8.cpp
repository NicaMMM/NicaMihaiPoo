#include <iostream>
#include <string>
using namespace std;

enum TipSala {Basic=1,Premium=2};
class Fitness
{
private:
	const	int id;
	string denumire;
	int nrabon;
	float* preturi;
	TipSala tip;

public:
	static int nrsali;

	Fitness():id(++nrsali)
	{
		this->denumire="necunoscut";
		this->nrabon=0;
		this->tip=Premium;
		this->preturi=nullptr;
	}

	Fitness(int iddat,string denumiredat,int nrabondat,float* preturidat,TipSala tipdat):id(iddat)
	{
		this->denumire=denumiredat;
		this->nrabon=nrabondat;
		this->tip=tipdat;
		this->preturi=new float [nrabondat];
		for(int i=0; i<nrabondat; i++)
		{
			this->preturi[i]=preturidat[i];
		}

		nrsali++;
	}

	//c copiere
	Fitness(const Fitness&c):id(++nrsali)
	{
		this->denumire=c.denumire;
		this->nrabon=c.nrabon;
		this->tip=c.tip;
		this->preturi=nullptr;
		if(c.preturi!=nullptr)
		{
			this->preturi=new float [c.nrabon];
			for(int i=0; i<c.nrabon; i++)
			{
				this->preturi[i]=c.preturi[i];
			}
		}

	}

	//op=
	Fitness&operator=(const Fitness&c)
	{
		if(this!=&c)
		{
			delete[] this->preturi;
			this->denumire=c.denumire;
			this->nrabon=c.nrabon;
			this->tip=c.tip;
			this->preturi=nullptr;
			if(c.preturi!=nullptr)
			{
				this->preturi=new float [c.nrabon];
				for(int i=0; i<c.nrabon; i++)
				{
					this->preturi[i]=c.preturi[i];
				}

			}

		}
		return *this;
	}

	// get
	int getnrabon()
	{
		return this->nrabon;
	}

	void setnrabon(int nrabonou)
	{
		if(nrabonou>=0)
		{
			this->nrabon=nrabonou;
		}
		else
		{
			throw "val neg";
		}
	}
	void afisare()
	{
		cout<<"id= "<<this->id<<endl;
		cout<<"denummire= "<<this->denumire<<endl;
		cout<<"nr abon= "<<this->nrabon<<endl;
		cout<<"pret= ";
		for(int i=0; i<nrabon; i++)
		{
			cout<<preturi[i]<<" ";
		}
		if(this->tip=Basic)
		{
			cout<<"Basic";
		} else {
			cout <<"Premium";
		}
		cout<<endl<<endl;
	}
	~Fitness()
	{
		delete[] this->preturi;
	}
};

int Fitness::nrsali=0;
int main()
{
	Fitness c1;
	c1.afisare();
	float vector[]= {159,199,204};
	Fitness c2(2,"ESX",3,vector,Premium);
	c2.afisare();
	Fitness c3=c2;
	c3.afisare();
	c2=c1;

	try
	{
		c2.setnrabon(-2);

	}
	catch(...)
	{
		cout<<"val neg"<<endl;
	}

	cout<<"val nou="<<c2.getnrabon()<<endl;


	cout<<"total sali= "<<Fitness::nrsali<<endl;








}