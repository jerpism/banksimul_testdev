/*const express = require('express');
const router = express.Router();
const actions  = require('../models/actions_model');


router.post('/withdraw_action',
    function(request, response){
        actions.withdrawAction(request.body, function(err, dbResult){
            if(err){
                response.json(err);
             }else{
                 response.json(dbResult.affectedRows);
             }
        });
    });

router.post('/transfer_action',
    function(request, response){
        actions.transferAction(request.body, function(err, dbResult){
            if(err){
                response.json(err);
            }else{
                response.json(dbResult.affectedRows);
            }
        });
    });

module.exports = router;



*/
