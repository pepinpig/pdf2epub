# OCR-EPUB : un moteur OCR pour convertir des PDF en EPUB structurés

**Statut** : Projet en cours de développement — version instable  
**Objectif** : Développer un OCR open-source capable de convertir des documents PDF scannés (livres, articles) en fichiers EPUB avec une **structure logique conservée** (titres, corps du texte, notes de bas de page, etc.)

---

## Objectifs

Ce projet vise à :
- Convertir un **PDF scanné** en **images haute résolution**
- Appliquer une **segmentation par régions** pour identifier :
  - le corps principal du texte
  - les titres de chapitres
  - les notes de bas de page
  - les numéros de pages
- Effectuer une **reconnaissance optique de caractères (OCR)**
- Reconstituer le **texte structuré** en EPUB (chapitres, paragraphes, notes)

---

## 🔧 Structure prévue du projet
ocr-epub/
├── data/ # PDF source, images extraites, annotations
├── src/ # Code source Python ou C
├── tests/ # Scripts de test et validation
├── results/ # Sorties texte et EPUB générés
├── Makefile # Compilation automatisée
├── README.md # Présent fichier
├── LICENCE
└── requirements.txt # Dépendances Python 


---

## Technologies envisagées

- Python / C pour le traitement d’image
- Clustering (K-means / HAC) pour la segmentation par régions
- OCR maison (à affiner)
- Export final au format **EPUB** (à affiner)

---

## Avancement

| Étape                                 | Statut     |
|--------------------------------------|------------|
| Extraction des images depuis PDF     | ✅ Fait     |
| Pré-traitement et binarisation       | ✅ En cours |
| Segmentation des régions             | 🔧 À venir |
| OCR et reconnaissance des caractères | 🔧 À venir |
| Génération d’un EPUB structuré       | 🔧 À venir |

---

## Contribuer

Ce projet est en développement actif. Toute contribution, idée ou retour est bienvenu.  
Tu peux ouvrir une **issue** ou une **pull request**.

---

## Licence

Ce projet est distribué sous licence MIT.  
Voir le fichier [LICENSE](./LICENSE) pour plus d'informations.