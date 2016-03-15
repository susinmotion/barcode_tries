# MyApp.py
import Tkinter as tk
from ROI import ROI
from shared import remove_default_text
import tkMessageBox
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
		self.filenames.bind("<Button-1>", lambda event: remove_default_text(self,self.filenames))
		self.filenames.clicked =False
		self.filenames.pack(pady=(0,10))

		self.threshlabel=tk.Label(self, text="inclusion threshold")
		self.threshlabel.pack()
		self.thresh = tk.IntVar(self)
		self.thresh.set(3)
		self.thresh_menu =tk.OptionMenu(self, self.thresh, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20)
		self.thresh_menu.pack(pady=(0,10))

		self.number_of_ROIs_label=tk.Label(self, text="number of ROIs")
		self.number_of_ROIs_label.pack()
		self.number_of_ROIs= tk.IntVar(self)
		self.number_of_ROIs.set(0)
		self.number_of_ROIs_menu = tk.OptionMenu(self, self.number_of_ROIs, 1,2,3,4,5,6,7,8,9,10)
		self.number_of_ROIs_menu.pack(pady=(0,10))	   

		self.barcode_label=tk.Label(self, text="barcode length")
		self.barcode_label.pack()
		self.barcode_length=tk.IntVar()
		self.barcode_menu=tk.OptionMenu(self, self.barcode_length,'4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25')
		self.barcode_menu.pack(pady=(0,10))	

		self.create_roi=tk.Button(self, text="Create ROIs", command=lambda: self.new_ROI_window(self.number_of_ROIs.get()))
		self.create_roi.pack()



		#self.geneslabel=tk.Label(self, text="genes, comma separated")
		#self.geneslabel.pack()
		#self.genes = tk.Entry(self, fg="gray")
		#self.genes.insert(tk.END, 'eg. rpoB,mrcA,rpoZ')
		#self.genes.bind("<Button-1>", lambda event: remove_default_text(self,self.genes))
		#self.genes.clicked =False
		#self.genes.pack(pady=(0,10))

	
		self.b = tk.Button(self,text = "Submit",command = self.save)
		self.b.pack()

		self.ROIs=[]

	def save(self): 
		incomplete=False
		filenames=self.filenames.get().replace(" ","")
		threshold=str(self.thresh.get())
		if filenames=="" or "eg." in filenames:
			incomplete=True
			tkMessageBox.showwarning("Error", "Please fill out all fields.")
		if len(self.ROIs)!=self.number_of_ROIs.get():
			incomplete=True
			warning="Not all ROIs specified. " +str(self.number_of_ROIs.get())+" required. You input:\n"+"\n".join([ROI.gene for ROI in self.ROIs])
			tkMessageBox.showwarning("Missing ROI",warning)

		if incomplete==False:
			warning="Zipped: "+str(self.zipped.get())+"\nFilenames: "+filenames+ "\n Threshold of Importance: "+str(threshold)+" \nROIs: "+", ".join([ROI.gene for ROI in self.ROIs])+"\n \nAre these the correct parameters? There is no turning back!"
			confirmation=tkMessageBox.askyesno("Slow Down", warning)
			if confirmation:
				self.write_config_file()
				self.master.destroy()

	def write_config_file(self):
		with open("config.cfg","wb") as f:
			f.write("ZIPPED="+str(self.zipped.get())+"\n")
			f.write("FILENAMES="+self.filenames.get().replace(" ","")+"\n")
			genes=[]
			forwards=[]
			reverses=[]
			targets=[]
			phase_maps=[]

			for ROI in self.ROIs:
				genes.append(ROI.gene)
				forwards.append(ROI.forward)
				reverses.append(ROI.reverse)
				targets.append(ROI.target)
				phase_map=""
				max_phase=0
				for i in range(len(ROI.rev_phases)):
					phase_map+=(str(i)+":"+str(ROI.rev_phases[i])+"|")
					if i>max_phase:
						max_phase=i
				phase_map=phase_map.strip("|")
				phase_maps.append(phase_map)

			print genes, forwards, reverses, targets, phase_maps
			f.write("GENES "+",".join(genes)+"\n")
			f.write("BARCODE_LENGTH "+str(self.barcode_length.get())+"\n")
			f.write("FORWARD_ALIGN_SEQ "+",".join(forwards)+"\n")
			f.write("REVERSE_ALIGN_SEQ "+",".join(reverses)+"\n")
			f.write("TARGET "+",".join(targets)+"\n")
			f.write("THRESHOLD_OF_IMPORTANCE "+str(self.thresh.get())+"\n")
			f.write("MAX_PHASE "+str(max_phase)+"\n")
			f.write("PHASE_SHIFTS_REV_TO_FORWARD "+",".join(phase_maps)+"\n")

	def on_resize(self,event):
		pass

	def new_ROI_window(self, number_of_ROIs):
		for i in range(number_of_ROIs):
			newROI=ROI(master=self)

	def appendROI(self,ROI):
		self.ROIs.append(ROI)



