#include <iostream>
#include <string>
using namespace std;

enum TipMangazin {Haine=1,Mancare=2};
class Magazin {
private:
	const int id;
	string denumire;
	int nrProduse;
	float* preturi;
	TipMangazin tip;

public:
	static int nrmag;
	//c fara parametrii
	Magazin():id(++nrmag)

	{
		this->denumire="necunoscut";
		this->nrProduse=0;
		this->preturi=nullptr;
		this->tip=Haine;
	}
	//cu parametrii
	Magazin(int iddat,string denumiredat,int nrProdusedat,float* preturidat,TipMangazin tipdat):id(iddat)
	{
		this->denumire=denumiredat;
		this->nrProduse=nrProdusedat;
		this->preturi=new float [nrProdusedat];
		for(int i=0; i<nrProdusedat; i++)
		{
			this->preturi[i]=preturidat[i];
		}
		this->tip=tipdat;
		nrmag++;
	}
	//c copiere
	Magazin(const Magazin&c):id(++nrmag)
	{
		this->denumire=c.denumire;
		this->nrProduse=c.nrProduse;
		this->tip=c.tip;
		if(c.preturi!=nullptr) {
			this->preturi=new float [c.nrProduse];
			for(int i=0; i<c.nrProduse; i++)
			{
				this->preturi[i]=c.preturi[i];
			}
		}
		else {
			this->preturi=nullptr;
		}
	}
	//op=
	Magazin& operator=(const Magazin&c)
	{
		if(this!=&c)
		{
			delete[] this->preturi;
			this->denumire=c.denumire;
			this->nrProduse=c.nrProduse;
			this->tip=c.tip;
			this->preturi=nullptr;

			if(c.preturi!=nullptr) {
				this->preturi=new float [c.nrProduse];
				for(int i=0; i<c.nrProduse; i++)
				{
					this->preturi[i]=c.preturi[i];
				}

			}
		}
		return *this;

	}
	int getnrprod()
	{
		return this->nrProduse;
	}

	void setnrprod(int nrProdusenou)
	{
		if(nrProdusenou>=0)
		{
			this->nrProduse=nrProdusenou;
		}
		else
		{
			throw "val neg";
		}
	}
	//afis
	void afisare()
	{
		cout<<"id= "<<this->id<<endl;
		cout<<"denumire="<<this->denumire<<endl;
		cout<<"nr produse= "<<this->nrProduse<<endl;

		cout<<"preturi= ";
		for(int i=0; i<nrProduse; i++)
		{
			cout<<this->preturi[i]<<" ";
		}


		cout<<endl<<"tip: ";
		if(this->tip==Haine)
		{
			cout<<Haine;
		}
		else cout<<Mancare;
		cout<<endl<<endl;
	}
	//destructor
	~Magazin()
	{
		delete[] this->preturi;
	}
};

int Magazin::nrmag=0;
int main()
{
	Magazin c1;

	float valori[]= {22,33,55};
	Magazin c2(2,"zarva",3,valori,Haine);

	Magazin c3=c2;

	c2=c1;

	//set si get
	try {
		c1.setnrprod(-2);
	}
	catch(...)
	{
		"val neg";
	}
	cout<<"nr prod noi= "<<c1.getnrprod()<<endl;
	//sau
	c1.setnrprod(5);
	cout<<"nr prod noi= "<<c1.getnrprod()<<endl;

	//cate mag am creat
	cout<<"total mag crreate= "<<Magazin::nrmag<<endl;
}




