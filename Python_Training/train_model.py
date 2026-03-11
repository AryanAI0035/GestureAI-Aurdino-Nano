import pandas as pd
import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from micromlgen import port

# --- 1. CONFIGURATION ---
# We are capturing 10 readings per second (100ms delay in Arduino).
# A swipe takes about 0.6 to 1 seconds. So, our "window" is 8 rows.
WINDOW_SIZE = 8 
FILES = {
    "idle.csv": 0,
    "push_in.csv": 1,
    "swipe_left.csv": 2,
    "swipe_right.csv": 3
}

def create_windows(data, window_size):
    """ Converts a continuous stream of data into overlapping time windows """
    windows = []
    # Slide over the data, grabbing chunks of 'window_size'
    for i in range(len(data) - window_size):
        window = data.iloc[i : i + window_size].values.flatten()
        windows.append(window)
    return np.array(windows)

# --- 2. DATA INGESTION & PREPROCESSING ---
print("Loading and Windowing Data...")
X_all = []
y_all = []

for filename, label in FILES.items():
    try:
        # Read CSV, ignoring any malformed lines
        df = pd.read_csv(filename, on_bad_lines='skip')
        
        # Ensure we only grab our 3 columns in case of empty spaces
        df = df.iloc[:, :3] 
        
        # Create sliding windows
        X_windows = create_windows(df, WINDOW_SIZE)
        y_labels = np.full(X_windows.shape[0], label)
        
        X_all.append(X_windows)
        y_all.append(y_labels)
        print(f"  -> Extracted {len(X_windows)} windows from {filename}")
        
    except FileNotFoundError:
        print(f"CRITICAL ERROR: Cannot find {filename}. Make sure it is in the same folder!")
        exit()

# Stack all the lists into a single master dataset
X = np.vstack(X_all)
y = np.concatenate(y_all)

# --- 3. TRAIN / TEST SPLIT ---
# We hold back 20% of the data. The AI will NEVER see this during training.
# We use this at the end to test if it actually learned, or if it just memorized the data.
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# --- 4. MODEL TRAINING ---
print("\nTraining Decision Tree")
# max_depth=6 restricts how deep the if/else statements can go, saving massive memory!
clf = DecisionTreeClassifier(max_depth=8, random_state=42)
clf.fit(X_train, y_train)

# --- 5. EVALUATION ---
print("\n--- MODEL BENCHMARK RESULTS ---")
y_pred = clf.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
print(f"Overall Accuracy: {accuracy * 100:.2f}%\n")

print("Confusion Matrix (How often did it confuse Left for Right?):")
print(confusion_matrix(y_test, y_pred))

print("\nDetailed Classification Report:")
target_names = ["0: Idle", "1: Push In", "2: Swipe Left", "3: Swipe Right"]
print(classification_report(y_test, y_pred, target_names=target_names))


# --- 6. C++ EXPORT (TINYML) ---
print("\nExporting model to raw C++ header...")
# We use micromlgen to compile the Random Forest into Arduino C++
c_code = port(clf, classmap={0: "Idle", 1: "Push In", 2: "Swipe Left", 3: "Swipe Right"})

# Save it to a file
with open("GestureModel.h", "w") as file:
    file.write(c_code)

print("SUCCESS! Saved 'GestureModel.h'. This is the brain we will upload to the Arduino.")
