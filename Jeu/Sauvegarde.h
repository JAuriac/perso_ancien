#pragma once
#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <iostream>
#include <ostream>
#include <istream>
#include "stdafx.h"
using namespace std;

class Sauvegarde
{
public:
	Sauvegarde();
	Sauvegarde(string nom);
	Sauvegarde(string nom, int nbEssai, string* inv);
	~Sauvegarde();
	void addObject(string object);
	void initInv();
	void afficherInv();
	void afficherInvDet();
	void permanent(string object, char which);
	string getName() { return nom; }
	void setName(string name) { nom = name; }
	int getTry() { return nbEssai; }
	void setTry(int nouvNbEssai) { nbEssai = nouvNbEssai; }
	string getInv(int a);
	bool getInvDisp(int a);
	bool getInvDispNom(string a);
	void setInv(string inv, int a);
	//a -1 dans InvUn et InvZero mais a dans get et set ???
	void setInvUn(int a) { inventaire_[a - 1][1] = "1"; }
	//mettre if else pour changer le texte de main bleue
	void setInvZero(int a) { inventaire_[a - 1][1] = "0"; cout << "Vous perdez alors votre " + inventaire_[a - 1][0] + "." << endl; }
	int indexFromString(string s);
	//char* ListLetters();
private:
	string nom;
	int nbEssai;
	string inventaire_[100][3];
};

#endif