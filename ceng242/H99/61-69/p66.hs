-- another placing nodes problem
type Pos = (Int,Int)
data Tree a = Empty | Branch a (Tree a) (Tree a) deriving Show

p66 :: Tree a -> Tree (a,Pos)
p66 t = t' where
        (l, t', r) = p66' x1 1 t
        x1 = maximum l + 1

        p66' :: Int -> Int -> Tree a -> ([Int], Tree (a, Pos), [Int])
        p66' _ _ Empty = ([], Empty, [])
        p66' x y (Branch a l r) = (ll', Branch (a,(x,y)) l' r', rr') where
                (ll, l', lr) = p66' (x-sep) (y+1) l
                (rl, r', rr) = p66' (x+sep) (y+1) r
                sep = maximum (0:zipWith (+) lr rl) `div` 2 + 1
                (ll',rr') = (0 : p66'' (map (+sep) ll) (map (subtract sep) rl),
                             0 : p66'' (map (+sep) rr) (map (subtract sep) lr)) where
                        p66'' :: [a] -> [a] -> [a]

                        p66'' [] ys = ys
                        p66'' xs [] = xs
                        p66'' (x:xs) (y:ys) = x : p66'' xs ys
