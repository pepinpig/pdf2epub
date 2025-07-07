import cv2
import numpy as np
import os

input_dir = "pages_jpg"
output_dir = "pages_txt"
os.makedirs(output_dir, exist_ok=True)

# Parcourir tous les fichiers .jpg du dossier d'entrée
for filename in os.listdir(input_dir):
    if filename.lower().endswith(".jpg"):
        input_path = os.path.join(input_dir, filename)
        image = cv2.imread(input_path, cv2.IMREAD_GRAYSCALE)

        if image is None:
            print(f"Erreur : impossible de lire l'image '{input_path}' !")
            continue

        height, width = image.shape
        image_name = os.path.splitext(filename)[0]
        output_path = os.path.join(output_dir, f"{image_name}.txt")

        with open(output_path, 'w') as f:
            f.write(f"{width} {height}\n")  # dimensions en première ligne
            for row in image:
                row_str = ' '.join(map(str, row))
                f.write(row_str + '\n')

        print(f"{filename} → convertie en '{output_path}'")
