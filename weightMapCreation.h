/*  Les deux fonctions relatives à l'initialisation du treillis d'attracteur */
void initializeMap(float * [], InputData);
float * createVector(InputData);


/*  Après avoir initialisé le treillis avec une liste sur des pointeurs de flottants,
    on crée un vecteur pour chaque attracteur.*/
void initializeMap(float * map[NBR_ROWS*NBR_COLUMNS], InputData data) {
    for (int i=0; i< NBR_ROWS*NBR_COLUMNS; i++) {
        map[i] = createVector(data);
    }
}


/*  Ce vecteur a la même taille que les vecteurs d'entrées et a ses valeurs générées aléatoirement selon deux modalités
    possibles. Soit à partir d'un interval additionné et soustrait à la moyenne de tous les flottants composant tous
    les vecteurs d'entrées, soit dans un interval compris par les macros définis en début de programme.*/
float * createVector(InputData data) {
    float * vector = malloc(sizeof(float)*data.aVectorLength);/*  Alloue mémoire puisque taille non connue
                                                                  en début de programme */
    float meanXValue = WEIGHTS_GENERATED_AROUND_X ? getMeanXValue(data) : 0; /*  Récupère la moyenne des flottants des
                                                                                 vecteurs d'entrées seulement si la macro
                                                                                 est active */
    for (int i = 0; i < data.aVectorLength; i++) { /*  Génère nombre aléatoire, change méthode au regard de la macro*/
        vector[i] = WEIGHTS_GENERATED_AROUND_X ? generateRandomFloatWithinIntervalOfX(meanXValue) : generateRandomFloatWithinMinAndMaxValue();
    }
    return vector;
}
