// Jeu.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <array>
#pragma comment(lib, "Winmm.lib")
using namespace std;
#include "Sauvegarde.h"
#ifdef max
#undef max
#endif

Sauvegarde sauv;
int nbSalle = 0;
int repasse = 0;
string events[30][2]{};

void autoToEvent(int dir);
void SupprRandInv()
{
	int ind = -1;
	while (sauv.getInvDisp(ind) == false)
	{
		ind = rand() % 103; // ind = 2; pour l'arc
	}
	sauv.setInvZero(ind+1);
}
void SupprPrecInv(string o)
{
	int ind = sauv.indexFromString(o);
	sauv.setInvZero(ind+1);
}
int GetBufferWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
		bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
}
int GetBufferHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferHeight, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
		bufferHeight = bufferInfo.dwSize.Y;
	}

	return bufferHeight;
}
void OutputText(string s)
{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length(); i++)
	{
		char c = s[i - 1];

		int spaceCount = 0;

		// Add whitespace if newline detected.
		if (c == '\n')
		{
			int charNumOnLine = ((i) % bufferWidth);
			spaceCount = bufferWidth - charNumOnLine;
			s.insert((i - 1), (spaceCount), ' ');
			i += (spaceCount);
			continue;
		}

		if ((i % bufferWidth) == 0)
		{
			if (c != ' ')
			{
				for (int j = (i - 1); j > -1; j--)
				{
					if (s[j] == ' ')
					{
						s.insert(j, spaceCount, ' ');
						break;
					}
					else spaceCount++;
				}
			}
		}
	}

	// Output string to console
	std::cout << s << std::endl;
}
/*char* ListOfLetters()
{
	sauv.ListLetters();
}*/
void afficheContour()
{
	string contourHorizontal = "-";
	int bWitdh = GetBufferWidth();
	//cout << contourHorizontal.length() << endl;
	//cout << bWitdh << endl;
	while (contourHorizontal.length() < bWitdh)
	{
		contourHorizontal.append("-");
	}
	cout << contourHorizontal << endl;

	string contourVertical = "|";
	for (int i = 0; i < bWitdh-1 ; i++) { contourVertical.append(" "); }
	contourVertical.append("|");
	int bHeight = GetBufferHeight();
	//cout << contourVertical.length() << endl;
	int indexHauteur = 0;
	while (indexHauteur*3 < bHeight)
	{
		cout << contourVertical << endl;
		indexHauteur++;
	}

	cout << contourHorizontal << endl;
}

