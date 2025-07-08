import fitz  # PyMuPDF
import os
import sys

def pdf_to_jpg(pdf_filename):
    data_dir = os.path.join(os.path.dirname(__file__), '..', 'data')
    pdf_path = os.path.join(data_dir, pdf_filename)
    output_dir = os.path.join(data_dir, 'pages_jpg')
    os.makedirs(output_dir, exist_ok=True)

    doc = fitz.open(pdf_path)

    for i, page in enumerate(doc):
        pix = page.get_pixmap(dpi=300)
        output_path = os.path.join(output_dir, f"page_{i:03d}.jpg")
        pix.save(output_path)
        
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 pdf_to_jpg.py <nom_du_pdf>")
        sys.exit(1)

    pdf_filename = sys.argv[1]
    pdf_to_jpg(pdf_filename)
