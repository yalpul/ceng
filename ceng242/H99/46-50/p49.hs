-- generate gray code
-- for n length bit inputs

p49 :: Int -> [String]
p49 0 = [""]
p49 n = let xs = p49 (n-1)
         in map ('0':) xs ++ map ('1':) (reverse xs)
