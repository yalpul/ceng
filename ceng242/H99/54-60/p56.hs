-- determine if subtrees of a tree
-- are symmetric

data Tree a = Empty | Branch a (Tree a) (Tree a)

p56 :: Tree Char -> Bool
p56 t = symmetric t t where
        symmetric Empty Empty = True
        symmetric (Branch _ l1 r1) (Branch _ l2 r2) = symmetric l1 r2 && symmetric r1 l2
        symmetric _ _ = False
