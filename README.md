# BE Écosystème

Simulation d'un écosystème en C++ avec affichage graphique via la bibliothèque **CImg** (X11).  
Des créatures appelées **bestioles** évoluent dans un aquarium 2D, chacune dotée d'un comportement propre, de capteurs sensoriels et d'accessoires qui influencent ses déplacements à chaque pas de simulation.

---

## Table des matières

1. [Aperçu du projet](#aperçu-du-projet)
2. [Architecture](#architecture)
3. [Comportements](#comportements)
4. [Capteurs](#capteurs)
5. [Accessoires](#accessoires)
6. [Patterns de conception](#patterns-de-conception)
7. [Prérequis](#prérequis)
8. [Compilation](#compilation)
9. [Utilisation](#utilisation)
10. [Personnalisation](#personnalisation)
11. [Structure des fichiers](#structure-des-fichiers)

---

## Aperçu du projet

Ce projet est un **bureau d'études (BE)** réalisé en C++11.  
Il met en œuvre les concepts de **programmation orientée objet** : héritage, polymorphisme, et de nombreux patrons de conception (**Strategy**, **Observer**, **Mémento**, **Factory**, **Prototype**, **Singleton**, **Décorateur**) pour modéliser les comportements, les capteurs et les accessoires des créatures.

L'écosystème se déroule dans une fenêtre 640 × 480 pixels.  
À chaque pas de simulation, chaque bestiole perçoit ses voisines via ses capteurs, puis adapte son orientation et sa vitesse en fonction de son comportement et de ses accessoires.  
Une bestiole meurt après un certain nombre de pas (âge maximal tiré aléatoirement).  
La simulation enregistre l'historique de la population (Mémento) et affiche un bilan à la fin.

---

## Architecture

```
Aquarium              – boucle principale et fenêtre graphique (CImg)
  └── Milieu          – contient la liste des bestioles, gère les collisions, notifie les Observer
        └── Bestiole* (n)  – entité mobile dotée d'un Comportement, de Capteurs et d'Accessoires
              ├── Comportement  – interface abstraite (Strategy)
              │     ├── Gregaire
              │     ├── Peureuse
              │     ├── Kamikaze
              │     ├── Prevoyante
              │     └── MultiPersonnalite  – composite de plusieurs comportements
              ├── ICapteur* (0..n)  – capteurs sensoriels (Strategy / Décorateur)
              │     ├── Yeux          – vision angulaire
              │     └── Oreilles      – détection sonore omnidirectionnelle
              └── IAccessoire* (0..n) – accessoires modificateurs (Décorateur)
                    ├── Camouflage    – réduit la visibilité
                    ├── Carapace      – protection + ralentissement
                    └── Nageoires     – augmentation de vitesse

BestiolesFactory (Singleton)  – crée et configure des bestioles complètes
  └── PrototypeRegistry        – registre de prototypes clonables (Prototype)
  └── PopulationConfig         – paramétrage du nombre de bestioles par type

EvenementObserver  – interface Observer
SimMemento         – historique de la population (Mémento)
SimulationAnalyser – affiche le bilan en fin de simulation
```

| Classe | Rôle |
|---|---|
| `Aquarium` | Crée la fenêtre, instancie le `Milieu`, exécute la boucle de simulation |
| `Milieu` | Gère la liste de bestioles, détecte les collisions, appelle `step()`, notifie les observateurs |
| `Bestiole` | Entité mobile (position, orientation, vitesse, âge, couleur, capteurs, accessoires) |
| `Comportement` | Interface abstraite imposant `action()` et `clone()` |
| `Gregaire` | Comportement grégaire |
| `Peureuse` | Comportement peureux (fuite) |
| `Kamikaze` | Comportement kamikaze (charge) |
| `Prevoyante` | Comportement prévoyant (évitement anticipé) |
| `MultiPersonnalite` | Composite cyclant sur plusieurs comportements |
| `ICapteur` | Interface abstraite pour les capteurs sensoriels |
| `Yeux` | Capteur visuel : détection dans un cône (angle, distance, facteur de camouflage) |
| `Oreilles` | Capteur sonore : détection omnidirectionnelle dans un rayon |
| `IAccessoire` | Interface abstraite pour les accessoires (Décorateur) |
| `Camouflage` | Réduit la probabilité d'être détecté |
| `Carapace` | Augmente la résistance aux collisions, réduit la vitesse |
| `Nageoires` | Multiplie la vitesse de déplacement |
| `BestiolesFactory` | Singleton créant des bestioles entièrement configurées (Factory) |
| `PrototypeRegistry` | Registre de prototypes clonables par nom (Prototype) |
| `PopulationConfig` | Structure de configuration du nombre de bestioles par type |
| `EvenementSim` | Événement de simulation (NAISSANCE, MORT, CHANGEMENT_COMPORTEMENT) |
| `EvenementObserver` | Interface Observer abonnée aux événements du Milieu |
| `SimMemento` | Sauvegarde l'historique de population à chaque pas |
| `SimulationAnalyser` | Analyse et affiche le bilan de la simulation |

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
Combine une liste de comportements et en change toutes les **50 itérations** (stratégie composite).

---

## Capteurs

Les capteurs (`ICapteur`) permettent à une bestiole de percevoir ses voisines.  
Chaque bestiole peut posséder zéro ou plusieurs capteurs, combinables librement.

### Yeux (`Yeux`)
Détection **visuelle** dans un cône directionnel.  
Paramètres : angle d'ouverture `alpha`, distance maximale `distance`, facteur `gamma` modulé par le camouflage de la cible.

```cpp
b->ajouterCapteur( new Yeux( 1.5, 60.0, 1.0 ) );
```

### Oreilles (`Oreilles`)
Détection **sonore omnidirectionnelle** dans un rayon fixe.  
La direction de déplacement n'entre pas en compte ; seule la distance compte.

```cpp
b->ajouterCapteur( new Oreilles( 50.0, 1.0 ) );
```

---

## Accessoires

Les accessoires (`IAccessoire`) modifient les caractéristiques d'une bestiole selon le pattern **Décorateur**.  
Chaque bestiole peut posséder zéro ou plusieurs accessoires.

### Camouflage (`Camouflage`)
Réduit la probabilité d'être détecté par les `Yeux` des autres bestioles (paramètre `psi`).

```cpp
b->ajouterAccessoire( new Camouflage( 0.5 ) );
```

### Carapace (`Carapace`)
Augmente la résistance aux collisions (`protection`) mais ralentit la bestiole (`ralentissement`).

```cpp
b->ajouterAccessoire( new Carapace( 0.3, 0.8 ) );
```

### Nageoires (`Nageoires`)
Multiplie la vitesse de déplacement par un facteur `facteur`.

```cpp
b->ajouterAccessoire( new Nageoires( 1.3 ) );
```

---

## Patterns de conception

| Pattern | Classes concernées | Description |
|---|---|---|
| **Strategy** | `Comportement`, `Gregaire`, `Peureuse`, `Kamikaze`, `Prevoyante`, `MultiPersonnalite` | Comportement interchangeable à la volée |
| **Décorateur** | `ICapteur`, `IAccessoire` et leurs sous-classes | Ajout de capteurs/accessoires sans modifier `Bestiole` |
| **Composite** | `MultiPersonnalite` | Agrège plusieurs comportements |
| **Observer** | `EvenementObserver`, `EvenementSim`, `Milieu` | Le Milieu notifie ses abonnés à chaque naissance/mort/changement |
| **Mémento** | `SimMemento`, `SimulationAnalyser` | Sauvegarde l'historique de population ; bilan affiché en fin de simulation |
| **Factory** | `BestiolesFactory` | Crée des bestioles entièrement configurées (comportement + capteurs + accessoires) |
| **Singleton** | `BestiolesFactory` | Instance unique de la factory |
| **Prototype** | `PrototypeRegistry` | Clonage de bestioles-types enregistrées par nom |

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
À la fin, un **bilan de population** est affiché dans le terminal (population initiale, finale, min et max).

### Population par défaut (`main.cpp`)

| Comportement | Capteur(s) | Accessoire | Nombre |
|---|---|---|---|
| Grégaire | Yeux | Nageoires | 5 |
| Peureuse | Oreilles | Camouflage | 5 |
| Kamikaze | Yeux | Carapace | 5 |
| Multi-personnalité (Grégaire + Kamikaze) | Yeux + Oreilles | — | 5 |

---

## Personnalisation

### Modifier la population initiale

Éditez `main.cpp` directement, en configurant comportement, capteurs et accessoires :

```cpp
// Exemple : ajouter 3 bestioles prévoyantes avec nageoires et yeux
for ( int i = 0; i < 3; ++i ) {
    Bestiole* b = new Bestiole();
    b->setComportement( new Prevoyante() );
    b->ajouterCapteur( new Yeux( 1.5, 60.0, 1.0 ) );
    b->ajouterAccessoire( new Nageoires( 1.3 ) );
    ecosysteme.getMilieu().addMember( b );
}
```

Ou utilisez la **factory** et `PopulationConfig` pour une configuration centralisée :

```cpp
PopulationConfig cfg( 10, 5, 3, 2 );  // g, p, k, multi
BestiolesFactory::getInstance()->peuplerMilieu( ecosysteme.getMilieu(), cfg );
```

### Changer la taille de la fenêtre ou la vitesse d'affichage

```cpp
Aquarium ecosysteme( 640, 480, 30 );
//                   ^    ^    ^
//                   largeur hauteur délai(ms)
```

---

## Structure des fichiers

```
BE_ecosysteme/
├── main.cpp                      # Point d'entrée – initialise et lance l'écosystème
├── Aquarium.{h,cpp}              # Fenêtre graphique et boucle de simulation
├── Milieu.{h,cpp}                # Environnement contenant les bestioles ; diffuse les événements Observer
├── Bestiole.{h,cpp}              # Entité mobile (position, orientation, âge, capteurs, accessoires)
│
├── Comportement.h                # Interface abstraite Strategy
├── Gregaire.{h,cpp}              # Comportement grégaire
├── Peureuse.{h,cpp}              # Comportement peureux
├── Kamikaze.{h,cpp}              # Comportement kamikaze
├── Prevoyante.{h,cpp}            # Comportement prévoyant
├── MultiPersonnalite.{h,cpp}     # Composite de comportements
│
├── ICapteur.h                    # Interface abstraite des capteurs
├── Yeux.{h,cpp}                  # Capteur visuel (cône directionnel)
├── Oreilles.{h,cpp}              # Capteur sonore (omnidirectionnel)
│
├── IAccessoire.h                 # Interface abstraite des accessoires (Décorateur)
├── Camouflage.{h,cpp}            # Accessoire : camouflage
├── Carapace.{h,cpp}              # Accessoire : carapace (protection + ralentissement)
├── Nageoires.{h,cpp}             # Accessoire : nageoires (accélération)
│
├── BestiolesFactory.{h,cpp}      # Factory Singleton – crée des bestioles configurées
├── PrototypeRegistry.{h,cpp}     # Registre de prototypes clonables (Prototype)
├── PopulationConfig.{h,cpp}      # Configuration du nombre de bestioles par type
│
├── EvenementSim.h                # Événements de simulation (NAISSANCE, MORT, …)
├── EvenementObserver.h           # Interface Observer
├── SimMemento.{h,cpp}            # Historique de population (Mémento)
├── SimulationAnalyser.{h,cpp}    # Bilan de simulation
│
├── CImg.h                        # Bibliothèque d'affichage image (CImg)
├── UImg.h                        # Alias de type pour CImg
└── Makefile                      # Règles de compilation
```

---

## Licence

Projet académique — utilisation libre à des fins d'apprentissage.
