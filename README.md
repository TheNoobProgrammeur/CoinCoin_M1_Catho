# Projet CoinCoin

CoinCoin est un mineur pour la cryptomonnaie coincoin (qui n'a aucune valeur 😊 )

# Definition d'une pièce CoiCoin : 

On appelle pièce CoinCoin un token T tel que:CoinHash(T) commence par une suite de N ‘c’ consécutifs, avec N > 0

# Valeur :

| Commence par N ‘c’ | Nom                     | Valeur        |Probabilité    |
|--------------------|-------------------------|---------------|---------------|
| 0..5               | Miette                  | 0             |P(xc) = 1/16^x |
| 6                  | Subcoin                 | 1/16 Coin     |P(6) = 1/16^6  |
| 7                  | Coin                    | 1 Coin        |P(7) = 1/16^7  |
| 8                  | Hexacoin                | 16 Coins      |P(8) = 1/16^8  |
| 9                  | Arkenstone              | 256 Coins     |P(9) = 1/16^9  |
| 10                 | Blackstar (rare)        | 16 Arkenstone |P(10) = 1/16^10|
| 11                 | Grand Cross (legendary) | 16 Blackstart |P(11) = 1/16^11|

# Lancement:

## Build :

```
$ make packages
$ make coin
```

## Run :

### Benchmark 

```
$ ./coinminer -z
```

### Minage 
```
$ ./coinminer -t [Votre trigramme] -m [nombre min de c]
```

# Correction des Coin Tokens
```
- Hexcoin (8) : mh}hzh}AR=p$LRU_JFsR8K%WuldUObWl-ABR-CC1.0-1587778567-0f0f0f --> cccccccc45c5396821c8326f61502f54664eeb90
- Arkenstone (9) : io~qrPtJ2`d^&&Jjwn+:[!Hp9v|9C`5S-ABR-CC1.0-1587848512-0f0f0f --> cccccccccbcd0252eab7fb664fd1b3afcf9cbac3
- Blackstar (10) : /G,Y 3r)m 6oq+ULS[M8>p|MbIFbqRZh-ABR-CC1.0-1587862905-0f0f0f --> cccccccccce8d4f2adbeefd901817d31e10e76fc
- Blackstar via rasberry (10) : %ryB\gi )VU=#iH?W.P|NQ;4-/#@kY7l-ABR-CC1.0-1589439269-0f0f0f --> cccccccccc0bd3ae4c43e9fd865dd288e72b0180
- Grand Cross (11) : Si$1}cnY{ht+>k[{mRJwAJ9dz"Xi6+uO-ABR-CC1.0-1589494242-0f0f0f --> ccccccccccceb3ea9111743f431dd6b3b38da7d6
```
