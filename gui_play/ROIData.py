class ROIData():
	def __init__(self, gene, forward, barcode, reverse, target, rev_phases):
		#all strings except max phase=int, phaseshifts=dict
		self.gene=gene
		self.forward=forward
		self.reverse=reverse
		self.barcode=barcode
		self.barcode_length=len(self.barcode)
		self.target=target
		self.rev_phases=rev_phases

