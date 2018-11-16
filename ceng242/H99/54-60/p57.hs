-- construct BST from a list

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving (Show, Eq, Ord)

p57 :: Ord a => [a] -> Tree a
p57 [] = Empty
p57 (x:xs) = let lesses = [ z | z <- xs, z < x ]
                 greats = [ z | z <- xs, z > x ]
             in Branch x (p57 lesses) (p57 greats)
