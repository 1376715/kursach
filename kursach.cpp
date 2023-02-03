#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
ofstream fout;
ifstream finR,finD;
struct dissovet{string name;int rang;};
struct region{int id;string name;int kolD;dissovet *dissovets;int rang;};
void table(int n)
{
	int i;
	for(i=0;i<n;i++)
		cout<<"_";
}
void outputToConsole(region *R,int kol)
{
	int i;
	table(62);
	cout<<endl;
	cout<<"|��� �������|       ������������ �������        |���� �������|"<<endl;
	table(62);
	cout<<endl;
	for(i=0;i<kol;i++)
	{
		cout<<"|"<<setw(6)<<R[i].id<<setw(6)<<"|"<<R[i].name<<setw(36-R[i].name.length())<<"|"<<setw(7)<<R[i].rang<<setw(6)<<"|"<<endl;
		table(62);
		cout<<endl;
	}
}
void fastSort1(int nStart,int nEnd,region *R)
{
	int l,r,x;
	region temp;
	if(nStart>=nEnd)
		return;
	l=nStart;
	r=nEnd;
	x=R[(l+r)/2].id;
	while(l<=r)
	{
		while(R[l].id<x)
			l++;
		while(R[r].id>x)
			r--;
		if(l<=r)
		{
			temp=R[l];
			R[l]=R[r];
			R[r]=temp;
			l++;
			r--;
		}
	}
	fastSort1(nStart,r,R);
	fastSort1(l,nEnd,R);
}
void fastSort2(int nStart,int nEnd,region *R)
{
	int l,r,x;
	region temp;
	if(nStart>=nEnd)
		return;
	l=nStart;
	r=nEnd;
	x=R[(l+r)/2].rang;
	while(l<=r)
	{
		while(R[l].rang<x)
			l++;
		while(R[r].rang>x)
			r--;
		if(l<=r)
		{
			temp=R[l];
			R[l]=R[r];
			R[r]=temp;
			l++;
			r--;
		}
	}
	fastSort2(nStart,r,R);
	fastSort2(l,nEnd,R);
}
void sampleSort2(region *R,int n)
{
	int i,j,nMin;
	region temp;
	for(i=0;i<n-1;i++)
	{
		nMin=i;
		for(j=i+1;j<n;j++)
		{
			if(R[j].rang>R[nMin].rang)
				nMin=j;
		}
		if(i!=nMin)
		{
			temp=R[nMin];
			R[nMin]=R[i];
			R[i]=temp;
		}
	}
}
void query(region *R,int kol)
{
	int id,i;
	bool check=0;
	cout<<"������� ��� �������: ";
	cin>>id;
	for(i=0;i<kol;i++)
		if(id==R[i].id)
		{
			check=1;
			cout<<R[i].name<<", ���� ����� "<<R[i].rang<<endl;
		}
		if(!check)
			cout<<"������ � ����� "<<id<<" �� ������!\n";
}
void outputToFail(region *R,int kol)
{
	int i;
	fout.open("output.xls");
	fout<<"��� �������\t������������ �������\t���� �������\n";
	for(i=0;i<kol;i++)
		fout<<R[i].id<<"\t"<<R[i].name<<"\t"<<R[i].rang<<"\n";
	fout.close();
}
void sData1(region *R, int kol)
{
	int i;
	table(70);
	cout<<endl;
	cout<<"|��� ������|���������� ����������|       ������������ �������        |"<<endl;
	table(70);
	cout<<endl;
	for(i=0;i<kol;i++)
	{
		cout<<"|"<<setw(6)<<R[i].id<<setw(5)<<"|"<<setw(11)<<R[i].kolD<<setw(11)<<"|"<<R[i].name<<setw(36-R[i].name.length())<<"|"<<endl;
		table(70);
		cout<<endl;
	}
}
void sData2(region *R, int kol)
{
	int i,j;
	table(155);
	cout<<endl;
	cout<<"|���� ���������|                                                          ������������ ���������                                                           |"<<endl;
	table(155);
	cout<<endl;
	for(i=0;i<kol;i++)
	{
		for(j=0;j<R[i].kolD;j++)
		{
			cout<<"|"<<setw(7)<<R[i].dissovets[j].rang<<setw(8)<<"|"<<R[i].dissovets[j].name<<setw(140-R[i].dissovets[j].name.length())<<"|"<<endl;
			table(155);
			cout<<endl;
		}
	}
}
int main()
{
	setlocale(LC_CTYPE, "");
	system("color f0");
	system("cls");
	int kolR=0,i,j,all_kolD=0,sum,num,num2,num2_1,num2_2,n1,n2,n3,n5;
	string temp;
	finR.open("regions.txt");
	while(!finR.eof())
	{
		getline(finR,temp,'\n');
		kolR++;
	}
	finR.close();
	region *Rs = new region[kolR];
	finR.open("regions.txt");
	finD.open("dissovets.txt");
	for(i=0;i<kolR;i++)
	{
		finR>>Rs[i].id;
		finR>>Rs[i].kolD;
		all_kolD+=Rs[i].kolD;
		getline(finR,Rs[i].name);
		Rs[i].name.erase(0,1);
		Rs[i].dissovets = new dissovet[Rs[i].kolD];
		for (j = 0;j<Rs[i].kolD;j++)
		{
			finD>>Rs[i].dissovets[j].rang;
			getline(finD, Rs[i].dissovets[j].name);
			Rs[i].dissovets[j].name.erase(0,1);
		}
	}
	finR.close();
	finD.close();
	for(i=0;i<kolR;i++)
	{
		sum=0;
		for(j=0;j<Rs[i].kolD;j++)
			sum+=Rs[i].dissovets[j].rang;
		Rs[i].rang=Rs[i].kolD*all_kolD-sum;
	}
	while(1)
	{
		system("cls");
		cout<<"1. ������� ������� �������� �� �����.\n";
		cout<<"2. ������������� ������.\n";
		cout<<"3. ��������� ������ �� ���� �������.\n";
		cout<<"4. �������� ������ � ����.\n";
		cout<<"5. ������� �������� ������ �� �����.\n";
		cout<<"6. ����� �� ���������.\n";
		cout<<"������� �����: ";
		cin>>num;
		switch(num)
		{
		case 1:outputToConsole(Rs,kolR);break;
		case 2:
			cout<<"1. ���������� �� ���� ������� � ������� �����������.\n";
			cout<<"2. ���������� �� ����� �������.\n";
			cout<<"������� �����: ";
			cin>>num2;
			switch(num2)
			{
			case 1:
				fastSort1(0,kolR-1,Rs);
				cout<<"���������� �� ����� ������� � ������� ����������� ������� ���������!\n������ ������� ������� �������� �� �����?\n���� ��, �� ������� 1.\n";
					cin>>n1;
					if(n1==1)
						outputToConsole(Rs,kolR);
					break;
			case 2:
				cout<<"1. ���������� � ������� �����������.\n";
				cout<<"2. ���������� � ������� ��������.\n";
				cout<<"������� �����: ";
				cin>>num2_2;
				switch(num2_2)
				{
				case 1:
					fastSort2(0,kolR-1,Rs);
					cout<<"���������� �� ����� ������� � ������� ����������� ������� ���������!\n������ ������� ������� �������� �� �����?\n���� ��, �� ������� 1.\n";
					cin>>n2;
					if(n2==1)
						outputToConsole(Rs,kolR);
					break;
				case 2:
					sampleSort2(Rs,kolR);
					cout<<"���������� �� ����� ������� � ������� ����������� ������� ���������!\n������ ������� ������� �������� �� �����?\n���� ��, �� ������� 1.\n";
					cin>>n3;
					if(n3==1)
						outputToConsole(Rs,kolR);
					break;
				default:cout<<"������� ������ �����!\n";
				}
			}
			break;
		case 3:query(Rs,kolR);break;
		case 4:
			outputToFail(Rs,kolR);
			cout<<"������ ������ � ���� 'output.xls' ������� ���������!\n";
			break;
		case 5:
			cout<<"1. ������� ������ �� ����� 'regions.txt'.\n";
			cout<<"2. ������� ������ �� ����� 'dissovets.txt'.\n";
			cout<<"������� �����: ";
			cin>>n5;
			switch(n5)
			{
			case 1:sData1(Rs,kolR);break;
			case 2:sData2(Rs, kolR);break;
			default:cout<<"������� ������ �����!\n";
			}
			break;
		case 6:return 0;
		default:cout<<"������� ������ �����!\n";
		}
		system("pause");
	}
}
