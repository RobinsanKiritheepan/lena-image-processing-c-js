/*------------------------------------------------------
Auteurs :
		- ROBINSAN Kiritheepan
		- LENARD DUNSTAN Kishor
	
Co-auteur :
		- ChatGPT
--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NB_LIGNES 256
#define NB_COLONNES 256
#define ENTETE_TAILLE 256

// Prototypes
unsigned char **charger_image(const char *nomFichier);
unsigned char **applyConvolution(unsigned char **im, int width, int height, int kernel[3][3], int divisor, int isSobel);
void sauvegarder_image(const char *nomFichier, unsigned char **im, const char *sourceHeader);
void filtre_median(unsigned char **im, unsigned char **im2, int width, int height);
void tri_min(int tab[9]);
void ajouter_bruit_poivre_sel(unsigned char **im, unsigned char **im2, int width, int height, float pourcentage);
unsigned char **traiter_image(int choix, unsigned char **im, int kernel[3][3], int *divisor, int *isSobel);
unsigned char **filtre_gaussien(unsigned char **im, int width, int height);

// Fonctions auxiliaires du main
void demander_nom_fichier_source(char *nom);
int verifier_image_chargee(unsigned char **im);
int demander_choix_filtre();
void initialiser_parametres_filtre(int kernel[3][3], int *divisor, int *isSobel);
void demander_nom_fichier_sortie(char *nom);
void afficher_message_sauvegarde(const char *nom);
void liberer_images(unsigned char **im1, unsigned char **im2);


// ---------------- MAIN ---------------------

/*----------------------------------------------------------------
 * Fonction : main
 * But      : Point d'entrée du programme de traitement d'image PGM.
 *            Permet de charger une image, appliquer un filtre
 *            sélectionné par l'utilisateur, et sauvegarder le résultat.
 *
 * Étapes :
 *    1. Demander le nom du fichier source (.lena ou .pgm)
 *    2. Charger l'image dans une matrice 2D (im)
 *    3. Afficher le menu de choix de filtre (convolution, médian, bruit...)
 *    4. Appliquer le traitement choisi via traiter_image()
 *    5. Sauvegarder l'image résultante
 *    6. Libérer la mémoire allouée
 *
 * Remarques :
 *    - Le filtre est sélectionné par l'utilisateur (valeur entre 1 et 6)
 *    - `traiter_image()` gère l'application concrète du traitement
 *    - L'image résultante est enregistrée dans un nouveau fichier
 *----------------------------------------------------------------*/
 
int main() {
    char nomSource[100], nomDest[100];
    unsigned char **im, **im_filtree;
    int kernel[3][3];
    int divisor, isSobel, choix;

    demander_nom_fichier_source(nomSource);

    im = charger_image(nomSource);
    if (!verifier_image_chargee(im)) return 1;

    choix = demander_choix_filtre();

    initialiser_parametres_filtre(kernel, &divisor, &isSobel);

    im_filtree = traiter_image(choix, im, kernel, &divisor, &isSobel);
    if (!im_filtree) return 1;

    demander_nom_fichier_sortie(nomDest);
    sauvegarder_image(nomDest, im_filtree, nomSource);
    afficher_message_sauvegarde(nomDest);

    liberer_images(im, im_filtree);

    return 0;
}


void demander_nom_fichier_source(char *nom) {
    printf("Nom du fichier image source (.lena) : ");
    scanf("%s", nom);
}

int verifier_image_chargee(unsigned char **im) {
    if (!im) {
        printf("\u274c Echec du chargement.\n");
        return 0;
    }
    return 1;
}

int demander_choix_filtre() {
    int choix;
    printf("\nVeuillez choisir le filtre a appliquer :\n");
    printf("1 : Detection horizontale personnalisee\n");
    printf("2 : Contours diagonaux personnalises\n");
    printf("3 : Filtre moyenneur 3x3 (1/9)\n");
    printf("4 : Detection diagonale inversee\n");
    printf("5 : Filtre median (tri_min)\n");
    printf("6 : Ajouter du bruit poivre et sel\n");
    printf("7 : Filtre gaussien 3x3\n");
    printf("Entrez votre choix (1 a 7) : ");
    scanf("%d", &choix);
    return choix;
}

void initialiser_parametres_filtre(int kernel[3][3], int *divisor, int *isSobel) {
    *divisor = 1;
    *isSobel = 0;
    // Laisser la fonction traitement remplir le kernel si besoin
}

void demander_nom_fichier_sortie(char *nom) {
    printf("Nom du fichier de sortie (.lena) : ");
    scanf("%s", nom);
}

