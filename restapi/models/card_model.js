const database=require('../database');

const card={

    getAccount: function(id, callback){
        return database.query('select account.id_account from account join card on account.id_account = card.id_account where id_card=?',[id],callback);
    },

    getPin: function(id, callback){
        return database.query('select pin from card where id_card=?',[id],callback);
    }

};


module.exports=card;
