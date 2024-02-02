from bigBoard import BigBoard
from mcts import MCTS
from copy import *
from gui import *

board = BigBoard()
player = MCTS('O', compTime=1)

prevMove = None
turn = True
while not done:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			done = True
		elif event.type == pygame.K_q:
			done = True
		elif(turn):
			if event.type == pygame.MOUSEBUTTONDOWN:
				pos = pygame.mouse.get_pos()
				xcord = ((pos[0] - ((pos[0]//tot3by3)-1)*MARGIN) - 2*MARGIN) // (MARGIN+WIDTH)
				ycord = ((pos[1] - ((pos[1]//tot3by3)-1)*MARGIN) - 2*MARGIN)// (MARGIN+HEIGHT)
				move = [xcord,ycord]
				
				board.playMove(move, 'X')
				prevMove = move
				if xcord /8 <= 1 and ycord /8 <= 1:
					if grid[xcord][ycord] == 0:
						if allowedx == -1 and allowedy == -1: #move anywhere
							if redPlaying == True:
								grid[xcord][ycord] = 1
								redPlaying = False
								playcolour = BLUE
							else:
								grid[xcord][ycord] = 2
								redPlaying = True
								playcolour = RED
							winCalc([xcord,ycord],grid,TotalGrid)
							allowedx ,allowedy = NextBox([xcord,ycord],TotalGrid)
							ResizePlayBox(playrect,allowedx,allowedy)
						elif allowedx <= xcord <= allowedx+2 and allowedy <= ycord <= allowedy+2:
							if redPlaying == True:
								grid[xcord][ycord] = 1
								redPlaying = False
								playcolour = BLUE
							else:
								grid[xcord][ycord] = 2
								redPlaying = True
								playcolour = RED
							winCalc([xcord,ycord],grid,TotalGrid)
							allowedx ,allowedy = NextBox([xcord,ycord],TotalGrid)
							ResizePlayBox(playrect,allowedx,allowedy)
				turn ^=1
				
			
		# player turn
		elif(not turn):
			move = player.getMove(deepcopy(board), prevMove) 
			xcord,ycord = move[0],move[1]
			board.playMove(move, 'O')
			prevMove = move
			if xcord /8 <= 1 and ycord /8 <= 1:
				if grid[xcord][ycord] == 0:
					if allowedx == -1 and allowedy == -1: #move anywhere
						if redPlaying == True:
							grid[xcord][ycord] = 1
							redPlaying = False
							playcolour = BLUE
						else:
							grid[xcord][ycord] = 2
							redPlaying = True
							playcolour = RED
						winCalc([xcord,ycord],grid,TotalGrid)
						allowedx ,allowedy = NextBox([xcord,ycord],TotalGrid)
						ResizePlayBox(playrect,allowedx,allowedy)
					elif allowedx <= xcord <= allowedx+2 and allowedy <= ycord <= allowedy+2:
						if redPlaying == True:
							grid[xcord][ycord] = 1
							redPlaying = False
							playcolour = BLUE
						else:
							grid[xcord][ycord] = 2
							redPlaying = True
							playcolour = RED
						winCalc([xcord,ycord],grid,TotalGrid)
						allowedx ,allowedy = NextBox([xcord,ycord],TotalGrid)
						ResizePlayBox(playrect,allowedx,allowedy)
			turn^=1


	screen.fill(BLACK)
	extramarginx = 0
	extramarginy = 0
	for row in range(amtrow):
		if row%3 == 0:
			extramarginy = extramarginy +MARGIN
		for column in range(amtcol):
			color = WHITE
			if column%3 == 0:
				extramarginx = extramarginx + MARGIN
			if grid[column][row] == 1:
				color = RED
			if grid[column][row] == 2:
				color = BLUE
			pygame.draw.rect(screen,
							color,
							[((MARGIN + WIDTH) * column) + MARGIN + extramarginx,
							((MARGIN + HEIGHT) * row) + MARGIN+ extramarginy,
							WIDTH,
							HEIGHT])

			pygame.draw.rect(screen, playcolour, playrect,playwidth)
		extramarginx =0

	clock.tick(60)

	pygame.display.flip()

pygame.quit()