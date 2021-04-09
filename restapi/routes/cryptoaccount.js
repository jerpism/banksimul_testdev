const express = require('express');
const router = express.Router();
const cryptoaccount = require('../models/cryptoaccount_model');


router.get('/getBalance/:id',
    function(request, response){
        cryptoaccount.getBalance(request.params.id, function(err, dbResult){
            if(err){
                response.json(err);
            } else if(!dbResult[0]){
                console.log("Account not found");
                response.json("Account not found");
            }else{
                response.json(dbResult[0].balance);
            }
        
    });
});

router.post('/buy_crypto',
    function(request, response){
        cryptoaccount.buyCrypto(request.body, function(err, dbResult){
            if(err){
                response.json(err.errno);
            }else{
                response.json(dbResult.affectedRows);
            }
        });
    });

router.post('/sell_crypto',
    function(request, response){
        cryptoaccount.sellCrypto(request.body, function(err, dbResult){
            if(err){
                response.json(err.errno);
            }else{
                response.json(dbResult.affectedRows);
            }
        });
    });

module.exports = router;
