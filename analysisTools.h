/*  Toutes les fonctions qui permettent l'analyse de la carte topologique :
    On trouvera une qui imprime à la console les rangs et les colonnes avec les valeurs de chaque
    attracteur, les autres sont destinées à préparer les données pour GNUPLOT. */
void readMap(float * [], int);
void exportUMatrixChart(float * [], InputData);
void setDistanceMap(float [], float * [], int);
void setActiveAttractorsMap(float ** , float * [], InputData);
char * stringifyForGNUPLOT(float [], char * , enum bool);
int findIndexByClass(InputData, char *);


/*  Très simple, permet l'impression des vecteurs pour chaque attracteur dans la carte. */
void readMap(float * map[NBR_ROWS*NBR_COLUMNS], int aVectorLength) {
    for (int i=0; i< NBR_ROWS*NBR_COLUMNS; i++) {
        printf("row: %d column: %d\n", i/NBR_ROWS + 1, i%NBR_COLUMNS + 1);
        for (int j=0; j < aVectorLength; j++) {
            printf("%f ", map[i][j]);
        }
        printf("\n");
    }
}


/*  Crée les arguments nécessaires pour générer la visualisation à partir de GNUPLOT. Je détaille en interne les
    différentes arguments créés. */
void exportUMatrixChart(float * map[NBR_ROWS*NBR_COLUMNS], InputData data) {

    /*  Génère matrice des distances euclidiennes accumulées par rapport aux activations sur la carte (U-Matrix). */
    float averageEuclideanDistFromBMUs[NBR_ROWS*NBR_COLUMNS]={0};
    setDistanceMap(averageEuclideanDistFromBMUs, map, data.aVectorLength);
    /*  Réprésentation en chaîne de caractères pour GNUPLOT. */
    char * uMatrix = stringifyForGNUPLOT(averageEuclideanDistFromBMUs, "distances", false);

    /*  Initialise à 0 une matrice de taille classe par vecteurs d'attracteurs */
    float ** bmusPerClasses = calloc(data.totalClassTypes, sizeof(float **));
    for(int j=0; j<data.totalClassTypes; j++) {
        bmusPerClasses[j] = calloc(NBR_ROWS*NBR_COLUMNS, sizeof(float *));
    }
    /*  Itère sur toutes les entrées pour indiquer les atracteurs activés pour chaque classe. */
    setActiveAttractorsMap(bmusPerClasses, map, data);

    /*  Overkill un peu mais bon, sur une carte avec énormément de neurones, on pourrait avoir de très grandes
        définitions. */
    char variableDefinitions[131072] = {0};
    char plottingDefinition[8192] = "plot '$distances' matrix with image";

    char legendDefinition[8192] = {0};

    char variableNameBuffer[256] = {0};

    /*  On peut visualiser jusqu'jusqu'à 8 classes max. */
    char * special[] = {"○", "□", "△", "▻",  "▽", "◊", "▱", "●"};
    char * colors[] = {"yellow", "red", "blue", "purple",  "green", "orange", "pink", "brown"};

    /* Une seule itération pour définir la légende, les variables et l'initialisation de la carte avec les variables. */
    for(int i = 0; i < data.totalClassTypes; i++) {
        sprintf(variableNameBuffer, "map%d", i);

        sprintf(variableDefinitions  + strlen(variableDefinitions) , "%s\n", stringifyForGNUPLOT(bmusPerClasses[i], variableNameBuffer, true));

        sprintf(legendDefinition + strlen(legendDefinition), "set label %d at %d,0 offset 0,-%d  front '%s - %s'\n", 16+i, NBR_COLUMNS-(NBR_COLUMNS/3), 6+i, special[i], data.inputClassTypes[i]);

        sprintf(plottingDefinition + strlen(plottingDefinition), ", '$%s' matrix using 1:2:($3 == 0 ? '' : '%s')  with labels font ',25' tc rgb '%s'", variableNameBuffer, special[i], colors[i]);
    }
    strcat(plottingDefinition, "\n");

    /*  Rappel des paramètres d'entrées pour la génération de la carte. */

    /*  Nom du fichier de sortie */
    char fileExport[256];
    sprintf(fileExport, "set output '%s'", U_MATRIX_FILE_EXPORT);

    /*  Echelle du plan. */
    char xrange[256];
    sprintf(xrange, "set xrange [ -0.5 : %d.50000 ] noreverse nowriteback", NBR_COLUMNS-1);

    char yrange[256];
    sprintf(yrange, "set yrange [ -0.5 : %d.50000 ] noreverse nowriteback", NBR_ROWS-1);

    char weightsGeneratedAroundX[256];
    sprintf(weightsGeneratedAroundX, "set label 1 at 0,0 offset -2,-5  front 'weights generated around x: %s'", WEIGHTS_GENERATED_AROUND_X ? "true" : "false");

    char intervalFromX[256];
    if(WEIGHTS_GENERATED_AROUND_X){
        sprintf(intervalFromX, "set label 2 at 0,0 offset -2,-6  front 'interval from x: %.2f'", INTERVAL_FROM_X);
    }
    else {
        strcpy(intervalFromX, "set label 2 at 0,0 offset -2,-6  front 'interval from x: N/A'");
    }


    char minValueFloatWeight[256];
    if(WEIGHTS_GENERATED_AROUND_X){
        strcpy(minValueFloatWeight, "set label 3 at 0,0 offset -2,-7  front 'min value float weight: N/A");
    }
    else {
        sprintf(minValueFloatWeight, "set label 3 at 0,0 offset -2,-7  front 'min value float weight: %.2f'", MIN_VALUE_FLOAT_WEIGHT);
    }

    /*  Rappel de toutes les valeurs d'entrées */
    char maxValueFloatWeight[256];
    if(WEIGHTS_GENERATED_AROUND_X){
        strcpy(maxValueFloatWeight, "set label 4 at 0,0 offset -2,-8  front 'max value float weight: N/A'");
    }
    else {
        sprintf(maxValueFloatWeight, "set label 4 at 0,0 offset -2,-8  front 'max value float weight: %.2f'", MAX_VALUE_FLOAT_WEIGHT);
    }


    char nInit[256];
    sprintf(nInit, "set label 5 at 0,0 offset -2,-9  front 'N Init: %d/100'", N_INIT);

    char maxItPhase1[256];
    sprintf(maxItPhase1, "set label 6 at 0,0 offset -2,-10  front 'max it phase 1: %d'", MAX_IT_PHASE_1);

    char maxItPhase2[256];
    sprintf(maxItPhase2, "set label 7 at 0,0 offset -2,-11  front 'max it phase 2: %d'", MAX_IT_PHASE_2);

    char alphaPhase1[256];
    sprintf(alphaPhase1, "set label 8 at 0,0 offset -2,-12  front 'alpha phase 1: %.2f'", ALPHA_PHASE_1);

    char alphaPhase2[256];
    sprintf(alphaPhase2, "set label 9 at 0,0 offset -2,-13  front 'alpha phase2: %.2f'", ALPHA_PHASE_2);

    char sigmaBegin[256];
    sprintf(sigmaBegin, "set label 10 at 0,0 offset -2,-14  front 'sigma begin: %.2f'", SIGMA_BEGIN);

    char sigmaEnd[256];
    sprintf(sigmaEnd, "set label 11 at 0,0 offset -2,-15  front 'sigma end: %.2f'", SIGMA_END);

    char epsilonBegin[256];
    sprintf(epsilonBegin, "set label 12 at 0,0 offset -2,-16  front 'epsilon begin: %.2f'", EPSILON_BEGIN);

    char epsilonEnd[256];
    sprintf(epsilonEnd, "set label 13 at 0,0 offset -2,-17  front 'epsilon end: %.2f'", EPSILON_END);

    char learningFunction[256];
    sprintf(learningFunction, "set label 14 at 0,0 offset -2,-18  front 'learning function: %s'", LEARNING_FUNC ? "inverse time" : "linear time");

    char neighborhoodFunction[256];
    sprintf(neighborhoodFunction, "set label 15 at 0,0 offset -2,-19  front 'neighborhood function: %s'", NEIGHBORHOOD_FUNC ? "binary" : "gaussian");

    /* Vecteurs avec tous les arguments */
    char * commandsForGnuplot[] = {"set term png enhanced font 'Arial Unicode MS,15' size 800, 950",
                                   fileExport,
                                   "unset key",
                                   "set view map",
                                   "set xtics border in scale 0,0 mirror norotate  offset character 0, 0, 0 autojustify",
                                   "set ytics border in scale 0,0 mirror norotate  offset character 0, 0, 0 autojustify",
                                   "set ztics border in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify",
                                   "set nocbtics",
                                   "set rtics axis in scale 0,0 nomirror norotate  autojustify",
                                   "set title 'U-matrix avec BMUs listés'",
                                   xrange,
                                   "set x2range [ * : * ] noreverse writeback",
                                   yrange,
                                   "set y2range [ * : * ] reverse writeback",
                                   "set zrange [ * : * ] reverse writeback",
                                   "set cblabel 'Score'",
                                   "set cbrange [ 0 : 1 ] noreverse nowriteback",
                                   "set rrange [ * : * ] reverse nowriteback",
                                   "set pal gray",
                                   weightsGeneratedAroundX,
                                   intervalFromX,
                                   minValueFloatWeight,
                                   maxValueFloatWeight,
                                   nInit,
                                   maxItPhase1,
                                   maxItPhase2,
                                   alphaPhase1,
                                   alphaPhase2,
                                   sigmaBegin,
                                   sigmaEnd,
                                   epsilonBegin,
                                   epsilonEnd,
                                   learningFunction,
                                   neighborhoodFunction,
                                   legendDefinition,
                                   "set bmargin 19",
                                   uMatrix,
                                   variableDefinitions,
                                   plottingDefinition
    };

    /*  Ouverture par piping de gnuplot puis passe tous les arguments. */
    FILE * gnuplotPipe = popen ("gnuplot", "w");
    for (int i=0; i < sizeof(commandsForGnuplot)/ sizeof(char *); i++){
        printf("%s \n", commandsForGnuplot[i]); //si nécessaire pour débuguer.
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
    }
}


