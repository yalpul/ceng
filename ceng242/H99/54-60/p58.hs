-- generate all symmetric balanced trees
-- with given node number


data Tree a = Empty | Branch a (Tree a) (Tree a) deriving (Show, Eq)

p55 :: Int -> [Tree Char]
p55 0 = [Empty]
p55 n = let (q,r) = quotRem (n-1) 2
        in [ (Branch 'x' l r) | i <- [q..q+r],
                                l <- p55 i,
                                r <- p55 (n-i-1) ]
p56 :: Tree Char -> Bool
p56 t = symmetric t t where
        symmetric Empty Empty = True
        symmetric (Branch _ l1 r1) (Branch _ l2 r2) = symmetric l1 r2 && symmetric r1 l2
        symmetric _ _ = False

p58 :: Int -> [Tree Char]
p58 n = filter p56 (p55 n)
