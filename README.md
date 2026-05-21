# Traitement d'image — Lena (C & Web Canvas)

Projet complet de **traitement d'image** implémenté en **C** et en **JavaScript (Canvas)**.
L'objectif est d'appliquer différents filtres sur une image 256×256 (format `.lena` / `.pgm`).

Deux versions sont disponibles :
- **Version C** — manipulation directe des pixels (lecture/écriture binaire, convolution, bruit, médian)
- **Version Web** — interface graphique interactive avec HTML, Bootstrap et Canvas

---

## Démo en ligne

[Voir la version web sur GitHub Pages](https://robinsankiritheepan.github.io/lena-image-processing-c-js/)

---

## Structure du dépôt

```
lena-image-processing-c-js/
├─ c-src/                  # Version C (console)
│  ├─ masque5.c
│  ├─ Makefile
│  └─ README.md
├─ docs/                   # Interface web interactive (GitHub Pages)
│  ├─ index.html
│  └─ README.md
├─ Rapport_traitement_image_ROBINSAN.pdf
└─ README.md               # Ce fichier
```

---

## Démarrage rapide

### Option A — Interface Web

1. Ouvrir `docs/index.html` dans le navigateur (ou utiliser la démo GitHub Pages)
2. Choisir une image `.lena` (ou `.pgm` 256×256)
3. Appliquer un filtre, visualiser, télécharger le résultat

### Option B — Version C (console)

```bash
cd c-src
make
./masque5
```

Suivre les instructions : choisir un fichier source, un filtre et un nom de sortie.

---

## Filtres disponibles

### Convolutifs 3×3

| Type | Matrice (exemple) | Diviseur |
|------|-------------------|----------|
| Détection horizontale | `[-1 -1 -1; 0 0 0; 1 1 1]` | 1 |
| Contours diagonaux | `[-1 0 1; -1 0 1; -1 1 1]` | 1 |
| Moyenneur | `[1 1 1; 1 1 1; 1 1 1]` | 9 |
| Gaussien | `[1 2 1; 2 4 2; 1 2 1]` | 16 |

### Non-linéaires

- **Filtre médian** — réduction du bruit en préservant les contours
- **Bruit poivre et sel** — ajout aléatoire de pixels noirs (0) et blancs (255)

---

## Points techniques

- Lecture / écriture d'image brute `.lena` (entête 256 octets + matrice 256×256)
- Implémentation complète du filtre médian (tri des 9 voisins)
- Bruit sel & poivre contrôlable par pourcentage
- Matrices de convolution personnalisées
- Visualisation instantanée via Canvas et JavaScript

---

## Technologies

- **C** — fichiers binaires, convolution, filtrage, allocation dynamique
- **HTML / Bootstrap / JS** — Canvas 2D, filtrage matriciel, rendu dynamique
- **Makefile** — compilation automatisée
- **GitHub Pages** — hébergement de la version web

---

ROBINSAN Kiritheepan — Étudiant ingénieur à l'ENSEA
