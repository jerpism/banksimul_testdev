const db = require('../database');

const actions = {

    getRecent: function(id, callback){
        return db.query('SELECT amount,convert(date, varchar(45)) as date,action_type FROM account_action JOIN account ON account.id_account = account_action.id_account where account.id_account = ? order by date DESC',[id],callback);

    },

    getRecentLimit: function(id, limit, callback){
        return db.query('SELECT amount,convert(date, varchar(45)) as date, action_type FROM account_action JOIN account ON account.id_account = account_action.id_account where account.id_account = ? order by date DESC LIMIT ?',[id,limit],callback);
    },

    getRecentLimitBetween: function(id, limit, limit_b, callback){
        return db.query('SELECT amount,convert(date, varchar(45)) as date, action_type FROM account_action JOIN account ON account.id_account = account_action.id_account where account.id_account = ? order by date DESC LIMIT ?,?',[id,limit,limit_b],callback);
    },

    getRecentCount: function(id, callback){
        return db.query('SELECT count(*) as lkm from account_action where id_account=?',[id], callback);
    }

};
module.exports = actions;

