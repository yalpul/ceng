-- count the nodes of a n-ary tree

data Tree a = Node a [Tree a]

p70 :: Tree a -> Int
p70 (Node x []) = 1
p70 (Node x xs) = 1 + p70' xs where
        p70' [] = 0
        p70' (x:xs) = p70 x + p70' xs