/*  Modifie par référence une matrice de taille de la carte qui permettra la génération d'une heatmap (U-Matrix)
    en prenant le BMU et en additionnant les distances euclidiennes du voisinage immédiat vis-à-vis de ce BMU.
    Ainsi, nous pourrons voir les attracteurs creux et pleins (attention, c'est relatif à l'attracteur qui a enregistré
    la plus grande distance cumulée). */
void setDistanceMap(float averageEuclideanDistFromBMUs[], float * map[NBR_ROWS*NBR_COLUMNS], int aVectorLength) {
    float elToScaleTo = 0;
    int i;
    for(i = 0; i < NBR_ROWS * NBR_COLUMNS; i++) {
        for (int j = 0; j < NBR_ROWS * NBR_COLUMNS; j++) {
            if (getDnode(i, j) < 1.5) { //1.44 pour le voisinage immédiat si on veut vraiment être précis
                averageEuclideanDistFromBMUs[i] += getDWeight(map[i], map[j], aVectorLength);
            }
        }
        if(elToScaleTo<averageEuclideanDistFromBMUs[i]) {
            elToScaleTo = averageEuclideanDistFromBMUs[i];
        }
    }

    for(i = 0; i < NBR_ROWS * NBR_COLUMNS; i++) {
        averageEuclideanDistFromBMUs[i] /= elToScaleTo;
    }
}