void afficher_message_sauvegarde(const char *nom) {
    printf("\u2705 Image sauvegardee dans %s\n", nom);
}

void liberer_images(unsigned char **im1, unsigned char **im2) {
    for (int i = 0; i < NB_LIGNES; i++) {
        free(im1[i]);
        free(im2[i]);
    }
    free(im1);
    free(im2);
}

/*----------------------------------------------------------------
 * Fonction : traiter_image
 * But      : Applique un filtre à une image selon le choix utilisateur.
 * Paramètres :
 *    - choix    : Numéro du filtre sélectionné (1 à 6).
 *    - im       : Image source.
 
 *    - kernel   : Tableau pour stocker le masque 3x3 utilisé par la convolution.
 *    - divisor  : Pointeur vers le diviseur de la convolution.
 *    - isSobel  : Pointeur vers le flag indiquant un filtre Sobel (val absolue).
 * Retour    : Nouvelle image filtrée (im_filtree) ou NULL si erreur/annulation.
 *----------------------------------------------------------------*/

unsigned char **traiter_image(int choix, unsigned char **im, int kernel[3][3], int *divisor, int *isSobel) {
    int i, j;
    unsigned char **im_filtree = malloc(NB_LIGNES * sizeof(unsigned char *));
    for (i = 0; i < NB_LIGNES; i++) {
        im_filtree[i] = malloc(NB_COLONNES * sizeof(unsigned char));
    }

    if (choix == 1) {
        kernel[0][0] = -1; kernel[0][1] = -1; kernel[0][2] = -1;
        kernel[1][0] =  0; kernel[1][1] =  0; kernel[1][2] =  0;
        kernel[2][0] =  1; kernel[2][1] =  1; kernel[2][2] =  1;
    } else if (choix == 2) {
        kernel[0][0] = -1; kernel[0][1] = 0;  kernel[0][2] = 1;
        kernel[1][0] = -1; kernel[1][1] = 0;  kernel[1][2] = 1;
        kernel[2][0] = -1; kernel[2][1] = 1;  kernel[2][2] = 1;
        *isSobel = 1;
    } else if (choix == 3) {
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                kernel[i][j] = 1;
        *divisor = 9;
    } else if (choix == 4) {
        kernel[0][0] = -1; kernel[0][1] = -1; kernel[0][2] =  0;
        kernel[1][0] = -1; kernel[1][1] =  0; kernel[1][2] =  1;
        kernel[2][0] =  0; kernel[2][1] =  1; kernel[2][2] =  1;
        *isSobel = 1;
    } else if (choix == 5) {
        filtre_median(im, im_filtree, NB_COLONNES, NB_LIGNES);
        printf("\u2705 Filtre median applique.\n");
        return im_filtree;
    } else if (choix == 6) {
        char reponse;
        printf("Souhaitez-vous ajouter du bruit poivre et sel ? (o/n) : ");
        scanf(" %c", &reponse);

        if (reponse == 'o' || reponse == 'O') {
            float pourcentage;
            printf("Pourcentage de bruit (ex: 0.05 pour 5%%) : ");
            scanf("%f", &pourcentage);
            ajouter_bruit_poivre_sel(im, im_filtree, NB_COLONNES, NB_LIGNES, pourcentage);
            printf("\u2705 Bruit poivre et sel applique.\n");
            return im_filtree;
        } else {
            printf("\u274c Aucun bruit ajoute. Fin du programme.\n");
            return NULL;
        }
    } else if (choix == 7) {
        return filtre_gaussien(im, NB_COLONNES, NB_LIGNES);
    } else {
        printf("\u274c Choix invalide.\n");
        return NULL;
    }

    im_filtree = applyConvolution(im, NB_COLONNES, NB_LIGNES, kernel, *divisor, *isSobel);
    printf("\u2705 Filtre convolutif applique.\n");
    return im_filtree;
}

// ---------------- Filtrage Gaussien ---------------------

/*----------------------------------------------------------------
 * Fonction : filtre_gaussien
 * But      : Appliquer un filtre gaussien 3×3 à une image en niveaux de gris
 *            pour effectuer un lissage (réduction du bruit et des détails fins).
 *
 * Paramètres :
 *    - im     : Image source (matrice 2D de pixels)
 *    - width  : Largeur de l'image
 *    - height : Hauteur de l'image
 *
 * Retour :
 *    - Nouvelle image filtrée (matrice 2D), obtenue après convolution avec
 *      le noyau gaussien.
 *
 * Remarques :
 *    - Utilise un noyau gaussien 3×3 classique :
 *         [1 2 1]
 *         [2 4 2]
 *         [1 2 1]
 *    - Le diviseur est 16 (somme des poids) pour conserver l’intensité lumineuse.
 *    - L’appel à applyConvolution() effectue le traitement.
 *----------------------------------------------------------------*/

