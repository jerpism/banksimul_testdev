const database=require('../database');

const card={

    getAccount: function(id, callback){
        return database.query('select account.id_account from account join card on account.id_account = card.id_account where id_card=?',[id],callback);
    },

    getCryptoAccount: function(id, callback){
        return database.query('select cryptoaccount.id_cryptoaccount from cryptoaccount join card on cryptoaccount.id_cryptoaccount = card.id_cryptoaccount where id_card=?',[id],callback);
    },

    lock: function(id, callback){
        return database.query('UPDATE card SET locked = 1 WHERE id_card=?',[id],callback);

    }

};


module.exports=card;
