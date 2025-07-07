import fitz  # PyMuPDF
import os

pdf_path = "extrait.pdf"
output_dir = "pages_jpg"
os.makedirs(output_dir, exist_ok=True)

doc = fitz.open(pdf_path)

for i, page in enumerate(doc):
    # Générer l'image de la page entière (pas de "clip")
    pix = page.get_pixmap(dpi=300)
    output_path = os.path.join(output_dir, f"page_{i:03d}.jpg")
    pix.save(output_path)