/*  Itère sur les données d'entrée pour l'obtention des BMUs, récupère le nom de la classe associée, son index
        pour placer un 1 dans le vecteur créé ci-dessus. */
void setActiveAttractorsMap(float ** bmusPerClasses, float * map[NBR_ROWS*NBR_COLUMNS], InputData data) {
    for(int i = 0 ; i < data.totalVectors; i++) {
        int BMU = getBMU(map, data.inputVectors[i], data.aVectorLength);
        char * inputClassOfVector = data.vectorsToClassesMapping[i];
        int classTypeListIdx = findIndexByClass(data, inputClassOfVector);

        /*  Problème si classe non présente dans le vecteur des classes - fichier d'entrée avec classe non-labélisée. */
        if(classTypeListIdx == -1){
            perror("Erreur avec les classes du fichier.");
        }
        else {
            /*  Activation binaire, 1 pour un attracteur activé, sinon 0, pour l'indice de la classe. */
            bmusPerClasses[classTypeListIdx][BMU] = 1;
        }
    }
}


/*  Petite fonction utilitaire qui récupère l'index de la classe dans le vecteur qui contient toutes les classes
    Nécessaire pour générer une les vecteurs d'activation pour chaque classe. */
int findIndexByClass(InputData data, char * aString) {
    for(int i = 0 ; i < data.totalClassTypes; i++) {
        if (strcmp(data.inputClassTypes[i], aString) == 0) {
            return i;
        }
    }
    return -1;
}


/*  Transforme les divers matrices en chaînes préformatées en tableaux prêtes à être passées en argument de GNUPLOT. On
    s'en servira pour imprimer les classes ainsi que la heatmap. Je me donne énormément de mémoire afin de pouvoir
    générer de très grandes cartes. Dans l'idéal, il faudrait générer dynamiquement la taille des buffers à partir du
    nombre de colonnes et de rangs. Ici, ce n'est pas nécesssaire. Peut générer des représentations en entier ou
    décimales. */
char * stringifyForGNUPLOT(float anArrayOfFloat[], char * name , enum bool toInt) {
    char buffer[65536] = {0}; //
    sprintf(buffer, "$%s << EOD", name);
    for(int i = 0; i<NBR_ROWS * NBR_COLUMNS;i++) {
        if(i%NBR_ROWS == 0) {
            strcat(buffer, "\n");
        }
        if(toInt) {
            sprintf(buffer + strlen(buffer), "%d ", (int)anArrayOfFloat[i]);
        }
        else {
            sprintf(buffer + strlen(buffer), "%f ", (float)anArrayOfFloat[i]);
        }
    }
    strcat(buffer, "\nEOD");
    return strdup(buffer);
}