-- collect the leaves of a given tree
-- to a list

data Tree a = Empty | Branch a (Tree a) (Tree a)

p61a :: Tree a -> [a]
p61a Empty = []
p61a (Branch b Empty Empty) = [b]
p61a (Branch _ l r) = p61a l ++ p61a r
