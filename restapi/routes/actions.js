const express = require('express');
const router = express.Router();
const actions  = require('../models/actions_model');


router.get('/getRecent/:id?&:limit?&:limit_b',
    function(request, response){
    const limitToInt=parseInt(request.params.limit);
    const limitToInt_b=parseInt(request.params.limit_b);
        actions.getRecentLimitBetween(request.params.id, limitToInt, limitToInt_b, function(err, dbResult){
            if(err){
                response.json(err);
            }else{
                response.json(dbResult);
            }
        });
    });

router.get('/getRecent/:id?&:limit',
    function(request, response){
    const limitToInt=parseInt(request.params.limit);
        actions.getRecentLimit(request.params.id, limitToInt, function(err, dbResult){
            if(err){
                response.json(err);
            }else{
                response.json(dbResult);
            }
        });
    });

router.get('/getRecent/:id',
    function(request, response){
        actions.getRecent(request.params.id, function(err, dbResult){
            if(err){
                response.json(err);
            }else{
                response.json(dbResult);
            }
        });
    });

router.get('/getCount/:id',
    function(request, response){
        actions.getRecentCount(request.params.id, function(err, dbResult){
            if(err){
                response.json(err);
            }else{
                response.json(dbResult[0].lkm);
            }
        });
    });


module.exports = router;



