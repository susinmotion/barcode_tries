# MyApp.py
import Tkinter as tk
from ROI import ROI
#from Tkinter import Label, Button, Frame, Entry, END
# Extend the Frame class, to inherit
# the mainloop function.
class MyApp(tk.Frame):
	def __init__ (self, master = None):
   		# Construct the Frame object.
		tk.Frame.__init__ (self, master)
		self.pack()
		self.bind("<Configure>", self.on_resize)
		self.mainLabel = tk.Label(self, text = "MDS Parameters", font=("calibri", 20), fg="red")
	   	self.mainLabel.pack(pady=20)

	   	self.zipped=tk.BooleanVar()
	   	tk.Checkbutton(self, text="My data is zipped",variable=self.zipped).pack(pady=(0,10))


	   	self.filenameslabel=tk.Label(self, text="filenames, comma separated")
	   	self.filenameslabel.pack()
	   	self.filenames = tk.Entry(self, fg="gray")
	   	self.filenames.insert(tk.END, 'eg. 20160210.fastq.gz,20160211.fastq.gz')
	   	self.filenames.bind("<Button-1>", lambda event: self.remove_default_text(self.filenames))
	   	self.filenames.clicked =False
	   	self.filenames.pack(pady=(0,10))

	   	self.threshlabel=tk.Label(self, text="inclusion threshold")
	   	self.threshlabel.pack()
	   	self.thresh = tk.Entry(self, fg="gray")
	   	self.thresh.insert(tk.END, 'eg. 3')
	   	self.thresh.bind("<Button-1>", lambda event: self.remove_default_text(self.thresh))
	   	self.thresh.clicked =False
	   	self.thresh.pack(pady=(0,10))

	   	self.create_roi=tk.Button(self, text="Create ROI", command=self.new_ROI_window)
	   	self.create_roi.pack()

	   	self.number_of_ROIs_label=tk.Label(self, text="number of ROIs")
	   	self.number_of_ROIs_label.pack()
	   	self.number_of_ROIs= tk.IntVar(self)
	   	self.number_of_ROIs.set(1)
	   	self.number_of_ROIs_menu = tk.OptionMenu(self, self.number_of_ROIs, 1,2,3,4,5,6,7,8,9,10)
		self.number_of_ROIs_menu.pack(pady=(0,10))	   	


	   	self.geneslabel=tk.Label(self, text="genes, comma separated")
	   	self.geneslabel.pack()
	   	self.genes = tk.Entry(self, fg="gray")
	   	self.genes.insert(tk.END, 'eg. rpoB,mrcA,rpoZ')
	   	self.genes.bind("<Button-1>", lambda event: self.remove_default_text(self.genes))
	   	self.genes.clicked =False
	   	self.genes.pack(pady=(0,10))

	
	   	self.b = tk.Button(self,text = "Submit",command = self.save)
	   	self.b.pack()
		# Function called when the button
		# is pressed.

	def save(self): 
		with open("config","wb") as f:
			f.write("ZIPPED="+str(self.zipped.get())+"\n")
			f.write("FILENAMES="+self.filenames.get().replace(" ","")+"\n")
			f.write("GENES "+self.genes.get().replace(" ","")+"\n")
			f.write("number_of_ROIs "+ str(self.number_of_ROIs.get())+"\n")
			f.write("THRESHOLD_OF_IMPORTANCE "+self.thresh.get()+"\n")
			f.write("YO YO Yo!")
		self.master.destroy()

	def remove_default_text(self,entry):
		if entry.clicked==False:
			entry.delete(0,tk.END)
			entry.config(fg="black")
			entry.clicked=True

	def on_resize(self,event):
		pass

	def new_ROI_window(self):
		self.ROI=ROI(master=self)


class ROIData():
	def __init__(self, forward, barcode_length, reverse, target, phase_shifts):
		#all strings except max phase=int, phaseshifts=dict
		self.forward=forward
		self.reverse=reverse
		self.barcode_length=barcode_length
		self.target=target
		self.phase_shifts=phase_shifts
		self.max_phase=max(max(phase_shifts), max(phase_shifts.values()))

if __name__ == "__main__":
	MyApp().mainloop()