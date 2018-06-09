Eos = require('eosjs')    

BlockWorkApi = require("./blockworkapi.js");

keyProvider = 'PW5JUqhN4KeWktNRDnxerzVFhuS8UBhcdyz4V6UnLUyQNA5CaHHRS'

var config = {
  chainId: null, // 32 byte (64 char) hex string
  keyProvider: ["5JPRj64ng9N37bZGnrHMwxb8LGoyR8dsXxTFXCLzT21xCHdPYQn", "5JgS8oAp4WFpiqex1VLAqwiQHgSUY3vtgJaiXJQr5d7QfpNj96P"], // WIF string or array of keys..
  httpEndpoint: 'http://127.0.0.1:8888',
  expireInSeconds: 60,
  broadcast: true,
  debug: false, // API and transactions
  sign: true       
}

eos = Eos(config);

//BlockWorkApi.markcomplete(eos, "reviewer", 110);

var id = 119;

BlockWorkApi.create(eos, "blockwork", id, "Test", "Hello" , "100").then(result => {
    console.log(result);    
    
    return BlockWorkApi.markcomplete(eos, "blockwork", id);
        
}).then(result => {
    console.log(result);    

    return BlockWorkApi.queryjob(eos, id);
    
}).then((result) => {
    console.log(result);
});