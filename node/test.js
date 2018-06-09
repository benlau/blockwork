Eos = require('eosjs')    
    
keyProvider = ''

// If you're loading a wasm file, you do not need binaryen. If you're loading
// a "wast" file you can include and configure the binaryen compiler:
//
// $ npm install binaryen@37.0.0
// binaryen = require('binaryen')
// eos = Eos({keyProvider, binaryen})

eos = Eos({keyProvider})

var id = 111;

// Error reading contract; https://github.com/EOSIO/eos/issues/3159
eos.contract('blockwork').then(c => {
    
    eos.getTableRows({
        scope: "blockwork",
        code: "blockwork",
        table: "job",
        json: true,
        lower_bound: id,
        upper_bound: id+1,
        limit: 10        
    }).then(result => {
       console.log(result); 
    }).catch(err => {
        console.log("error");
        reject(err)
    });
})
