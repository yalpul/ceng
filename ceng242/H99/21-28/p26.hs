-- combinations from a list


p26 :: Int -> [a] -> [[a]]

p26 0 _ = [[]]
p26 n xs = [xs !! i : tls | i <- [0..length xs - 1],
                            tls <- p26 (n-1) (drop (i+1) xs)]
