import pandas as pd

def load_data(path):
    return pd.read_csv(path)

def clean_data(df):
    df = df.drop(columns=["Unnamed: 0"], errors="ignore")
    df = df.drop_duplicates()
    return df