import qrcode
import pandas as pd
import os

def format_tel(num):
    if pd.isna(num) or not str(num).strip():
        return ''
    num = str(num).strip()
    if not num.startswith('+'):
        num = '+' + num
    return num

output_dir = 'output'
os.makedirs(output_dir, exist_ok=True)

base_url = "https://tonprojet.vercel.app/output"  # À modifier avec  un  vrai lien après hébergement

df = pd.read_csv('personnes.csv', dtype=str)

for index, row in df.iterrows():
    prenom = row['Prénom']
    nom = row['Nom']

    # Génération VCF
    vcard = f"""BEGIN:VCARD
VERSION:3.0
N:{nom};{prenom}
FN:{prenom} {nom}
TEL;TYPE=CELL:{format_tel(row['Téléphone'])}
TEL;TYPE=CELL;TYPE=HOME:{format_tel(row['Téléphone2'])}
TEL;TYPE=WhatsApp:{format_tel(row['WhatsApp'])}
EMAIL;TYPE=INTERNET:{row['Email']}
"""
    if pd.notna(row['Instagram']) and row['Instagram'].strip():
        vcard += f"X-SOCIALPROFILE;type=instagram:x-apple:{row['Instagram']}\n"
    vcard += "END:VCARD"

    vcf_filename = f"{prenom}_{nom}.vcf"
    vcf_path = os.path.join(output_dir, vcf_filename)
    with open(vcf_path, 'w', encoding='utf-8') as f:
        f.write(vcard)

    # Génération HTML
    html_content = f"""<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="UTF-8" />
<title>{prenom} {nom}</title>
<style>
  body {{
    background: linear-gradient(145deg, #3a0d0d, #000000);
    font-family: Arial, sans-serif;
    text-align: center;
    padding-top: 50px;
    color: #f0e6e6;
    text-shadow: 1px 1px 3px #660000;
  }}
  .card {{
    background: linear-gradient(145deg, #4b1a1a, #1a0000);
    display: inline-block;
    padding: 30px;
    border-radius: 20px;
    box-shadow: 8px 8px 15px #1a0000, -8px -8px 15px #6b2222;
    color: #f0e6e6;
  }}
  .card img {{
    width: 150px;
    border-radius: 10px;
    box-shadow: 3px 3px 10px #330000;
  }}
  .card h1 {{
    margin: 10px 0;
  }}
  .card button {{
    background: linear-gradient(145deg, #660000, #330000);
    border: none;
    border-radius: 10px;
    padding: 12px 25px;
    font-size: 18px;
    color: #fff0f0;
    cursor: pointer;
    box-shadow: 3px 3px 5px #220000, -3px -3px 5px #990000;
    transition: background 0.3s ease;
  }}
  .card button:hover {{
    background: linear-gradient(145deg, #330000, #660000);
  }}
</style>
</head>
<body>
<div class="card">
  <img src="{row['Photo_path']}" alt="Photo {prenom}" />
  <h1>{prenom} {nom}</h1>
  <a href="{vcf_filename}" download>
    <button>➕ Ajouter Contact</button>
  </a>
</div>
</body>
</html>"""

    html_filename = f"{prenom}_{nom}.html"
    html_path = os.path.join(output_dir, html_filename)
    with open(html_path, 'w', encoding='utf-8') as f:
        f.write(html_content)

    # Génération QR code
    url_html = f"{base_url}/{html_filename}"

    qr = qrcode.QRCode(version=None, box_size=6, border=4,
                       error_correction=qrcode.constants.ERROR_CORRECT_M)
    qr.add_data(url_html)
    qr.make(fit=True)

    qr_img = qr.make_image(fill_color="black", back_color="white").convert('RGB')
    qr_img_path = os.path.join(output_dir, f"qr_{prenom}_{nom}.png")
    qr_img.save(qr_img_path)

print("\nTous les fichiers sont dans le dossier 'output'.")
print("Héberge ce dossier sur un serveur public (Vercel, GitHub Pages, Netlify, etc.).")
print("Pense à modifier la variable 'base_url' avec le lien réel de ton site.")
