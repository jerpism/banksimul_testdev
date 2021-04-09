const db = require('../database');

const cryptoaccount = {
    getBalance: function(id, callback){
        return db.query(
            'SELECT balance FROM cryptoaccount WHERE id_cryptoaccount=?',[id],callback);
    },

    buyCrypto: function(procedure_params, callback){
        return db.query(
            'CALL buy_crypto(?,?,?)',
            [procedure_params.id_acc,procedure_params.id_crypto,procedure_params.amount],callback
        );
    },

    sellCrypto: function(procedure_params, callback){
        return db.query(
            'CALL sell_crypto(?,?,?)',
            [procedure_params.id_acc,procedure_params.id_crypto,procedure_params.amount],callback
        );
    }
};

module.exports = cryptoaccount;
