-- O programa foi desenvolvido com o auxílio de diversas funções
--pré-definidas no "Prelude", como "filter".

main = do
    lx <- getLine
    ly <- getLine
    let x = read lx
    let y = read ly
    putStrLn $ show $ maximum $ differences $ primes x y

primes :: Integer -> Integer -> [Integer]
primes a b = filter (>= a) $ crivo [2..b]
    where
        crivo :: [Integer] -> [Integer]
        crivo [] = []
        crivo (x:xs) = x:(crivo $ filter ((/=0).(`mod` x)) xs)

differences :: (Num a) => [a] -> [a]
differences [] = [0]
differences [x] = [0]
differences (x:xs) = (head(xs) - x):(differences xs)
