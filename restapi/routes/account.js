const express = require('express');
const router = express.Router();
const account  = require('../models/account_model');


router.post('/withdraw_action',
    function(request, response){
        account.withdrawAction(request.body, function(err, dbResult){
            if(err){
                response.json(err.errno);
             }else{
                 response.json(dbResult.affectedRows);
             }
        });
    });

router.post('/transfer_action',
    function(request, response){
        account.transferAction(request.body, function(err, dbResult){
            if(err){
                response.json(err.errno);
            }else{
                response.json(dbResult.affectedRows);
            }
        });
    });

router.get('/getBalance/:id',
    function(request, response){
        account.getBalance(request.params.id, function(err, dbResult){
            if(err){
                response.json(err.errno);
                console.log(err);
            }else if(!dbResult[0]){
               console.log("Account not found");
                response.json("Account not found");
            }else{
                response.json(dbResult[0].balance);
            }
        });
    });

module.exports = router;
