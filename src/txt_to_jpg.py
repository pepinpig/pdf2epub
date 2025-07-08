import cv2
import numpy as np
import os

def txt_to_image(input_filename):
    base_dir = os.path.join(os.path.dirname(__file__), '..', 'data')
    input_path = os.path.join(base_dir, 'pages_txt', input_filename)
    output_dir = os.path.join(base_dir, 'pages_reconstruites')
    os.makedirs(output_dir, exist_ok=True)

    if not input_filename.lower().endswith(".txt"):
        print(f"Erreur : le fichier '{input_filename}' n'est pas un fichier .txt")
        return

    if not os.path.exists(input_path):
        print(f"Erreur : fichier introuvable '{input_path}'")
        return

    with open(input_path, 'r') as f:
        lines = f.readlines()

    if not lines:
        print(f"Erreur : fichier vide '{input_path}'")
        return

    try:
        height, width = map(int, lines[0].strip().split())
        pixel_lines = lines[1:]

        if len(pixel_lines) != height:
            print(f"Erreur : nombre de lignes incorrect dans '{input_filename}'")
            return

        image_array = []
        for line in pixel_lines:
            row = list(map(float, line.strip().split()))
            if len(row) != width:
                print(f"Erreur : largeur incorrecte dans '{input_filename}'")
                return
            image_array.append(row)

        image_np = np.round(np.array(image_array)).astype(np.uint8)
        output_filename = os.path.splitext(input_filename)[0] + '.jpg'
        output_path = os.path.join(output_dir, output_filename)
        cv2.imwrite(output_path, image_np)
        print(f"{input_filename} → reconstruit en '{output_path}'")
    except Exception as e:
        print(f"Erreur lors de la lecture de '{input_filename}': {e}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage : python script.py nom_fichier.txt")
    else:
        txt_to_image(sys.argv[1])
