import Tkinter as tk

class ROI(tk.Toplevel):
	def __init__(self, master):
	    tk.Toplevel.__init__(self)
	    self.forwardLabel=tk.Label(self, text="fwd. align sequence")
	    self.forwardLabel.grid(row=1, column=0)
	    self.forward=tk.Entry(self, fg="gray")
	    self.forward.insert(tk.END, "eg. ACGTAA")
	    self.forward.bind("<Button-1>", lambda event: self.remove_default_text(self.forward))
	    self.forward.clicked=False
	    #self.forward.pack(pady=(0,10))

	    self.barcodelabel=tk.Label(self, text="sample barcode (for length)")
	    self.barcodelabel.grid(row=1, column=1)
	    self.barcode=tk.Entry(self, fg="gray")
	    self.barcode.insert(tk.END, "eg. NNNNNN (length=5)")
	    self.barcode.bind("<Button-1>", lambda event: self.remove_default_text(self.barcode))
	    self.barcode.clicked=False
	    #self.barcode.pack(pady=(0,10))

	    self.targetlabel=tk.Label(self, text="target sequence")
	    self.targetlabel.grid(row=1, column=2)
	    self.target=tk.Entry(self, fg="gray")
	    self.target.insert(tk.END, "eg. ACGGGGTATTACCCCTAGTATA")
	    self.target.bind("<Button-1>", lambda event: self.remove_default_text(self.target))
	    self.target.clicked=False
	    self.target.grid(row=0, column=2, sticky=(tk.E, tk.W))

	    self.reverselabel=tk.Label(self, text="rev. align sequence")
	    self.reverselabel.grid(row=1, column=3)
	    self.reverse=tk.Entry(self, fg="gray")
	    self.reverse.insert(tk.END, "eg. CAGATTA")
	    self.reverse.bind("<Button-1>", lambda event: self.remove_default_text(self.reverse))
	    self.reverse.clicked=False
	    self.reverse.grid(row=0, column=3, sticky=(tk.E, tk.W))

	    self.forward.grid(row=0, column=0, sticky=(tk.E, tk.W))
	    self.barcode.grid(row=0, column=1, sticky=(tk.E, tk.W))

	    #self.saveROI()
	    self.b = tk.Button(self,text = "Save ROI",command = self.saveROI)
	    self.b.grid(row=2, column=0)




	def saveROI(self):
		print "HII"
		#window.destroy()
