-- Atividade desenvolvida por:
-- Lucas Dúckur Nunes Andreolli     N°USP: 15471518


main = do
    l <- getLine
    let jogadas = map read $ words l :: [Integer]
    putStrLn $ escreve_jogadas jogadas 1 ++ "| " ++ (show $ analisa_jogadas jogadas 1)


-- Função que calcula o total de pontos de um jogo de boliche, representado por uma lista de inteiros.
analisa_jogadas :: [Integer] -> Integer -> Integer
analisa_jogadas [] _ = 0
analisa_jogadas (x:xs) frame
    | x == 10 && frame /= 10  = x + head(xs) + (head $ tail xs) + analisa_jogadas xs (frame + 1)  -- É strike e não á a último frame.
    | x == 10 && frame == 10  = x + head(xs) + (head $ tail xs)   -- É strike e é o último frame.
    | x + head(xs) == 10 && frame /= 10 = x + head(xs) + (head $ tail xs) + analisa_jogadas (tail xs) (frame + 1)   -- É spare e não é o último frame.
    | x + head(xs) == 10 && frame == 10 = x + head(xs) + (head $ tail xs)     -- É spare e é o último frame.
    | otherwise = x + head(xs) + analisa_jogadas (tail xs) (frame + 1)    -- Não é strike nem spare.


-- Função que retorna o placar de um jogo de boliche em formato de string.
escreve_jogadas :: [Integer] -> Integer -> [Char]
escreve_jogadas [] _ = []
escreve_jogadas (x:xs) frame
    | x == 10 && frame /= 10  = (printa_jogadas x (-1) True False False) ++ escreve_jogadas xs (frame + 1)  -- É strike e não á a último frame.                   
    | x == 10 && frame == 10  = (printa_jogadas x (-1) True False True) ++ escreve_jogadas xs 10    -- É strike e já está no último frame.
    | xs == [] = printa_jogadas x (-1) False False True -- Lançamento extra único após o spare no frame 10.
    | x + head(xs) == 10 && frame /= 10 = (printa_jogadas x (-1) False True False) ++ escreve_jogadas (tail xs) (frame + 1)  -- É spare e não é o último frame.
    | x + head(xs) == 10 && frame == 10 = (printa_jogadas x (-1) False True True) ++ escreve_jogadas (tail xs) 10   -- É spare e é o último frame.
    | frame == 10 = printa_jogadas x (head xs) False False True -- Dois lançamentos extras após o strike no frame 10. (não é strike nem spare).
    | otherwise = (printa_jogadas x (head xs) False False False) ++ escreve_jogadas (tail xs) (frame + 1) -- Não é strike, nem spare, nem lançamentos extras.


-- Função que retorna a pontuação de um único frame em formato de string.
printa_jogadas :: Integer -> Integer -> Bool -> Bool -> Bool -> [Char] 
printa_jogadas ponto1 ponto2 ehStrike ehSpare ehBonus
    | ehStrike && ehBonus = "X "    -- Strike nos lançamentos extras.
    | ehStrike && not ehBonus = "X _ | "    -- Strike nos lançamentos dos dez frames convencionais.
    | ehSpare && ehBonus = (show ponto1) ++ " / "   -- Spare nos lançamentos extras.
    | ehSpare && not ehBonus = (show ponto1) ++ " / | " -- Spare nos lançamentos dos dez frames convencionais.
    | ehBonus  && ponto2 == -1 = (show ponto1) ++ " "   -- Lançamento extra único após o spare no frame 10 (sem ser strike nem spare).
    | ehBonus && ponto2 /= -1 = (show ponto1) ++ " " ++ (show ponto2) ++ " " -- Dois lançamentos extras após o strike no frame 10 (sem ser strike, nem spare). 
    | otherwise = (show ponto1) ++ " " ++ (show ponto2) ++ " | "    -- Não é strike, nem spare, nem lançamentos extras.





