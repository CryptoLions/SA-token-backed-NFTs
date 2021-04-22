# SimpleAssets  token backed NFTs

## Build
```
./build.sh
```

## Deploy

```
ACC=simplebacked

./cleos.sh set account permission $ACC active --add-code -f
./cleos.sh set contract $ACC ./build/backtoken -p $ACC
```
