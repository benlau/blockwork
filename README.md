# blockwork
A Project in EOS Hackathon

docker run  --name eosio -d -p 8888:8888 -p 9876:9876 -v `pwd`:/work -v /tmp/eosio/data:/mnt/dev/data -v /tmp/eosio/config:/mnt/dev/config eosio/eos-dev  /bin/bash -c "nodeos -e -p eosio --plugin eosio::wallet_api_plugin --plugin eosio::wallet_plugin --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin -d /mnt/dev/data --config-dir /mnt/dev/config --http-server-address=0.0.0.0:8888 --access-control-allow-origin=* --contracts-console"

cleos wallet create
cleos wallet import 5JPRj64ng9N37bZGnrHMwxb8LGoyR8dsXxTFXCLzT21xCHdPYQn
cleos wallet import 5JgS8oAp4WFpiqex1VLAqwiQHgSUY3vtgJaiXJQr5d7QfpNj96P

cd /work/contracts/blockwork

eosiocpp -o blockwork.wast blockwork.cpp ; eosiocpp -g blockwork.abi blockwork.cpp ; sed -ie "s/i64i64i64/i64/" blockwork.abi 
cleos set contract blockwork /work/blockwork/contracts/blockwork -p blockwork



