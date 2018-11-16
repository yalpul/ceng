-- collect all nodes from a tree
-- at a specific level

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving Show

p62b :: Tree a -> Int -> [a]
p62b _ 0 = []
p62b Empty _ = []
p62b (Branch t l r) 1 = [t]
p62b (Branch t l r) n = p62b l (n-1) ++ p62b r (n-1)
