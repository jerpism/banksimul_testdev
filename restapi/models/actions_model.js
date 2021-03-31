const db = require('../database');

const actions = {

    getRecent: function(id, callback){
        return db.query('SELECT amount,convert(date, varchar(45)) as date,action_type FROM account_action JOIN account ON account.id_account = account_action.id_account where account.id_account = ? order by date DESC LIMIT 10',[id],callback);

    }
};


module.exports = actions;

