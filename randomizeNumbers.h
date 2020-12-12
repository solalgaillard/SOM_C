/*   Toutes les fonctions relatives à la création de nombres aléatoires */
int generateRandomIntUpToIncludedValue(int);
float generateRandomFloatWithinMinAndMaxValue();
float generateRandomFloatWithinIntervalOfX(float);

/*  Génère un nombre entier entre 0 et le nombre donné en argument (inclu) */
int generateRandomIntUpToIncludedValue(int maxValue) {
    return rand() % (maxValue+1);
}

/*  Génère un flottant entre une valeur minimale et une valeur maximale (non-incluses) définies par des macros */
float generateRandomFloatWithinMinAndMaxValue() {
    if (MAX_VALUE_FLOAT_WEIGHT == MIN_VALUE_FLOAT_WEIGHT) {
        return MIN_VALUE_FLOAT_WEIGHT;
    }
    else if (MIN_VALUE_FLOAT_WEIGHT < MAX_VALUE_FLOAT_WEIGHT) {
        return (MAX_VALUE_FLOAT_WEIGHT - MIN_VALUE_FLOAT_WEIGHT) * ((float)rand() / RAND_MAX) + MIN_VALUE_FLOAT_WEIGHT;
    }
    return -1;
}

/*  Génère un flottant dans un interval donné par une macro à partir de la valeur prise en argument
    (la moyenne de chaque vecteur de données en entrée) */
float generateRandomFloatWithinIntervalOfX(float meanXValue) {
    return (meanXValue + INTERVAL_FROM_X - (meanXValue - INTERVAL_FROM_X)) * ((float) rand() / RAND_MAX) + (meanXValue - INTERVAL_FROM_X);
}