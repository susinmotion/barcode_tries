import Tkinter as tk
import tkMessageBox
from shared import remove_default_text
from ROIData import ROIData

class ROI(tk.Toplevel):
	def __init__(self, master):
	    tk.Toplevel.__init__(self, master)
	    self.geneLabel=tk.Label(self, text="gene")
	    self.geneLabel.grid(row=0, column=0)
	    self.gene=tk.Entry(self, fg="gray")
	    self.gene.insert(tk.END, "eg. rpoB")
	    self.gene.bind("<Button-1>", lambda event: remove_default_text(self,self.gene))
	    self.gene.clicked=False
	    self.gene.grid(row=0,column=1)

	    self.forwardLabel=tk.Label(self, text="fwd. align sequence")
	    self.forwardLabel.grid(row=3, column=0)
	    self.forward=tk.Entry(self, fg="gray")
	    self.forward.insert(tk.END, "eg. ACGTAA")
	    self.forward.bind("<Button-1>", lambda event: remove_default_text(self,self.forward))
	    self.forward.clicked=False
	    #self.forward.pack(pady=(0,10))

	    self.barcodelabel=tk.Label(self, text="Barcode")
	    self.barcodelabel.grid(row=2, column=1)
	    #self.barcode.pack(pady=(0,10))

	    self.targetlabel=tk.Label(self, text="target sequence")
	    self.targetlabel.grid(row=3, column=2)
	    self.target=tk.Entry(self, fg="gray")
	    self.target.insert(tk.END, "eg. ACGGGGTATTACCCCTAGTATA")
	    self.target.bind("<Button-1>", lambda event: remove_default_text(self,self.target))
	    self.target.clicked=False


	    self.reverselabel=tk.Label(self, text="rev. align sequence")
	    self.reverselabel.grid(row=3, column=3)
	    self.reverse=tk.Entry(self, fg="gray")
	    self.reverse.insert(tk.END, "eg. CAGATTA")
	    self.reverse.bind("<Button-1>", lambda event: remove_default_text(self,self.reverse))
	    self.reverse.clicked=False

	    self.target.grid(row=2, column=2, sticky=(tk.E, tk.W))
	    self.reverse.grid(row=2, column=3, sticky=(tk.E, tk.W))
	    self.forward.grid(row=2, column=0, sticky=(tk.E, tk.W))
	    #self.barcode.grid(row=2, column=1, sticky=(tk.E, tk.W))

	    self.maxphase_label=tk.Label(self, text="max phase")
	    self.maxphase_label.grid(row=4, column=1)
	    self.maxphase=tk.StringVar()
	    self.maxphase.set("-")
	    self.maxphase_menu=tk.OptionMenu(self, self.maxphase,"0",'1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20', command=self.show_phase_boxes)
	    self.maxphase_menu.grid(row=4, column=2)

	    self.rev_phase_objects=[]

	    self.maxRow=4
	    self.b = tk.Button(self,text = "Save ROI",command = self.saveROI)
	    self.b.grid(row=6, column=0)

	def getMaxRow(self):
		return self.maxRow

	def show_phase_boxes(self,maxphase):
		row=5
		self.fwd_phase_label=tk.Label(self, text="fwd. phase")
		self.fwd_phase_label.grid(row=row, column=1)
		self.rev_phase_label=tk.Label(self, text="rev. phase")
		self.rev_phase_label.grid(row=row, column=2)

		for item in self.rev_phase_objects:
			item.destroy()

		self.rev_phase_objects=[]
		self.data=None

		for i in range(int(maxphase)+1):
			row+=1
			self.temp_ph=tk.Entry(self, fg="black", width=5, justify=tk.LEFT)
			self.rev_phase_objects.append(self.temp_ph )

			self.ph_lab=tk.Label(self, text=(str(i)+"  <->"), anchor=tk.E)
			self.ph_lab.grid(row=row, column=1)

			self.rev_phase_objects[i].grid(row=row, column=2)
		self.maxRow=row+1


	def set_data(self):

		rev_phases=[int(item.get()) for item in self.rev_phase_objects]
		return ROIData(gene=self.gene.get(),forward=self.forward.get(), reverse=self.reverse.get(), target=self.target.get(), rev_phases=rev_phases) 

	def saveROI(self):                                                                    
		incomplete=False
		try:
			self.data=self.set_data()
			values=self.data.__dict__.values()
		except ValueError,AttributeError:
			self.show_incomplete()
			return

		for value in values:
			if type(value)==str:
				if value=="" or ("eg." in value):
					self.show_incomplete()
					return
			elif type(value)==list:
				if len(value)==0:
					self.show_incomplete()
					return
				for number in value:
					if number=="":
						self.show_incomplete()
						return

			elif type(value)==int:
				if value=="":
					self.show_incomplete()
					return

		else:
			confirmation=tkMessageBox.askyesno("Slow Down","Did you double check your parameters? There is no turning back!")
			print confirmation
			if confirmation:
				self.master.appendROI(self.data)
				self.destroy()
		#window.destroy()

	def show_incomplete(self):
		master=self
		tkMessageBox.showwarning("Error","Please fill out all fields")

