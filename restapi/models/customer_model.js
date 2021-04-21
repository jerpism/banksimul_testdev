const db = require('../database');

const customer = {
    getName: function(id, callback){
        return db.query('select fname, lname from customer where id_customer=?', [id],callback);
    }
};

module.exports = customer;
