import tkinter as tk
from tkinter import filedialog

def select_arduino_file():
    root = tk.Tk()
    root.withdraw()  # we don't want a full GUI, so keep the root window from appearing
    file_path = filedialog.askopenfilename(
        initialdir="C:/Users/matty/Documents/Arduino/projects",
        title="Select file",
        filetypes=(("Arduino Files", "*.ino"), ("All files", "*.*"))
    )
    return file_path

if __name__ == "__main__":
    selected_file = select_arduino_file()
    if selected_file:
        print(selected_file)  # This will be captured by the batch script
