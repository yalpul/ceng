-- mark each node of a binary tree with
-- (x,y) coordinates 
-- x -> inorder place
-- y -> depth

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving Show

countN Empty = 0
countN (Branch _ l r) = 1 + countN l + countN r

p65 :: Tree a -> Tree (a,(Int,Int))
p65 t = p65' t 1 where
        p65' Empty _ = Empty
        p65' (Branch n l r) h = Branch (n,(countN l + 1,h)) 
                                       (p65' l (h+1)) 
                                       (p65' r (h+1))
