from smallBoard import SmallBoard

class BigBoard():
	
	def __init__(self):
		
		self.board = [[SmallBoard(), SmallBoard(), SmallBoard()], 
					  [SmallBoard(), SmallBoard(), SmallBoard()], 
					  [SmallBoard(), SmallBoard(), SmallBoard()]]


		self.opponentMap = {
			'X': 'O',
			'O': 'X'
		}

	def convertIndToBig(self, slots, smallBoardInd):

		for i in range(len(slots)):
			slots[i] = [3*smallBoardInd[0] + slots[i][0], 3*smallBoardInd[1] + slots[i][1]]
		return slots

	def getAllEmptySlots(self):

		slots = []
		for i in range(3):
			for j in range(3):
				slots = slots + self.convertIndToBig(self.board[i][j].getAllEmptySlots(), [i, j])
		return slots

	def getValidMoves(self, prevMove):

		if prevMove == None:
			return (self.getAllEmptySlots(), 'X')

		# Finding mapping to the small board
		smallBoardInd = [prevMove[0]%3, prevMove[1]%3]

		if self.board[smallBoardInd[0]][smallBoardInd[1]].getState()[0] != 'N':
			return (self.getAllEmptySlots(), 
				self.opponentMap[self.board[prevMove[0]//3][prevMove[1]//3].board[prevMove[0]%3][prevMove[1]%3]])
		else:
			return (self.convertIndToBig(self.board[smallBoardInd[0]][smallBoardInd[1]].getAllEmptySlots(), smallBoardInd),
				self.opponentMap[self.board[prevMove[0]//3][prevMove[1]//3].board[prevMove[0]%3][prevMove[1]%3]])

	def playMove(self, move, symbol):

		self.board[move[0]//3][move[1]//3].playMove([move[0]%3, move[1]%3], symbol)

	def getState(self):
			
		# Creating a small Board version for easier computation
		smallVer = SmallBoard()
		for i in range(3):
			for j in range(3):
				curState = self.board[i][j].getState()

				if curState[0] == 'W':
					smallVer.board[i][j] = curState[1]

		curState = smallVer.getState()
		if curState[0] == 'W':
			return 'W', curState[1]

		if len(self.getAllEmptySlots()) == 0:
			return 'D', '_'

		return 'N', '_'

