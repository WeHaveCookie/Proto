# Proto

Pré-requis (pour la compilation): 
- SFML 2.3 
- c++11 

Le sprite "Player" peut être déplacer avec les bouton: 
-'q' : Déplacement vers la gauche 
-'s' : Déplacement vers le bas 
-'d' : Déplacement vers la droite 
-'space' : Déplacement vers le haut 


Plusieurs commandes sont à disposition: 
-'j' : Créer un case aléatoirement sur la map 
-Clique droit : Fait une query range pour indiquer les cases présente à l'endroit du curseur (sur un carré de 32x32) 
-Clique gauche : 
  -En mode ajout : Ajoute une case à l'endroit du curseur 
  -En mode suppression : Supprime la case à l'endroit du curseur (sur un carré de 32x32) 
-'a' : ajout <-> suppression 
-'c' : Clear l'ensemble de la map 
-'p' : Detruit le quadtree et le recrée (Brutal) 
-'k' : Affiche ou non les cases de la map 
-'Escape' : Ferme le programme 
