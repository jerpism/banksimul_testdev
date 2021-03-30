const db = require('../database');

const actions = {

    withdrawAction: function(procedure_params, callback){
        return db.query(
            'CALL withdraw_money(?,?)',
            [procedure_params.id, procedure_params.amount],
            callback
        );
    },

    transferAction: function(procedure_params, callback){
        return db.query(
            'CALL transfer_money(?,?,?)',
            [procedure_params.id_sender, procedure_params.id_recipient, procedure_params.amount],
            callback
        );
    }
};

module.exports = actions;
