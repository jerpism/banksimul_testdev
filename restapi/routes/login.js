const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');

router.post('/', 
  function(request, response) {
    if(request.body.id && request.body.pin){
      const id = request.body.id;
      const pin = request.body.pin;

    /*  login.isLocked(id, function(dbError, dbResult){
          if(dbError){
              response.json(dbError);
          }
          if(dbResult.length > 0){
              if(dbResult[0].locked == 1){
                  console.log("Tili on lukittu");
                  response.send("locked");
                  response.end();
              }
          }
      }
      );*/
     
     login.checkPin(id, function(dbError, dbResult) {
         if(dbError){
             response.json(dbError);
          }else{
            if (dbResult.length > 0) {

            if(dbResult[0].locked == 1){
                response.send("locked");
            }else{
              bcrypt.compare(pin,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                    console.log("succes");
                    response.send(true);
                }else{
                    console.log("wrong pin");
                    response.send(false);
                }			
                  response.end();
              }
            
              );
            }
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
          
    else{
      console.log("id or pin missing");
      response.send(false);
    }
  }
);
  

module.exports=router;
