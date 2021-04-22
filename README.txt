--- SA_tokens_back Project ---

 - How to Build -
   - cd to 'build' directory
   - run the command 'cmake ..'
   - run the command 'make'

 - After build -
   - The built smart contract is under the 'SA_tokens_back' directory in the 'build' directory
   - You can then do a 'set contract' action with 'cleos' and point in to the './build/SA_tokens_back' directory

 - Additions to CMake should be done to the CMakeLists.txt in the './src' directory and not in the top level CMakeLists.txt


## Deploy

```
ACC=simplebacked

./cleos.sh set account permission $ACC active --add-code -f
./cleos.sh set contract $ACC ./build/backtoken -p $ACC
```