unsigned char **filtre_gaussien(unsigned char **im, int width, int height) {
    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    int divisor = 16;
    return applyConvolution(im, width, height, kernel, divisor, 0);
}


// ---------------- Chargement ---------------------


/*----------------------------------------------------------------
 * Fonction : charger_image
 * But      : Charger une image en niveaux de gris (format brut .lena)
 *            depuis un fichier et la stocker dans un tableau 2D alloué dynamiquement.
 *
 * Paramètres :
 *    - nomFichier : Nom du fichier à charger (chemin relatif ou absolu)
 *
 * Retour :
 *    - Pointeur vers une image 2D (unsigned char **), ou NULL en cas d'échec
 *
 * Remarques :
 *    - Le fichier contient un en-tête binaire qu'on saute (ENTETE_TAILLE octets)
 *    - L'image est supposée avoir une taille fixe : NB_LIGNES × NB_COLONNES
 *    - Chaque pixel est codé sur 1 octet (niveaux de gris)
 *----------------------------------------------------------------*/
 
unsigned char **charger_image(const char *nomFichier) {
    FILE *f = fopen(nomFichier, "rb");
    if (!f) return NULL;

    for (int i = 0; i < ENTETE_TAILLE; i++) fgetc(f);

    unsigned char **im = malloc(NB_LIGNES * sizeof(unsigned char *));
    for (int i = 0; i < NB_LIGNES; i++) {
        im[i] = malloc(NB_COLONNES * sizeof(unsigned char));
        fread(im[i], sizeof(unsigned char), NB_COLONNES, f);
    }

    fclose(f);
    return im;
}

// ---------------- Convolution ---------------------

/*----------------------------------------------------------------
 * Fonction : applyConvolution
 * But      : Appliquer un filtre (masque 3×3) sur l'image (tableau im) et stocker
 *            le résultat dans im2.
 * Paramètres :
 *    - im      : Image source.
 *    - width   : Largeur de l'image.
 *    - height  : Hauteur de l'image.
 *    - kernel  : Masque 3x3.
 *    - divisor : Diviseur pour normaliser le résultat.
 *    - isSobel : Flag indiquant s'il faut prendre la valeur absolue du résultat.
 * Retour    : Nouvelle image filtrée.
 *----------------------------------------------------------------*/
 
unsigned char **applyConvolution(unsigned char **im, int width, int height,
                                 int kernel[3][3], int divisor, int isSobel) {
    unsigned char **im2 = malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++)
        im2[i] = malloc(width * sizeof(unsigned char));

    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            int somme = 0;
            for (int ki = -1; ki <= 1; ki++)
                for (int kj = -1; kj <= 1; kj++)
                    somme += kernel[ki + 1][kj + 1] * im[i + ki][j + kj];

            if (divisor != 0) somme /= divisor;
            if (isSobel && somme < 0) somme = -somme;
            if (somme < 0) somme = 0;
            if (somme > 255) somme = 255;

            im2[i][j] = (unsigned char)somme;
        }
    }

    for (int i = 0; i < height; i++) {
        im2[i][0] = im[i][0];
        im2[i][width - 1] = im[i][width - 1];
    }
    for (int j = 0; j < width; j++) {
        im2[0][j] = im[0][j];
        im2[height - 1][j] = im[height - 1][j];
    }

    return im2;
}

// ---------------- Tri min ---------------------

/*----------------------------------------------------------------
 * Fonction : tri_min
 * But      : Trier un tableau de 9 entiers dans l'ordre croissant.
 *
 * Paramètres :
 *    - tab : Tableau d'entiers de taille fixe (9 éléments)
 *
 * Remarques :
 *    - Utilise un tri par sélection (simple et efficace pour de petites tailles)
 *    - Principalement utilisé dans le filtre médian pour trouver la valeur médiane
 *----------------------------------------------------------------*/
 
void tri_min(int tab[9]) {
    for (int i = 0; i < 8; i++) {
        int min = i;
        for (int j = i + 1; j < 9; j++)
            if (tab[j] < tab[min]) min = j;
        if (min != i) {
            int tmp = tab[i];
            tab[i] = tab[min];
            tab[min] = tmp;
        }
    }
}

// ---------------- Filtrage Médian ---------------------

