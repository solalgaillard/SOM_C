/*  Fonction organisatrice des données en entrée prise sur fichier. */
InputData readDataFile();
/*  Ouvre le fichier présenté dans la macro. Initialise la structure InputData qui gardera toutes les infos sur les
    vecteurs d'entrées. La taille d'un vecteur est obtenu dynamiquement et sera utilisé pour générer les vecteurs
    des attracteurs de la carte */
InputData readDataFile() {
    FILE *f = fopen(DATA_FILE, "r");
    if (f == NULL) {
        perror("Erreur de lecture fichier.");
    }

    InputData data;
    data.inputVectors = NULL;
    data.vectorsToClassesMapping = NULL;
    data.inputClassTypes = NULL;
    data.totalVectors = 0;
    data.aVectorLength = 0;
    data.totalClassTypes = 0;

    /*  Nécessaire à chaque itération. */
    char line[1024];
    char * token;
    int i;
    int j;
    int classAlreadyInList;
    int resultSscanf;
    char inputClass[256];



    while (fgets(line, 1024, f) != NULL) {

        /*  Sépare les valeurs. */
        token = strtok(line, ",");
        i = 0;
        j = 0;
        float * vector = NULL;
        void * tmpPtrReallocValid1;
        void * tmpPtrReallocValid2;

        /*  Utilisation de strtok et sscanf pour récupérer  les flottants. Réalloue mémoire à chaque flottant rencontré
            pour le mettre dans le vecteur. */
        while (token != NULL) {
            tmpPtrReallocValid1 = realloc(vector, sizeof(float *) * (i + 1));
            /*  Vérification réallocation fonctionne. */
            if (tmpPtrReallocValid1 == NULL) {
                perror("Erreur allocation mémoire");
            }
            vector = tmpPtrReallocValid1;

            /*  Essaie de récupérer un flottant */
            resultSscanf = sscanf(token, "%f", &vector[i]);
            if (resultSscanf != 1) { /*  En cas d'échec, c'est qu'il s'agit d'un label. */
                resultSscanf = sscanf(token, "%s", inputClass);
                if (resultSscanf != 1) { /*  Le fichier doit contenir une classe pour chaque vecteur .*/
                    perror("Erreur, données mal préparées");
                }
            }
            else {
                i++; /*  On incrémente la taille du vecteur */
            }
            token = strtok (NULL, ","); /*  Et on continue sur le prochain token. */
        }
        /*  Réalloue de la place sur la struct InputData pour y mettre la classe et le vecteur */
        tmpPtrReallocValid1 = realloc(data.inputVectors, sizeof(float *) * (data.totalVectors + 1));
        tmpPtrReallocValid2 = realloc(data.vectorsToClassesMapping, sizeof(char *) * (data.totalVectors + 1));
        if (tmpPtrReallocValid1 == NULL || tmpPtrReallocValid2 == NULL) {
            perror("Erreur allocation mémoire");
        }

        /*  Assigne vecteur et la classe et augmente le nombre total de vecteur. */
        data.inputVectors = tmpPtrReallocValid1;
        data.inputVectors[data.totalVectors] = vector;
        data.vectorsToClassesMapping = tmpPtrReallocValid2;
        data.vectorsToClassesMapping[data.totalVectors++] = strdup(inputClass);


        /*  Regarde si la classe doit être assigné à la liste de classe. */
        classAlreadyInList = false;

        /*  Itère sur la liste et si on trouve, on tourne le flag classAlreadyInList à true*/
        while(j!= data.totalClassTypes) {
            if(strcmp(data.inputClassTypes[j], inputClass) == 0) {
                classAlreadyInList = true;
                  break;
            }
            j++;
        }


        /*  Assigne classe si on rencontre la classe pour la première fois. */
        if(!classAlreadyInList) {
            tmpPtrReallocValid1 = realloc(data.inputClassTypes, sizeof(char *) * (data.totalClassTypes + 1));
            if (tmpPtrReallocValid1 == NULL) {
                perror("Erreur allocation mémoire");
            }
            data.inputClassTypes = tmpPtrReallocValid1;
            data.inputClassTypes[data.totalClassTypes++] = strdup(inputClass);
        }



        /* Mesure de sécurité, on vérifie que tous les vecteurs on la même taille.*/
        if(!data.aVectorLength) {
            data.aVectorLength = i;
        }
        else if(data.aVectorLength != i) {
            perror("Erreur, données mal préparées");
        }
    }

    data.totalVectors--; /* Dernière itération à une incrémentation en trop. */
    return data;
}