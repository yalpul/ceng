-- construct height balanced trees
-- with given node number n
import Data.List

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving (Show, Eq)

p59 :: a -> Int -> [Tree a]
p59 x n = trees !! n where 
        trees = [Empty] : [Branch x Empty Empty] : zipWith combine (tail trees) trees where
                combine t st = [ Branch x l r | (lt, rt) <- [(t,t), (t,st), (st,t)],
                                                l <- lt, r <- rt ]
p60 :: Char -> Int -> [Tree Char]
p60 _ 0 = [Empty]
p60 x n = concatMap filteredTrees [minH .. maxH] where
        filteredTrees = filter ( (n==) . countN ) . p59 x
        minNodes = 0 : 1 : zipWith (\x y -> x + y + 1) minNodes (tail minNodes)
        minH = ceiling $ logBase 2 $ fromIntegral (n+1)
        maxH = (fromJ $ findIndex (>n) minNodes) - 1 where
                fromJ (Just j) = j
        countN Empty = 0
        countN (Branch _ l r) = 1 + (countN l) + (countN r)
        
