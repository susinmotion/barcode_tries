class ROIData():
	def __init__(self, gene, forward, reverse, target, rev_phases):
		#all strings except max phase=int, phaseshifts=dict
		self.gene=gene
		self.forward=forward
		self.reverse=reverse
		self.target=target
		self.rev_phases=rev_phases

