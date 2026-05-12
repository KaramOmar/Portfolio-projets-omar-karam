from sklearn.preprocessing import MinMaxScaler

def get_feature_cols():
    return [
        "danceability",
        "energy",
        "valence",
        "tempo",
        "acousticness",
        "instrumentalness",
        "loudness",
        "speechiness",
        "popularity"
    ]

def normalize_features(df, feature_cols):
    scaler = MinMaxScaler()
    df[feature_cols] = scaler.fit_transform(df[feature_cols])
    return df