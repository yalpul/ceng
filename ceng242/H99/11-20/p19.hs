-- rotate a list n places to the left

p19 :: [a] -> Int -> [a]
p19 xs n = take l . drop (mod n l) $ (xs ++ xs) where
        l = length xs
