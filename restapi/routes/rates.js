const express = require('express');
const router = express.Router();
const rates = require('../models/rates_model');

router.get('/getRate',
    function(request, response){
        rates.getRate(response, function(err,dbResult){
            if(err){
                response.json(err.errno);
            }else if(!dbResult[0]){
                console.log("Rate not found");
                response.json("Rate not found");
            }else{
                console.log(dbResult);
                response.json(dbResult[0].crypto);
            }
        })
    }
);

module.exports = router;
