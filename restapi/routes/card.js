const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/getAccount/:id',
    function(request, response){
        card.getAccount(request.params.id, function(err,dbResult){
            if(err){
                response.json(err.errno);
            }else{
                console.log(dbResult);
                response.json(dbResult[0].id_account);
            }
        })
    }
);

router.get('/getPin/:id',
    function(request, response){
        card.getPin(request.params.id, function(err,dbResult){
            if(err){
                response.json(err.errno);
            }else{
                console.log(dbResult);
                response.json(dbResult[0]);
            }
        })
    }
);

module.exports = router;


