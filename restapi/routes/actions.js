const express = require('express');
const router = express.Router();
const actions  = require('../models/actions_model');

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

module.exports = router;



