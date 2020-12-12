/*  Toutes les fonctions relatives aux calculs de distances, de poids des attracteurs, et de normalisations des
    vecteurs */
float getMeanXValue(InputData);
float getDWeight(float [], float *, int);
float getDnode(int, int);
int getBMU(float * [], float *, int);


/*  Obtient la moyenne de toutes les valeurs présentes dans les vecteurs d'entrées(utile lors de l'initialisation
    des vecteurs de chaque attracteur). */
float getMeanXValue(InputData data) {
    float meanXValue = 0;
    for(int i=0; i<data.totalVectors; i++) {
        for(int j=0; j<data.aVectorLength; j++) {
            meanXValue += data.inputVectors[i][j];
        }
    }
    return meanXValue/(data.totalVectors*data.aVectorLength);
}


/*  Calcul de la distance euclidienne entre deux vecteurs. */
float getDWeight(float weightVectorJ[], float * inputVector, int aVectorLength){
    float sum = 0;
    for (int i=0; i < aVectorLength; ++i) {
        sum += powf(inputVector[i] - weightVectorJ[i],2);
    }
    return sqrtf(sum);
}


/*  Calcul de la distance de voisinage entre deux attracteurs. */
float getDnode(int jIndex, int jStarIndex){
    return sqrtf(powf(jIndex/NBR_ROWS - jStarIndex/NBR_ROWS,2) + powf(jIndex%NBR_COLUMNS - jStarIndex%NBR_COLUMNS,2));
}


/*  Calcul de la norme euclidiennee. */
float getEuclidNorm(float * x, int vectorLength) {
    float sum = 0;
    for (int i=0; i < vectorLength; i++) {
        sum += powf(x[i],2);
    }
    return sqrtf(sum);
}


/*  Normalisation d'un vecteur par une norme */
void normalizeAVector(float norm, float * x, int vectorLength) {
    for (int i = 0; i < vectorLength; i++) {
        x[i] = x[i]/norm;
    }
}


/* Normalisation d'une matrice par norme euclidienne */
void normalizeAllVectors(InputData data) {
    float euclidNormResult;
    for (int i = 0; i < data.totalVectors; i++) {
        euclidNormResult = getEuclidNorm(data.inputVectors[i], data.aVectorLength);
        normalizeAVector(euclidNormResult, data.inputVectors[i], data.aVectorLength);
    }
}


/*  Obtention de l'index du BMU selon le calcul de la distance euclidienne. Pour éviter les effets de tassement
    en début de carte lorsqu'il y a une égalité, je garde une liste de tous les attracteurs activés avec un compteur
    qui me dit combien sont activés puis génère un accès aléatoire à l'index de cette liste. */
int getBMU(float * map[NBR_ROWS*NBR_COLUMNS], float * inputVector, int aVectorLength) {

    float prevEuclidDistance = getDWeight(map[0], inputVector, aVectorLength);
    float currentEuclidDistance;
    int allActivatedAttractors[NBR_ROWS*NBR_COLUMNS] = {0};
    int countEqualities = 0;

    for(int i = 1; i < NBR_ROWS*NBR_COLUMNS; i++) {
        if(prevEuclidDistance >= (currentEuclidDistance = getDWeight(map[i], inputVector, aVectorLength))) {
            if(prevEuclidDistance == currentEuclidDistance) {
                allActivatedAttractors[++countEqualities] = i;
            }
            else {
                prevEuclidDistance=currentEuclidDistance;
                allActivatedAttractors[0] = i;
                countEqualities = 0;
            }
        }
    }
    if (countEqualities) {
        return allActivatedAttractors[generateRandomIntUpToIncludedValue(countEqualities)];
    }
    return allActivatedAttractors[0];
}