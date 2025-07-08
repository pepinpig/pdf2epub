import cv2
import numpy as np
import os

def images_to_txt():
    base_dir = os.path.join(os.path.dirname(__file__), '..', 'data')
    input_dir = os.path.join(base_dir, 'pages_jpg')
    output_dir = os.path.join(base_dir, 'pages_txt')
    os.makedirs(output_dir, exist_ok=True)

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
                f.write(f"{height} {width}\n")  # dimensions en première ligne
                for row in image:
                    row_str = ' '.join(map(str, row))
                    f.write(row_str + '\n')


if __name__ == "__main__":
    images_to_txt()