void debut()
{
	system("cls");
	cout << "Vous vous �veillez brusquement, r�veill� par un froid intense.\n" << endl;
	Sleep(2000);
	cout << "Du sable.\nDu sable froid vous coule dessus depuis des orifices situ�s quatre m�tres au dessus de vous.\n" << endl;
	Sleep(2000);
	cout << "Vous ne poss�dez aucuns rep�res ici, vous �tes d�sorient�.\nLa petite salle o� vous vous trouvez est petite, carr�e, et jonch�e d'�quipements.\n" << endl;
	Sleep(2000);
	cout << "Vous n'arrivez � discerner qu'une sortie � cette salle,\nsous la forme d'un renfoncement sombre situ� deux m�tres au dessus de vous,\ndans un mur." << endl;
	Sleep(3000);
	cout << "Vous comprenez rapidement que le d�bit du sable vous place en danger imminent,\net que vous n'aurez le temps de vous saisir que d'un objet avant de devoir fuir.\nVous remarquez alors que trois objets se d�marquent du reste de la salle, des armes :\nUn glaive, une lance, et un arc enroul� d'un carquois." << endl;
	if (sauv.getInvDisp(8) == true) { cout << "Non alarm� par le besoin d'une arme, d� � la pr�sence de votre arme magique sur vous,\nvous prenez le temps de regarder plus consciencieusement les objets r�partis dans la pi�ce,\n et remarquez maintenant la pr�sence d'une torche en bon �tat, d'un vase empli de sable, et d'un ..." << endl; }
	cout << "Que prendrez-vous ?\n\t1. Le glaive\n\t2. La lance\n\t3. L'arc";
	if (sauv.getInvDisp(8) == true) { "\n\t4. La torche\n\t5. Le vase\n\t6. Le truc"; }
	cout << endl;
	string choix;
	cin >> choix;
	if (sauv.getInvDisp(8) == false)
	{
		while (!(choix == "1" || choix == "2" || choix == "3"))
		{
			choix = "";
			cout << "Que prendrez-vous ?\n\t1. Le glaive\n\t2. La lance\n\t3. L'arc";
			cout << endl;
			cin >> choix;
		}
	}
	else 
	{
		while (!(choix == "1" || choix == "2" || choix == "3" || choix == "4" || choix == "5" || choix == "6"))
		{
			choix = "";
			cout << "Que prendrez-vous ?\n\t1. Le glaive\n\t2. La lance\n\t3. L'arc\n\t4. La torche\n\t5. Le vase\n\t6. Le truc";
			cout << endl;
			cin >> choix;
		}
	}
	{
		if (choix == "1") { sauv.setInvUn(1); }
		if (choix == "2") { sauv.setInvUn(2); }
		if (choix == "3") { sauv.setInvUn(3); }
		if (choix == "4") { sauv.setInvUn(4); }
		if (choix == "5") { sauv.setInvUn(5); }
		if (choix == "6") { sauv.setInvUn(6); }
	}
	cout << "Apr�s vous en �tre empar�, vous ne tardez pas � sortir de la salle, de peur d'�tre enseveli, et vous vous engoufrez dans un long couloir sombre..." << endl;
	Sleep(3000);
}
void passerelle()
{
	string rep = "";
	cout << "Un gobelin vous attaque !\n(Appuyez sur \"G\")" << endl;

	LARGE_INTEGER frequency;
	LARGE_INTEGER t1, t2;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	cin >> rep;
	QueryPerformanceCounter(&t2);
	double elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	if (elapsedTime < 2000 && (rep == "G" || rep == "g")) //tape le gob
	{
		cout << "did it" << endl;
	}
	if (elapsedTime > 2000) //gob le tape
	{
		cout << "slooow" << endl;
	}
	if (elapsedTime > 30000) //patience
	{
		cout << "workin'" << endl;
	}
	cout << elapsedTime << endl;
	cout << "out" << endl;

	//clock_t start = clock();
	//cin >> rep;
	//double temps = (clock() - start) / CLOCKS_PER_SEC;
	//if (temps < 2)
	//{
	//	cout << "did it" << endl;
	//}
	//if (temps > 30)
	//{
	//	cout << "slooow" << endl;
	//}
	//if ((temps < 1000) && (rep == "G" || rep == "g"))
	//{
	//	cout << "workin'" << endl;
	//	cout << temps << endl;
	//}
	//cout << "out" << endl;
}
void conservation()
{
	cout << "Apr�s avoir d�pass� une porte ouverte faite d'un bois v�n�rable, vous arrivez dans une petite salle, �clair�e uniquement par un puit de lumi�re, o� y culmine une lourde grille de fer.\nAu centre de la salle se trouve un petit autel sur lequel se trouve un linge de soie � l'aspect particuli�rement raffin�.\nDe l'autre c�t� de la salle se trouve une porte semblable � la porte pr�c�dente, elle est elle aussi ouverte." << endl;
	char choix;
	string choixP = "1234";
	do
	{
		cout << "Que voulez-vous faire ?\n\t1. Enrouler un de vos objets dans le linge, et partir avec.\n\t2. Poser un de vos objets sur le linge, et partir.\n\t3. Essayer d'escalader la paroi.\n\t4. Passer en ignorant l'autel.\n" << endl;
		cin >> choix;
	} while (!(choix == '1' || choix == '2' || choix == '3' || choix == '4'));
	//while (!choixP.find(choix));
	if (choix == '3')
	{
		cout << "Apr�s quelques essais, vous arrivez rapidement � la conclusion que ni votre �quipement, ni vos comp�tences, ne peuvent vous permettre d'atteindre le haut de ce puit." << endl;
		choixP = "123";
		do
		{
			cout << "Que voulez-vous faire ?\n\t1. Enrouler un de vos objets dans le linge, et partir avec.\n\t2. Poser un de vos objets sur le linge, et partir.\n\t3. Passer en ignorant l'autel.\n" << endl;
			cin >> choix;
		} while (!(choix == '1' || choix == '2' || choix == '3'));
	}
	if (choix == '1' || choix == '2')
	{
		cout << "Quel objet ?" << endl;
		sauv.afficherInv();
		string toInf;
		cin >> toInf;
		sauv.permanent(toInf, choix);
	}
	cout << "Dehors." << endl; //verbeux
	Sleep(3000);
}
void porte()
{
	srand(time(0));
	int dir = 0;
	int dirB = 0;
	int dirT = 0;
	if (nbSalle < 10) { dir = rand() % 20; dirB = rand() % 20; dirT = rand() % 20; }
	else { dir = rand() % 30; dirB = rand() % 30; dirT = rand() % 30; }
	while (events[dir][1] == "n" || events[dirB][1] == "n" || events[dirT][1] == "n")
	{
		if (nbSalle < 10) { dir = rand() % 20; dirB = rand() % 20; dirT = rand() % 20; }
		else { dir = rand() % 30; dirB = rand() % 30; dirT = rand() % 30; }
	}
	//cout << "dir: " << dir << " tab: " << events[dir] << " 0: " << events[dir][0] << " 1: " << events[dir][1] << endl;
	//cout << "dir: " << dirB << " tab: " << events[dirB] << " 0: " << events[dirB][0] << " 1: " << events[dirB][1] << endl;
	//cout << "dir: " << dirT << " tab: " << events[dirT] << " 0: " << events[dirT][0] << " 1: " << events[dirT][1] << endl;
	cout << "Vous sortez d'un couloir �troit, apr�s avoir march� pendant quelques longues minutes, pour arriver � une grande salle, d'une vingtaine de m�tres de largeur, �clair�e uniquements � la lumi�re de quelques torches �parses." << endl;
	Sleep(3000);
	cout << "Dans cette grande salle vide, vous apercevez trois portes, portant de gauche � droite les inscriptions \"" << events[dir][0] << "\", \"" << events[dirB][0] << "\" et \"" << events[dirT][0] << "\"." << endl;
	string choix;
	//string choixP = "1234";
	do
	{
		cout << "Que voulez-vous faire ?\n\t1. Passer par la porte de gauche.\n\t2. Passer par la porte du milieu.\n\t3. Passer par la porte de droite.\n\t4. Entrouvrir les trois portes et attendre.\n" << endl;
		cin >> choix;
	} while (!(choix == "1" || choix == "2" || choix == "3" || choix == "4"));
	if (choix == "4")
	{
		cout << "La porte de gauche donne sur un escalier descendant. La porte du milieu sur un couloir parfaitement droit. La porte de gauche donne sur un escalier ascendant. Les trois chemins s'�tendent � perte de vue, dans les t�n�bres." << endl;
		Sleep(3000);
		cout << "Apr�s avoir attendu quelque instants, vous finissez par discernez une sorte de gargouillement sourd, semblant provenir de quelque part tr�s loin dans l'�difice." << endl;
		Sleep(3000);
		do
		{
			choix = "";
			cout << "Que voulez-vous faire ?\n\t1. Passer par la porte de gauche.\n\t2. Passer par la porte du milieu.\n\t3. Passer par la porte de droite.\n" << endl;
			cin >> choix;
		} while (!(choix == "1" || choix == "2" || choix == "3"));
	}
	string temp = " ";
	if (choix == "1") { nbSalle++; autoToEvent(dir); }
	if (choix == "2") { nbSalle++; autoToEvent(dirB); }
	if (choix == "3") { nbSalle++; autoToEvent(dirT); }
}
void sourd() //changer nom
{
	cout << "Apr�s avoir pass� plusieurs passages exigus et franchi plusieurs couloirs semblant tourner en angle droit sans aucune coh�rence architecturale, le passage que vous empruntez d�bouche enfin sur une grande salle bien plus illumin�e que les pr�c�dentes.\nCette salle est en effet �clair�e par de tr�s longues torches plac�es tr�s hauts sur les murs.\nVous remarquez en y entrant qu'une personne se trouve ici.\nEn effet, au milieu de cette salle se trouve un homme, immense, longiligne, debout, qui vous fixe.\n Cet homme est s�par� du reste de la salle par un gouffre dessinant un carr� dans le sol de la salle.\nVous comprenez rapidement qu'il est muet, alors qu'il ne vous semble pas reconna�tre cet homme, sans pouvoir vous expliquer comment vous en �tes arriv� � cette conclusion.\nDe plus, une inspection rapide de la salle n'en r�v�le aucune sortie." << endl; //reconna" << char(140) << "tre
	Sleep(5000);
	cout << "Alors que vous faites vos premiers pas dans la salle, vous remarquez une inscription sur le sol, devant vous :\n 'Dites le nom que vous d�sirez obtenir.'\n" << endl;
	string nouvNom;
	cin >> nouvNom;
	if (nouvNom == "Aucun" || nouvNom == "Rien" || nouvNom == " ") { nouvNom = ""; }
	sauv.setName(nouvNom);
	Sleep(2000);
	cout << "Soudainement, une partie du sol de la salle, qui semblait jusqu�alors commune au reste,\nse d�robe pour r�v�ler un escalier s'enfon�ant dans les profondeurs obscures de ces lieux.\nAvant de l'emprunter, vous jetez un dernier regard vers l'homme r�sidant dans cette salle.\nIl est maintenant assis en tailleur." << endl;
}
void sourdV2() //test OutputText
{
	cout << "Apr�s avoir pass� plusieurs passages exigus et franchi plusieurs couloirs semblant tourner en angle droit sans aucune coh�rence architecturale, le passage que vous empruntez d�bouche enfin sur une grande salle bien plus illumin�e que les pr�c�dentes.\nCette salle est en effet �clair�e par de tr�s longues torches plac�es tr�s hauts sur les murs.\nVous remarquez en y entrant qu'une personne se trouve ici.\nEn effet, au milieu de cette salle se trouve un homme, immense, longiligne, debout, qui vous fixe.\n Cet homme est s�par� du reste de la salle par un gouffre dessinant un carr� dans le sol de la salle.\nVous comprenez rapidement qu'il est muet, alors qu'il ne vous semble pas reconna�tre cet homme, sans pouvoir vous expliquer comment vous en �tes arriv� � cette conclusion.\nDe plus, une inspection rapide de la salle n'en r�v�le aucune sortie." << endl; //reconna" << char(140) << "tre
	string s = "Apr�s avoir pass� plusieurs passages exigus et franchi plusieurs couloirs semblant tourner en angle droit sans aucune coh�rence architecturale, le passage que vous empruntez d�bouche enfin sur une grande salle bien plus illumin�e que les pr�c�dentes.\nCette salle est en effet �clair�e par de tr�s longues torches plac�es tr�s hauts sur les murs.\nVous remarquez en y entrant qu'une personne se trouve ici.\nEn effet, au milieu de cette salle se trouve un homme, immense, longiligne, debout, qui vous fixe.\n Cet homme est s�par� du reste de la salle par un gouffre dessinant un carr� dans le sol de la salle.\nVous comprenez rapidement qu'il est muet, alors qu'il ne vous semble pas reconna�tre cet homme, sans pouvoir vous expliquer comment vous en �tes arriv� � cette conclusion.\nDe plus, une inspection rapide de la salle n'en r�v�le aucune sortie.";
	OutputText(s);

	getchar();
	
	Sleep(5000);
	cout << "Alors que vous faites vos premiers pas dans la salle, vous remarquez une inscription sur le sol, devant vous :\n 'Dites le nom que vous d�sirez obtenir.'\n" << endl;
	string nouvNom;
	cin >> nouvNom;
	if (nouvNom == "Aucun" || nouvNom == "Rien" || nouvNom == " ") { nouvNom = ""; }
	sauv.setName(nouvNom);
	Sleep(2000);
	cout << "Soudainement, une partie du sol de la salle, qui semblait jusqu�alors commune au reste,\nse d�robe pour r�v�ler un escalier s'enfon�ant dans les profondeurs obscures de ces lieux.\nAvant de l'emprunter, vous jetez un dernier regard vers l'homme r�sidant dans cette salle.\nIl est maintenant assis en tailleur." << endl;
}
void aveugle()
{
	cout << "Alors que votre avanc�e vous am�ne � emprunter un escalier non �clair�,\nvous arrivez dans une salle gigantesque,\no� l'escalier que vous empruntiez semble sortir d'un mur de fa�on anarchique.\nCette salle, pourtant relativement bien �clair�e, ne dispose d'aucunes sources de lumi�res apparentes.\nVous remarquez en y entrant qu'une personne se trouve ici.\nEn effet, au milieu de cette salle se trouve un homme, maigre, bossu, assis en tailleur, qui semble perdu, regardant alternativement le sol devant lui, et quelque chose d'invisible semblant se mouvoir rapidement dans les airs.\nCet homme est s�par� du reste de la salle par un gouffre dessinant un cercle dans le sol de la salle.";
	if (sauv.getName() != "") { cout << "\nDe plus, vous remarquez que malgr� le bandeau sur les yeux de cet homme,\nil se tourne toujours de mani�re � vous faire face."; }
	cout << "Une sortie semble pr�sente sous la forme d'un autre escalier non �clair�,\ndont la forme s'oppose fondamentalement � celui par lequel vous �tes arriv�s." << endl;
	//---------------------------------------------------------------
}
void diable()
{
	//cf note, il faut prendre trois fois � droite, puis une fois � gauche c�t� du diable => donne un bout de mcguffin, si �choue -> passe
	array<string, 4> choix;
	array<string, 4> sol { "1", "1", "1", "2" };
	for (int i = 0; i < 4; i++)
	{
		string s = "Alors que vous continuez � avancer, la lumi�re change au rouge�tre, et vous d�bouchez dans une tr�s petite pi�ce. Vous y trouvez deux portes, et un �criteau : 'Jamais deux sans trois, mais le mal revient toujours.'";
		string s2 = "Que voulez-vous faire ?\n\t1. Passer par la porte de gauche.\n\t2. Passer par la porte de droite.\n";
		OutputText(s);
		OutputText(s2);
		cin >> choix[i];
		while (!(choix[i] == "1" || choix[i] == "2"))
		{
			choix[i] = "";
			OutputText(s2);
			cin >> choix[i];
		}
	}
	//verbeux
	if (choix == sol)
	{
		cout << "Oui" << endl;
	}
	else
	{
		cout << "Non" << endl;
	}
	Sleep(3000);
}
void froid()
{

}
void chaud()
{

}
//sous-salles x4
bool trembler()
{
	string response;
	bool w = false;
	cout << "La voix reprend alors instantan�ment :\n 'Je fais trembler les gens depuis la nuit des temps.'\n 'L�homme me combat r�guli�rement.'\n 'Je crains le soleil.'\n 'Qui suis-je ?'" << endl;
	cin >> response;
	if (response == "Le froid" || response == "Le Froid" || response == "froid" || response == "Froid") { w = true; }
	return w;
}
bool patience()
{
	Sleep(1000);
	string rep = "";
	LARGE_INTEGER frequency;
	LARGE_INTEGER t1, t2;
	cout << "pat" << endl;
	bool w = false;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	cin >> rep;
	getline(cin, rep);
	QueryPerformanceCounter(&t2);
	double elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

	if (elapsedTime > 60000) //patience
	{
		cout << "Patience �prouv�e." << endl; //verbeux ?
		w = true;
	}
	else
	{
		cout << "De ne pas confondre h�te et rapidit�." << endl;
	}
	/*cout << elapsedTime << endl;
	cout << w << endl;
	cout << "out" << endl;*/
	return w;
}
bool menteur()
{
	string response;
	bool w = false;
	cout << "La voix reprend alors instantan�ment :\n 'J�ai deux pieds,'\n 'Six jambes,'\n 'Huit bras,'\n 'Deux t�tes,'\n 'Et un �il.'\n 'Qui suis-je ?'" << endl;
	cin >> response;
	if (response == "Un menteur" || response == "Un Menteur" || response == "menteur" || response == "Menteur") { w = true; }
	return w;
}
bool souffle()
{
	string response;
	bool w = false;
	cout << "La voix reprend alors instantan�ment :\n 'Plus vous courez,'\n 'Moins vous l'aurez,'\n 'Qui suis-je ?'" << endl;
	cin >> response;
	if (response == "Le souffle" || response == "Le Souffle" || response == "souffle" || response == "Souffle") { w = true; }
	return w;
}
void recherche()
{
	srand(time(0));
	string rep = "";
	cout << "Alors que vous marchez dans un couloir �troit,\net que vous suivez un changement de direction,\nvous vous retrouvez dans une impasse.\nAvant de pouvoir r�agir, vous vous retrouvez enferm�s,\nalors que les murs se d�placent pour vous emp�cher de revenir sur vos pas." << endl;
	Sleep(5000);
	cout << "\nUn instant apr�s la fin de ce vacarme,\nvous entendez une voix assourdissante :\n '�nigme, ou Offrande.'" << endl;
	cin >> rep;
	if (rep == "�nigme" || rep == "Enigme" || rep == "�nigme" || rep == "enigme")
	{
		int laquelle = rand() % 4;
		bool wise = false;
		if (laquelle == 0) { wise = trembler(); }
		if (laquelle == 1) { wise = patience(); } //----------------------------------------------------------------------Probl�me �chec automatique - OK (j'avais laiss� cin en commentaire pour un test)
		if (laquelle == 2) { wise = menteur(); }
		if (laquelle == 3) { wise = souffle(); }
		if (wise == false) { cout << " 'Faux'" << endl; OutputText("Un brusque coup de vent se fait alors sentir, et vous vous trouvez oblig� de fermer les yeux, alors que cette brise glaciale vient se heurter contre votre dos, et vous vous savez repartir plus l�ger."); SupprRandInv(); } //Tester supprRandInv ici - OK
		else { cout << " 'Vrai'" << endl; } //----------------------------------------------------------------------------Obtenir ? Obtenir plume ?
	}
	else
	{
		cout << "La voix reprend :\n 'Quel objet ?'" << endl; //verbeux
		sauv.afficherInv();
		string offr;
		cin >> offr;
		while (sauv.getInvDispNom(offr) == false) //Tester getInvDispNom ici - OK
		{
			cin >> offr;
		}
		SupprPrecInv(offr);
		sauv.afficherInv();
	}
	//cout << "" << endl; //verbeux
	OutputText("De la m�me mani�re dont l'impasse s'�tait ferm�e derri�re vous,\nle grincement des murs et une faible lueur\nsont les signes vous annon�ant que vous pouvez poursuivre votre chemin.");
}
void deite() //Punition pour event 20 � 29
{
	cout << "Alors que vous luttez pour prendre des rep�res dans cet endroit enti�rement sombre, un �cho se fait entendre, suivi par l'apparition d'une faible lueur verte." << endl;
	Sleep(3000);
	cout << "Devant vous se trouve un bas-relief imposant, couvrant l'enti�ret� du mur vous faisant face. Cette salle est une salle rectangulaire aux proportions d�mesur�es, que ce soit dans sa hauteur, ou dans sa largeur dont vous ne pouvez pas apercevoir les extremit�s dans l'obscurit�." << endl; // Bas-relief
	string s =
		"Devant vous se trouve un bas-relief imposant, couvrant l'enti�ret� du mur vous faisant face. Cette salle est une salle rectangulaire aux proportions d�mesur�es, que ce soit dans sa hauteur, ou dans sa largeur dont vous ne pouvez pas apercevoir les extremit�s dans l'obscurit�. "
		"La lueur verte, qui se trouve � votre exacte oppos� dans le mur du bas-relief, est bient�t rejointe par ce qui semble �tre une infinit� d'autres, et vous commencez � apercevoir les contours des formes qui compose cette sculpture. "
		"Malgr� le manque de contraste originellement pr�sent, et l'usure avanc�e qui semble �tre attribu�e � l'�ge, vous parvenez maintenant � discerner de nombreuses repr�sentations diff�rentes d'animaux, de traits tr�s disparates, comme si autant d'individus avaient particip�s � cette scupture. "
		"De plus, vous remarquez que des phrases dans une langue qui vous est inconnue soulignent les repr�sentations de certains animaux. "
		"Un changement dans l'intensit� des lueurs met en surbrillance certaines lettres de ces phrases, toujours la m�me.";
	OutputText(s);

	//Lire inventaire -> Cr�er liste de toutes les lettres existantes
	//ListOfLetters();
	//Choisir une lettre au hasard dans cette liste (qui n'a pas d�j� �t� choisie)
	//GetLetter();
	//�nigme avec cette lettre, choisir un objet dont se d�barasser avec cette lettre, ou perdre un objet al�atoirement

	string s1 =
		"Un autel, que vous n'aviez pas remarqu� jusque l� en d�pit de sa proximit�, attire maintenant votre �il. Sa structure est ovale, et il repose sur un lourd socle de pierre marbr�. Il est impr�gn� d'un liquide ocre, �pais et visqueux. "
		"\n\nQue voulez vous faire ? \n\n\t1. Ajouter une bille dans le vase. \n\t2. Retirer une bille du vase. \n\t3. Ajouter cinq billes dans le vase. \n\t4. Ajouter dix billes dans le vase. \n\t5. Prendre une poign�e de billes dans votre sac. \n\t6. Briser le vase. \n\t7. Repartir.";
	OutputText(s1);	
	
	//GetRiddle();
	//R�p�ter trois fois, � mesure que l'air se fait plus �pais et �touffant (sinon �pais � chercher, opaque)
	// --------------------------------------------------------------
}
void etroit()
{
	int largeur = GetSystemMetrics(SM_CXSCREEN);
	int longueur = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetForegroundWindow();
	//SetWindowPos(hwnd, HWND_TOPMOST, largeur/3, longueur/10, largeur/3, (longueur/5)*4, NULL); //En Page
	//cout << "En Page" << endl;
	//Sleep(1000);
	//SetWindowPos(hwnd, HWND_TOPMOST, (largeur/10)*4, (longueur-((largeur/10)*2))/2, largeur/5, largeur/5, NULL); //En Cadre
	//cout << "En Cadre" << endl;
	//Sleep(3000);
	float X = largeur/3;
	float Y = longueur/10;
	float cx = largeur/3;
	float cy = (longueur/5)*4;
	float i = 0;
	while (i < largeur/3)
	{
		Y = Y + 1;
		cy = cy - 2;
		if (cx >= cy)
		{
			//Y = Y + 1;
			cy = cy + 1;
			X = X + 1;
			cx = cx - 2;
		}
		SetWindowPos(hwnd, HWND_TOPMOST, X, Y, cx, cy, 0x0008); //https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos SWP_NOREDRAW
		HWND x = GetConsoleWindow();
		ShowScrollBar(x, SB_BOTH, FALSE);
		if (cy <= largeur / 5) { break; }
		i++;
		afficheContour();
		Sleep(10);
		system("cls");
	}

	Sleep(5000);
	cout << "Le passage qui s'offre maintenant � vous n'est pas �clair�";
	if (sauv.getInvDisp(3) == true) { cout << ", \net suis une pente douce � travers le gr�s et l'argile." << endl; }
	else { cout << "." << endl; }
	cout << "Vous n'avez d'autre choix que de le parcourir, et, \nce qui s'apparente � un couloir aussi haut que large\ndevient vite �touffant alors que \nsa taille semble se r�duire continuellement\nalors que vous y progressez." << endl;
	cout << "test" << endl;
	mciSendString(_T("open \"Disasterpiece - Vignette Visions.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	mciSendString(_T("play mp3"), NULL, 0, NULL);
	cout << "test" << endl;
	Sleep(30000);
	cout << "test" << endl;
	mciSendString(_T("close mp3"), NULL, 0, NULL);
}
void information()
{
	//cf nbEssai requis pour mort()
}
void mort()
{
	//grande salle, d�s au sol, vase vide au milieu, mettre autant de d�s que nbEssai dans le vase gagne
	string choix;
	int nombre = 0;
	bool r�solu = false;
	string s =
		"Cet endroit semble vouloir vous emp�cher d'avancer, et vos sens vous paraissent embu�s. Vous vous trouvez maintenant dans une salle si petite que vous peindez � tenir debout. Le sol de cette salle est jonch� de billes parfaitement ronde, grise, chrom�es, et au milieu de la salle se trouve un vase transparent en forme de goutte. "
		"Bouger n'importe quelle bille de cette salle, et un bourdonnement brise le silence. Chaque bille boug�e ajoute un nouveau bourdonnement continu au fond sonore. Le vase est actuellement vide. Il semblerait que vous ne pouvez sortir de cette salle que par le chemin qui vous y a amen�. "
		"\n\nQue voulez vous faire ? \n\n\t1. Ajouter une bille dans le vase. \n\t2. Retirer une bille du vase. \n\t3. Ajouter cinq billes dans le vase. \n\t4. Ajouter dix billes dans le vase. \n\t5. Prendre une poign�e de billes dans votre sac. \n\t6. Briser le vase. \n\t7. Repartir.";
	OutputText(s);
	cin >> choix;
	while (!(choix == "7"))
	{
		if (choix == "1") { nombre++; }
		else if (choix == "2") { nombre--; }
		else if (choix == "3") { nombre += 5; }
		else if (choix == "4") { nombre += 10; }
		else if (choix == "5") { if (sauv.getInvDisp(8) == false) { sauv.setInvUn(9); string eu = "Vous prenez quelques billes et les mettez dans votre sac. Au bruit ambient s'ajoute plusieurs bourdonnements et un �cho assourdissant."; OutputText(eu); } else { string nonEu = "Vous poss�dez d�j� dans votre sac des billes similaires, et leurs poids vous font rapidement changer d'avis. Mieux vaut ne pas en emporter plus."; OutputText(nonEu); } }
		else if (choix == "6") { cout << "nombre" << nombre << endl; cout << "nbEssai" << sauv.getTry() << endl; if (nombre == sauv.getTry()) { r�solu = true; } break; }

		s = "Que voulez vous faire d'autre ? \n\t1. Ajouter une bille dans le vase. \n\t2. Retirer une bille du vase. \n\t3. Ajouter cinq billes dans le vase. \n\t4. Ajouter dix billes dans le vase. \n\t5. Prendre une poign�e de billes dans votre sac. \n\t6. Briser le vase. \n\t7. Repartir.";
		OutputText(s);
		cin >> choix;
	}
	if (r�solu == true) { cout << "resolu" << endl; } //revele un truc, et les bourdonnements d�j� pr�sent deviennent rapidement de plus en plus fort jusqu'� faire, vous poussant � sortir
	else { cout << "non resolu" << endl; } //rajouter phrase dans le cas 7 direct, ou cas defaut rejoint
	//si vase mal cass� ? : alors que vous sortez, le bruit qui semblait alors s'�loigner de vous au fur et � mesure que vous vous �loigniez de la pi�ce semble maintenant se rapprocher de vous � grande vitesse => bourdonnement();

}

const char* strToChar(string str)
{
	char* cstr = new char[str.length() + 1];
	strcpy_s(cstr, str.length() + 1, str.c_str());
	return cstr;
}
bool iskeypressed(unsigned timeout_ms = 0)
{
	return WaitForSingleObject(
		GetStdHandle(STD_INPUT_HANDLE),
		timeout_ms
	) == WAIT_OBJECT_0;
}
void initEvent()
{
	int colonnes = 30;
	int lignes = 2;
	for (int j = 0; j < colonnes - 5; j++)
	{
		for (int i = 0; i < lignes; i++)
		{
			events[j][1] = "y";
		}
	}
	for (int j = colonnes - 5; j < colonnes; j++)
	{
		for (int i = 0; i < lignes; i++)
		{
			events[j][1] = "n";
		}
	}

	//� enlever (temporaire), juste pour ne pas laisser aller vers event vide, apr�s 5
	for (int j = 5; j < colonnes; j++)
	{
		for (int i = 0; i < lignes; i++)
		{
			events[j][1] = "n";
		}
	}

	events[0][0] = "Destin";
	events[1][0] = "Pr�servation";
	events[2][0] = "Porte";
	events[3][0] = "Les Yeux";
	events[4][0] = "Les Oreilles";
	events[5][0] = "Destin";
	events[6][0] = "Destin";
	events[7][0] = "Destin";
	//events[7][0] = "In�vitable"; // pour mort()
	/*for (int j = 0; j < colonnes; j++)
	{
		for (int i = 0; i < lignes; i++)
		{
			cout << events[j][i] << endl;
		}
	}*/
}
void toEvent()
{
	//remplacer l'al�atoire par ce qu'il y a au dessus du void Jeu() ---------------------------------------------
	int dir;
	if (nbSalle < 10) { dir = rand() % 20; }
	else { dir = rand() % 30; }
	while (events[dir][1] == "n" && dir > 5)
	{
		if (nbSalle < 10) { dir = rand() % 20; } //0 � 19
		else { dir = rand() % 30; } //0 � 29
	}
	//debug dir
	cout << dir << endl;
	cout << events[dir][1] << endl;
	cout << nbSalle << endl;
	cout << (events[dir][1] == "n") << endl;
	cout << (events[dir][1] == "y") << endl;
	{
		if (dir == 0) { passerelle(); events[dir][1] = "n"; nbSalle++; }
		if (dir == 1) { conservation(); events[dir][1] = "n"; nbSalle++; }
		if (dir == 2) { porte(); nbSalle++; }
		if (dir == 3) { aveugle(); events[dir][1] = "n"; nbSalle++; }
		if (dir == 4) { sourd(); events[dir][1] = "n"; nbSalle++; }
		if (dir == 5) { mort(); events[dir][1] = "n"; nbSalle++; }
	}
}
void autoToEvent(int dir)
{
	if (dir == 0) { passerelle(); events[dir][1] = "n"; nbSalle++; }
	if (dir == 1) { conservation(); events[dir][1] = "n"; nbSalle++; }
	if (dir == 2) { porte(); nbSalle++; }
	if (dir == 3) { aveugle(); events[dir][1] = "n"; nbSalle++; }
	if (dir == 4) { sourd(); events[dir][1] = "n"; nbSalle++; }
}


bool isSave()
{
	std::ifstream infile("Sauvegarde.txt");
	return infile.good();
}
bool isSaveB()
{
	std::ifstream infile("SauvegardeBis.txt");
	return infile.good();
}
bool isSaveT()
{
	std::ifstream infile("SauvegardeTri.txt");
	return infile.good();
}
bool isSaveQ()
{
	std::ifstream infile("SauvegardeQua.txt");
	return infile.good();
}
void readSave()
{
	ifstream myReadFile;
	myReadFile.open("Sauvegarde.txt");
	char output[100];
	if (myReadFile.is_open()) 
	{
		while (!myReadFile.eof()) 
		{
			myReadFile >> output;
			cout << output << endl;
		}
	}
	myReadFile.close();
}
void readInGameSave()
{
	cout << "ingamesave" << endl;
	cout << sauv.getName() << endl;
	cout << sauv.getTry() << endl;
	cout << sauv.getInv(0) << endl;
	cout << sauv.getInv(1) << endl;
	cout << sauv.getInv(2) << endl;
	cout << "ingamesaveend" << endl;
}
void saveToGame()
{
	ifstream myReadFile;
	myReadFile.open("Sauvegarde.txt");
	char output[103];
	int compteur = -2;
	string n;
	int e;
	string inv[103];
	if (myReadFile.is_open())
	{
		cout << myReadFile.eof() << endl;
		while (!myReadFile.eof())
		{
			if (compteur == -2) { myReadFile >> output; n = output; } //cout << "n : " << n << endl;
			if (compteur == -1) { myReadFile >> output; e = stoi(output); } //(int)output  cout << "outp : " << output << endl; cout << "e : " << e << endl; compteur++; 
			if (compteur != -2 && compteur != -1) { myReadFile >> output; inv[compteur] = output; } //cout << "inv[] : " << output << endl;
			//if (compteur == 0) { cout << "inv[0] : " << output << endl; }
			compteur++;
		}
		/*{
			if (compteur == -2) { myReadFile >> output; n = output; compteur++; } //cout << "n : " << n << endl;
			if (compteur == -1) { myReadFile >> output; e = stoi(output); } //(int)output  cout << "outp : " << output << endl; cout << "e : " << e << endl; compteur++; 
			else { myReadFile >> output; inv[compteur] = output; cout << "inv[] : " << output << endl; }
			//if (compteur == 0) { cout << "inv[0] : " << output << endl; }
			compteur++;
		}*/
	}
	myReadFile.close();

	sauv.setName(n);
	//cout << n << endl;
	sauv.setTry(e);
	//cout << (char)e << endl;
	//Sleep(3000);
	/*for each (string s in inv)
	{
		cout << s << endl;
	}*/
	for (int i = 0; i < 100; i++)
	{
		//cout << inv[i] << endl;
		sauv.setInv(inv[i],i);
	}
}
void writeSave()
{
	ofstream fichier;
	fichier.open("Sauvegarde.txt");
	fichier << "Writing this to a file.\n";
	fichier << "Writing this to a file.\n";
	fichier << "Writing this to a file.\n";
	fichier << "Writing this to a file.\n";
	fichier.close();
}
void gameToSave()
{
	ofstream fichier;
	fichier.open("Sauvegarde.txt");
	fichier << sauv.getName() << endl;
	fichier << sauv.getTry() << endl;
	for (int i = 0; i < 100; i++)
	{
		fichier << sauv.getInv(i) << endl;
	}
	fichier.close();
}
void eraseSave()
{
	char choix;
	cout << "Supprimer Sauvegarde.txt ? y/n" << endl;
	cin >> choix;
	if (choix == 'y'){ remove("Sauvegarde.txt"); }
	else
	{
		string aSuppr;
		cout << "Quel est le nom du fichier " << char(133) << " supprimer ?" << endl;
		cin >> aSuppr;
		const char* cstr = strToChar(aSuppr);
		remove(cstr);
	}
}
void Credits()
{
	system("cls");
	cout << "Sinistre Chemin\n\n" << endl;
	Sleep(1000);
	cout << "Programmation :";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "\t\tJulian Auriac\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Sleep(1000);
	cout << "Sc�nari :";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "\t\tJulian Auriac\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Sleep(1000);
	cout << "Musique : \t\tEuh... Y en a pas...\n" << endl;
	Sleep(1000);
	cout << "Alpha-Testeurs :";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "\tLe Micka�l" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "\t\t\tLe Cl�ment\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Sleep(3000);
}

void afficherTableauString2D(string evenements[30][2])
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << evenements[i][j] << " ";
		}
		cout << endl;
	}
}

