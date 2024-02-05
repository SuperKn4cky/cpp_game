# Cahier des charges

**Rôles :**

- Fenêtre graphique : Quentin, Maxence

- Logique de Jeu et Terminal : Nolan, Romain, Neil

- Réseau : Evan, Martin

- Coordinateur de jeu : Martin, Noah

**Règles du Jeu (Européenne):**

- Plateau de jeu (10x10)

- 1ère phase :
	- placement de bateaux (dans l'orientation désirée et non chevauchable):
		- 1 de 5 cases (de long)
		- 1 de 4 cases "
		- 2 de 3 cases "
		- 1 de 2 cases "
	
- 2ème phase (qd ts les bateux placés):
	- choisir une case où tirer :
		- si touché -> rejouer
		- si bateau coulé (toutes ses cases touchées)-> rejouer
		- si raté -> au tour de l'adversaire

- Conditions de victoires :
	- couler tous les bateaux de l'adversaires en premier

**Les données de l'état de jeu :**
- la logique de jeu stocke :
	- (coordonées bateaux + missiles)x2
	- l'index du joueur dont c'est le tour
	- int pour le tableau-association
- l'Afficheur prend :
	- coordonées bateaux + missiles
	- l'index du joueur dont c'est le tour
	- int pour le tableau-association
- la classe joueur (hérite de l'Afficheur)prend :
	- le pid / son adresse
	- l'index (1 -> j1, 2 -> j2)
	- le mode (terminal, graphique, réseau)
- ordre de jouer :
	- int à prendre dans un tableau association qui renvoie un string (demande de jouer, rejouer, fin)
- action :
	- coordonnées de la case où on veut tirer
- on transmet :
	- server -> client : le contenu de l'Afficheur
	- client -> server : coordonnées de la case sous string

**Déroulée d'une partie :**

Le joueur 1 lance une partie et place ses bateaux, le jouer 2 rejoins la partie du joueur 1 et place ces bateaux, une fois que les deux joueurs ont validée leurs placements, la partie se lance.

Les deux joueurs peuvent voir la position de leurs bateaux sur une map ainsi que la position des missiles ratée et la position des bateaux touchée par ces missiles. 

Le joueur 1 commence et décide la position que le missile va toucher chez le joueur adverse, s’il touche un bateau advers, alors le bateau est affiché comme détruit chez les deux joueurs puis le joueur 1 re joue.

Si le joueurs 1 rate sa cible, l’impacte du missile va être afficher sur la case sélectionner par le joueur 2 chez le joueur 1 et 2.

Le joueur 2 décide donc la position que le missile va toucher chez le joueur adverse, s’il touche un bateau advers, alors le bateau est affiché comme détruit chez les deux joueurs puis le joueur 2 re joue.
Si le joueurs 2 rate sa cible, l’impact du missile va être afficher sur la case sélectionner par le joueur 2 chez le joueur 1 et 2.

Et ainsi de suite jusque ce que le joueur 2 abatte tous les bateaux du joueur 1. Le joueur 2 a donc un message « Vous avez gagné ! » d’afficher et le joueur 1 a un message « Vous avez perdus» d’afficher.

**SFML (graphique / réseau) :**
- boutons interactifs


