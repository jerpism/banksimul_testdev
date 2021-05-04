const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/getAccount/:id',
    function(request, response){
        card.getAccount(request.params.id, function(err,dbResult){
            if(err){
                response.json(err.errno);
            }else if(!dbResult[0]){
                console.log("Account not found");
                response.json("Account not found");
            }else{
                console.log(dbResult);
                response.json(dbResult[0].id_account);
            }
        })
    }
);

router.get('/getCryptoAccount/:id',
    function(request, response){
        card.getCryptoAccount(request.params.id, function(err,dbResult){
            if(err){
                response.json(err.errno);
            }else if(!dbResult[0]){
                console.log("Account not found");
                response.json("Account not found");
            }else{
                console.log(dbResult);
                response.json(dbResult[0].id_cryptoaccount);
            }
        })
    }
);

router.put('/lock/:id',
    function(request, response){
        card.lock(request.params.id, function(err,dbResult){
            if(err){
                response.json(err.errno);
            }else if(!dbResult){
                console.log("Card not found");
                response.json("Card not found");
            }else{
                console.log(dbResult);
                response.json(dbResult.affectedRows);
            }
        })
    }
);
            


module.exports = router;


