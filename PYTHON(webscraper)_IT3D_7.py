import requests
from bs4 import BeautifulSoup
import tkinter as tk
from tkinter import ttk, messagebox

#input function
def scrape_website(url, element, class_name):
    try:
        response = requests.get(url)
        response.raise_for_status()  # Check for request errors
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Extract elements based on user input
        if class_name:
            elements = soup.find_all(element, class_=class_name)
        else:
            elements = soup.find_all(element)
        
        data = [el.get_text() for el in elements]
        
        return data
    except requests.exceptions.RequestException as e:
        messagebox.showerror("Error", f"Request failed: {e}")
        return []

#output function
def show_data():
    url = entry_url.get()
    element = entry_element.get()
    class_name = entry_class.get()
    
    data = scrape_website(url, element, class_name)
    
    result_text.delete(1.0, tk.END)
    if not data:
        result_text.insert(tk.END, "No data found. Please check the URL or the structure of the website.")
    else:
        for item in data:
            result_text.insert(tk.END, f"{item}\n\n")

#gui interface
root = tk.Tk()
root.title("Flexible Web Scraper")

frame = ttk.Frame(root, padding="10")
frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

tk.Label(frame, text="Enter URL:").grid(row=0, column=0, padx=5, pady=5)
entry_url = ttk.Entry(frame, width=50)
entry_url.grid(row=0, column=1, padx=5, pady=5)

tk.Label(frame, text="HTML Element:").grid(row=1, column=0, padx=5, pady=5)
entry_element = ttk.Entry(frame, width=50)
entry_element.grid(row=1, column=1, padx=5, pady=5)

tk.Label(frame, text="Class Name:").grid(row=2, column=0, padx=5, pady=5)
entry_class = ttk.Entry(frame, width=50)
entry_class.grid(row=2, column=1, padx=5, pady=5)

scrape_button = ttk.Button(frame, text="Scrape", command=show_data)
scrape_button.grid(row=3, column=0, columnspan=2, padx=5, pady=5)

result_text = tk.Text(frame, wrap='word', height=20, width=80)
result_text.grid(row=4, column=0, columnspan=2, padx=5, pady=5)

root.mainloop()