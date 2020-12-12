/*  Toutes les fonctions relatives à l'apprentissage du modèle par la carte. */
void trainModel(float * [], InputData, int, float);
void mapReorganizing(float * [], float *, int, int, int, int, float);
void modifyWeights(float, float [], int, float *, int, int, float);
float getH(float, int, int);
float processSigmaOrEpsilon(float, float, int, int);
float linearTime(int, int);
float inverseTime(int, int);


/*  Fonction pilote, elle prend la carte, calcul les BMUS pour chaque entrée et réorganise la carte. Elle recommence
    pour un nombre d'itérations passé en argument. */
void trainModel(float * map[NBR_ROWS*NBR_COLUMNS], InputData data, int tTotal, float alpha) {
    for (int t = 1; t<=tTotal; t++) {
        for(int i = 0; i<data.totalVectors;i++){
            int currentBmu = getBMU(map, data.inputVectors[i], data.aVectorLength);
            mapReorganizing(map, data.inputVectors[i], data.aVectorLength, currentBmu, t, tTotal, alpha);
        }
    }
}


/*  Fonction pour réorganiser la carte. Calcul de la taille du voisinage de manière linéaire en fonction de
    l'itération en cours et du nombre total d'itération (en fonction de N_INIT aussi évidemment). Calcul de la distance
    de voisinage entre l'attracteur activé et les autres atracteurs. On modifira les poids des vecteurs des attracteurs
    seulement si la taille de voisinage est supérieur à la distance de voisinage entre BMU et autre attracteur. */
void mapReorganizing(float * map[NBR_ROWS*NBR_COLUMNS], float * anInputVector, int aVectorLength, int bmu, int t, int tTotal, float alpha) {
    float NSize = MAX(NBR_ROWS, NBR_COLUMNS)*(N_INIT/100.)*linearTime(t, tTotal);
    for (int j = 0; j < NBR_ROWS * NBR_COLUMNS; j++) {
        float dNode = getDnode(j, bmu);
        if (dNode < NSize) {
            modifyWeights(dNode, map[j], aVectorLength, anInputVector, t, tTotal, alpha);
        }
    }
}


/*  Ici, on modifie les poids de chaque flottants dans le vecteur d'un attracteur. Il y a deux paramètres qui rentrent
    en jeu et que l'on peut modifier. Premièrement, nous pouvons choisir d'avoir une fonction de voisinage binaire
    ou gaussienne. Binaire veut dire que cette fonction n'est pas prise en compte pour la modification des poids.
    Gaussienne, nous prenons en compte sigma, epsilon, et la distance de voisinage afin de créer un effet d'inhibation
    si l'attracteur est distant du BMU (bordure de voisinage) et devient un exposant dans le calcul de poids.
    Ensuite, nous pouvons choisir une fonction d'aprentissage linéaire ou inverse du temps. */
void modifyWeights(float dNode, float weightVector[], int aVectorLength, float * inputVector, int t, int tTotal, float alpha) {
    float hResult = NEIGHBORHOOD_FUNC == gaussian ? getH(dNode, t, tTotal) : 1;
    for(int i = 0; i<aVectorLength; i++) {
        weightVector[i] = weightVector[i] + (alpha * (LEARNING_FUNC == linear ? linearTime(t, tTotal) : inverseTime(t, tTotal)) ) * hResult  * (inputVector[i] - weightVector[i]);
    }
}


/*  Fonction de voisinage en fonction de sigmaT, epislonT et de dNode. */
float getH(float dNode, int t, int tTotal) {
    float epsilonT = processSigmaOrEpsilon(EPSILON_BEGIN, EPSILON_END, t, tTotal);
    float sigmaT = processSigmaOrEpsilon(SIGMA_BEGIN, SIGMA_END, t, tTotal);
    return epsilonT*expf(-(powf(dNode,2)/(2*powf(sigmaT,2))));
}


/*  Calcul de sigma ou epsilon en fonction de l'itération et de leurs valeurs initiales et finales respectives. */
float processSigmaOrEpsilon(float valueInit, float valueEnd, int t, int tTotal) {
    return valueInit*powf(valueEnd/valueInit,((float)t/tTotal));
}


/*  Fonction d'apprentissage linéaire. */
float linearTime(int t, int tTotal) {
    return (1-((float)t/tTotal));
}


/*  Fonction d'apprentissage en inverse du temps. */
float inverseTime(int t, int tTotal) {
    return tTotal/100./ (tTotal/100. + t);
}