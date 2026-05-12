from sklearn.metrics.pairwise import cosine_similarity
import numpy as np

def recommend(song_name, df, feature_cols, top_n=5):

    #  trouver la chanson
    matches = df[df["track_name"] == song_name]

    if matches.empty:
        return f" Song '{song_name}' not found in dataset"

    idx = matches.index[0]

    #  genre
    genre = df.loc[idx, "track_genre"]

    #  filtre genre + nettoyage énergie (amélioration)
    df_filtered = df[
        (df["track_genre"] == genre) &
        (df["energy"] > 0.3)
    ].copy()

    #  vecteur chanson cible
    song_vector = df.loc[idx, feature_cols].values.reshape(1, -1)

    #  similarité cosine
    similarities = cosine_similarity(song_vector, df_filtered[feature_cols])[0]

    #  score hybride (similarité + popularité)
    final_score = (
        similarities * 0.7 +
        df_filtered["popularity"].values * 0.3
    )

    #  top recommandations
    top_indices = final_score.argsort()[::-1][1:top_n+1]

    return df_filtered.iloc[top_indices][["track_name", "artists", "track_genre"]]