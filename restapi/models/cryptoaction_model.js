const db = require('../database');

const actions = {
    getRecent: function(id, callback){
        return db.query('SELECT amount,convert(date, varchar(45)) as date, action_type FROM cryptoaccount_action JOIN cryptoaccount ON cryptoaccount.id_cryptoaccount = cryptoaccount_action.id_cryptoaccount WHERE cryptoaccount.id_cryptoaccount = ? order by date DESC LIMIT 10',[id],callback);
    }
};

module.exports = actions;
