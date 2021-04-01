const db = require('../database');

const cryptoaccount = {
    getBalance: function(id, callback){
        return db.query(
            'SELECT balance FROM cryptoaccount WHERE id_cryptoaccount=?',[id],callback);
    }
};

module.exports = cryptoaccount;
