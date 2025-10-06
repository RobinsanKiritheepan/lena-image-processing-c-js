# 🖼️ Traitement d'image – Lena (C & Web Canvas)

Projet complet de **traitement d'image** implémenté en **C** et en **JavaScript (Canvas)**.  
L’objectif est d’appliquer différents filtres sur une image 256×256 (format `.lena` ou `.pgm`).

Deux versions sont disponibles :  
- 🖥️ **Version C** : manipulation directe des pixels (lecture/écriture binaire, convolution, bruit, médian…)  
- 🌐 **Version Web** : interface graphique interactive avec **HTML, Bootstrap et Canvas**

---

## 🌍 Démo en ligne

👉 <a href="https://robinsankiritheepan.github.io/lena-image-processing-c-js/" target="_blank">
Voir la version web sur GitHub Pages 🌐
</a>

---

## 📂 Structure du dépôt
```
traitement-image-lena/
├─ web/                    # Interface web interactive
│  ├─ index.html
│  └─ README.md
│
├─ c-src/                  # Version C (console)
│  ├─ masque5.c
│  ├─ Makefile
│  └─ README.md
│
└─ README.md               # Ce fichier (présentation globale)
```

---

## 🚀 Démarrage rapide

### 🧠 Option A — Interface Web (facile)
1. Ouvre simplement `web/index.html` dans ton navigateur.  
2. Choisis une image `.lena` (ou `.pgm` adaptée 256×256).  
3. Applique un filtre → visualise → télécharge le résultat !

> 💡 Cette version est aussi accessible en ligne via GitHub Pages.

---

### ⚙️ Option B — Version C (console)
1. Ouvre un terminal dans le dossier `c-src`
2. Compile le programme :
   ```bash
   make
   ```
3. Exécute :
   ```bash
   ./masque5
   ```
4. Suis les instructions : choisis un fichier source, un filtre et un nom de sortie.

---

## 🧪 Filtres disponibles

### 🔹 Convolutifs 3×3 :
| Type                      | Matrice (exemple) | Diviseur |
|----------------------------|------------------|-----------|
| Détection horizontale      | `[-1 -1 -1; 0 0 0; 1 1 1]` | 1 |
| Contours diagonaux         | `[-1 0 1; -1 0 1; -1 1 1]` | 1 |
| Moyenneur                  | `[[1,1,1],[1,1,1],[1,1,1]]` | 9 |
| Détection diagonale inversée | `[-1 -1 0; -1 0 1; 0 1 1]` | 1 |
| Gaussien                   | `[[1,2,1],[2,4,2],[1,2,1]]` | 16 |

### 🔹 Non-linéaires :
- **Filtre médian** : réduction du bruit tout en préservant les contours  
- **Bruit poivre et sel** : ajout aléatoire de pixels noirs (0) et blancs (255)

---

## 📦 Technologies utilisées
- **C** : manipulation de fichiers binaires, convolution, filtrage, allocation dynamique  
- **HTML / Bootstrap / JS** : Canvas 2D, filtrage matriciel, rendu dynamique  
- **Makefile** : compilation automatisée  
- **GitHub Pages** : hébergement de la version web  

---

## 🧠 Points techniques mis en œuvre
- Lecture et écriture d’image brute `.lena` (entête 256 octets + matrice 256×256)  
- Implémentation complète du filtre médian (tri des 9 voisins)  
- Ajout d’un bruit sel & poivre contrôlable par pourcentage  
- Utilisation de matrices de convolution personnalisées  
- Visualisation instantanée via Canvas et JavaScript  

---

## 🏷️ Compétences démontrées
- Programmation bas niveau en **C**  
- Traitement du signal et d’image  
- Développement **Frontend** (Canvas)  
- Architecture claire (séparation C / Web)  
- Utilisation professionnelle de **GitHub**

---

## 📄 Licence
Code publié sous licence **MIT** (libre d'utilisation et de modification)

---

## 👤 Auteur
**KirithEEPAN ROBINSAN**  
Étudiant ingénieur à **l’ENSEA**  
Architecte Logiciel en alternance – **SNCF**  

[🔗 Mon profil GitHub](https://github.com/RobinsanKirithEEPAN)
