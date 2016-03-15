import Tkinter as tk

def remove_default_text(self,entry):
	if entry.clicked==False:
		entry.delete(0,tk.END)
		entry.config(fg="black")
		entry.clicked=True