//changer le random pour random_device rd, mt19937, gen(rd()) puis distribution ?
/*
std::random_device rd;
std::mt19937 e{rd()}; // or std::default_random_engine e{rd()};
std::uniform_int_distribution<int> dist{1, 5};
*/
void Jeu()
{
	srand(time(0));
	//Sauvegarde sauv;
	int essai = sauv.getTry();
	sauv.setTry(essai + 1);
	initEvent();
	bool done = false;
	while (done == false)
	{
		nbSalle++;
		toEvent();
		gameToSave();
		//cout << sauv.getName() << endl;
		//cout << sauv.getTry() << endl;
		//sauv.afficherInv();
		Sleep(3000);
	}
}

void Titre()
{
	system("cls");
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	for (int i = 0; i < (columns / 2) - 1; i++) { cout << " "; }
	cout << "S" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2); i++) { cout << " "; }
	cout << "I" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2) + 1; i++) { cout << " "; }
	cout << "N" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2); i++) { cout << " "; }
	cout << "I" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2) - 1; i++) { cout << " "; }
	cout << "S" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2); i++) { cout << " "; }
	cout << "T" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2) + 1; i++) { cout << " "; }
	cout << "R" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2); i++) { cout << " "; }
	cout << "E" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2) - 1; i++) { cout << " "; }
	cout << " " << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2) - 1; i++) { cout << " "; }
	cout << "C" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2); i++) { cout << " "; }
	cout << "H" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2) + 1; i++) { cout << " "; }
	cout << "E" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2); i++) { cout << " "; }
	cout << "M" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2) - 1; i++) { cout << " "; }
	cout << "I" << endl;
	Sleep(500);
	for (int i = 0; i < (columns / 2); i++) { cout << " "; }
	cout << "N" << endl;
	Sleep(500);
}
void Intro()
{
	cout << "Les t�n�bres vous entourent." << endl;
	for (int i = 0; i < 3; i++) { /*Sleep(3000);*/ cout << "." << endl; }
	cout << "Une douce chaleur vous r�veille." << endl;
	for (int i = 0; i < 3; i++) { /*Sleep(3000);*/ cout << "." << endl; }
	cout << "Vous entendez une voix." << endl; /*Sleep(3000);*/ cout << "Cette voix semble � la fois distante et proche.\nVous vous trouvez dans un lieu qui vous est inconnu, dans la p�nombre,\net vous n'arrivez pas � discerner quoi que ce soit autour de vous." << endl; Sleep(3000);
	cout << "\'Quel est votre nom ?\'" << endl;
	string nom;
	cin >> nom;
	sauv.setName(nom);
	cout << "\'Non.\'" << endl;
	Sleep(500);
	cout << "\'Cela n'a aucune importance\'." << endl;
	Sleep(500);
	cout << "Vous vous rendormez instantan�ment, comme frapp� d'une fatigue soudaine,\nmais pas sans discerner une silhouette se tenant\nau dessus de vous au moment o� vous sombrez." << endl;
	Sleep(3000);
}

