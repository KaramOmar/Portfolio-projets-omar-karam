def print_recommendations(df):
    for _, row in df.iterrows():
        print(f"{row['track_name']} - {row['artists']}")