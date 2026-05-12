from src.data_preprocessing import load_data, clean_data
from src.feature_engineering import get_feature_cols, normalize_features
from src.recommender import recommend

# 1. Charger dataset
df = load_data("data/spotify.csv")

# 2. Nettoyage
df = clean_data(df)

#  3. Réduction dataset (performance)
df = df.sample(20000, random_state=42)

# 4. Features audio
feature_cols = get_feature_cols()

# 5. Normalisation
df = normalize_features(df, feature_cols)

# 🔎 6. Afficher quelques chansons disponibles
print("\n🎧 Sample songs available:")
print(df["track_name"].sample(10).values)

#  7. Chanson à tester
song = "Blinding Lights"

# 8. Recommandation sécurisée
result = recommend(song, df, feature_cols, top_n=5)

# 9. Affichage résultat
print("\n🎧 Recommendations for:", song)
print(result)