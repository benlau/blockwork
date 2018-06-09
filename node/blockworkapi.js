Eos = require('eosjs')    
var Promise = require("bluebird");

const markcomplete = (eos, reviewer, jobId) => {

    return new Promise((fulfill, reject) => {
        eos.contract("blockwork").then(c => {
           c.markcomplete({
               reviewer: reviewer,
               jobId: jobId
           }, {
               authorization: ["blockwork"]               
           }).then(result => {
                fulfill(result);
           });
        });
    });    
}

const create = (eos, submitter, jobId, jobName, jobDescription, price) => {
    return new Promise((fulfill, reject) => {
        eos.contract("blockwork").then(c => {
           c.create({
               submitter: submitter,
               jobId: jobId,
               jobName: jobName, 
               jobDescription: jobDescription,
               price: price
           }, {
               authorization: ["blockwork"]               
           }).then(result => {
                fulfill(result);
           });
        });
    });
}

const queryjob = (eos, jobId) => {
    return new Promise( (fulfill, reject) => {
        eos.contract('blockwork').then(c => {
    
            eos.getTableRows({
                scope: "blockwork",
                code: "blockwork",
                table: "job",
                json: true,
                lower_bound: jobId,
                upper_bound: jobId+1,
                limit: 10
            }).then(result => {
                fulfill(result.rows[0]);
            }).catch(err => {
                reject(err);
            });
        });        
    });
}

module.exports = {
    create: create,
    markcomplete: markcomplete,
    queryjob: queryjob
}