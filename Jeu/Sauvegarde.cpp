#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#include "Sauvegarde.h"

string linventaire[100][3] = {"défaut, ne doit pas apparaître","0","n"}; //glaive lance arc torche mainbleue armemagique
Sauvegarde::Sauvegarde() : nom(""), nbEssai(0)
{
	inventaire_[0][0] = "glaive";
	inventaire_[1][0] = "lance";
	inventaire_[2][0] = "arc";
	inventaire_[3][0] = "torche";
	inventaire_[4][0] = "vase";
	inventaire_[5][0] = "truc";
	inventaire_[6][0] = "main bleue";
	inventaire_[7][0] = "arme magique";
	inventaire_[8][0] = "poignée de billes";
	for (int i = 0; i < 100; i++)
	{
		inventaire_[i][1] = linventaire[i][1];
		inventaire_[i][2] = linventaire[i][2];
	}
};
Sauvegarde::Sauvegarde(string nom) : nom(nom), nbEssai(0)
{
	inventaire_[0][0] = "glaive";
	inventaire_[1][0] = "lance";
	inventaire_[2][0] = "arc";
	inventaire_[3][0] = "torche";
	inventaire_[4][0] = "vase";
	inventaire_[5][0] = "truc";
	inventaire_[6][0] = "main bleue";
	inventaire_[7][0] = "arme magique";
	inventaire_[8][0] = "poignée de billes";
	for (int i = 0; i < 100; i++)
	{
		inventaire_[i][1] = linventaire[i][1];
		inventaire_[i][2] = linventaire[i][2];
	}
};
Sauvegarde::Sauvegarde(string n, int essai, string* inv) : nom(n), nbEssai(essai)
{
	for (int i = 0; i < 100; i++)
	{
		inventaire_[i][0] = inv[i][0];
		inventaire_[i][1] = inv[i][1];
		inventaire_[i][2] = inv[i][2];
	}
};
Sauvegarde::~Sauvegarde() {};

void Sauvegarde::addObject(string object)
{
	/*int compteur = 0;
	while (1)
	{
		if (!inventaire_[compteur][0].empty() || inventaire_[compteur][0] == "")
		{
			inventaire_[compteur][0] == object;
			break;
		}
	}*/
	for (int i = 0; i < 100; i++)
	{
		if (inventaire_[i][0] == object)
		{
			inventaire_[i][1] = "1";
			break;
		}
	}
}
void Sauvegarde::initInv()
{
	inventaire_[0][0] = "glaive";
	inventaire_[1][0] = "lance";
	inventaire_[2][0] = "arc";
	inventaire_[3][0] = "torche";
	inventaire_[4][0] = "vase";
	inventaire_[5][0] = "truc";
	inventaire_[6][0] = "main bleue";
	inventaire_[7][0] = "arme magique";
	inventaire_[8][0] = "poignée de billes";
	for (int i = 0; i < 100; i++)
	{
		inventaire_[i][1] = "0";
		inventaire_[i][2] = "n";
	}
}
void Sauvegarde::afficherInv()
{
	for (int i = 0; i < 100; i++)
	{
		if ((!inventaire_[i][0].empty() || inventaire_[i][0] != "") && inventaire_[i][1] == "1")
		{
			cout << inventaire_[i][0] << endl;
		}
	}
}
void Sauvegarde::afficherInvDet()
{
	for (int i = 0; i < 100; i++)
	{
		if (!inventaire_[i][0].empty() || inventaire_[i][0] != "")
		{
			cout << inventaire_[i][0] << ";" << inventaire_[i][1] << ";" << inventaire_[i][2] << endl;
		}
	}
}
void Sauvegarde::permanent(string object, char which)
{
	for (int i = 0; i < 100; i++)
	{
		if (inventaire_[i][0] == object)
		{
			if (which == '1') { inventaire_[i][1] = "1"; inventaire_[i][2] = "y"; }
			if (which == '2') { inventaire_[i][1] = "0"; inventaire_[i][2] = "y"; }
			break;
		}
	}
}
//conservation choix 2 ne perd pas l'objet ?
string Sauvegarde::getInv(int index)
{
	string temp = inventaire_[index][0];
	temp += ";";
	temp += inventaire_[index][1];
	temp += ";";
	temp += inventaire_[index][2];
	return temp;
}
bool Sauvegarde::getInvDisp(int index)
{
	bool b = false;
	if (inventaire_[index][1] == "1") { b = true; }
	return b;
}
bool Sauvegarde::getInvDispNom(string nom)
{
	bool b = false;
	for (auto& rows : inventaire_)
	{
		if (rows[0] == nom && rows[1] == "1") { b = true; break; }
	}
	return b;
}
void Sauvegarde::setInv(string inv, int index)
{
	char delimiter = ';';
	stringstream ss(inv);
	string item;
	vector<string> splittedStrings;
	while (getline(ss, item, delimiter))
	{
		splittedStrings.push_back(item);
	}
	inventaire_[index][0] = splittedStrings[0];
	inventaire_[index][1] = splittedStrings[1];
	inventaire_[index][2] = splittedStrings[2];
}
int Sauvegarde::indexFromString(string s)
{
	int retour = -1;
	for (int i = 0; i < 100; i++)
	{
		if (inventaire_[i][0] == s) { retour = i; break; }
	}
	return retour;
}
char* Sauvegarde::ListLetters()
{
	vector<string> vect;
	char* p;
	char listOfLetters[28];
	p = listOfLetters;

	for (int index = 0; index < 100; index++)
	{
		if (inventaire_[index][1] == "1")
		{
			vect.push_back(inventaire_[index][0]);
		}
	}

	for (int jndex = 0; jndex < vect.size(); jndex++)
	{
		for (char& c : vect[jndex])
		{
			for (int i = 0; i < sizeof(listOfLetters); i++) 
			{
				if (listOfLetters[i] == c) {
					break;
				}
			}
		}
	}
	
	return p;
}