-- Knight's Tour

knights :: Int -> [[(Int,Int)]]
knights n = loop (n*n) [[(1,1)]]
        where loop 1 = map reverse . id
              loop i = loop (i-1) . concatMap nextMoves

              nextMoves already@(x:xs) = [next:already | next <- possible]
                where possible = filter (\x -> on_board x && (x `notElem` already)) $ jumps x
                      jumps (x,y)    = [(x+a, y+b) | (a,b) <- [(2,2), (2,1), (2,-1), (1,-2), (-1,-2), (-2,-1), (-2,1), (-1,2)]]
                      on_board (x,y) = (x >= 1) && (x <= n) && (y >= 1) && (y <= n)
