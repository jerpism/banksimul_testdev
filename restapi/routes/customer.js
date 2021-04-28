const express = require('express');
const router = express.Router();
const customer = require('../models/customer_model');

router.get('/getInfo/:id',
    function(request, response){
            customer.getInfo(request.params.id, function(err, dbResult){
                if(err){
                    response.json(err);
                }else{
                    response.json(dbResult[0]);
                }
            });
        });

module.exports = router;
        
            

