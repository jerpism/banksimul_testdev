const express = require('express');
const router = express.Router();
const cryptoaction = require('../models/cryptoaction_model');

router.get('/getRecent/:id',
    function(request, response){
        cryptoaction.getRecent(request.params.id, function(err,dbResult){
            if(err){
                response.json(err);
            }else{
                response.json(dbResult);
            }
        });
    });

module.exports=router;

