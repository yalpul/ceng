-- generate balanced numbers
-- with max height n

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving (Show, Eq)

p59 :: a -> Int -> [Tree a]
p59 x n = trees !! n where 
        trees = [Empty] : [Branch x Empty Empty] : zipWith combine (tail trees) trees where
                combine t st = [ Branch x l r | (lt, rt) <- [(t,t), (t,st), (st,t)],
                                                l <- lt, r <- rt ]
