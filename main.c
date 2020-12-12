/*  Tous les paramètres adjustables qui ont une influence sur l'algorithme sont des constantes
    gérés par le pré-processeur. */
#define DATA_FILE "./data/iris.data"
#define NBR_ROWS 8
#define NBR_COLUMNS 8
#define WEIGHTS_GENERATED_AROUND_X false /*  Si true alors ni MIN_VALUE_FLOAT_WEIGHT ni MIN_VALUE_FLOAT_WEIGHT ne
                                             seront utilisés. L'opposé est vrai pour INTERVAL_FROM_X. */
#define INTERVAL_FROM_X 0.2
#define MIN_VALUE_FLOAT_WEIGHT 0.1
#define MAX_VALUE_FLOAT_WEIGHT 0.5
#define N_INIT 45 /*  Exprimé ici en pourcentage. */
#define MAX_IT_PHASE_1 100 /*  Nombre d'itérations lors de l'apprentisage phase 1. */
#define MAX_IT_PHASE_2 2000 /*  10 à 100 fois plus que MAX_IT_PHASE_1 dépendant d'ALPHA_PHASE_1. */
#define ALPHA_PHASE_1 .4 /*  Taux d'apprentissage. */
#define ALPHA_PHASE_2 1.0
#define SIGMA_BEGIN .8
#define SIGMA_END .4
#define EPSILON_BEGIN .8
#define EPSILON_END .2
#define LEARNING_FUNC linear /*  choix entre linear et inverse. */
#define NEIGHBORHOOD_FUNC gaussian /*  choix entre gaussian et binary. */
#define U_MATRIX_FILE_EXPORT "SOM-IRIS-U-MATRIX.png"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

enum bool {false, true};

enum {linear, inverse};

enum {gaussian, binary};

/*  Structure de données contenant toutes les informations et meta-informations sur les vecteurs d'entrées obtenues
    de manière exploratoire lors de l'ouverture de fichiers de données. */
typedef struct InputData {
    float ** inputVectors;
    char ** vectorsToClassesMapping;
    char ** inputClassTypes;
    int totalVectors;
    int aVectorLength;
    int totalClassTypes;
} InputData;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "randomizeNumbers.h"
#include "calculateDistances.h"
#include "processEntryData.h"
#include "weightMapCreation.h"
#include "modelTraining.h"
#include "analysisTools.h"



int main () {

    /*  Seeding avec time pour que rand produise un nombre aléatoire différent à chaque appel. */
    time_t t;
    srand((unsigned) time(&t));

    /*  Prend un fichier "comma, separated" et insère les données et informations
        sur ces données dans une struc InputData. Cette dernière contiendra les
        vecteurs,le nombre total de vecteurs, la taille d'un vecteur, les classes
        qui existent dans le fichier et une correspondance une à une entre une classe
        et un vecteur. */
    InputData data = readDataFile();

    /*  On normalise tous les vecteurs d'entrée avec une norme euclidienne. */
    normalizeAllVectors(data);


    /*  On crée le treilli d'attracteurs. */
    float * map[NBR_ROWS*NBR_COLUMNS];

    /*  Et on l'initialise avec des valeurs aléatoires. */
    initializeMap(map, data);

    /*  On réalise les deux étapes d'entraînement avec un nombre d'itérations différents et des constantes
        alphas différentes. */
    trainModel(map, data, MAX_IT_PHASE_1, ALPHA_PHASE_1);

    trainModel(map, data, MAX_IT_PHASE_2, ALPHA_PHASE_2);

    /*  Afin de pouvoir analyser. */
    exportUMatrixChart(map, data);

    return 0;

}

