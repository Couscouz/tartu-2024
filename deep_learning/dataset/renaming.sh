#!/bin/bash

# Vérifier si un argument est fourni
if [ $# -ne 2 ]; then
    echo "Usage: $0 <arg1>"
    exit 1
fi

# Assigner le premier argument à une variable
arg1="$1" #path to folder
arg2="$2" #classname

# Vérifier si le répertoire existe
if [ ! -d "$arg2" ]; then
    echo "Le répertoire $arg1 n'existe pas."
    exit 1
fi

# Compteur pour les nouveaux noms de fichiers
i=0

for file in "$arg1"/*.jpg; do
    # Construire le nouveau nom de fichier
    new_name="${arg1}/temp_${i}.jpg"
    # Renommer le fichier
    mv "$file" "$new_name"
    # Incrémenter le compteur
    ((i++))
done

i=0

# Parcourir tous les fichiers JPG dans le répertoire
for file in "$arg1"/*.jpg; do
    # Construire le nouveau nom de fichier
    new_name="${arg1}/${arg2}_${i}.jpg"
    # Renommer le fichier
    mv "$file" "$new_name"
    #echo $file
    #echo $new_name
    # Incrémenter le compteur
    ((i++))
done

echo "Renommage terminé."