int main()
{
	SetConsoleTitle(L"Sombre Chemin");

	locale::global(locale(""));
	//SetConsoleCP(437);
	//SetConsoleOutputCP(437);
	int largeur = GetSystemMetrics(SM_CXSCREEN);
	int longueur = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetForegroundWindow();
	
	SetFocus(hwnd);

	SetWindowPos(hwnd,HWND_TOPMOST,largeur/3,longueur/10,largeur/3,(longueur/5)*4,NULL); //En Page

	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0); //En plein �cran

	//--------Scrollbar
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

	HWND x = GetConsoleWindow();
	ShowScrollBar(x, SB_BOTH, FALSE);
	//--------ScrollbarFin

	bool valid = true;
	string choix = "";
	string test = "NPLSRC";
	do 
	{
		valid = true;
		choix = "";
		cout << "Que voulez vous faire ?\n" << endl;
		cout << "Commencer :	N" << endl;
		cout << "Continuer :	P" << endl;
		cout << "Charger :	L" << endl;
		cout << "Voir :		S" << endl;
		cout << "Effacer :	R" << endl;
		cout << "Cr�dits :	C" << endl;
		cin >> choix;
		if (!(choix == "N" || choix == "P" || choix == "L" || choix == "S" || choix == "R" || choix == "C" || choix == "T"))
		{
			cout << "Votre choix <" << choix << "> n'est pas valide. Veuillez recommencez." << endl;
			valid = false;
		}
	} while (!valid);
	system("cls");
	
	switch (choix[0])
	{
	case 'N':
	{
		if (isSave() == 1)
		{
			rename("Sauvegarde.txt", "SauvegardeBis.txt");
			cout << "La sauvegarde existante a �t� renomm�e \"SauvegardeBis.txt\"." << endl;
			Sleep(3000);
			system("cls");
		}
		sauv.initInv();
		/*sauv.afficherInv();
		cout << "abc" << endl;*/
		Intro();
		debut();
		/*sauv.afficherInv();
		cout << "def" << endl;*/
		Sleep(3000);
		Titre();
		Jeu();
		break;
	}	
	case 'P':
	{
		if (isSave() == 0)
		{
			cout << "Sauvegarde non trouv�e." << endl;
			Sleep(3000);
			break;
		}
		saveToGame();
		//Sleep(3000);
		//readInGameSave();
		//Sleep(3000);
		Jeu();
		break;
	}	
	case 'L':
	{
		int isGood = 0;
		if (isSave() && isSaveB() && isSaveT() && !isSaveQ())
		{
			rename("Sauvegarde.txt", "SauvegardeQua.txt");
			cout << "La sauvegarde existante a �t� renomm�e \"SauvegardeQua.txt\"." << endl;
			Sleep(3000);
			system("cls");
			isGood++;
		}
		if (isSave() && isSaveB() && !isSaveT() && isGood == 0)
		{
			rename("Sauvegarde.txt", "SauvegardeTri.txt");
			cout << "La sauvegarde existante a �t� renomm�e \"SauvegardeTri.txt\"." << endl;
			Sleep(3000);
			system("cls");
			isGood++;
		}
		if (isSave() && !isSaveB() && isGood == 0)
		{
			rename("Sauvegarde.txt", "SauvegardeBis.txt");
			cout << "La sauvegarde existante a �t� renomm�e \"SauvegardeBis.txt\"." << endl;
			Sleep(3000);
			system("cls");
			isGood++;
		}
		if (!isSave() && isGood == 0)
		{
			system("cls");
			isGood++;
		}
		if (isGood == 0) { break; }
		cout << "Quel est le nom de la sauvegarde � charger ? ex : SauvegardeBis.txt" << endl;
		string str;
		cin >> str; //attention � bien mettre l'extension .txt
		const char* cstr = strToChar(str);
		rename(cstr, "Sauvegarde.txt");
		saveToGame();
		//break;
	}	
	case 'S':
	{
		readSave();
		break;
	}	
	case 'R':
	{
		cout << "�tes-vous s�r ? y/n" << endl;
		cin >> choix;
		if (choix == "y") { eraseSave(); }
		break;
	}	
	case 'C':
	{
		Credits();
		break;
	}
	case 'T':
	{
		///*toEvent();
		//cout << events[15][1] << endl;
		//cout << events[3][0] << endl;*/
		//if (isSave() == 0)
		//{
		//	cout << "Sauvegarde non trouv�e." << endl;
		//	Sleep(3000);
		//	break;
		//}
		//saveToGame();
		////sauv.initInv();
		//sauv.afficherInvDet();
		//system("pause");

		//passerelle
		//recherche();

		//patience();

		//etroit(); //musique et r�tr�cissement fen�tre ---------------------------------- affreux contour

		//porte();

		//initEvent();
		//afficherTableauString2D(events);
		//toEvent();
		//afficherTableauString2D(events);
		//toEvent();
		//afficherTableauString2D(events);
		//toEvent();
		//afficherTableauString2D(events);
		//toEvent();
		//afficherTableauString2D(events);
		//toEvent();
		//afficherTableauString2D(events);

		//diable();

		saveToGame();
		sauv.afficherInvDet();
		mort();
		sauv.afficherInvDet();
		sauv.afficherInvDet();

		//sourdV2(); //OutputText

		//Rectangle(GetDC(hwnd),10,10,5,5);

		/*Fl_Box changeling = new Fl_Box(10, 10, 100, 20);
		changeling.box(FL_BORDER_FRAME);
		changeling.color(FL_RED);*/

		//saveToGame();
		//recherche();

		/*saveToGame();
		//recherche();
		//gameToSave();
		sauv.afficherInv();
		int ind = 0;
		while (sauv.getInvDisp(ind) == false)
		{
			ind = ind + 1;
		}
		cout << ind << endl;
		sauv.setInvZero(ind+1);
		sauv.afficherInv();
		cout << test << endl;*/

		break;
	}	
	default:
		break;
	}
    return 0;
}

//sauvegarde corrompu en ajoutant de nouveaux objets ? -> r�solu parce qu'en plus des deux constructeurs il faut changer la liste d'inventaire d'initialisation initInv
//torche qui fait avancer plus vite ?