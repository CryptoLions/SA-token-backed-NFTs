
# { SA_NFT = 0, SA_FT = 1, TOKEN = 2 };

#./cleos.sh.jungle3 push action simplebacked tokenprep '["bohdanbohdan", 100000000008709,[[["0,NONE",""],0],[["4,EOS","eosio.token"],2]]]' -p bohdanbohdan
#./cleos.sh.jungle3 push action simplebacked tokenprep '["bohdanbohdan", 100000000008709,[[["4,EOS","eosio.token"],2]]]'  -p bohdanbohdan

#./cleos.sh.jungle3 push action simplebacked delbtoken '[100000000008709]' -p simplebacked

#./cleos.sh.jungle3 push action eosio.token transfer '["bohdanbohdan", "simplebacked", "5.0000 EOS", "100000000008709"]' -p bohdanbohdan

#./cleos.sh.jungle3 push action simpleassets transfer '["bohdanbohdan", "simplebacked", [100000000008710], "100000000008709"]' -p bohdanbohdan
#./cleos.sh.jungle3 push action simpleassets transfer '["bohdanbohdan", "simplebacked", [100000000008711], "100000000008709"]' -p bohdanbohdan
#./cleos.sh.jungle3 push action simpleassets transfer '["bohdanbohdan", "simplebacked", [100000000008712], "100000000008709"]' -p bohdanbohdan



#./cleos.sh.jungle3 push action simplebacked tokenprep '["bohdanbohdan", 100000000008714,[[["0,NONE",""],0],[["4,EOS","eosio.token"],2]]'  -p bohdanbohdan
#./cleos.sh.jungle3 push action simpleassets transfer '["bohdanbohdan", "simplebacked", [100000000008713], "100000000008714"]' -p bohdanbohdan
