-- count leaves of a binary tree

data Tree a = Empty | Branch a (Tree a) (Tree a)

p61 :: Tree a -> Int
p61 Empty = 0
p61 (Branch _ Empty Empty) = 1
p61 (Branch _ l r) = p61 l + p61 r
