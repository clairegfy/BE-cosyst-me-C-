# BE Écosystème

Simulation d'un écosystème en C++ avec affichage graphique via la bibliothèque **CImg** (X11).  
Des créatures appelées **bestioles** évoluent dans un aquarium 2D, chacune dotée d'un comportement propre qui guide ses déplacements à chaque pas de simulation.

---

## Table des matières

1. [Aperçu du projet](#aperçu-du-projet)
2. [Architecture](#architecture)
3. [Comportements](#comportements)
4. [Prérequis](#prérequis)
5. [Compilation](#compilation)
6. [Utilisation](#utilisation)
7. [Personnalisation](#personnalisation)
8. [Structure des fichiers](#structure-des-fichiers)

---

## Aperçu du projet

Ce projet est un **bureau d'études (BE)** réalisé en C++11.  
Il met en œuvre les concepts de **programmation orientée objet** : héritage, polymorphisme et le patron de conception **Stratégie** (*Strategy pattern*) pour modéliser les comportements des créatures.

L'écosystème se déroule dans une fenêtre 640 × 480 pixels.  
À chaque pas de simulation, chaque bestiole perçoit ses voisines dans un rayon de vision, puis adapte son orientation et sa vitesse en fonction de son comportement.  
Une bestiole meurt après un certain nombre de pas (âge maximal tiré aléatoirement).

---

## Architecture

```
Aquarium          – boucle principale et fenêtre graphique (CImg)
  └── Milieu      – contient la liste des bestioles, gère les collisions et les étapes
        └── Bestiole* (n)  – entité mobile dotée d'un Comportement
                  └── Comportement  – interface abstraite (Strategy)
                        ├── Gregaire
                        ├── Peureuse
                        ├── Kamikaze
                        ├── Prevoyante
                        └── MultiPersonnalite  – composite de plusieurs comportements
```

| Classe | Rôle |
|---|---|
| `Aquarium` | Crée la fenêtre, instancie le `Milieu`, exécute la boucle de simulation |
| `Milieu` | Gère la liste de bestioles, détecte les collisions, appelle `step()` |
| `Bestiole` | Entité mobile (position, orientation, vitesse, âge, couleur) |
| `Comportement` | Interface abstraite imposant `action()` et `clone()` |
| `Gregaire` | Comportement grégaire |
| `Peureuse` | Comportement peureux (fuite) |
| `Kamikaze` | Comportement kamikaze (charge) |
| `Prevoyante` | Comportement prévoyant (évitement anticipé) |
| `MultiPersonnalite` | Composite cyclant sur plusieurs comportements |

---

## Comportements

### Grégaire (`Gregaire`)
La bestiole s'aligne sur la **direction moyenne** de ses voisines visibles.  
Si elle n'a pas de voisin, elle continue tout droit.

### Peureuse (`Peureuse`)
- Vitesse de croisière : **5 px/pas**
- Si le nombre de voisins ≥ 3 (*seuil_peur*) : demi-tour + vitesse de fuite **20 px/pas**
- Dès que la zone est dégagée : retour à la vitesse de croisière

### Kamikaze (`Kamikaze`)
S'oriente vers la **bestiole la plus proche** et fonce dessus.

### Prévoyante (`Prevoyante`)
Anticipe les positions futures des voisins sur un horizon de **10 pas**.  
Si une collision probable est détectée (distance future < 20 px), la bestiole dévie de **90°**.

### Multi-personnalité (`MultiPersonnalite`)
Combiner une liste de comportements et en change toutes les **50 itérations** (stratégie composite).

---

## Prérequis

- **g++** avec support C++11
- **Xlib** (paquet `libx11-dev` sous Debian/Ubuntu)
- **CImg** (fourni dans le dépôt : `CImg.h`)

Sur Ubuntu/Debian :
```bash
sudo apt-get install libx11-dev
```

Sur macOS (via Homebrew + XQuartz) :
```bash
brew install --cask xquartz
# puis compiler avec X11_PREFIX=/opt/X11
```

---

## Compilation

```bash
make
```

Pour nettoyer les fichiers objets et l'exécutable :
```bash
make clean
```

> Sur macOS, si X11 est installé dans un chemin non standard, précisez le préfixe :
> ```bash
> make X11_PREFIX=/opt/X11
> ```

---

## Utilisation

```bash
./main
```

Une fenêtre graphique s'ouvre et affiche la simulation en temps réel.  
Les bestioles sont représentées par des disques colorés se déplaçant selon leur comportement.  
La simulation tourne jusqu'à fermeture de la fenêtre.

### Population par défaut (`main.cpp`)

| Comportement | Nombre |
|---|---|
| Grégaire | 5 |
| Peureuse | 5 |
| Kamikaze | 5 |
| Multi-personnalité (Grégaire + Kamikaze) | 5 |

---

## Personnalisation

Pour modifier la population initiale, éditez `main.cpp` :

```cpp
// Exemple : ajouter 3 bestioles prévoyantes
for ( int i = 0; i < 3; ++i ) {
    Bestiole* b = new Bestiole();
    b->setComportement( new Prevoyante() );
    ecosysteme.getMilieu().addMember( b );
}
```

Pour changer la taille de la fenêtre ou la vitesse d'affichage, modifiez la ligne :

```cpp
Aquarium ecosysteme( 640, 480, 30 );
//                   ^    ^    ^
//                   largeur hauteur délai(ms)
```

---

## Structure des fichiers

```
BE_ecosysteme/
├── main.cpp              # Point d'entrée – initialise et lance l'écosystème
├── Aquarium.{h,cpp}      # Fenêtre graphique et boucle de simulation
├── Milieu.{h,cpp}        # Environnement contenant les bestioles
├── Bestiole.{h,cpp}      # Entité mobile (position, orientation, âge…)
├── Comportement.h        # Interface abstraite Strategy
├── Gregaire.{h,cpp}      # Comportement grégaire
├── Peureuse.{h,cpp}      # Comportement peureux
├── Kamikaze.{h,cpp}      # Comportement kamikaze
├── Prevoyante.{h,cpp}    # Comportement prévoyant
├── MultiPersonnalite.{h,cpp} # Composite de comportements
├── CImg.h                # Bibliothèque d'affichage image (CImg)
├── UImg.h                # Alias de type pour CImg
└── Makefile              # Règles de compilation
```

---

## Licence

Projet académique — utilisation libre à des fins d'apprentissage.