/*----------------------------------------------------------------
 * Fonction : filtre_median
 * But      : Appliquer un filtre médian 3×3 sur l'image (tableau im)
 *            et stocker le résultat dans im2.
 *
 * Principe : Pour chaque pixel (hors bords), on collecte les valeurs
 *            de ses 8 voisins + lui-même, on trie ces 9 valeurs, et
 *            on remplace le pixel central par la médiane (5e valeur).
 *
 * Paramètres :
 *    - im      : Image source.
 *    - im2     : Image résultat (filtrée).
 *    - width   : Largeur de l'image.
 *    - height  : Hauteur de l'image.
 *
 * Remarques :
 *    - Les pixels des bords ne sont pas filtrés : on les copie tels quels.
 *    - Ce filtre est particulièrement efficace contre le bruit impulsionnel
 *      (type sel et poivre), tout en préservant les contours.
 *----------------------------------------------------------------*/
 
void filtre_median(unsigned char **im, unsigned char **im2, int width, int height) {
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            int voisins[9], k = 0;
            for (int ki = -1; ki <= 1; ki++)
                for (int kj = -1; kj <= 1; kj++)
                    voisins[k++] = im[i + ki][j + kj];
            tri_min(voisins);
            im2[i][j] = voisins[4];
        }
    }
    for (int j = 0; j < width; j++) {
        im2[0][j] = im[0][j];
        im2[height - 1][j] = im[height - 1][j];
    }
    for (int i = 0; i < height; i++) {
        im2[i][0] = im[i][0];
        im2[i][width - 1] = im[i][width - 1];
    }
}

// ---------------- Sauvegarde ---------------------

/*----------------------------------------------------------------
 * Fonction : sauvegarder_image
 * But      : Sauvegarder une image en niveaux de gris (matrice 2D)
 *            dans un fichier, en conservant l'en-tête du fichier source.
 *
 * Paramètres :
 *    - nomFichier    : Nom du fichier de sortie à créer (.lena ou .pgm)
 *    - im            : Image à sauvegarder (matrice 2D de pixels)
 *    - sourceHeader  : Nom du fichier source contenant l'en-tête à copier
 *
 * Remarques :
 *    - L'en-tête (ENTETE_TAILLE octets) est copié du fichier original
 *    - L'image est écrite ligne par ligne à partir de la matrice `im`
 *    - Le fichier est ouvert en mode binaire pour éviter toute corruption
 *----------------------------------------------------------------*/
void sauvegarder_image(const char *nomFichier, unsigned char **im, const char *sourceHeader) {
    FILE *src = fopen(sourceHeader, "rb");
    FILE *dest = fopen(nomFichier, "wb");
    if (!src || !dest) return;
    for (int i = 0; i < ENTETE_TAILLE; i++) fputc(fgetc(src), dest);
    for (int i = 0; i < NB_LIGNES; i++)
        fwrite(im[i], sizeof(unsigned char), NB_COLONNES, dest);
    fclose(src);
    fclose(dest);
}

// ---------------- Bruit Poivre et Sel ---------------------

/*----------------------------------------------------------------
 * Fonction : ajouter_bruit_poivre_sel
 * But      : Ajouter un bruit aléatoire de type "poivre et sel"
 *            à une image, en copiant d'abord l'image originale.
 *
 * Paramètres :
 *    - im          : Image source (originale)
 *    - im2         : Image de destination (avec bruit ajouté)
 *    - width       : Largeur de l'image
 *    - height      : Hauteur de l'image
 *    - pourcentage : Proportion de pixels à bruiter (ex: 0.05 pour 5%)
 *
 * Remarques :
 *    - Le bruit "poivre et sel" correspond à des pixels mis à 0 (noir) ou 255 (blanc)
 *    - La graine du générateur aléatoire est initialisée avec l'heure système
 *    - L’image im2 est une copie bruitée de im (im reste inchangée)
 *----------------------------------------------------------------*/
 
void ajouter_bruit_poivre_sel(unsigned char **im, unsigned char **im2, int width, int height, float pourcentage) {
    int i, j;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            im2[i][j] = im[i][j];

    int total_pixels = width * height;
    int nb_bruit = (int)(total_pixels * pourcentage);
    srand(time(NULL));

    for (int n = 0; n < nb_bruit; n++) {
        i = rand() % height;
        j = rand() % width;
        im2[i][j] = (rand() % 2 == 0) ? 0 : 255;
    }
    printf("\u2705 Bruit ajoute dans im2 (%.2f%% des pixels).\n", pourcentage * 100);
}

