main = do
    la <- getLine
    lb <- getLine
    let a = read la
    let b = read lb
    putStrLn $ show $ quantidade (\x -> elements_sum (divisores_proprios x) < x) [a..b]
    putStrLn $ show $ quantidade (\x -> elements_sum (divisores_proprios x) == x) [a..b]
    putStrLn $ show $ quantidade (\x -> elements_sum (divisores_proprios x) > x) [a..b]


divisores_proprios :: Integer -> [Integer]
divisores_proprios 1 = []
divisores_proprios a = filtro ((==0).(a `mod`)) [1..(a - 1)]
    where
        filtro:: (a -> Bool) -> [a] -> [a]
        filtro p [] = []
        filtro p (x:xs)
            | p x = x:(filtro p xs)
            | otherwise = filtro p xs


elements_sum :: (Num a) => [a] -> a
elements_sum [] = 0
elements_sum (x:xs) = x + elements_sum xs

quantidade :: (a -> Bool) -> [a] -> Integer
quantidade _ [] = 0
quantidade condition (x:xs)
    |condition x = 1 + quantidade condition xs
    |otherwise = quantidade condition xs




