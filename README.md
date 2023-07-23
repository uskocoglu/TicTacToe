# TicTacToe

I used my locking algorithm in the function which the players select a location to mark in the game table. In each iteration the player locks the mutex and makes its move then unlocks the mutex. In main function, player x was created and joined then player o was created and joined so that player x always starts the game first. The usage of mutex makes it possible that the players are making their moves sequentially.
  
  (a) Acquire the lock.
  
  (b) Select a random cell on the board.
  
  (c) If it is not marked already, mark it with X or O. If marked, go to b.
  
  (d) Release the lock.
