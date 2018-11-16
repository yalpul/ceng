-- 8 Queens Problem

queens :: Int -> [[Int]]
queens n = map reverse $ queens' n
        where queens' 0       = [[]]
              queens' k       = [q:qs | qs <- queens' (k-1), q <- [1..n], isSafe q qs]
              isSafe   try qs = not (try `elem` qs || sameDiag try qs)
              sameDiag try qs = any (\(colDist,q) -> abs (try - q) == colDist) $ zip [1..] qs

