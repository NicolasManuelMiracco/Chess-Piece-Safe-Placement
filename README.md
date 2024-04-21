# Chess-Piece-Safe-Placement

One-line description: A C++ program to solve a modified chess problem by safely placing queens, knights, bishops, and pawns on an 8x8 board.

Summary: This C++ program is designed to solve a unique chess problem where the goal is to place five queens, one knight, one bishop, and one pawn on an 8x8 chessboard without any pieces threatening each other. The program uses a recursive backtracking algorithm to systematically try and place each piece on the board. It checks safety against all types of threats including direct attacks and special moves like the knight's L-shape, bishop's diagonal, and pawn's capture moves. Each type of piece has a specific safety function that checks for potential conflicts based on chess rules. If all pieces can be placed safely, the board configuration is printed. If not, the program outputs that no solution exists. This application illustrates complex problem-solving with multiple constraints in a classic game setting.
