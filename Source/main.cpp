// Qt
#include <QApplication>
#include <QDebug>
//
#include "ResourcesManager/Builder.h"

/**
 * \mainpage Projet IN204: QTetris
 * \brief Mini moteur de jeu & Demonstrateur du Tetris.
 * \author Mengmeng Zhang & Marouane Fazouane
 * \version 2.0
 * \date 18 March 2013
 *
 * \section Introduction
 *  Le programme est un demonstrateur du projet Tetris.
 * \section Details
 * \li  Projet : Tetris
 * \li	Langage : C++11/ Qt
 * \li	IDE : QtCreator
 * \li	Source Control : GIThttps://github.com/
 * \li	Documentation : Doxygen
 * \li	ModéliseurUML : Visio & Umbrello
 *
 * \subsection Roadmap
 * \li	Installer les bibliothèques sur nos ordinateurs
 * \li	Prendre un compte Micro sur github et configurer l’IDE
 *\li	Se mettre d’accord sur le CodingStyle
 *\li	Compléter la description des modules
 *\li	Compléter l’UseCase
 *\li	Commencer les diagrammes de classes
 *\li	Réaliser un mini Tetris (très simple jeu) en mode console : Premier prototype du jeu
 *\li   But :
 * -	tester la suppression de lignes ;
 * -    tester les actions (rotations, déplacements…)
 * -	tester la chute
 * -    tester la fin du jeu
 * \li Description :
 * -	 Carte : matrice
 * -	 Pièces : des positions : x,y (Model) ; des étoiles (View)
 * -	 Commandes données sur la console
 * \li	Réaliser un prototype du système de menus*
 * \li	Approuver les diagrammes et implémenter le diagramme de classe en C++
 * \li	Commencer la documentation
 *\li	Travailler la GUI basique et l’intégrer au code
 *\li	Développer la GUI et le système de menu
 *\li	Rajouter la configuration par xml et un gestionnaire de son
 */


int main(int argc, char *argv[])
{
	Builder b;
	QApplication a(argc,argv);
	b.build();
	b.start();
	return a.exec();
}
